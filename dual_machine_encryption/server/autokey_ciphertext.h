#include "iostream"
#include "string"
#include "fstream"
using namespace std;

class Autokey_ciphertext
{
public:
	string plaintext,ciphertext;

	string keyboard_encrypt(string plaintext,string key);
	void file_encrypt(string plain_addr,string key);
	string keyboard_decrypt(string ciphertext,string key);
	void file_decrypt(string cipher_addr,string key);

	string handle(string text);
};

string Autokey_ciphertext::keyboard_encrypt(string plaintext,string key)//����
{
	plaintext=handle(plaintext);

	string tableA="abcdefghijklmnopqrstuvwxyz";//��ĸ��
	string tableB="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i;
	int k=0;//ijk��Ϊ����
	string tempkey=key;
	int t1,t2;//����Ѱ��λ��

	for(i=0;i<plaintext.length();i++)
	{
		for(t1=0;t1<26;t1++)
		{
			if(tableA[t1]==plaintext[i]||tableB[t1]==plaintext[i])
				break;
		}
		for(t2=0;t2<26;t2++)
		{
			if(tableA[t2]==tempkey[i%key.length()] || tableB[t2]==tempkey[i%key.length()])
				break;
		}
		tempkey[i%key.length()]=tableA[(t1+t2)%26];
		ciphertext+=tableA[(t1+t2)%26];
	}
	
	return ciphertext;
}

string Autokey_ciphertext::keyboard_decrypt(string ciphertext,string key)//����
{
	ciphertext=handle(ciphertext);

	string tableA="abcdefghijklmnopqrstuvwxyz";//��ĸ��
	string tableB="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i;
	int k=0;//ijk��Ϊ����
	string plaintext;
	string tempkey=key;
	int t1,t2;//����Ѱ��λ��

	for(i=0;i<ciphertext.length();i++)
	{
		for(t1=0;t1<26;t1++)
		{
			if(tableA[t1]==ciphertext[i] || tableB[t1]==ciphertext[i])
				break;
		}
		for(t2=0;t2<26;t2++)
		{
			if(tableA[t2]==tempkey[i%key.length()] || tableB[t2]==tempkey[i%key.length()])
				break;
		}
		tempkey[i%key.length()]=ciphertext[i];
		plaintext+=tableA[(t1-t2+26)%26];
	}
	
	return plaintext;
}

void Autokey_ciphertext::file_encrypt(string plain_addr,string key)//����
{
	ifstream fin( plain_addr.c_str() ) ;
	if(fin.eof())
		exit(0);
	else
	{
		fflush(stdin);
		getline(fin,plaintext);
	}

	plaintext=handle(plaintext);

	string tableA="abcdefghijklmnopqrstuvwxyz";//��ĸ��
	string tableB="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i;
	int k=0;//ijk��Ϊ����
	string tempkey=key;
	int t1,t2;//����Ѱ��λ��
	ofstream out( "EventHandle.txt" ) ;
    if ( !out )
		exit(0) ; 

	for(i=0;i<plaintext.length();i++)
	{
		for(t1=0;t1<26;t1++)
		{
			if(tableA[t1]==plaintext[i]||tableB[t1]==plaintext[i])
				break;
		}
		for(t2=0;t2<26;t2++)
		{
			if(tableA[t2]==tempkey[i%key.length()] || tableB[t2]==tempkey[i%key.length()])
				break;
		}
		tempkey[i%key.length()]=tableA[(t1+t2)%26];
		ciphertext+=tableA[(t1+t2)%26];
		out<<tableA[(t1+t2)%26];
	}
	out.close();	
}

void Autokey_ciphertext::file_decrypt(string cipher_addr,string key)//����
{
	ifstream fin( cipher_addr.c_str() ) ;
	if(fin.eof())
		exit(0);
	else
	{
		fflush(stdin);
		getline(fin,ciphertext);
	}

	ciphertext=handle(ciphertext);

	string tableA="abcdefghijklmnopqrstuvwxyz";//��ĸ��
	string tableB="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i;
	int k=0;//ijk��Ϊ����
	string tempkey=key;
	int t1,t2;//����Ѱ��λ��
	ofstream out( "EventHandle.txt" ) ;
    if ( !out )
		exit(0) ;

	for(i=0;i<ciphertext.length();i++)
	{
		for(t1=0;t1<26;t1++)
		{
			if(tableA[t1]==ciphertext[i] || tableB[t1]==ciphertext[i])
				break;
		}
		for(t2=0;t2<26;t2++)
		{
			if(tableA[t2]==tempkey[i%key.length()] || tableB[t2]==tempkey[i%key.length()])
				break;
		}
		tempkey[i%key.length()]=ciphertext[i];
		plaintext+=tableA[(t1-t2+26)%26];
		out<<tableA[(t1-t2+26)%26];
	}
	out.close();

}

string Autokey_ciphertext::handle(string text)//ɾ�����Ļ������еķ���ĸ�ַ�
{
	//ȥ������ĸ�ַ�
	string table1="abcdefghijklmnopqrstuvwxyz";
	string table2="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i,j,flag;
	i=0;
	while(text[i+1]!=NULL)// ɾ��string�еķ���ĸ�ַ�
	{
		flag=0;
		for(j=0;j<26;j++)
		{
			if(text[i]==table2[j])
			{
				text[i]=table1[j];
				flag=1;
				break;
			}
			if(text[i]==table1[j])
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
			text.erase(i,1);
		else
			i++;
	}
	i=text.length()-1;
	flag=0;
	for(j=0;j<26;j++)
	{
		if(text[i]==table2[j])
		{
			text[i]=table1[j];
			flag=1;
			break;
		}
		if(text[i]==table1[j])
		{
			flag=1;
			break;
		}
	}
	if(flag==0)
		text.erase(text.end()-1);

	return text;
}