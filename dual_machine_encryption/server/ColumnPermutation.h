#include "string"
#include "fstream"
#include "stdlib.h"
using namespace std;

class COLUMN_PERMUTATION
{
public:
	string plaintext;
	string key;
	string CIPHERTEXT;
	string PLAINTEXT;
	string deciphertext;
	char **ciphertext;
	char **deplaintext;
	int *keytemp;

	string Str_erase(string s);//清除字符串当中的空格
	void operatekey();
	void INCODE();
	void DECODE();
	void FILE_INCODE(string plain_addr);
	void FILE_DECODE(string cipher_addr);

	~COLUMN_PERMUTATION(){}
};

string COLUMN_PERMUTATION::Str_erase(string s)
{
	int i = 0;
	for(;i<s.length();i++)
	{
		if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
			continue;
		else
			s.erase(i , 1);
	}
	return s;
}

void COLUMN_PERMUTATION::operatekey()
{
	int i,j;
	int l=key.length();
	keytemp=new(int [l]);
	for(i=0;i<l;i++)
		keytemp[i]=0;
	for(i=0;i<l;i++)
		for(j=0;j<l;j++)
		{
			if(i==j)
				continue;
			if(key[i]>key[j])
				keytemp[i]++;
		}
}

void COLUMN_PERMUTATION::INCODE()
{
	int pl=plaintext.length();
	int kl=key.length();
	int hl=pl/kl;
	int i,j,k,temp,pm=0;
	temp=pl%kl;
	if(temp!=0)
		hl++;
	operatekey();
	ciphertext=new(char *[hl]);
	for(i=0;i<hl;i++)
	{
		ciphertext[i]=new(char [kl]);
		for(j=0;j<kl;j++,pm++)
		{	
			if(plaintext[pm]!=NULL)
				ciphertext[i][j]=plaintext[pm];
			else
				ciphertext[i][j]='q';
		}
	}
	for(k=0;k<kl;k++)
	{
		for(i=0;i<hl;i++)
			for(j=0;j<kl;j++)
				if(j==keytemp[k])
				{
					CIPHERTEXT += ciphertext[i][j];
					break;
				}
	}
}

void COLUMN_PERMUTATION::DECODE()
{
	operatekey();
	int cl=deciphertext.length();
	int kl=key.length();	//矩阵列数
	int hl=cl/kl;	//矩阵行数
	int i,j,k,pm=0;
	deplaintext=new(char *[hl]);	//动态二维数组申请空间
	for(i=0;i<hl;i++)
		deplaintext[i]=new(char [kl]);
	for(k=0;k<kl;k++)
		for(i=0;i<kl;i++)	
			if(i==keytemp[k])
			{
				for(j=0;j<hl;j++,pm++)
				{
					if(deciphertext[pm]!=NULL)
						deplaintext[j][i]=deciphertext[pm];
				}
				break;
			}
	for(i=0;i<hl;i++)
		for(j=0;j<kl;j++)
			PLAINTEXT += deplaintext[i][j];
}

void COLUMN_PERMUTATION::FILE_INCODE(string plain_addr)
{
	FILE *FILE_PLAIN;
	fstream FILE_CIPHER;

	FILE_PLAIN = fopen(plain_addr.c_str() , "r");
	FILE_CIPHER.open("EventHandle.txt", ios::out);

	while(	!feof(FILE_PLAIN) )
	{
		plaintext += getc(FILE_PLAIN);
	}
	
	plaintext = Str_erase(plaintext);
	INCODE();

	FILE_CIPHER<<CIPHERTEXT;

	fclose(FILE_PLAIN);
	FILE_CIPHER.close();
}

void COLUMN_PERMUTATION::FILE_DECODE(string cipher_addr)
{
	FILE *FILE_CIPHER;
	fstream FILE_PLAIN;
	
	FILE_CIPHER = fopen(cipher_addr.c_str() , "r");
	FILE_PLAIN.open("EventHandle.txt" , ios::out);

	while(	!feof(FILE_CIPHER) )
		deciphertext += getc(FILE_CIPHER);

	deciphertext = Str_erase(deciphertext);
	DECODE();

	FILE_PLAIN<<PLAINTEXT;

	fclose(FILE_CIPHER);
	FILE_PLAIN.close();
}