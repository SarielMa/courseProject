#include "iostream"
#include "string"
#include "fstream"
using namespace std;

class Playfair
{
public:
	string plaintext,ciphertext,table;

	string handlekey(string key);
	string createtable(string key);

	string keyboard_plain(string plaintext,string key);
	string keyboard_cipher(string ciphertext,string key);
	void file_plain(string plain_addr,string key);
	void file_cipher(string cipher_addr,string key);

	string encrypt(int choice,string table,string plaintext);
	string decrypt(int choice,string table,string ciphertext);

	string handle(int classs,int choice,string table,string handletext);
};

string Playfair::handlekey(string key)//删除key中的重复字符
{
	int i,j,k=0,m=0;
	i=0;
	while(key[i+1]!=NULL)
	{
		j=i+1;
		while(key[j+1]!=NULL)
		{
		    if(key[i]==key[j])
			    key.erase(j,1);
			else
				j++;
		}
		i++;
	}
	int len;
	len=key.length();
	for(i=0;i<len-1;i++)
	{
		if(key[len-1]==key[i])
		{
			key.erase(key.end()-1);
			break;
		}
	}
	
	return key;
}

string Playfair::createtable(string key)//建表
{
	string table1="abcdefghiklmnopqrstuvwxyz";
	int flag=0,flag2=0;
	int len=key.length();
	int j,i=0;
	while(table1[i]!=NULL)//字母表中有key中字母的删除
	{
		flag=0;
		for(j=0;j<key.length();j++)
			if(table1[i]==key[j])
			{
				flag=1;
				table1.erase(i,1);
				break;
			}
		if(flag==0)
			i++;
	}

	flag=0;

	table=key+table1;

	return table;
}

string Playfair::keyboard_plain(string plaintext,string key)
{
	key=handlekey(key);//删除key中的重复字符
	table=createtable(key);//建表

	ciphertext=encrypt(1,table,plaintext);

	return ciphertext;
}

void Playfair::file_plain(string plain_addr,string key)
{
	key=handlekey(key);//删除key中的重复字符
	table=createtable(key);//建表

	ifstream fin( plain_addr.c_str() ) ;
	if(fin.eof())
		exit(0);
	else
	{
		fflush(stdin);
		getline(fin,plaintext);
	}

	ciphertext=encrypt(2,table,plaintext);
}

string Playfair::encrypt(int choice,string table,string plaintext)//加密函数
{
	string table1="abcdefghijklmnopqrstuvwxyz";
	string table2="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	//对明文的前期处理
	int i,j,flag;
	i=0;
	while(plaintext[i+1]!=NULL)// 删除string中的非字母字符
	{
		flag=0;
		for(j=0;j<26;j++)
		{
			if(plaintext[i]==table2[j])
			{
				plaintext[i]=table1[j];
				flag=1;
				break;
			}
			if(plaintext[i]==table1[j])
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
			plaintext.erase(i,1);
		else
			i++;
	}
	i=plaintext.length()-1;
	flag=0;
	for(j=0;j<26;j++)
	{
		if(plaintext[i]==table2[j])
		{
			plaintext[i]=table1[j];
			flag=1;
			break;
		}
		if(plaintext[i]==table1[j])
		{
			flag=1;
			break;
		}
	}
	if(flag==0)
		plaintext.erase(plaintext.end()-1);


	for(i=0;i<plaintext.length();i++)//明文中有j换成i
	{
		if(plaintext[i]==table1[9])
			plaintext[i]=table1[8];
	}
	i=0;
	while(plaintext[i+1]!=NULL)//明文中有连续字符中间插入q
	{
		if(plaintext[i]==plaintext[i+1])
			plaintext.insert(i+1,"q");
		i++;
	}
	int len=plaintext.length();
	if(len%2==1)
	{
		if(plaintext[len-1]!='q')//明文字符数为奇数且明文最后一个字母不为q，最后插入一个字符q
			plaintext.insert(len,"q");
		else//若为q则插入字符x
			plaintext.insert(len,"x");
	}

	ciphertext=handle(choice,1,table,plaintext);


	return ciphertext;
}

string Playfair::keyboard_cipher(string ciphertext,string key)
{
	key=handlekey(key);//删除key中的重复字符
	table=createtable(key);//建表

	plaintext=decrypt(1,table,ciphertext);

	return plaintext;
}

void Playfair::file_cipher(string cipher_addr,string key)
{
	key=handlekey(key);//删除key中的重复字符
	table=createtable(key);//建表

	ifstream fin( cipher_addr.c_str() ) ;
	if(fin.eof())
		exit(0);
	else
	{
		fflush(stdin);
		getline(fin,ciphertext);
	}

	plaintext=decrypt(2,table,ciphertext);
}

string Playfair::decrypt(int choice,string table,string ciphertext)//解密函数
{
	plaintext=handle(choice,2,table,ciphertext);
	return plaintext;
}

string Playfair::handle(int classs,int choice,string table,string handletext)//对处理后的明文加密或对密文解密
{
	ofstream out( "EventHandle.txt" ) ;
    if ( !out )
		exit(0);   

	int t1,t2,t3,t4;
	int i,j;
	string text;//加密后的密文或解密后的明文
	for(i=0;i<handletext.length();i=i+2)
	{
		//寻找两字母在table中的位置
		for(j=0;j<25;j++)
		{
			if(handletext[i]==table[j])
			{
				t1=j/5;
				t2=j%5;
				break;
			}
		}

		for(j=0;j<25;j++)
		{
			if(handletext[i+1]==table[j])
			{
				t3=j/5;
				t4=j%5;
				break;
			}
		}

		//加密(或解密)
		if(t1==t3)
		{
			if(choice==1){
			    t1=t1*5+(t2+1)%5;
			    t3=t3*5+(t4+1)%5;
			    text+=table[t1];
				if(classs==2)
					out<<table[t1];
			    text+=table[t3];
				if(classs==2)
					out<<table[t3];
			}
			else
			{
				t1=t1*5+(t2+4)%5;
			    t3=t3*5+(t4+4)%5;
			    text+=table[t1];
			    text+=table[t3];
			}
		}
		else if(t2==t4)
		{
			if(choice==1){
				t2=((t1+1)%5)*5+t2;
				t4=((t3+1)%5)*5+t4;
				text+=table[t2];
				if(classs==2)
					out<<table[t2];
				text+=table[t4];
				if(classs==2)
					out<<table[t4];
			}
			else
			{
				t2=((t1+4)%5)*5+t2;
				t4=((t3+4)%5)*5+t4;
				text+=table[t2];
				text+=table[t4];
			}
		}
		else
		{
			text+=table[t1*5+t4];
			if(choice==1)
			    out<<table[t1*5+t4];
			text+=table[t3*5+t2];
			if(choice==1)
			    out<<table[t3*5+t2];
		}
	}
	if(choice==2)
	{
		string readytodelete="qx";//等效字母
		i=1;
		while(text[i+1]!=NULL)
		{
			if(text[i]==readytodelete[0]&&text[i-1]==text[i+1])
				text.erase(i,1);
			i++;
		}
		if(text[i]==readytodelete[1]||text[i]==readytodelete[0])
			text.erase(text.end()-1);
		if(classs==2)
			out<<text;
	}

	out.close();

	return text;
}