#include "string"
#include "fstream"
#include "stdlib.h"
using namespace std;

class VIGENERE
{
public:
	string plaintext;
	string key;
	string ciphertext;
	
	string Str_erase(string s);
	void INCODE();
	void DECODE();

	void FILE_INCODE(string plain_addr);
	void FILE_DECODE(string cipher_addr);

	~VIGENERE(){}
};

string VIGENERE::Str_erase(string s)
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

void VIGENERE::INCODE()
{
	int i,j;
	int pl=plaintext.length();
	int kl=key.length();
	for(i=0;i<pl;i++)
	{
		j=i%kl;
		if(plaintext[i]+key[j]-'a'>'z')
			ciphertext+='a'+(key[j]-'a'+plaintext[i]-'z'-1);
		else
			ciphertext+=key[j]-'a'+plaintext[i];
	}
}

void VIGENERE::DECODE()
{
	int i,j;
	int cl=ciphertext.length();
	int kl=key.length();
	for(i=0;i<cl;i++)
	{
		j=i%kl;
		if(ciphertext[i]<key[j])
			plaintext+='z'-key[j]+ciphertext[i]+1;
		else
			plaintext+=ciphertext[i]-key[j]+'a';
	}
}

void VIGENERE::FILE_INCODE(string plain_addr)
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

	FILE_CIPHER<<ciphertext;


	fclose(FILE_PLAIN);
	FILE_CIPHER.close();
}

void VIGENERE::FILE_DECODE(string cipher_addr)
{
	FILE *FILE_CIPHER;
	fstream FILE_PLAIN;
	
	FILE_CIPHER = fopen(cipher_addr.c_str() , "r");
	FILE_PLAIN.open("EventHandle.txt" , ios::out);

	while(	!feof(FILE_CIPHER) )
		ciphertext += getc(FILE_CIPHER);

	ciphertext = Str_erase(ciphertext);
	DECODE();

	FILE_PLAIN<<plaintext;

	fclose(FILE_CIPHER);
	FILE_PLAIN.close();
}