#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "bklist.h"

pr createlist(void)//提文件
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
pr cleanlist(pr list)//清表
{
	pr pos;
	pr tmp;
	if(list==NULL)
	{
		printf("列表已经清空\n");
		return NULL;

	}
	pos=list;
	while(pos!=NULL)
	{
		tmp=pos->next;
		free(pos);
		pos=tmp;

	}
	printf("列表已经清空");
	return NULL;

}

void savelist(pr list)//存文件
{
	FILE* fp;
	pr pos=list;
	fp=fopen("data_file","wb");
	while(pos!=NULL)
	{
		fwrite(pos,sizeof(struct bk_node),1,fp);
		pos=pos->next;
	}
	printf("保存成功！\n");
	fclose(fp);
}
pr createnode(void)//创节点
{
	pr node;
	node=malloc(sizeof(struct bk_node));
	printf("编号：");
	gets(node->id);
	printf("书名：");
	gets(node->name);
	printf("作者：");
	gets(node->author);
	printf("出版日期（YY/MM/DD）：");
	gets(node->date);
	printf("价格：");
	scanf("%f",&node->price);
	node->next=NULL;
	getchar();
	return node;




		
}
pr insertnode(pr list,pr node)//插节点
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
pr deletenode(pr list,pr node)//删节点
{
	pr pos=list;
	pr tmp;
	if(list==NULL)
	{
		printf("列表为空！\n");
		return list;
	}
	if(pos==node)
	{
		tmp=pos->next;
		free(pos);
		printf("删除成功\n");
			return tmp;


	}
	while(pos->next!=node&&pos->next!=NULL)
		pos=pos->next;
	if(pos->next!=NULL)
	{
		pos->next=node->next;
		free(node);
		printf("删除成功！\n");

	} else
		printf("没有找到目录\n");
	return list;


}
pr querynode(pr list,char* id)//查书
{
	pr pos=list;
	while(pos!=NULL&&strcmp(pos->id,id)!=0)
		pos=pos->next;
	if(pos==NULL)
		printf("没有找到记录！\n");
	return pos;

}


void printlist(pr list)//显示结果
{
	pr pos=list;
	if(list==NULL)
	{
		printf("列表为空！\n");
		return;
	}
	printf("%-10s","编号");
    printf("%-30s","书名");
	printf("%-15s","作者");
	printf("%-10s","出版日期");
	printf("%s","价格");
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
void printnode(pr node)//查书结果
{
	printf("编号：%s\n",node->id);
	printf("书名：%s\n",node->name);
	printf("作者：%s\n",node->author);
	printf("出版日期：%s\n",node->date);
	printf("价格：%.2f\n",node->price);
}
void mem(nod *head)//录入并打印会员信息
{
     nod *p2=head;
	 int co=1;
	printf("请录入会员信息(以卡号为-999结束)\n");
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
			printf("序列：%d\n",co);
			printf("会员姓名：\n");
			printf("%s\n",p2->name);
			printf("会员卡号：\n");
			printf("%d\n",p2->num);
			printf("会员联系方式：\n");
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
		printf("输入姓名\n");
		scanf("%s",&head->name);
        printf("输入卡号\n");
        scanf("%d",&head->num);
		printf("输入电话号码\n");	
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
	printf("输入新密码：（8位数字）\n");
	scanf("%s",codes);
	fwrite(codes,sizeof(char),8,fp3);
	fclose(fp3);
	printf("修改成功\n");
}



