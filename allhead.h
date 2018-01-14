#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
void addInfo();
void editInfo();
void delInfo();
void showInfo();
void showInfo1();
void showInfo2();
void saveInfo();
void insert();
void display();
void choose();
void read();
void readdele();
void showdeleInfo();
typedef struct Info
{
	struct Info *pLast;	
	long number;
	char name[100];
	char sex[10];
	char tel[20];
	struct Info *pNext;	
}NODE,*PNODE;
void Namedel(PNODE);
void Numdel(PNODE);
void find();
void find1();
void find2();
int judge(char *);
void Numdel(PNODE p,char a[]);
void ex();
void insert(long);