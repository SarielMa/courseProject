#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "bklist.h"
void printmenu(void)
{
	printf("\n");
	printf("***********************************************\n");
	printf("  图书信息管理系统\n");
    printf("***********************************************\n");
	printf("1.列出图书\n");
	printf("2.查询图书\n");
    printf("3.增加记录\n");
	printf("4.删除记录\n");
	printf("5.清空列表\n");
	printf("6.保存修改\n");
	printf("7.会员信息\n");
	printf("8.修改密码\n");
	printf("0.退出系统\n");
	printf("\n");
	printf("请选择：    ");
}
int main()
{
	char c;
	char id[16];
	char code[50];
	char ncode[50];
	FILE *fp2;
	pr list;
	pr node;
	nod *head=(nod *)malloc(sizeof(nod));
	
	list=createlist();
	
	
	while(	fopen("code","r")!=NULL)
	{
		fp2=fopen("code","r");

	fscanf(fp2,"%s",ncode);
	printf("请输入密码：\n");
	scanf("%s",code);
	if(strcmp(code,ncode)!=0)
		printf("密码错误\n");
	else
		break;
	    fclose(fp2);
	}
	fflush(stdin);


	
	while(1)
	{
		printmenu();
	    
		c=getchar();
		getchar();
		switch(c)
		{
		case '1':
			printlist(list);
			break;
		case '2':
			printf("输入要查询的图书编号：");
			scanf("%s",id);
			getchar();
			node=querynode(list,id);
			if(node!=NULL)
	
			printnode(node);
		break;
		case '3':
			node=createnode();
			list=insertnode(list,node);
			break;
		case '4':
			printf("输入要删除的图书编号：");
			scanf("%s",id);
			getchar();

			node=querynode(list,id);
			if(node!=NULL)
				list=deletenode(list,node);
			break;
		case '5':
			list=cleanlist(list);
			break;
		case '6':
			savelist(list);
			break;
		case '7':
			mem(head);
			break;
		case '8':
			codef();
			break;
		case '0':
			return 0;
		default:
			printf("输入错误，重新输入!\n");




		}
		fflush(stdin);
		
	}return 0;
	
}
