#include"stdio.h"
#include"string.h"
#include"stdlib.h"
using namespace std;
typedef struct element 
{
	int b[8];
	int c;
	char a;
	struct element *next;
} ele;
//typedef sizeof(struct element ) len;
#define CA_len sizeof(struct element)
class CA{
public:
	void ca_tb(int b1[],int c1);
	void ca_create(int a2[],int b2[],int j1,int r1[]);
	int ca_td(int b3[],int c3);
	void ca_menu();
	void ca_jiami(char filename[],char savefile[],int j,int k,char *ca1,int rule);
	void ca_jiemi(char *filename,char *savefile,int j,int k,char *ca1,int rule);
	int ca_sjiami(ele* head,int count,int j,int k,char *ca1,int rule);
	int ca_sjiemi(ele* head,int count,int j,int k,char *ca1,int rule);
};
void CA::ca_tb(int b1[],int c1)// 10 to 2
{
	for(int i=0;i<=7;i++)
	{
		b1[i]=c1%2;
		c1=(c1-b1[i])/2;
	}
}
void CA::ca_create(int a2[],int b2[],int j,int r1[])//-----------conditions depend on this to convers-----------------------------------------------------------------------------------
{
	if(a2[j-1]==0&&a2[0]==0&&a2[1]==0)
		b2[0]=r1[7];
	else if(a2[j-1]==0&&a2[0]==0&&a2[1]==1)
		b2[0]=r1[6];
	else if(a2[j-1]==0&&a2[0]==1&&a2[1]==0)
		b2[0]=r1[5];
	else if(a2[j-1]==0&&a2[0]==1&&a2[1]==1)
		b2[0]=r1[4];
	else if(a2[j-1]==1&&a2[0]==0&&a2[1]==0)
		b2[0]=r1[3];
	else if(a2[j-1]==1&&a2[0]==0&&a2[1]==1)
		b2[0]=r1[2];
	else if(a2[j-1]==1&&a2[0]==1&&a2[1]==0)
		b2[0]=r1[1];
	else if(a2[j-1]==1&&a2[0]==1&&a2[1]==1)
		b2[0]=r1[0];
	for(int i=1;i<j;i++)
	{
		if(a2[i-1]==0&&a2[i]==0&&a2[i+1]==0)
		b2[i]=r1[7];
	else if(a2[i-1]==0&&a2[i]==0&&a2[i+1]==1)
		b2[i]=r1[6];
	else if(a2[i-1]==0&&a2[i]==1&&a2[i+1]==0)
		b2[i]=r1[5];
	else if(a2[i-1]==0&&a2[i]==1&&a2[i+1]==1)
		b2[i]=r1[4];
	else if(a2[i-1]==1&&a2[i]==0&&a2[i+1]==0)
		b2[i]=r1[3];
	else if(a2[i-1]==1&&a2[i]==0&&a2[i+1]==1)
		b2[i]=r1[2];
	else if(a2[i-1]==1&&a2[i]==1&&a2[i+1]==0)
		b2[i]=r1[1];
	else if(a2[i-1]==1&&a2[i]==1&&a2[i+1]==1)
		b2[i]=r1[0];
	}
	b2[j]=b2[0];

}
int CA::ca_td(int b3[],int c3)
{
	int sum=0;
	int basi=1;
	for(int i=0;i<8;i++)
	{
		b3[i]=b3[i]*basi;
		basi=basi*2;
		sum+=b3[i];
	}
	c3=sum;
	for(i=0;i<8;i++)
	{
		if(b3[i]!=0)
		{
			b3[i]=1;
		}
		
	}
	return sum;
}
void CA::ca_menu()
{
	printf("1、对文件加密\n");
	printf("2、对文件解密\n");
	printf("3、字符串加密\n");
	printf("4、字符串解密\n");

}
void CA::ca_jiami(char *filename,char *savefile,int j,int k,char *ca1,int rule)
{
	ele* head;//start
	ele* p1;//start
	ele* p2;//end
	head=NULL;
	char ch;
	int count=0;
//	int rule=0;
	int r[8];
	FILE *fp;
	//cout<<"请输入将要加密/解密的东东的路径"<<endl;
	//char filename[25];
	//scanf("%s",filename);
	//char *filename="D:\\mima\mima1.txt";
	//filename="D:\\mima\mima1.txt";
	 if((fp=fopen(filename,"r"))==NULL)
	 {
   printf("输入的文件不存在，请重新输入!\n");
	 return ;
	 }
	while((ch=fgetc(fp))!=EOF)
	{
		if(head==NULL)
		{
			head=(ele*)malloc(CA_len);
			head->a=ch;
			head->c=ch;
			p1=head;
			p2=head;
		}
		else
		{
			p1=(ele*)malloc(CA_len);
			p1->a=ch;
			p1->c=ch;
			p2->next=p1;
			p2=p1;
		}
		count++;
	}
	p1=head;
	p2->next=NULL;
	
	p1=head;
	fclose(fp);
		//-------------------------the codes above are the process where we receive arrays to be enciphered------------------------------------------------------------------------------------------
	while(p1->next!=NULL)
		{
			ca_tb(p1->b,p1->c);
			p1=p1->next;
		}
	ca_tb(p1->b,p1->c);
	p1=head;
	while(p1->next!=NULL)
		{
//			cout<<p1->a<<endl;
		//	for(int i=0;i<=7;i++)
			//	{
		//			cout<<p1->b[7-i];
			//}
//			cout<<endl;
//			cout<<p1->c<<endl;
			p1=p1->next;
		}
//	cout<<p1->a<<endl;
	
//	for(int i=0;i<=7;i++)
	//	{
//			cout<<p1->b[7-i];
	//	}
//	cout<<endl;
//	cout<<p1->c<<endl;
	p1=head;
      //---------------the codes above are about the process where decimalism is turned into binary-----------------------------------------------------------------------------
	//cout<<"现在请在1到255之间选择一个CA规则"<<endl;
	//cin>>rule;
	ca_tb(r,rule);
	//cout<<"现在输入你要初始的ca块长度"<<endl;
	// int j;
	//cin>>j;

	int **ca;
	ca= new int*[8*count];

//	cout<<"现在输入你要初始的ca块(中有回车)"<<endl;
	ca[0]=new int[j+1];
	for(int i=0;i<j;i++)
	{
		
		ca[0][i]=ca1[i]-'0';
		//cin>>*(*ca+i);
	}
	ca[0][j]=ca[0][0];
	/*for(int i=0;i<j+1;i++)
	{
		cout<<ca[0][i]<<endl;
	}*/
	/*for(int i=j+1;i<100;i++)
	{
		ca[i]=0;
	}*/
	//cout<<"请输入你要当作输出随机位的那一位"<<endl;
	//int k;
	//cin>>k;
	k--;//-------------------------------------ca[][k] is the one we want----------------------------------------------------------------------------------------------------------- 
	for(i=0;i<(count*8)-1;i++)
	{
		ca[i+1]=new int[j+1];
		ca_create(ca[i],ca[i+1],j,r);
		/*for(int w=0;w<j+1;w++)
		cout<<ca[i+1][w];
		cout<<endl;*/
	}
	/*for(int i=0;i<count*8;i++)//-------------------------------------------------------------------------------------
	{
		cout<<ca[i][k]<<" ";
	}*/
	//-----------conditions depend on codes above to convers-----------------------------------------------------------------------------------
	/*while(p1->next!=NULL)
		{
			cout<<p1->a<<endl;
			cout<<p1->c<<endl;
			p1=p1->next;
		}
	cout<<p1->a<<endl;
	cout<<p1->c<<endl;
	p1=head;*/
	//cout<<"加/解密中。。。。"<<endl;
//	for(int i=0;i<count*8;i++)//-------------------------------------------------------------------------------------
//	{
//		cout<<ca[i][k]<<" ";
//	}
//	cout<<endl;
	for( i=0;i<count;i++)
	{
		for(int l=0;l<8;l++)
		{
			p1->b[7-l]=(p1->b[7-l]+ca[i*8+l][k])%2;
		}
		p1=p1->next;
	}
	p1=head;
	FILE *fp1;
	//char  savefile[25];
	printf("存放的加密后文件路径为: ");
    //scanf("%s",savefile);
	//printf("\n");
    fp1=fopen(savefile,"w");
	while(p1->next!=NULL)
		{
			for( i=0;i<=7;i++)
				{
			//		cout<<p1->b[7-i]<<" ";
					fprintf(fp1,"%d",p1->b[7-i]);
				}
			p1=p1->next;
		}
	
	for( i=0;i<=7;i++)
				{
			//		cout<<p1->b[7-i]<<" ";
					fprintf(fp1,"%d",p1->b[7-i]);
				}
		//	cout<<endl;
			p1=head;
			fclose(fp1);
}
void CA::ca_jiemi(char *filename,char *savefile,int j,int k,char *ca1,int rule)
{
	ele* head;//start
	ele* p1;//start
	ele* p2;//end
	head=NULL;
	//char ch;
	int count=0;
	//int rule=0;
	int r[8];
		FILE*fp2;
		char ch1;
	//cout<<"请输入将要加密/解密的东东的路径"<<endl;
	//char filename[25];
	//scanf("%s",filename);
	 if((fp2=fopen(filename,"r"))==NULL)
	 {
 //  printf("输入的文件不存在，请重新输入!\n");
	 return ;
	 }
	while((ch1=fgetc(fp2))!=EOF)
	{
		if(head==NULL)
		{
			head=(ele*)malloc(CA_len);
			head->b[7]=ch1-'0';
			for(int i=0;i<7;i++)
			{
				ch1=fgetc(fp2);
				head->b[6-i]=ch1-'0';
			}
			p1=head;
			p2=head;
		}
		else
		{
			p1=(ele*)malloc(CA_len);
			p1->b[7]=ch1-'0';
			for(int i=0;i<7;i++)
			{
				ch1=fgetc(fp2);
				p1->b[6-i]=ch1-'0';
			}
			p2->next=p1;
			p2=p1;
		}
		count++;
	}
	p1=head;
	p2->next=NULL;
	
	p1=head;
		//-------------------------the codes above are the process where we receive arrays to be enciphered------------------------------------------------------------------------------------------
	
	fclose(fp2);
	/*while(p1->next!=NULL)
		{
			
			for(int i=0;i<=7;i++)
				{
					cout<<p1->b[7-i];
				}
			cout<<endl;
			
			p1=p1->next;
		}
	
	
	for(int i=0;i<=7;i++)
		{
			cout<<p1->b[7-i];
		}
	cout<<endl;
	
	p1=head;*/
      //---------------the codes above are about the process where decimalism is turned into binary-----------------------------------------------------------------------------
	//cout<<"现在请在1到255之间选择一个CA规则"<<endl;
	//cin>>rule;
	ca_tb(r,rule);
	//cout<<"现在输入你要初始的ca块长度"<<endl;
	// int j;
	//cin>>j;

	int **ca;
	ca= new int*[8*count];

	//cout<<"现在输入你要初始的ca块(中有回车)"<<endl;
	ca[0]=new int[j+1];
	for(int i=0;i<j;i++)
	{
		
		ca[0][i]=ca1[i]-'0';
		//cin>>*(*ca+i);
	}
	ca[0][j]=ca[0][0];
	/*for(int i=0;i<j+1;i++)
	{
		cout<<ca[0][i]<<endl;
	}*/
	/*for(int i=j+1;i<100;i++)
	{
		ca[i]=0;
	}*/
	//cout<<"请输入你要当作输出随机位的那一位"<<endl;
	//int k;
	//cin>>k;
	k--;//-------------------------------------ca[][k] is the one we want----------------------------------------------------------------------------------------------------------- 
	for( i=0;i<(count*8)-1;i++)
	{
		ca[i+1]=new int[j+1];
		ca_create(ca[i],ca[i+1],j,r);
		/*for(int w=0;w<j+1;w++)
		cout<<ca[i+1][w];
		cout<<endl;*/
	}
	/*for(int i=0;i<count*8;i++)//-------------------------------------------------------------------------------------
	{
		cout<<ca[i][k]<<" ";
	}*/
	//-----------conditions depend on codes above to convers-----------------------------------------------------------------------------------
	/*while(p1->next!=NULL)
		{
			cout<<p1->a<<endl;
			cout<<p1->c<<endl;
			p1=p1->next;
		}
	cout<<p1->a<<endl;
	cout<<p1->c<<endl;
	p1=head;*/
	//cout<<"加/解密中。。。。"<<endl;
	/*for(int i=0;i<count*8;i++)//-------------------------------------------------------------------------------------
	{
		cout<<ca[i][k]<<" ";
	}
	cout<<endl;*/
	for( i=0;i<count;i++)
	{
		for(int l=0;l<8;l++)
		{
			p1->b[7-l]=(p1->b[7-l]+ca[i*8+l][k])%2;
		}
		p1=p1->next;
	}
	p1=head;
	
	/*while(p1->next!=NULL)
		{
			for(int i=0;i<=7;i++)
				{
					cout<<p1->b[7-i]<<" ";
				}
			p1=p1->next;
		}
	cout<<p1->a<<endl;
	for(int i=0;i<=7;i++)
				{
					cout<<p1->b[7-i]<<" ";
				}
			cout<<endl;
			p1=head;*/
	while(p1->next!=NULL)//----------------------------------turn-----------------------------------------------------
		{
			p1->c=ca_td(p1->b,p1->c);
			p1->a='a'+(int)(p1->c-'a');
			p1=p1->next;
		}
	p1->c=ca_td(p1->b,p1->c);
	p1->a='a'+(int)(p1->c-'a');
	p1=head;
	/*while(p1->next!=NULL)
		{
			cout<<p1->a<<endl;
			for(int i=0;i<=7;i++)
				{
					cout<<p1->b[7-i]<<" ";
				}
			cout<<endl;
			cout<<p1->c<<endl;
			p1=p1->next;
		}
	cout<<p1->a<<endl;
	for(int i=0;i<=7;i++)
				{
					cout<<p1->b[7-i]<<" ";
				}
			cout<<endl;
	cout<<p1->c<<endl;
	p1=head;*/
	FILE* fp3;
	//char  savefile[25];
	//printf("存放的解密后文件路径为: ");
   // scanf("%s",savefile);
	//printf("\n");
    fp3=fopen(savefile,"w");
	while(p1->next!=NULL)
		{
			
					fputc(p1->a,fp3);
				
			p1=p1->next;
		}
	
	
					fputc(p1->a,fp3);
				
//			cout<<endl;
			p1=head;
			fclose(fp3);
	
	
}

