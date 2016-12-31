#include "string"
#include "fstream"
#include "stdlib.h"
using namespace std;

class CAESAR
{
public:
	string plaintext;
	string ciphertext;
	
	string INCODE(string pl , int kl);
	string DECODE(string ci , int kl);

	void FILE_INCODE(string plain_addr , int kl);
	void FILE_DECODE(string cipher_addr , int kl);

	~CAESAR(){}
};

string CAESAR::INCODE(string pl , int kl)
{
	string a = pl;
	int k = kl;
	for(int i=0;i<a.length();i++)
	{
		if('a'<=a[i] && a[i]<='z')
			a[i]=('a'+(a[i]-'a'+(k%26)+26)%26);
		else if('A'<=a[i] && a[i]<='Z')
			a[i]=('A'+(a[i]-'A'+(k%26)+26)%26);
	}
	return a;
}

string CAESAR::DECODE(string ci , int kl)
{
	string a = ci;
	int k = kl;
	for(int i=0;i<a.length();i++)
	{
		if('a'<=a[i] && a[i]<='z')
			a[i]='a'+(a[i]-'a'-(k%26)+26)%26;
		else if('A'<=a[i] && a[i]<='Z')
			a[i]=('A'+(a[i]-'A'-(k%26)+26)%26);
	}
	return a;
}

void CAESAR::FILE_INCODE(string plain_addr , int kl)
{
	FILE *FILE_PLAIN;
	fstream FILE_CIPHER;

	FILE_PLAIN = fopen(plain_addr.c_str() , "r");
	FILE_CIPHER.open("EventHandle.txt", ios::out);

	while(	!feof(FILE_PLAIN) )
	{
		plaintext += getc(FILE_PLAIN);
	}
	
	ciphertext = INCODE(plaintext , kl);

	FILE_CIPHER<<ciphertext;


	fclose(FILE_PLAIN);
	FILE_CIPHER.close();
}

void CAESAR::FILE_DECODE(string cipher_addr , int kl)
{
	FILE *FILE_CIPHER;
	fstream FILE_PLAIN;
	
	FILE_CIPHER = fopen(cipher_addr.c_str() , "r");
	FILE_PLAIN.open("EventHandle.txt" , ios::out);

	while(	!feof(FILE_CIPHER) )
		ciphertext += getc(FILE_CIPHER);

	plaintext = DECODE(ciphertext , kl);

	FILE_PLAIN<<plaintext;

	fclose(FILE_CIPHER);
	FILE_PLAIN.close();
}