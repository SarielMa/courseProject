#include "string"
#include "stdio.h"
#include "stdlib.h"
using namespace std;

class RC_FOUR
{
public:
	string plaintext;
	string ciphertext;
	string deplaintext;
	string key;

	char S[256];//S组
	char K[256];//K组
	int i;
	int j;

	void swap(char *s, int rci, int rcj);
	void RC4_KSA(string rc_key, int key_length);	//初始化S/K数组
	char RC4_PRGA();

	void FILE_INCODE(string plain_addr);
	void FILE_DECODE(string cipher_addr);

	~RC_FOUR(){}
};

void RC_FOUR::swap(char *s, int rci, int rcj)
{
	char temp = s[rci];
    s[rci] = s[rcj];
    s[rcj] = temp;
}

void RC_FOUR::RC4_KSA(string rc_key, int key_length)
{
	for (i = 0; i < 256; i++)
	{
        S[i] = i;
		K[i] = rc_key[i % key_length];
	}

    for (i = j = 0; i < 256; i++) 
	{
        j = (j + K[i] + S[i]) % 256;
		if(j < 0)
			j = j+256;
        swap(S, i, j);
    }
 
    i = j = 0;
}

char RC_FOUR::RC4_PRGA()
{
	i = (i + 1) % 256;
    j = (j + S[i]) % 256;
	if(j < 0)
		j = j+256;
    swap(S, i, j);
 
    return S[(S[i] + S[j] + 256) % 256];
}

void RC_FOUR::FILE_INCODE(string plain_addr)
{
	FILE *PLAIN;
	FILE *CIPHER;
	int y;
	char temp;
	
	PLAIN = fopen(plain_addr.c_str() , "rb");
	CIPHER = fopen("EventHandle.txt" , "wb");
	while(	!feof(PLAIN) )
		plaintext += getc(PLAIN);
	i = j = 0;
	RC4_KSA(key,key.length());

	for(y=0; y<plaintext.length();y++)
	{
		temp = RC4_PRGA();
		ciphertext +=plaintext[y] ^ temp;
	}

	fprintf(CIPHER , "%s" , ciphertext.c_str());

	fclose(PLAIN);
	fclose(CIPHER);

}

void RC_FOUR::FILE_DECODE(string cipher_addr)
{
	FILE *k;
	FILE *p;
	int y;
	char temp;

	k = fopen(cipher_addr.c_str() , "rb");
	p = fopen("EventHandle.txt" , "wb");

	while(!feof(k))
		ciphertext += getc(k);
	i = j = 0;
	RC4_KSA(key,key.length());
	for(y=0; y<ciphertext.length();y++)
	{
		temp = RC4_PRGA();
		deplaintext+=ciphertext[y] ^ temp;
	}

	fprintf(p , "%s" , deplaintext.c_str());
	fclose(k);
	fclose(p);
}