int CA::ca_sjiami(ele* head,int count,int j,int k,char *ca1,int rule)
{
	//ele* head;//start
	ele* p1;//start
	//ele* p2;//end
	//head=NULL;
	//char ch;
	//int count=0;
	//int rule=0;
	int c=0;
	int r[8];
	p1=head;

	
	

		//-------------------------the codes above are the process where we receive arrays to be enciphered------------------------------------------------------------------------------------------
	while(p1->next!=NULL)
		{
			ca_tb(p1->b,p1->c);
			p1=p1->next;
		}
	ca_tb(p1->b,p1->c);
	p1=head;
	while(p1->next!=NULL)
		{
//			cout<<p1->a<<endl;
			for(int i=0;i<=7;i++)
				{
//					cout<<p1->b[7-i];
				}
//			cout<<endl;
//			cout<<p1->c<<endl;
			p1=p1->next;
		}
//	cout<<p1->a<<endl;
	
	for(int i=0;i<=7;i++)
		{
//			cout<<p1->b[7-i];
		}
//	cout<<endl;
//	cout<<p1->c<<endl;
	p1=head;
      //---------------the codes above are about the process where decimalism is turned into binary-----------------------------------------------------------------------------
	//cout<<"现在请在1到255之间选择一个CA规则"<<endl;
	//cin>>rule;
	ca_tb(r,rule);
	//cout<<"现在输入你要初始的ca块长度"<<endl;
	// int j;
	//cin>>j;

	int **ca;
	ca= new int*[8*count];

	//cout<<"现在输入你要初始的ca块(中有回车)"<<endl;
	ca[0]=new int[j+1];
	for( i=0;i<j;i++)
	{
		
		ca[0][i]=ca1[i]-'0';
		//cin>>*(*ca+i);
	}
	ca[0][j]=ca[0][0];
	/*for(int i=0;i<j+1;i++)
	{
		cout<<ca[0][i]<<endl;
	}*/
	/*for(int i=j+1;i<100;i++)
	{
		ca[i]=0;
	}*/
	//cout<<"请输入你要当作输出随机位的那一位"<<endl;
	//int k;
	//cin>>k;
	k--;//-------------------------------------ca[][k] is the one we want----------------------------------------------------------------------------------------------------------- 
	for( i=0;i<(count*8)-1;i++)
	{
		ca[i+1]=new int[j+1];
		ca_create(ca[i],ca[i+1],j,r);
	//	for(int w=0;w<j+1;w++)
//		cout<<ca[i+1][w];
//		cout<<endl;
	}
	/*for(int i=0;i<count*8;i++)//-------------------------------------------------------------------------------------
	{
		cout<<ca[i][k]<<" ";
	}*/
	//-----------conditions depend on codes above to convers-----------------------------------------------------------------------------------
	/*while(p1->next!=NULL)
		{
			cout<<p1->a<<endl;
			cout<<p1->c<<endl;
			p1=p1->next;
		}
	cout<<p1->a<<endl;
	cout<<p1->c<<endl;
	p1=head;*/
//	cout<<"加/解密中。。。。"<<endl;
	for( i=0;i<count*8;i++)//-------------------------------------------------------------------------------------
	{
//		cout<<ca[i][k]<<" ";
	}
//	cout<<endl;
//	char *results=new char[count*8];
	for( i=0;i<count;i++)
	{
		for(int l=0;l<8;l++)
		{
			p1->b[7-l]=(p1->b[7-l]+ca[i*8+l][k])%2;
		}
		p1=p1->next;
	}
	p1=head;
/*	while(p1->next!=NULL)
		{
			for( i=0;i<=7;i++)
				{
					results[c]=p1->b[7-i]+48;
					c++;
				}
			p1=p1->next;
		}
	for( i=0;i<=7;i++)
				{
						results[c]=p1->b[7-i]+48;
					c++;
					
				}*/
	count=count*8;
	return count;
}
int CA::ca_sjiemi(ele* head,int count,int j,int k,char *ca1,int rule)
{
	//ele* head;//start
	ele* p1;//start
	//ele* p2;//end
	//head=NULL;
	//char ch;
	//int count=0;
	//int rule=0;
	int r[8];
//	char ch1;
	
	
	p1=head;
		//-------------------------the codes above are the process where we receive arrays to be enciphered------------------------------------------------------------------------------------------
	

	while(p1->next!=NULL)
		{
			
			for(int i=0;i<=7;i++)
				{
//					cout<<p1->b[7-i];
				}
	//		cout<<endl;
			
			p1=p1->next;
		}
	
	
	for( int i=0;i<=7;i++)
		{
	//		cout<<p1->b[7-i];
		}
	//cout<<endl;
	
	p1=head;
      //---------------the codes above are about the process where decimalism is turned into binary-----------------------------------------------------------------------------
	//cout<<"现在请在1到255之间选择一个CA规则"<<endl;
	//cin>>rule;
	ca_tb(r,rule);
	//cout<<"现在输入你要初始的ca块长度"<<endl;
	// int j;
	//cin>>j;

	int **ca;
	ca= new int*[8*count];

	//cout<<"现在输入你要初始的ca块(中有回车)"<<endl;
	ca[0]=new int[j+1];
	for(i=0;i<j;i++)
	{
		
		ca[0][i]=ca1[i]-'0';
		//cin>>*(*ca+i);
	}
	ca[0][j]=ca[0][0];
	/*for(int i=0;i<j+1;i++)
	{
		cout<<ca[0][i]<<endl;
	}*/
	/*for(int i=j+1;i<100;i++)
	{
		ca[i]=0;
	}*/
	//cout<<"请输入你要当作输出随机位的那一位"<<endl;
	//int k;
	//cin>>k;
	k--;//-------------------------------------ca[][k] is the one we want----------------------------------------------------------------------------------------------------------- 
	for(i=0;i<(count*8)-1;i++)
	{
		ca[i+1]=new int[j+1];
		ca_create(ca[i],ca[i+1],j,r);
		//for(int w=0;w<j+1;w++)
	//	cout<<ca[i+1][w];
	//	cout<<endl;
	}
	/*for(int i=0;i<count*8;i++)//-------------------------------------------------------------------------------------
	{
		cout<<ca[i][k]<<" ";
	}*/
	//-----------conditions depend on codes above to convers-----------------------------------------------------------------------------------
	/*while(p1->next!=NULL)
		{
			cout<<p1->a<<endl;
			cout<<p1->c<<endl;
			p1=p1->next;
		}
	cout<<p1->a<<endl;
	cout<<p1->c<<endl;
	p1=head;*/
//	cout<<"加/解密中。。。。"<<endl;
	for(i=0;i<count*8;i++)//-------------------------------------------------------------------------------------
	{
//		cout<<ca[i][k]<<" ";
	}
//	cout<<endl;
	for( i=0;i<count;i++)
	{
		for(int l=0;l<8;l++)
		{
			p1->b[7-l]=(p1->b[7-l]+ca[i*8+l][k])%2;
		}
		p1=p1->next;
	}
	p1=head;
	
	while(p1->next!=NULL)
		{
			for(int i=0;i<=7;i++)
				{
		//			cout<<p1->b[7-i]<<" ";
				}
			p1=p1->next;
		}
//	cout<<p1->a<<endl;
	for( i=0;i<=7;i++)
				{
	//				cout<<p1->b[7-i]<<" ";
				}
	//		cout<<endl;
			p1=head;
	while(p1->next!=NULL)//----------------------------------turn-----------------------------------------------------
		{
			p1->c=ca_td(p1->b,p1->c);
			p1->a='a'+(int)(p1->c-'a');
			p1=p1->next;
		}
	p1->c=ca_td(p1->b,p1->c);
	p1->a='a'+(int)(p1->c-'a');
	p1=head;
	while(p1->next!=NULL)
		{
//			cout<<p1->a;
			p1=p1->next;
		}
//	cout<<p1->a<<endl;
//	cout<<endl;
	p1=head;
	return count;
}
