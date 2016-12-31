#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "bklist.h"

pr createlist(void)//���ļ�
{
FILE* fp;
pr list=NULL;
pr node;
fp=fopen("data_file","rb");
if(fp==NULL)
return list;
while(1)
{
	node=malloc(sizeof(struct bk_node));
	if (fread(node,sizeof(struct bk_node),1,fp)==0)
	break;
	node->next=NULL;
	list=insertnode(list,node);
}
return list;
}
pr cleanlist(pr list)//���
{
	pr pos;
	pr tmp;
	if(list==NULL)
	{
		printf("�б��Ѿ����\n");
		return NULL;

	}
	pos=list;
	while(pos!=NULL)
	{
		tmp=pos->next;
		free(pos);
		pos=tmp;

	}
	printf("�б��Ѿ����");
	return NULL;

}

void savelist(pr list)//���ļ�
{
	FILE* fp;
	pr pos=list;
	fp=fopen("data_file","wb");
	while(pos!=NULL)
	{
		fwrite(pos,sizeof(struct bk_node),1,fp);
		pos=pos->next;
	}
	printf("����ɹ���\n");
	fclose(fp);
}
pr createnode(void)//���ڵ�
{
	pr node;
	node=malloc(sizeof(struct bk_node));
	printf("��ţ�");
	gets(node->id);
	printf("������");
	gets(node->name);
	printf("���ߣ�");
	gets(node->author);
	printf("�������ڣ�YY/MM/DD����");
	gets(node->date);
	printf("�۸�");
	scanf("%f",&node->price);
	node->next=NULL;
	getchar();
	return node;




		
}
pr insertnode(pr list,pr node)//��ڵ�
{
	pr pos=list;
	if(list==NULL)
	{
		list=node;
		return list;

	}
	while(pos->next!=NULL)
		pos=pos->next;
	node->next=pos->next;
	pos->next=node;
	return list;
}
pr deletenode(pr list,pr node)//ɾ�ڵ�
{
	pr pos=list;
	pr tmp;
	if(list==NULL)
	{
		printf("�б�Ϊ�գ�\n");
		return list;
	}
	if(pos==node)
	{
		tmp=pos->next;
		free(pos);
		printf("ɾ���ɹ�\n");
			return tmp;


	}
	while(pos->next!=node&&pos->next!=NULL)
		pos=pos->next;
	if(pos->next!=NULL)
	{
		pos->next=node->next;
		free(node);
		printf("ɾ���ɹ���\n");

	} else
		printf("û���ҵ�Ŀ¼\n");
	return list;


}
pr querynode(pr list,char* id)//����
{
	pr pos=list;
	while(pos!=NULL&&strcmp(pos->id,id)!=0)
		pos=pos->next;
	if(pos==NULL)
		printf("û���ҵ���¼��\n");
	return pos;

}


void printlist(pr list)//��ʾ���
{
	pr pos=list;
	if(list==NULL)
	{
		printf("�б�Ϊ�գ�\n");
		return;
	}
	printf("%-10s","���");
    printf("%-30s","����");
	printf("%-15s","����");
	printf("%-10s","��������");
	printf("%s","�۸�");
	printf("\n");
	while(pos!=NULL)
	{
    printf("%-10s",pos->id);
    printf("%-30s",pos->name);
	printf("%-15s",pos->author);
	printf("%-10s",pos->date);
	printf("%.2f\n",pos->price);
	printf("\n");
	pos=pos->next;
	}

}
void printnode(pr node)//������
{
	printf("��ţ�%s\n",node->id);
	printf("������%s\n",node->name);
	printf("���ߣ�%s\n",node->author);
	printf("�������ڣ�%s\n",node->date);
	printf("�۸�%.2f\n",node->price);
}
void mem(nod *head)//¼�벢��ӡ��Ա��Ϣ
{
     nod *p2=head;
	 int co=1;
	printf("��¼���Ա��Ϣ(�Կ���Ϊ-999����)\n");
	list(head);
	p2=head;
	if(p2==NULL)
		{
			printf("error");
		}
	else
	{
		
	

	
		while(p2->next!=NULL)
		{
			printf("************************************\n");
			printf("���У�%d\n",co);
			printf("��Ա������\n");
			printf("%s\n",p2->name);
			printf("��Ա���ţ�\n");
			printf("%d\n",p2->num);
			printf("��Ա��ϵ��ʽ��\n");
			printf("%s\n",p2->telephone);
			printf("*************************************\n");
			p2=p2->next;
			co++;

		}
	}
		


		

}
void list(nod *head)
{

	
	
	if(head==NULL)
	{
		printf("error\n");
		
	}
	
	
	else
	{
		printf("��������\n");
		scanf("%s",&head->name);
        printf("���뿨��\n");
        scanf("%d",&head->num);
		printf("����绰����\n");	
		scanf("%s",head->telephone);
		if(head->num==-999)
		{
		head->next=NULL;
		
		}
	     else
		 {head->next=(nod *)malloc(sizeof(nod));
	
	     
		list(head->next);
		}
	}
		
	
	
}
void codef()
{
	FILE *fp3;
	char codes[50];
	fp3=fopen("code","w");
	printf("���������룺��8λ���֣�\n");
	scanf("%s",codes);
	fwrite(codes,sizeof(char),8,fp3);
	fclose(fp3);
	printf("�޸ĳɹ�\n");
}



