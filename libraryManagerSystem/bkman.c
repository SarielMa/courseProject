#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "bklist.h"
void printmenu(void)
{
	printf("\n");
	printf("***********************************************\n");
	printf("  ͼ����Ϣ����ϵͳ\n");
    printf("***********************************************\n");
	printf("1.�г�ͼ��\n");
	printf("2.��ѯͼ��\n");
    printf("3.���Ӽ�¼\n");
	printf("4.ɾ����¼\n");
	printf("5.����б�\n");
	printf("6.�����޸�\n");
	printf("7.��Ա��Ϣ\n");
	printf("8.�޸�����\n");
	printf("0.�˳�ϵͳ\n");
	printf("\n");
	printf("��ѡ��    ");
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
	printf("���������룺\n");
	scanf("%s",code);
	if(strcmp(code,ncode)!=0)
		printf("�������\n");
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
			printf("����Ҫ��ѯ��ͼ���ţ�");
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
			printf("����Ҫɾ����ͼ���ţ�");
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
			printf("���������������!\n");




		}
		fflush(stdin);
		
	}return 0;
	
}
