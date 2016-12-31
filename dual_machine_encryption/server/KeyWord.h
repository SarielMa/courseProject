#include "fstream"
#include "stdlib.h"
#include "string"
using namespace std;

typedef struct tagKeywordTable
{
	char p;
	char c;
}KeywordTable;


KeywordTable keyword_table[26];

class KEYWORD
{
public:
	string plaintext;
	string ciphertext;

	void KeyTable_INIT(char *in_key);

	string INCODE(string plain_txt);
	string DECODE(string cipher_txt);

	void FILE_INCODE(string plain_addr);
	void FILE_DECODE(string cipher_addr);

	~KEYWORD(){}
};

void KEYWORD::KeyTable_INIT(char *in_key)
{
	int i = 0, j, k;
	int char_count = 0, left_ch_index = 0;
	char ch, left_chs[26] = {0}, key[26] = {0};
	int key_len;
	strcpy (key, in_key);
	key_len = strlen (key);
	while (1)
	{
		if (key[i] == ' ')
		{
			for (j = i; j < key_len - 1; ++j)
				key[j] = key[j + 1];
			key_len--;
		}
		if (i == key_len)
			break;
		i++;
	}
	for (i = 0; i < 26; ++i)
	{
		ch = 'a' + i;
		j = 0;
		char_count = 0;
		while (1)
		{
			if (key[j] == ch)
			{
				char_count++;
				if (char_count > 1)
				{
					for (k = j; k < key_len -1; ++k)
						key[k] = key[k + 1];
					key_len--;
				}
				else
					j++;
			}
			else
				j++;
			if (j == key_len)
				break;
		}
		if (char_count == 0)
			left_chs[left_ch_index++] = ch;
	}

	for (i = 0; i < left_ch_index; ++i)
		key[key_len++] = left_chs[i];
	for (i = 0; i < 26; ++i)
	{
		keyword_table[i].p = 'a' + i;
		keyword_table[i].c = key[i];
	}
}

string KEYWORD::INCODE(string plain_txt)
{
	string cipher_txt;
	int length = plain_txt.length();
	int i;
	for (i = 0; i < length; ++i)
	{
		if (plain_txt[i] >= 'a' && plain_txt[i] <= 'z')
		{
			cipher_txt += keyword_table[plain_txt[i] - 'a'].c;
		}
		else if (plain_txt[i] >= 'A' && plain_txt[i] <= 'Z')
		{
			cipher_txt += keyword_table[plain_txt[i] - 'A'].c - 32;
		}
		else
			cipher_txt += plain_txt[i];
	}

	return cipher_txt;
}

string KEYWORD::DECODE(string cipher_txt)
{
	string plain_txt;
	int length =  cipher_txt.length();
	int i, j;
	for (i = 0; i < length; ++i)
	{
		if (cipher_txt[i] >= 'a' && cipher_txt[i] <= 'z')
		{
			for (j = 0; j < 26; ++j)
			{
				if (keyword_table[j].c == cipher_txt[i])
				{
					plain_txt += keyword_table[j].p;
					break;
				}
			}
		}
		else if (cipher_txt[i] >= 'A' && cipher_txt[i] <= 'Z')
		{
			for (j = 0; j < 26; ++j)
			{
				if (keyword_table[j].c == cipher_txt[i] + 32)
				{
					plain_txt += keyword_table[j].p - 32;
					break;
				}
			}

		}
		else
			plain_txt += cipher_txt[i];
	}
	
	return plain_txt;
}

void KEYWORD::FILE_INCODE(string plain_addr)
{
	FILE *FILE_PLAIN;
	fstream FILE_CIPHER;

	FILE_PLAIN = fopen(plain_addr.c_str() , "r");
	FILE_CIPHER.open("EventHandle.txt", ios::out);
	
	while(	!feof(FILE_PLAIN) )
	{
		plaintext += getc(FILE_PLAIN);
	}

	ciphertext = INCODE(plaintext);

	FILE_CIPHER<<ciphertext;

	fclose(FILE_PLAIN);
	FILE_CIPHER.close();
}

void KEYWORD::FILE_DECODE(string cipher_addr)
{
	FILE *FILE_CIPHER;
	fstream FILE_PLAIN;
	
	FILE_CIPHER = fopen(cipher_addr.c_str() , "r");
	FILE_PLAIN.open("EventHandle.txt" , ios::out);

	while(	!feof(FILE_CIPHER) )
		ciphertext += getc(FILE_CIPHER);

	plaintext = DECODE(ciphertext);

	FILE_PLAIN<<plaintext;

	fclose(FILE_CIPHER);
	FILE_PLAIN.close();
}