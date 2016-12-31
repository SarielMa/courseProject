#include"stdio.h"
#include"string.h"
#include "stdlib.h"  
#include "time.h"
#include "math.h"
#include "malloc.h"
#include "iostream"
using namespace std;


#define LENGTH sizeof(struct rsan)


struct rsan
{
 int  num[100];
 /*num[98]������������ţ�1����0��num[99]�����ʵ�ʳ���*/
    struct rsan *next;
};

/*/--------------------------------------RSA���������-------------------------------------*/
class RSA
{
public:
//void sub(int a[100],int b[100] ,int c[100] );
void  print(  int a[100] )
{
    int i;
    for(i=0;i<a[99];i++)
     printf("%d",a[a[99]-i-1]);
    printf("\n\n");
    
}


int  cmp(int a1[100],int a2[100])
{   int l1, l2;
 int i;
 l1=a1[99];
 l2=a2[99];
 if (l1>l2)
     return 1;
    if (l1<l2)
       return -1;
    for(i=(l1-1);i>=0;i--)
   {
    if (a1[i]>a2[i])
     return 1 ;
    if (a1[i]<a2[i])
     return -1;
   }
    return 0;
}

void mov(int a[100],int *b)
{
 int j;
  for(j=0;j<100;j++)
   b[j]=a[j];
  
  return ;
}


void mul(int a1[100],int a2[100],int *c)
{
 int i,j;
 int y;
 int x;
 int z;
 int w;
 int l1, l2;
 l1=a1[99];
 l2=a2[99];
 if (a1[98]=='-'&& a2[98]=='-')
  c[98]=0;
 else if (a1[98]=='-')
  c[98]='-';
 else if (a2[98]=='-')
  c[98]='-';
 for(i=0;i<l1;i++)
 {
  for(j=0;j<l2;j++)
  {
     x=a1[i]*a2[j];
     y=x/10;
     z=x%10;
     w=i+j;
     c[w]=c[w]+z;
     c[w+1]=c[w+1]+y+c[w]/10;
     c[w]=c[w]%10;
  }
 }
 w=l1+l2;
 if(c[w-1]==0)w=w-1;
 c[99]=w;
 return;
}

void add(int a1[100],int a2[100],int *c)
{

    int i,l1,l2;
    int RSA_len=0;
	int temp[100];
	int k=0;
	l1=a1[99];
	l2=a2[99];
	if((a1[98]=='-')&&(a2[98]=='-'))
	{
		c[98]='-';
	}
	else if (a1[98]=='-')
	{
		mov(a1,temp);
		temp[98]=0;
			sub(a2,temp,c);
	 return;
	}
	else if (a2[98]=='-')
	{
		mov(a2,temp);
		temp[98]=0;
		sub(a1,temp,c);
		return;
	}

	if(l1<l2)RSA_len=l1;
	else RSA_len=l2;
	for(i=0;i<RSA_len;i++)
	{
		c[i]=(a1[i]+a2[i]+k)%10;
		k=(a1[i]+a2[i]+k)/10;
	}
	if(l1>RSA_len)
	{
		for(i=RSA_len;i<l1;i++)
		{
			c[i]=(a1[i]+k)%10;
			k=(a1[i]+k)/10;  
		}
		if(k!=0)
		{
			c[l1]=k;
			RSA_len=l1+1;
		}
		else RSA_len=l1;
	 }
	 else
	 {
		for(i=RSA_len;i<l2;i++)
		{
			c[i]=(a2[i]+k)%10;
			k=(a2[i]+k)/10;  
		}
		if(k!=0)
		{
			c[l2]=k;
			RSA_len=l2+1;
		}
		else RSA_len=l2;
	 }
	c[99]=RSA_len;
	return;
}


void sub(int a1[100],int a2[100],int *c)
{
 int i,l1,l2;
 int RSA_len,t1[100],t2[100];
 int k=0;
l1=a1[99];
l2=a2[99];
if ((a1[98]=='-') && (a2[98]=='-'))
{
 mov(a1,t1);
        mov(a2,t2);
 t1[98]=0;
        t2[98]=0;
 sub(t2,t1,c);
 return;
}
else if( a2[98]=='-')
{
 mov(a2,t2);
 t2[98]=0;
 add(a1,t2,c);
 return;
}
else if (a1[98]=='-')
{
 mov(a2,t2);
 t2[98]='-';
 add(a1,t2,c);
 return;
}

 if(cmp(a1,a2)==1)
 {
 
  RSA_len=l2;
 for(i=0;i<RSA_len;i++)
 {
  if ((a1[i]-k-a2[i])<0)
 {
  c[i]=(a1[i]-a2[i]-k+10)%10;
     k=1;
 }
     else
  {
   c[i]=(a1[i]-a2[i]-k)%10;
      k=0;
  }
 }


  for(i=RSA_len;i<l1;i++)
  {
   if ((a1[i]-k)<0)
 {
  c[i]=(a1[i]-k+10)%10;
     k=1;
 }
     else
  {
   c[i]=(a1[i]-k)%10;
      k=0;
  }
  }
  if(c[l1-1]==0)/*ʹ������C�е�ǰ������0�ַ�����ʾ�ˣ���1000-20=0980--->��ʾΪ980��*/
  {
      RSA_len=l1-1;
   i=2;
   while (c[l1-i]==0)/*111456-111450=00006������0������6��*/
   {
     RSA_len=l1-i;
    i++;
   }

  }

  else
  {
   RSA_len=l1;
  }
 }
else
if(cmp(a1,a2)==(-1))
 {
  c[98]='-';
  RSA_len=l1;
  for(i=0;i<RSA_len;i++)
 {
  if ((a2[i]-k-a1[i])<0)
 {
  c[i]=(a2[i]-a1[i]-k+10)%10;
     k=1;
 }
     else
  {
   c[i]=(a2[i]-a1[i]-k)%10;
      k=0;
  }
 }
  for(i=RSA_len;i<l2;i++)
  {
    if ((a2[i]-k)<0)
 {
  c[i]=(a2[i]-k+10)%10;
     k=1;
 }
     else
  {
   c[i]=(a2[i]-k)%10;
      k=0;
  }  
  }
  if(c[l2-1]==0)
  { 
   RSA_len=l2-1;
   i=2;
   while (c[l1-i]==0)
   {
     RSA_len=l1-i;
     i++;
   }

  }

  else RSA_len=l2;
 
 }

else if(cmp(a1,a2)==0)
   {
    RSA_len=1;
    c[RSA_len-1]=0;
   }
 c[99]=RSA_len;
return;
}

void  mod(int a[100],int b[100],int  *c)/*/c=a mod b//ע�⣺������֪���˴�A��C�����鶼�ı��ˡ�*/
{ int d[100];
 mov (a,d);
 while (cmp(d,b)!=(-1))/*/c=a-b-b-b-b-b.......until(c<b)*/
 {
  sub(d,b,c);
  mov(c,d);/*/c���Ƹ�a*/
 } 
 return ;
}


void  divt(int t[100],int b[100],int  *c ,int *w)/*//���̷�//�����Ժ�wΪa mod b, CΪa  div b;*/
{

 int a1,b1,i,j,m;/*w������ʱ��������*/
 int d[100],e[100],f[100],g[100],a[100];
 
 mov(t,a);
  for(i=0;i<100;i++)
    e[i]=0;
 for(i=0;i<100;i++)
    d[i]=0;
 for(i=0;i<100;i++) g[i]=0;
 a1=a[99];
    b1=b[99];
 if (cmp(a,b)==(-1))
 {
  c[0]=0;
  c[99]=1;
  mov(t,w);
  return;
 }
 else if (cmp(a,b)==0)
 {
  c[0]=1;
        c[99]=1;
  w[0]=0;
  w[99]=1;
  return;
 }
  m=(a1-b1);
    for(i=m;i>=0;i--)/*341245/3=341245-300000*1--->41245-30000*1--->11245-3000*3--->2245-300*7--->145-30*4=25--->25-3*8=1*/
 {
      for(j=0;j<100;j++)
        d[j]=0;
  d[i]=1;
  d[99]=i+1;
  mov(b,g);
        mul(g,d,e);

 
  while (cmp(a,e)!=(-1))
  {
   c[i]++;
   sub(a,e,f);
      mov(f,a);/*f���Ƹ�g*/
  }

     for(j=i;j<100;j++)/*��λ����*/
        e[j]=0;
 
 }
 mov(a,w);
 if (c[m]==0) c[99]=m;
 else c[99]=m+1;

 return;
}

void mulmod(int a[100] ,int b[100] ,int n[100],int *m)/*��� �� m=a*b mod n;*/
{
 int c[100],d[100];
 int i;
 for(i=0;i<100;i++)
  d[i]=c[i]=0;
 mul(a,b,c);
   divt(c,n, d,m);
   for(i=0;i<m[99];i++)
  printf("%d",m[m[99]-i-1]);
     printf("\nm  length is :  %d \n",m[99]);
}

/*���������ص�������Ҫ���ֽ�� m=a^p  mod n�ĺ������⡣*/

void expmod(int a[100] ,int p[100] ,int n[100],int *m)
{
 int t[100],l[100],temp[100]; /*/t����2��l����1��*/
 int w[100],s[100],c[100],b[100],i;
 for(i=0;i<99;i++)
  b[i]=l[i]=t[i]=w[i]=0;
 t[0]=2;t[99]=1;
 l[0]=1;l[99]=1;
    mov(l,temp);
	mov(a,m);
    mov(p,b);

while(cmp(b,l)!=0)
{
    for(i=0;i<100;i++)
 w[i]=c[i]=0;

    divt(b,t,w,c);/*// c=p mod 2  w= p /2*/
 
    mov(w,b);/*//p=p/2*/

if(cmp(c,l)==0) /*/����c==1*/
{
 for(i=0;i<100;i++)
 w[i]=0;
 mul(temp,m,w);
 mov(w,temp);
 
 for(i=0;i<100;i++)
 w[i]=c[i]=0;

  divt(temp,n,w,c);/* /cΪ��c=temp % n��wΪ��w=temp/n */

  mov(c,temp);
}

for(i=0;i<100;i++)
 s[i]=0;

mul(m,m,s);//s=a*a

for(i=0;i<100;i++)
 c[i]=0;

divt(s,n,w,c);/*/w=s/n;c=s mod n*/

mov (c,m);

}

for(i=0;i<100;i++)
 s[i]=0;

mul(m,temp,s);

for(i=0;i<100;i++)
 c[i]=0;

divt(s,n,w,c);

mov (c,m);/*����s��m*/

m[98]=a[98];/*Ϊ����ĺ�����ʾ��Ҫ���õ�99λ��Ϊ���*/

return;
/*/k=temp*k%n;*/

}


int   is_prime_san(int p[100] )
{
 
   int i,a[100],t[100],s[100],o[100];
   for(i=0;i<100;i++)
    s[i]=o[i]=a[i]=t[i]=0;
   t[0]=1;
   t[99]=1;
   a[0]=2;// { 2,3,5,7 }
   a[99]=1;

   sub(p,t,s);

   expmod ( a, s, p ,o);
       if ( cmp(o,t) != 0 )
    {
   return 0;
    }

   a[0]=3;
   for(i=0;i<100;i++)  o[i]=0;

   expmod ( a, s, p ,o);
       if ( cmp(o,t) != 0 )    
    {
   return 0;
    }

      a[0]=5;
   for(i=0;i<100;i++)  o[i]=0;

   expmod ( a, s, p ,o);
   if ( cmp(o,t) != 0 )
   {   
   return 0;
   }

     a[0]=7;
   for(i=0;i<100;i++)  o[i]=0;

   expmod ( a, s, p ,o);

  if ( cmp(o,t) != 0 )
  {

   return 0;
  }

  return 1;
}


int coprime(int e[100],int s[100]) /*//// ����������֮���Ƿ���////*/

{
    int a[100],b[100],c[100],d[100],o[100],l[100];
    int i;
 for(i=0;i<100;i++)
  l[i]=o[i]=c[i]=d[i]=0;
 o[0]=0;o[99]=1;
 l[0]=1;l[99]=1;
 mov(e,b);
 mov(s,a);
do
{
if(cmp(b,l)==0)
{
    return 1;
}
for(i=0;i<100;i++)
 c[i]=0;
 divt(a,b,d,c);
 mov(b,a);/*b--->a*/
 mov(c,b);/*c--->b*/

}while(cmp(c,o)!=0);
/* printf("Ihey are  not coprime!\n");*/
return 0;
}


void prime_random(int *p,int *q)
{
 int i,k;
 time_t t;
  p[0]=1;
  q[0]=3;
 
// p[19]=1;
// q[18]=2;
 
 p[99]=10;
    q[99]=11;

 
 do
 {
   t=time(NULL);
    srand((unsigned long)t);
 for(i=1;i<p[99]-1;i++)
 {
 k=rand()%10;
 p[i]=k;
 }
 k=rand()%10;
 while (k==0)
 {
  k=rand()%10;
 }
 p[p[99]-1]=k;

 }while((is_prime_san(p))!=1);
  printf("���� p Ϊ  : ");
    for(i=0;i<p[99];i++)
 {
 printf("%d",p[p[99]-i-1]);
 }
    printf("\n\n");
  do
 {
   t=time(NULL);
    srand((unsigned long)t);
 for(i=1;i<q[99];i++)
 {
 k=rand()%10;
 q[i]=k;
 }

 }while((is_prime_san(q))!=1);
  printf("���� q Ϊ : ");
    for(i=0;i<q[99];i++)
 {
 printf("%d",q[q[99]-i-1]);
 }
    printf("\n\n");
 return;
}
 
void  erand(int e[100],int m[100],int p[100],int q[100])
{
 int i,k;
 time_t t;
e[99]=13;
 printf("�������һ����(p-1)*(q-1)���ص� e :");
  do
 {
   t=time(NULL);
    srand((unsigned long)t);
    for(i=0;i<e[99]-1;i++)
    {
    k=rand()%10;
     e[i]=k;
    }
    while((k=rand()%10)==0)
       k=rand()%10;
    e[e[99]-1]=k;
	
 }while(coprime( e, m)!=1);
    for(i=0;i<e[99];i++)
       {
           printf("%d",e[e[99]-i-1]);
       }
    printf("\n\n");
 return;
}

void rsad(int e[100],int g[100],int *d)
{
 int   r[100],n1[100],n2[100],k[100],w[100];
 int     i,t[100],b1[100],b2[100],temp[100];
 mov(g,n1);
 mov(e,n2);
 for(i=0;i<100;i++)
  k[i]=w[i]=r[i]=temp[i]=b1[i]=b2[i]=t[i]=0;
 b1[99]=0;b1[0]=0;           /*/b1=0;*/
 b2[99]=1;b2[0]=1;           /*/b2=1;*/
 while(1)
 {

  for(i=0;i<100;i++)
    k[i]=w[i]=0;
  divt(n1,n2,k,w);/*/k=n1/n2;*/
  for(i=0;i<100;i++)
  temp[i]=0;
  mul(k,n2,temp);/*/temp=k*n2;*/
    for(i=0;i<100;i++)
  r[i]=0;
        sub(n1,temp,r);

  if((r[99]==1) && (r[0]==0))/*/r=0*/
  {
   break;
  }
  else
  {
   mov(n2,n1);/*/n1=n2;*/
   mov( r,n2);/*/n2=r;*/
   mov(b2, t);/*/t=b2;*/
   for(i=0;i<100;i++)
        temp[i]=0;
   mul(k,b2,temp);/*/b2=b1-k*b2;*/
   for(i=0;i<100;i++)
        b2[i]=0;
   sub(b1,temp,b2);
   mov(t,b1);
  }
 }

   for(i=0;i<100;i++)
    t[i]=0;
   add(b2,g,t);
   for(i=0;i<100;i++)
    temp[i]=d[i]=0;
      divt(t,g,temp,d);
    printf("�����ϵ�(p-1)*(q-1)�� e ����ó��� d : ");
    for(i=0;i<d[99];i++)
 printf("%d",d[d[99]-i-1]);
    printf("\n\n");
}

 

 

/*/�������Կd�ĺ���(����Euclid�㷨)96403770511368768000*/
/*/�������Կd�ĺ���(����Euclid�㷨)*/
unsigned long  rsa(unsigned long p,unsigned long q,unsigned long e) 

{
unsigned long g,k,r,n1,n2,t;
unsigned long b1=0,b2=1;

 g=(p-1)*(q-1);
 n1=g;
 n2=e;
   
    while(1)
 {
        k=n1/n2;
        r=n1-k*n2;
  if(r!=0)
  {
     n1=n2;
     n2=r;
     t=b2;
     b2=b1-k*b2;
     b1=t;
  }

  else
  {
   break;
  }

 }

    return (g+b2)%g;
}
/*/------------------------------------------���뵼����Կ��˽Կ------------------------------------/*/
void loadpkey(int e[100],int n[100],char *filename)  //���빫Կ
{
 FILE *fp;
 char str[100],ch;
 int i,k;
 for(i=0;i<100;i++)
  e[i]=n[i]=0;
 while(1)
 {
    printf("\n");
 //printf("Ϊ����(e,n)�������������Կ���ļ�·��: \n");
    //scanf("%s",filename);
  if((fp=fopen(filename,"r"))==NULL)
   printf("������ļ������ڣ�����������!\n");
  else break;
 }
  k=0;
  while((ch=fgetc(fp))!=EOF)
  { 
  if(ch!=' ')
  {
  str[k]=ch;
              k++;
  }
     else
  {
    for(i=0;i<k;i++)
    {
  e[i]=str[k-i-1]-48;
    }
     e[99]=k;
     k=0;
  }
 }
   for(i=0;i<k;i++)
  n[i]=str[k-i-1]-48;
  n[99]=k;
  printf("\n������Կ e : ");
  for(i=0;i<e[99];i++)
  printf("%d",e[e[99]-i-1]);
  printf("\n");
  printf("\n    ��Կ n : ");
  for(i=0;i<n[99];i++)
  printf("%d",n[n[99]-i-1]);
  printf("\n");
  fclose(fp);
  printf("\n����(e,n)�ɹ�!\n");
  getchar();
}

void loadskey(int d[100],int n[100],char *filename) //����˽Կ
{
 {
 FILE *fp;
 char str[100],ch;
 int i,k;
 for(i=0;i<100;i++)
  d[i]=n[i]=0;
 while(1)
 {
 //printf("Ϊ����(d,n)�������������Կ���ļ���·��: \n");
  //  scanf("%s",filename);
  if((fp=fopen(filename,"r"))==NULL)
  {
    printf("������ļ������ڣ�����������!\n");  
  }
  else break;
 }
  k=0;
  while((ch=fgetc(fp))!=EOF)
  { 
  if(ch!=' ')
  {
  str[k]=ch;
        k++;
  }
     else
  {
    for(i=0;i<k;i++)
    {
  d[i]=str[k-i-1]-48;
    }
     d[99]=k;
     k=0;
  }
 }
   for(i=0;i<k;i++)
      n[i]=str[k-i-1]-48;
  n[99]=k;
  printf("\n������Կ d : ");
  for(i=0;i<d[99];i++)
      printf("%d",d[d[99]-i-1]);
  printf("\n");
  printf("\n    ��Կ n : ");
  for(i=0;i<n[99];i++)
      printf("%d",n[n[99]-i-1]);
  printf("\n");
  fclose(fp);
  printf("\n����(d,n)�ɹ�!\n");
  getchar();
}
}

void savepkey(int e[100],int n[100],char *savefile)//������Կ
{
    FILE *fp;
  int  i;
 char ch;
 printf("����������Կ(e,n)����ŵ��ļ�·��Ϊ: ");
 //   scanf("%s",savefile);
 //printf("\n");
    fp=fopen(savefile,"w");
 for(i=0;i<e[99];i++)
 {
  ch=e[e[99]-i-1]+48;
  fputc(ch,fp);
 }
 ch=' ';
 fputc(ch,fp);
 for(i=0;i<n[99];i++)
 {
  ch=n[n[99]-i-1]+48;
  fputc(ch,fp);
 }
 fclose(fp);
 printf("\n����(e,n)�������!\n");
}

void saveskey(int d[100],int n[100],char *savefile)//����˽Կ
{
    FILE *fp;
  int  i;
 char  ch;
 //printf("����������Կ(d,n)����ŵ��ļ�·��Ϊ: ");
 //   scanf("%s",savefile);
// printf("\n");
    fp=fopen(savefile,"w");
 for(i=0;i<d[99];i++)
 {
  ch=d[d[99]-i-1]+48;
  fputc(ch,fp);
 }
 ch=' ';
 fputc(ch,fp);
 for(i=0;i<n[99];i++)
 {
  ch=n[n[99]-i-1]+48;
  fputc(ch,fp);
 }
 fclose(fp);
 printf("\n����(d,n)�������!\n");


}

//------------------------------------------���ܺͽ��ܵĿ�------------------------------------

void  printbig(struct rsan *h)
{
  struct rsan *p;
     int i;
  p=(struct rsan * )malloc(LENGTH);
  p=h;
   if(h!=NULL)
 do
 {
  for(i=0;i<p->num[99];i++)
        printf("%d",p->num[p->num[99]-i-1]);
        p=p->next;
 }

 while(p!=NULL);
    printf("\n\n");

 }

void  tencrypto(int e[100], int n[100],char *filename)/*//������Ҫ���ļ����м���*/
{
   FILE *fp;
    int i,k,count,temp,c;
   char ch,encryfile[25];
   struct rsan  *p,*p1,*p2;
   struct rsan  *h;
   h=p=p1=p2=(struct rsan * )malloc(LENGTH);
   h=NULL;
  // printf("\n������Ҫ���ܵ��ļ�·�� : ");
   //scanf("%s",filename);
   if((fp=fopen(filename,"r"))==NULL)
   {
    printf("Cannot open file !\n");
    exit(0);
   }
//printf("\n�ļ���ԭ�����ݣ�\n\n");
   count=0;
   while((ch=fgetc(fp))!=EOF)
   { 
    putchar(ch);
       c=ch;
       k=0;
 if(c<0)
 {
  c=abs(c);/*/�Ѹ���ȡ��������һ�����*/
  p1->num[98]='0';
 }
 else
 {
  p1->num[98]='1';
 }

 while(c/10!=0)
 {
  temp=c%10;
  c=c/10;
  p1->num[k]=temp;
  k++;
 }
 p1->num[k]=c;
    p1->num[99]=k+1;
 count=count+1;
 if(count==1)
  h=p1;
 else p2->next=p1;
 p2=p1;
    p1=(struct rsan * )malloc(LENGTH);
 }
    p2->next=NULL;
    printf("\n");
    fclose(fp);


   fp=fopen("EventHandle.txt","w");
   p=p1=(struct rsan * )malloc(LENGTH);
   p=h;
   printf("\n���ܺ��ļ������γ����ģ�\n\n");
   if(h!=NULL)
 do
 {
  expmod( p->num , e ,n ,p1->num);
  ch=p1->num[98];
  printf("%c",ch);
     fputc(ch,fp);
  if ((p1->num[99]/10) ==0)/*/�ж�p1->num[99]���Ƿ����ʮ��*/
  {
   ch=0+48;
   printf("%c",ch);
   fputc(ch,fp);
   ch=p1->num[99]+48;
   printf("%c",ch);
   fputc(ch,fp);
  }
  else
  {
   ch=p1->num[99]/10+48;
            printf("%c",ch);
   fputc(ch,fp);
   ch=p1->num[99]%10+48;
   printf("%c",ch);
   fputc(ch,fp);
  }

     for(i=0;i<p1->num[99];i++)
     {
   printf("%d",p1->num[i]);
         ch=p1->num[i]+48;
      fputc(ch,fp);
  }
     p=p->next;
  p1=(struct rsan * )malloc(LENGTH);
 }while(p!=NULL);
 printf("\n\n");
    fclose(fp);
 return;
}

void  tdecrypto(int d[100], int n[100],char *encryfile)
{
 
   FILE *fp;  
 struct rsan *h,*p1,*p2;
   char ch,decryfile[25];
    int i,j,k,c,count,temp;
  // printf("\n������ܹ����ļ�·�� : ");
  // scanf("%s",encryfile);
   if((fp=fopen(encryfile,"r"))==NULL)
   {
    printf("���ļ�������!\n");
    exit(0);
   }
   printf("\n�ļ����������ݣ�\n\n");
   i=0;
   j=3;
   count=0;
   h=p1=p2=(struct rsan * )malloc(LENGTH);
  
      while((ch=fgetc(fp))!=EOF)
   { 
    putchar(ch);
       c=ch;   
    if(j==3)
    {
    p1->num[98]=c;
    j--;
    }
    else if(j==2)
    {
     temp=c-48;
     j--;
    }
    else if(j==1)
    {
     p1->num[99]=temp*10+c-48;
     j--;
    }
    else if (j==0)
    {
      p1->num[i]=c-48;
         i++;
      if(i==p1->num[99])
     {
      i=0;
      j=3;
      count++;
         if (count==1)
      h=p1;
            else p2->next=p1;
            p2=p1;
               p1=(struct rsan * )malloc(LENGTH);
     }
    }
   }
  p2->next=NULL;
  printf("\n");
    fclose(fp);

 

   fp=fopen("EventHandle.txt","w");
 printf("\n�������ĺ��ļ��е�����:\n\n");
 p2=(struct rsan * )malloc(LENGTH);
    p1=h;
 k=0;
 if(h!=NULL)/*/tempΪ�ݴ�ASIIC���intֵ*/
   do
   {
    for(i=0;i<100;i++)
     p2->num[i]=0;
    expmod( p1->num , d ,n ,p2->num);   
    temp=p2->num[0]+p2->num[1]*10+p2->num[2]*100;
  if (( p2->num[98])=='0')
  {
   temp=0-temp;
  }/*/ת��Ϊ��ȷ��ASIIC�룬��-78-96�γɺ��� */ 
  ch=temp;/*  str[k]--->ch */
  printf("%c",ch);/*  str[k]--->ch */
  fputc(ch,fp);/*/д���ļ�str[k]--->ch*/
  k++;
     p1=p1->next;
  p2=(struct rsan * )malloc(LENGTH);
  }while (p1!=NULL);
     printf("\n\n");
        fclose(fp);
return;

}


/* struct rsan *input(char *ch1)//�������Ĳ��ҷ���ͷָ�룬û�м���ʱ��ת��������
{  
  struct  rsan *head;
  struct  rsan *p1,*p2;
     int  i,n,c,x,temp;
    char  ch;
     n=0;
	 x=0;
 p1=p2=(struct rsan * )malloc(LENGTH);
 head=NULL;
 printf("\n����������Ҫ��/���ܵ�����:\n");
 while((ch=ch1[x])!='#')
   {
	   x++;
 i=0;
 c=ch;
 if(c<0)
 {
  c=abs(c);//�Ѹ���ȡ��������һ�����
  p1->num[98]='0';
 }
    else
 {
  p1->num[98]='1';
 }
 while(c/10!=0)
 {
  temp=c%10;
  c=c/10;
  p1->num[i]=temp;
  i++;
 }
 p1->num[i]=c;
    p1->num[99]=i+1;
 n=n+1;
 if(n==1)
  head=p1;
 else p2->next=p1;
 p2=p1;
    p1=(struct rsan*)malloc(LENGTH);
 }
    p2->next=NULL;
	cout<<"oooooooooookkkkkkkkkkk"<<endl;
 return(head);
}
*/
 

int jiami(int  e[100],int  n[100],char* ch1, struct rsan  *h)
{
 int i,k,count,temp,c,x;
 int sum=0;
   char ch,encryfile[25];
   struct rsan  *p,*p1,*p2;
  
   x=0;
   p=p1=p2=h;
   h=NULL;
  // printf("\n������Ҫ���ܵ��ļ�·�� : ");
   //scanf("%s",filename);
   
printf("\nԭ�����ݣ�\n\n");
   count=0;
   while((ch=ch1[x])!='\0')
   { x++;
    putchar(ch);
       c=ch;
       k=0;
 if(c<0)
 {
  c=abs(c);/*/�Ѹ���ȡ��������һ�����*/
  p1->num[98]='0';
 }
 else
 {
  p1->num[98]='1';
 }

 while(c/10!=0)
 {
  temp=c%10;
  c=c/10;
  p1->num[k]=temp;
  k++;
 }
 p1->num[k]=c;
    p1->num[99]=k+1;
 count=count+1;
 if(count==1)
  h=p1;
 else p2->next=p1;
 p2=p1;
    p1=(struct rsan * )malloc(LENGTH);
 }
    p2->next=NULL;
    printf("\n");
 


  
   p=p1=(struct rsan * )malloc(LENGTH);
   p=h;
   printf("\n���ܺ��ļ������γ����ģ�\n\n");
   if(h!=NULL)
 do
 {
  expmod( p->num , e ,n ,p1->num);
  ch=p1->num[98];
  //printf("%c",ch);
     sum++;
  if ((p1->num[99]/10) ==0)/*/�ж�p1->num[99]���Ƿ����ʮ��*/
  {
   ch=0+48;
  // printf("%c",ch);
  sum++;
   ch=p1->num[99]+48;
 //  printf("%c",ch);
   sum++;

  }
  else
  {
   ch=p1->num[99]/10+48;
       //     printf("%c",ch);
			sum++;
   
   ch=p1->num[99]%10+48;
  // printf("%c",ch);
   sum++;
  
  }

     for(i=0;i<p1->num[99];i++)
     {
  // printf("%d",p1->num[i]);
   
         ch=p1->num[i]+48;
		 sum++;
   
  }
     p=p->next;
  p1=(struct rsan * )malloc(LENGTH);
 }while(p!=NULL);
 printf("ok\n");
   return sum;
 

   
}

int jiemi(int d[100],int n[100],char *ch1,struct  rsan *h)
{
    struct rsan *p1,*p2;
   char ch,decryfile[25];
    int i,j,k,c,count,temp;
	int x=0;
  // printf("\n������ܹ����ļ�·�� : ");
  // scanf("%s",encryfile);
  
   printf("\n�������ݣ�\n\n");
   i=0;
   j=3;
   count=0;
   p1=p2=h;
  
      while((ch=ch1[x])!='\0')
   { x++;
    putchar(ch);
       c=ch;   
    if(j==3)
    {
    p1->num[98]=c;
    j--;
    }
    else if(j==2)
    {
     temp=c-48;
     j--;
    }
    else if(j==1)
    {
     p1->num[99]=temp*10+c-48;
     j--;
    }
    else if (j==0)
    {
      p1->num[i]=c-48;
         i++;
      if(i==p1->num[99])
     {
      i=0;
      j=3;
      count++;
         if (count==1)
      h=p1;
            else p2->next=p1;
            p2=p1;
               p1=(struct rsan * )malloc(LENGTH);
     }
    }
   }
  p2->next=NULL;
  printf("\n");

  printf("\n�������ĺ��ļ��е�����:\n\n");
 p2=(struct rsan * )malloc(LENGTH);
    p1=h;
 k=0;
 if(h!=NULL)/*/tempΪ�ݴ�ASIIC���intֵ*/
   do
   {
    for(i=0;i<100;i++)
     p2->num[i]=0;
    expmod( p1->num , d ,n ,p2->num);   
    temp=p2->num[0]+p2->num[1]*10+p2->num[2]*100;
  if (( p2->num[98])=='0')
  {
   temp=0-temp;
  }/*/ת��Ϊ��ȷ��ASIIC�룬��-78-96�γɺ��� */ 
  ch=temp;/*  str[k]--->ch */
  printf("%c",ch);/*  str[k]--->ch */
   
  k++;
     p1=p1->next;
  p2=(struct rsan * )malloc(LENGTH);
  }while (p1!=NULL);
     printf("\n\n");
	 /*/tempΪ�ݴ�ASIIC���intֵ*/
  


    return k;
 }


void menu()

{
 printf("\n\n\n");
 printf("               1��������Կ��      \n\n");
 printf("               2��������Կ��      \n\n");
 printf("               3��������Կ��      \n\n");
 printf("               4�����ļ�����      \n\n");
 printf("               5�����ļ�����      \n\n");
 printf("               6���ַ�������        \n\n");
 printf("               7���ַ�������        \n\n");
 printf("               0���˳�            \n\n");
 printf("��ѡ��һ�ֲ�����");

}

};
