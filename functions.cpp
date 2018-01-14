#include"allhead.h"
long val;//用来生成员工工号
long va;
int z=0;
PNODE pHead;//头指针
PNODE pTail;//尾指针
PNODE pHead1;//头指针
PNODE pTail1;//尾指针
void display()//窗口显示函数，输出菜单
{
	printf("		员工管理系统\n");
	printf("	----------------------------\n");
	printf("	       0-退出\n");
	printf("	       1-增加员工信息\n");
	printf("	       2-修改员工信息\n");
	printf("	       3-删除员工信息\n");
	printf("	       4-查找员工信息\n");
	printf("	       5-显示员工信息\n");
	printf("	       6-显示被删信息\n");
	printf("	       7-擦除屏幕信息\n");
	printf("	       8-保存员工信息\n");
	printf("	----------------------------\n");
	printf("		请选择（0～8）:");
}
void ex()
{
	getchar();//choose函数里面获取的数字a的回车会产生影响
	char ch;
	printf("退出前请确认信息是否已保存!\n");
	printf("是否退出(y/n):");
	ch=getchar();
	getchar();
	if(ch=='y'||ch=='Y')
	{
		printf("退出成功!\n\n");	
		exit(-1);
	}
}
void choose()//选择函数，选择菜单
{
	display();//输出菜单
	int a,b=1;
	scanf("%d",&a);
	switch(a)//菜单选择
	{
	case 0:ex();break;
	case 1:addInfo();break;
	case 2:editInfo();break;
	case 3:delInfo();break;
	case 4:find();break;
	case 5:showInfo();break;
	case 6:showdeleInfo();break;
	case 7:system("cls");break;
	case 8:saveInfo();break;
	default:printf("无效输入!\n\n");
	}
	//choose();//递归调用，用来重复菜单,由于递归占用内存太大，所以改用循环
}
void read()//读取文件中已经存在的信息
{
	FILE * fp;
	fp = fopen("data.txt","r");//打开文件，文件不存在返回空指针
	pHead = (PNODE)malloc(sizeof(NODE));
	pTail = pHead;
	pHead->pLast=NULL;
	pTail->pNext=NULL;//创建链表
	if(fp==NULL)//判断文件是否存在
	{
		val=1;
		return;
	}
	while(!feof(fp))
	{
		PNODE pNew = (PNODE)malloc(sizeof(NODE));
		fscanf(fp,"%ld%s%s%s",&(pNew->number),pNew->name,pNew->sex,pNew->tel);//读取文件中对应内容存入对应数组；
		val=pNew->number+1;//val作为工号，新增的工人工号只能排在老工人之后
		//printf("%ld ",val);本句调试时候检测工号是否生成正确
		pTail->pNext = pNew;//指向新的节点
		pNew->pLast=pTail;
		pNew->pNext = NULL;
		pTail = pNew;//尾指针指到尾节点
	}
	fclose(fp);//关闭文件
}
void readdele()//读取文件中已经存在的信息
{
	FILE * fp;
	fp = fopen("deledata.txt","r");//打开文件，文件不存在返回空指针
	pHead1 = (PNODE)malloc(sizeof(NODE));
	pTail1 = pHead1;
	pTail1->pNext=NULL;//创建链表
	if(fp==NULL)//判断文件是否存在
	{
		return;
	}
	while(!feof(fp))
	{
		PNODE pNew = (PNODE)malloc(sizeof(NODE));
		fscanf(fp,"%ld%s%s%s",&(pNew->number),pNew->name,pNew->sex,pNew->tel);//读取文件中对应内容存入对应数组；
		
		if(val<pNew->number)
			val=pNew->number+1;//用来判断下一个工号
		pTail1->pNext = pNew;//指向新的节点
		pNew->pNext = NULL;
		pTail1 = pNew;//尾指针指到尾节点
	}
	fclose(fp);//关闭文件
}
void editInfo()
{
	int n;
	long num;
	PNODE p = pHead->pNext;//利用p指针来遍历链表找出相应员工
	if(p==NULL)//判断链表里面是否有员工信息
	{
		printf("员工信息为空，请录入后修改!\n");
		return;//员工信息为空无法修改，结束修改函数
	}
	printf("请输入需要修改信息的员工工号：");
	scanf("%ld",&num);//遍历找出需要修改的人人员信息
	while (NULL != p)
	{
		if(num==p->number)
		{
			break;//找到要修改的员工信息退出循环
		}
		p = p->pNext;
	}
	printf("工号：%05ld\n",p->number);
	printf("姓名：");
	puts(p->name);
	printf("姓别：");
	puts(p->sex);
	printf("电话：");
	puts(p->tel);
	printf("\n\n");
	printf("请选择修改项：");
	printf("1-名字 2-性别 3-电话 4-全部: ");
	scanf("%d",&n);
	getchar();//避免不必要的回车对下面的影响
	switch(n)
	{
	case 1:printf("请输入新姓名：");gets(p->name);break;
	case 2:
		if(strcmp(p->sex,"男")==0)
			strcpy(p->sex,"女");
		else
			strcpy(p->sex,"男");
		break;
	case 3:printf("请输入新号码：");gets(p->tel);
		if(judge(p->tel))
		{
			printf("修改信息失败!\n\n");
			return;
		}
		break;
	case 4:
		{
			printf("请输入新姓名：");gets(p->name);
			if(strcmp(p->sex,"男")==0)
				strcpy(p->sex,"女");
			else
				strcpy(p->sex,"男");
			printf("请输入新号码：");gets(p->tel);
			if(judge(p->tel))
			{
				printf("修改信息失败!\n\n");
				return;
			}
			break;
		}
	default:printf("选项无效!\n\n");return;
	}
	printf("修改成功!\n\n");
	
}
void addInfo()//增加新员工信息函数
{
	int n;//用来选择员工性别
	PNODE pNew = (PNODE)malloc(sizeof(NODE));//创建新节点，接在链表末尾
	pNew->number=val;//给员工工号
	printf("工号：%05ld\n",pNew->number);
	printf("请输入员工姓名：");
	scanf("%s",pNew->name);
	getchar();
	printf("请选择员工性别：1-男 2-女: ");	
	scanf("%d",&n);
	switch(n)
	{
	case 1:strcpy(pNew->sex,"男");break;
	case 2:strcpy(pNew->sex,"女");break;
	}
	getchar();
	printf("请输入员工电话：");
	gets(pNew->tel);

	if(judge(pNew->tel))
	{
		printf("添加信息失败!\n");
		return;
	}
	//getchar();加入这行代码会引起下一次主菜单输入错误
	printf("录入成功!\n\n");
	val++;//自加作为下一个员工工号
	pTail->pNext = pNew;//移动尾指针
	pNew->pLast = pTail;
	pNew->pNext = NULL;
	pTail = pNew;

}
void showInfo1()//遍历输出链表
{
	PNODE p = pHead->pNext;
	if(p==NULL)
	{
		printf("您还未录入信息，无法显示，请先录入!\n\n");//如果文件中没有信息，则员工信息为空，无法输出，
		return;//结束函数
	}
	while (NULL != p)//遍历链表
	{
		printf("工号：%05ld\n",p->number);
		printf("姓名：");
		puts(p->name);
		printf("姓别：");
		puts(p->sex);
		printf("电话：");
		puts(p->tel);
		printf("\n\n");
		p = p->pNext;
	}
	printf("\n");
}
void showInfo2()//遍历输出链表
{
	PNODE p = pTail;
	if(p->pLast==NULL)
	{
		printf("您还未录入信息，无法显示，请先录入!\n\n");//如果文件中没有信息，则员工信息为空，无法输出，
		return;//结束函数
	}
	while (NULL != p->pLast)//遍历链表
	{
		printf("工号：%05ld\n",p->number);
		printf("姓名：");
		puts(p->name);
		printf("姓别：");
		puts(p->sex);
		printf("电话：");
		puts(p->tel);
		printf("\n\n");
		p = p->pLast;
	}
	printf("\n");
}
void showInfo()
{
	int n;
	printf("1-正序输出 2-倒序输出：");
	scanf("%d",&n);
	switch(n)
	{
	case 1:showInfo1();break;
	case 2:showInfo2();break;
	default:printf("输入无效!\n\n");break;
	}

}
void showdeleInfo()//遍历输出链表
{
	PNODE p = pHead1->pNext;
	if(p==NULL)
	{
		printf("您没有删除记录!\n");//如果文件中没有信息，则员工信息为空，无法输出，
		return;//结束函数
	}
	while (NULL != p)//遍历链表
	{
		printf("工号：%05ld\n",p->number);
		printf("姓名：");
		puts(p->name);
		printf("姓别：");
		puts(p->sex);
		printf("电话：");
		puts(p->tel);
		printf("\n\n");
		p = p->pNext;
	}
	printf("\n");
}
void delInfo()
{
	int n;
	PNODE p = pHead;
	if(p->pNext==NULL)//本次判断是为了排除员工信息为空的可能
	{
		printf("未检索到该员工，删除失败!\n\n");
		return;
	}
	printf("1-输入工号删除 2-输入姓名删除: ");
	scanf("%d",&n);
	switch(n)
	{
	case 1:Numdel(p);break;//工号删除函数
	case 2:Namedel(p);break;//姓名删除函数
	default:printf("无效选择!\n\n");return;
	}
}
void saveInfo()
{
	PNODE p = pHead->pNext;
	PNODE q = pHead1->pNext;
	if(p==NULL&&q==NULL)//检测是否有员工信息
	{
		printf("未检索到员工信息，请添加后再保存!\n\n");
		return;
	}
	FILE * fp;
	if(p!=NULL)
	{
		fp=fopen("data.txt","w");//以写的形式打开文件
		while (NULL != p)//遍历存入文件
		{
			fprintf(fp,"%05ld\t",p->number);
			fprintf(fp,"%s\t",p->name);
			fprintf(fp,"%s\t",p->sex);
			fprintf(fp,"%s",p->tel);
			p = p->pNext;
			if(p!=NULL)//判断是否是最后一组数据，最后一组数据的最后不能换行，要不文件中就会多一行，再次读文件时候就会多读一行无用数据
				fprintf(fp,"\n");
		}
		fclose(fp);
	}
	else
		remove("data.txt");//防止员工信息被删除完了以后，留下空文件，读取出来一行乱码，所以将空文件删除
	if(q!=NULL)
	{
		fp=fopen("deledata.txt","w");//以写的形式打开文件
		while (NULL != q)//遍历存入文件
		{
			fprintf(fp,"%05ld\t",q->number);
			fprintf(fp,"%s\t",q->name);
			fprintf(fp,"%s\t",q->sex);
			fprintf(fp,"%s",q->tel);
			q = q->pNext;
			if(q!=NULL)//判断是否是最后一组数据，最后一组数据的最后不能换行，要不文件中就会多一行，再次读文件时候就会多读一行无用数据
				fprintf(fp,"\n");
		}
		fclose(fp);
	}
	
	printf("保存成功!\n\n");

}
void Namedel(PNODE p)
{
	PNODE q;
	q = p->pNext;
	char b[100];
	printf("请输入需要删除的员工姓名：");
	scanf("%s", b);
	//getchar();
	while (NULL != q)
	{
		if (strcmp(q->name, b) == 0)//对比输入的姓名，输出对应的员工信息，防止删错
		{
			z++;
			printf("工号：%05ld\n", q->number);
			printf("姓名：");
			puts(q->name);
			printf("姓别：");
			puts(q->sex);
			printf("电话：");
			puts(q->tel);
			printf("\n\n");
	
		}
		q = q->pNext;
	}
	if(q==NULL&&z==0)//未找到对应员工信息，说明该员工不存在输入错误，给用户反馈
		{
			printf("未检索到该员工，删除失败!\n\n");
			return;
		}
	else
	{
		printf("共找到%d位叫%s的员工,",z,b);//防止出现同名同姓员工
		Numdel(p,b);
	}
}
void Numdel(PNODE p)
{
	PNODE pNew = (PNODE)malloc(sizeof(NODE));//创建新节点，接在链表末尾
	char ch;
	long num;
	printf("请输入需要删除的员工号：");
	scanf("%ld", &num);
	getchar();
	while (NULL != p)
	{
		if (num == p->number)//对比输入的工号，输出对应的员工信息，防止删错
		{
			printf("工号：%05ld\n", p->number);
			printf("姓名：");
			puts(p->name);
			printf("姓别：");
			puts(p->sex);
			printf("电话：");
			puts(p->tel);
			printf("\n\n");
			printf("是否删除(y/n):");
			ch = getchar();

			if (ch == 'y' || ch == 'Y')//再次确定是否删除信息
			{
				pNew = p->pNext;//将要删除的员工信息存入链表
				pTail1->pNext = pNew;//移动尾指针
				p->pNext = p->pNext->pNext;//打断链表，指向下一个节点
				pNew->pNext = NULL;
				pTail1 = pNew;
				printf("删除成功!\n");
			}
			else
			{
				printf("取消删除成功!\n");
			}
			return;//取消删除结束函数或者删除完结束函数
		}
		p = p->pNext;
	}
	if (p == NULL)//未找到对应员工信息，说明工号输入错误，给用户反馈
	{
		printf("未检索到该员工，删除失败!\n\n");
		return;
	}

}
void Numdel(PNODE p,char a[])
{
	PNODE pNew = (PNODE)malloc(sizeof(NODE));//创建新节点，接在链表末尾
	char ch;
	long num;
	printf("请输入需要删除的员工号：");
	scanf("%ld", &num);
	getchar();
	while (NULL != p)
	{
		if (num == p->number&&strcmp(p->name,a)==0)//对比输入的工号，输出对应的员工信息，防止删错
		{
			printf("工号：%05ld\n", p->number);
			printf("姓名：");
			puts(p->name);
			printf("姓别：");
			puts(p->sex);
			printf("电话：");
			puts(p->tel);
			printf("\n\n");
			printf("是否删除(y/n):");
			ch = getchar();

			if (ch == 'y' || ch == 'Y')//再次确定是否删除信息
			{
				pNew = p->pNext;//将要删除的员工信息存入链表
				pTail1->pNext = pNew;//移动尾指针
				p->pNext = p->pNext->pNext;//打断链表，指向下一个节点
				pNew->pNext = NULL;
				pTail1 = pNew;
				printf("删除成功!\n");
			}
			else
			{
				printf("取消删除成功!\n");
			}//取消删除结束函数或者删除完结束函数
			return;
		}
		p = p->pNext;
	}
	if (p == NULL)//未找到对应员工信息，说明工号输入错误，给用户反馈
	{
		printf("工号与员工姓名所在工号不同，删除失败!\n\n");
		return;
	}

}
void find1()
{
	long num;
	printf("请输入工号：");
	scanf("%ld",&num);
	PNODE p=pHead;
	while(p!=NULL)
	{
		if (num == p->number)//对比输入的工号，输出对应的员工信息
		{
			printf("工号：%05ld\n", p->number);
			printf("姓名：");
			puts(p->name);
			printf("姓别：");
			puts(p->sex);
			printf("电话：");
			puts(p->tel);
			printf("\n\n");
			return;
		}
		p=p->pNext;
	}
	printf("未找到工号为%ld的员工!\n\n",num);

}
void find2()
{
	char a[100];
	printf("请输入姓名：");
	getchar();//避免执行switch语句时候输入的数字对下面产生影响
	gets(a);
	int t=0;
	PNODE p=pHead;
	while(p!=NULL)
	{
		if(strcmp(a,p->name)==0)
		{
			t++;
			printf("工号：%05ld\n", p->number);
			printf("姓名：");
			puts(p->name);
			printf("姓别：");
			puts(p->sex);
			printf("电话：");
			puts(p->tel);
			printf("\n\n");
		}
		
		p=p->pNext;
		
	}
	if(t==0)
		printf("未检测到该员工!\n\n");
	else
		printf("共找到%d个叫%s的员工!\n\n",t,a);
	
}
void find()//查找函数，可工号或姓名查找
{
	int n;
	printf("请选择搜索方式：1-工号 2-姓名：");
	scanf("%d",&n);
	switch(n)
	{
	case 1:find1();break;
	case 2:find2();break;
	default:printf("无效输入!\n\n");return;
	}
}
int judge(char tel[])//用来检测手机号输入是否合法
{
	int i=0;
	int j=0;
	while(tel[i]!='\0')
	{
		if(tel[i]<'0'||tel[i]>'9')
		{
			printf("输入不合法!");
			j++;
			break;
		}
		i++;
	}
	return j;//不合法返回1合法返回0
}