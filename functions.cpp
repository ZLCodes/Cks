#include"allhead.h"
long val;//��������Ա������
long va;
int z=0;
PNODE pHead;//ͷָ��
PNODE pTail;//βָ��
PNODE pHead1;//ͷָ��
PNODE pTail1;//βָ��
void display()//������ʾ����������˵�
{
	printf("		Ա������ϵͳ\n");
	printf("	----------------------------\n");
	printf("	       0-�˳�\n");
	printf("	       1-����Ա����Ϣ\n");
	printf("	       2-�޸�Ա����Ϣ\n");
	printf("	       3-ɾ��Ա����Ϣ\n");
	printf("	       4-����Ա����Ϣ\n");
	printf("	       5-��ʾԱ����Ϣ\n");
	printf("	       6-��ʾ��ɾ��Ϣ\n");
	printf("	       7-������Ļ��Ϣ\n");
	printf("	       8-����Ա����Ϣ\n");
	printf("	----------------------------\n");
	printf("		��ѡ��0��8��:");
}
void ex()
{
	getchar();//choose���������ȡ������a�Ļس������Ӱ��
	char ch;
	printf("�˳�ǰ��ȷ����Ϣ�Ƿ��ѱ���!\n");
	printf("�Ƿ��˳�(y/n):");
	ch=getchar();
	getchar();
	if(ch=='y'||ch=='Y')
	{
		printf("�˳��ɹ�!\n\n");	
		exit(-1);
	}
}
void choose()//ѡ������ѡ��˵�
{
	display();//����˵�
	int a,b=1;
	scanf("%d",&a);
	switch(a)//�˵�ѡ��
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
	default:printf("��Ч����!\n\n");
	}
	//choose();//�ݹ���ã������ظ��˵�,���ڵݹ�ռ���ڴ�̫�����Ը���ѭ��
}
void read()//��ȡ�ļ����Ѿ����ڵ���Ϣ
{
	FILE * fp;
	fp = fopen("data.txt","r");//���ļ����ļ������ڷ��ؿ�ָ��
	pHead = (PNODE)malloc(sizeof(NODE));
	pTail = pHead;
	pHead->pLast=NULL;
	pTail->pNext=NULL;//��������
	if(fp==NULL)//�ж��ļ��Ƿ����
	{
		val=1;
		return;
	}
	while(!feof(fp))
	{
		PNODE pNew = (PNODE)malloc(sizeof(NODE));
		fscanf(fp,"%ld%s%s%s",&(pNew->number),pNew->name,pNew->sex,pNew->tel);//��ȡ�ļ��ж�Ӧ���ݴ����Ӧ���飻
		val=pNew->number+1;//val��Ϊ���ţ������Ĺ��˹���ֻ�������Ϲ���֮��
		//printf("%ld ",val);�������ʱ���⹤���Ƿ�������ȷ
		pTail->pNext = pNew;//ָ���µĽڵ�
		pNew->pLast=pTail;
		pNew->pNext = NULL;
		pTail = pNew;//βָ��ָ��β�ڵ�
	}
	fclose(fp);//�ر��ļ�
}
void readdele()//��ȡ�ļ����Ѿ����ڵ���Ϣ
{
	FILE * fp;
	fp = fopen("deledata.txt","r");//���ļ����ļ������ڷ��ؿ�ָ��
	pHead1 = (PNODE)malloc(sizeof(NODE));
	pTail1 = pHead1;
	pTail1->pNext=NULL;//��������
	if(fp==NULL)//�ж��ļ��Ƿ����
	{
		return;
	}
	while(!feof(fp))
	{
		PNODE pNew = (PNODE)malloc(sizeof(NODE));
		fscanf(fp,"%ld%s%s%s",&(pNew->number),pNew->name,pNew->sex,pNew->tel);//��ȡ�ļ��ж�Ӧ���ݴ����Ӧ���飻
		
		if(val<pNew->number)
			val=pNew->number+1;//�����ж���һ������
		pTail1->pNext = pNew;//ָ���µĽڵ�
		pNew->pNext = NULL;
		pTail1 = pNew;//βָ��ָ��β�ڵ�
	}
	fclose(fp);//�ر��ļ�
}
void editInfo()
{
	int n;
	long num;
	PNODE p = pHead->pNext;//����pָ�������������ҳ���ӦԱ��
	if(p==NULL)//�ж����������Ƿ���Ա����Ϣ
	{
		printf("Ա����ϢΪ�գ���¼����޸�!\n");
		return;//Ա����ϢΪ���޷��޸ģ������޸ĺ���
	}
	printf("��������Ҫ�޸���Ϣ��Ա�����ţ�");
	scanf("%ld",&num);//�����ҳ���Ҫ�޸ĵ�����Ա��Ϣ
	while (NULL != p)
	{
		if(num==p->number)
		{
			break;//�ҵ�Ҫ�޸ĵ�Ա����Ϣ�˳�ѭ��
		}
		p = p->pNext;
	}
	printf("���ţ�%05ld\n",p->number);
	printf("������");
	puts(p->name);
	printf("�ձ�");
	puts(p->sex);
	printf("�绰��");
	puts(p->tel);
	printf("\n\n");
	printf("��ѡ���޸��");
	printf("1-���� 2-�Ա� 3-�绰 4-ȫ��: ");
	scanf("%d",&n);
	getchar();//���ⲻ��Ҫ�Ļس��������Ӱ��
	switch(n)
	{
	case 1:printf("��������������");gets(p->name);break;
	case 2:
		if(strcmp(p->sex,"��")==0)
			strcpy(p->sex,"Ů");
		else
			strcpy(p->sex,"��");
		break;
	case 3:printf("�������º��룺");gets(p->tel);
		if(judge(p->tel))
		{
			printf("�޸���Ϣʧ��!\n\n");
			return;
		}
		break;
	case 4:
		{
			printf("��������������");gets(p->name);
			if(strcmp(p->sex,"��")==0)
				strcpy(p->sex,"Ů");
			else
				strcpy(p->sex,"��");
			printf("�������º��룺");gets(p->tel);
			if(judge(p->tel))
			{
				printf("�޸���Ϣʧ��!\n\n");
				return;
			}
			break;
		}
	default:printf("ѡ����Ч!\n\n");return;
	}
	printf("�޸ĳɹ�!\n\n");
	
}
void addInfo()//������Ա����Ϣ����
{
	int n;//����ѡ��Ա���Ա�
	PNODE pNew = (PNODE)malloc(sizeof(NODE));//�����½ڵ㣬��������ĩβ
	pNew->number=val;//��Ա������
	printf("���ţ�%05ld\n",pNew->number);
	printf("������Ա��������");
	scanf("%s",pNew->name);
	getchar();
	printf("��ѡ��Ա���Ա�1-�� 2-Ů: ");	
	scanf("%d",&n);
	switch(n)
	{
	case 1:strcpy(pNew->sex,"��");break;
	case 2:strcpy(pNew->sex,"Ů");break;
	}
	getchar();
	printf("������Ա���绰��");
	gets(pNew->tel);

	if(judge(pNew->tel))
	{
		printf("�����Ϣʧ��!\n");
		return;
	}
	//getchar();�������д����������һ�����˵��������
	printf("¼��ɹ�!\n\n");
	val++;//�Լ���Ϊ��һ��Ա������
	pTail->pNext = pNew;//�ƶ�βָ��
	pNew->pLast = pTail;
	pNew->pNext = NULL;
	pTail = pNew;

}
void showInfo1()//�����������
{
	PNODE p = pHead->pNext;
	if(p==NULL)
	{
		printf("����δ¼����Ϣ���޷���ʾ������¼��!\n\n");//����ļ���û����Ϣ����Ա����ϢΪ�գ��޷������
		return;//��������
	}
	while (NULL != p)//��������
	{
		printf("���ţ�%05ld\n",p->number);
		printf("������");
		puts(p->name);
		printf("�ձ�");
		puts(p->sex);
		printf("�绰��");
		puts(p->tel);
		printf("\n\n");
		p = p->pNext;
	}
	printf("\n");
}
void showInfo2()//�����������
{
	PNODE p = pTail;
	if(p->pLast==NULL)
	{
		printf("����δ¼����Ϣ���޷���ʾ������¼��!\n\n");//����ļ���û����Ϣ����Ա����ϢΪ�գ��޷������
		return;//��������
	}
	while (NULL != p->pLast)//��������
	{
		printf("���ţ�%05ld\n",p->number);
		printf("������");
		puts(p->name);
		printf("�ձ�");
		puts(p->sex);
		printf("�绰��");
		puts(p->tel);
		printf("\n\n");
		p = p->pLast;
	}
	printf("\n");
}
void showInfo()
{
	int n;
	printf("1-������� 2-���������");
	scanf("%d",&n);
	switch(n)
	{
	case 1:showInfo1();break;
	case 2:showInfo2();break;
	default:printf("������Ч!\n\n");break;
	}

}
void showdeleInfo()//�����������
{
	PNODE p = pHead1->pNext;
	if(p==NULL)
	{
		printf("��û��ɾ����¼!\n");//����ļ���û����Ϣ����Ա����ϢΪ�գ��޷������
		return;//��������
	}
	while (NULL != p)//��������
	{
		printf("���ţ�%05ld\n",p->number);
		printf("������");
		puts(p->name);
		printf("�ձ�");
		puts(p->sex);
		printf("�绰��");
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
	if(p->pNext==NULL)//�����ж���Ϊ���ų�Ա����ϢΪ�յĿ���
	{
		printf("δ��������Ա����ɾ��ʧ��!\n\n");
		return;
	}
	printf("1-���빤��ɾ�� 2-��������ɾ��: ");
	scanf("%d",&n);
	switch(n)
	{
	case 1:Numdel(p);break;//����ɾ������
	case 2:Namedel(p);break;//����ɾ������
	default:printf("��Чѡ��!\n\n");return;
	}
}
void saveInfo()
{
	PNODE p = pHead->pNext;
	PNODE q = pHead1->pNext;
	if(p==NULL&&q==NULL)//����Ƿ���Ա����Ϣ
	{
		printf("δ������Ա����Ϣ������Ӻ��ٱ���!\n\n");
		return;
	}
	FILE * fp;
	if(p!=NULL)
	{
		fp=fopen("data.txt","w");//��д����ʽ���ļ�
		while (NULL != p)//���������ļ�
		{
			fprintf(fp,"%05ld\t",p->number);
			fprintf(fp,"%s\t",p->name);
			fprintf(fp,"%s\t",p->sex);
			fprintf(fp,"%s",p->tel);
			p = p->pNext;
			if(p!=NULL)//�ж��Ƿ������һ�����ݣ����һ�����ݵ�����ܻ��У�Ҫ���ļ��оͻ��һ�У��ٴζ��ļ�ʱ��ͻ���һ����������
				fprintf(fp,"\n");
		}
		fclose(fp);
	}
	else
		remove("data.txt");//��ֹԱ����Ϣ��ɾ�������Ժ����¿��ļ�����ȡ����һ�����룬���Խ����ļ�ɾ��
	if(q!=NULL)
	{
		fp=fopen("deledata.txt","w");//��д����ʽ���ļ�
		while (NULL != q)//���������ļ�
		{
			fprintf(fp,"%05ld\t",q->number);
			fprintf(fp,"%s\t",q->name);
			fprintf(fp,"%s\t",q->sex);
			fprintf(fp,"%s",q->tel);
			q = q->pNext;
			if(q!=NULL)//�ж��Ƿ������һ�����ݣ����һ�����ݵ�����ܻ��У�Ҫ���ļ��оͻ��һ�У��ٴζ��ļ�ʱ��ͻ���һ����������
				fprintf(fp,"\n");
		}
		fclose(fp);
	}
	
	printf("����ɹ�!\n\n");

}
void Namedel(PNODE p)
{
	PNODE q;
	q = p->pNext;
	char b[100];
	printf("��������Ҫɾ����Ա��������");
	scanf("%s", b);
	//getchar();
	while (NULL != q)
	{
		if (strcmp(q->name, b) == 0)//�Ա�����������������Ӧ��Ա����Ϣ����ֹɾ��
		{
			z++;
			printf("���ţ�%05ld\n", q->number);
			printf("������");
			puts(q->name);
			printf("�ձ�");
			puts(q->sex);
			printf("�绰��");
			puts(q->tel);
			printf("\n\n");
	
		}
		q = q->pNext;
	}
	if(q==NULL&&z==0)//δ�ҵ���ӦԱ����Ϣ��˵����Ա��������������󣬸��û�����
		{
			printf("δ��������Ա����ɾ��ʧ��!\n\n");
			return;
		}
	else
	{
		printf("���ҵ�%dλ��%s��Ա��,",z,b);//��ֹ����ͬ��ͬ��Ա��
		Numdel(p,b);
	}
}
void Numdel(PNODE p)
{
	PNODE pNew = (PNODE)malloc(sizeof(NODE));//�����½ڵ㣬��������ĩβ
	char ch;
	long num;
	printf("��������Ҫɾ����Ա���ţ�");
	scanf("%ld", &num);
	getchar();
	while (NULL != p)
	{
		if (num == p->number)//�Ա�����Ĺ��ţ������Ӧ��Ա����Ϣ����ֹɾ��
		{
			printf("���ţ�%05ld\n", p->number);
			printf("������");
			puts(p->name);
			printf("�ձ�");
			puts(p->sex);
			printf("�绰��");
			puts(p->tel);
			printf("\n\n");
			printf("�Ƿ�ɾ��(y/n):");
			ch = getchar();

			if (ch == 'y' || ch == 'Y')//�ٴ�ȷ���Ƿ�ɾ����Ϣ
			{
				pNew = p->pNext;//��Ҫɾ����Ա����Ϣ��������
				pTail1->pNext = pNew;//�ƶ�βָ��
				p->pNext = p->pNext->pNext;//�������ָ����һ���ڵ�
				pNew->pNext = NULL;
				pTail1 = pNew;
				printf("ɾ���ɹ�!\n");
			}
			else
			{
				printf("ȡ��ɾ���ɹ�!\n");
			}
			return;//ȡ��ɾ��������������ɾ�����������
		}
		p = p->pNext;
	}
	if (p == NULL)//δ�ҵ���ӦԱ����Ϣ��˵������������󣬸��û�����
	{
		printf("δ��������Ա����ɾ��ʧ��!\n\n");
		return;
	}

}
void Numdel(PNODE p,char a[])
{
	PNODE pNew = (PNODE)malloc(sizeof(NODE));//�����½ڵ㣬��������ĩβ
	char ch;
	long num;
	printf("��������Ҫɾ����Ա���ţ�");
	scanf("%ld", &num);
	getchar();
	while (NULL != p)
	{
		if (num == p->number&&strcmp(p->name,a)==0)//�Ա�����Ĺ��ţ������Ӧ��Ա����Ϣ����ֹɾ��
		{
			printf("���ţ�%05ld\n", p->number);
			printf("������");
			puts(p->name);
			printf("�ձ�");
			puts(p->sex);
			printf("�绰��");
			puts(p->tel);
			printf("\n\n");
			printf("�Ƿ�ɾ��(y/n):");
			ch = getchar();

			if (ch == 'y' || ch == 'Y')//�ٴ�ȷ���Ƿ�ɾ����Ϣ
			{
				pNew = p->pNext;//��Ҫɾ����Ա����Ϣ��������
				pTail1->pNext = pNew;//�ƶ�βָ��
				p->pNext = p->pNext->pNext;//�������ָ����һ���ڵ�
				pNew->pNext = NULL;
				pTail1 = pNew;
				printf("ɾ���ɹ�!\n");
			}
			else
			{
				printf("ȡ��ɾ���ɹ�!\n");
			}//ȡ��ɾ��������������ɾ�����������
			return;
		}
		p = p->pNext;
	}
	if (p == NULL)//δ�ҵ���ӦԱ����Ϣ��˵������������󣬸��û�����
	{
		printf("������Ա���������ڹ��Ų�ͬ��ɾ��ʧ��!\n\n");
		return;
	}

}
void find1()
{
	long num;
	printf("�����빤�ţ�");
	scanf("%ld",&num);
	PNODE p=pHead;
	while(p!=NULL)
	{
		if (num == p->number)//�Ա�����Ĺ��ţ������Ӧ��Ա����Ϣ
		{
			printf("���ţ�%05ld\n", p->number);
			printf("������");
			puts(p->name);
			printf("�ձ�");
			puts(p->sex);
			printf("�绰��");
			puts(p->tel);
			printf("\n\n");
			return;
		}
		p=p->pNext;
	}
	printf("δ�ҵ�����Ϊ%ld��Ա��!\n\n",num);

}
void find2()
{
	char a[100];
	printf("������������");
	getchar();//����ִ��switch���ʱ����������ֶ��������Ӱ��
	gets(a);
	int t=0;
	PNODE p=pHead;
	while(p!=NULL)
	{
		if(strcmp(a,p->name)==0)
		{
			t++;
			printf("���ţ�%05ld\n", p->number);
			printf("������");
			puts(p->name);
			printf("�ձ�");
			puts(p->sex);
			printf("�绰��");
			puts(p->tel);
			printf("\n\n");
		}
		
		p=p->pNext;
		
	}
	if(t==0)
		printf("δ��⵽��Ա��!\n\n");
	else
		printf("���ҵ�%d����%s��Ա��!\n\n",t,a);
	
}
void find()//���Һ������ɹ��Ż���������
{
	int n;
	printf("��ѡ��������ʽ��1-���� 2-������");
	scanf("%d",&n);
	switch(n)
	{
	case 1:find1();break;
	case 2:find2();break;
	default:printf("��Ч����!\n\n");return;
	}
}
int judge(char tel[])//��������ֻ��������Ƿ�Ϸ�
{
	int i=0;
	int j=0;
	while(tel[i]!='\0')
	{
		if(tel[i]<'0'||tel[i]>'9')
		{
			printf("���벻�Ϸ�!");
			j++;
			break;
		}
		i++;
	}
	return j;//���Ϸ�����1�Ϸ�����0
}