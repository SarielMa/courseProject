#include "fstream"
#include "string"
#include "stdlib.h"
using namespace std;

class PERMUTATION
{
public:
	int PERMUTATION_D;//√‹‘ød
	int *PERMUTATION_F;//√‹‘ø◊Èf
	int *PERMUTATION_TF;//Ω‚√‹√‹‘ø◊ÈTF
	string PER_Plaintext;
	string PER_DePlaintext;
	string PER_Ciphertext;

	void PERMUTATION_Init(int KEY[]);
	string PER_HANDLE_PLAINTEXT( string PER_PL );
	char *PER_HANDLE_CODE( string PER_STRING , int PER_ARRAY[] , int PER_ARRAY_LEN );
	void PER_FILE_INCODE(string plain_addr);
	void PER_FILE_DECODE(string cipher_addr);
};

void PERMUTATION::PERMUTATION_Init(int KEY[])
{
	int i;
	PERMUTATION_F = (int *)malloc(PERMUTATION_D * sizeof(int));
	PERMUTATION_TF = (int *)malloc(PERMUTATION_D * sizeof(int));

	for( i = 0 ; i < PERMUTATION_D ; i++ )
		PERMUTATION_F[i] = KEY[i];
	for( i = 0 ; i < PERMUTATION_D ; i++ )
		PERMUTATION_TF[i] = PERMUTATION_F[PERMUTATION_D - 1 - i];
}

string PERMUTATION::PER_HANDLE_PLAINTEXT( string PER_PL )
{
	string temp_plain;
	int per_D = PERMUTATION_D;
	int per_i;

	for( per_i = 0 ; per_i < PER_PL.length() ; per_i ++ )
		if( (PER_PL[per_i] <= 'z' && PER_PL[per_i] >= 'a') || (PER_PL[per_i] <= 'Z' && PER_PL[per_i] >= 'A'))//≥˝ø’∏Ò
			temp_plain += PER_PL[per_i];


	while( temp_plain.length() % per_D != 0 )
		temp_plain += 'x';

	return temp_plain;
}

char *PERMUTATION::PER_HANDLE_CODE( string PER_STRING , int PER_ARRAY[] , int PER_ARRAY_LEN )
{
	int per_plen = PER_STRING.length();
	int per_i = 0;
	int per_ring = 0;
	char *per_temp;

	per_temp = (char *)malloc(per_plen * sizeof(char));
	
	for( ; per_i < per_plen ; per_i ++)
	{
		per_ring = (per_i / PER_ARRAY_LEN) * PER_ARRAY_LEN ;
		per_temp[(PER_ARRAY[ per_i % PER_ARRAY_LEN] -1)+ per_ring] = PER_STRING[per_i] ;
	}

	per_temp[per_i] = '\0';

	return per_temp;
}

void PERMUTATION::PER_FILE_INCODE(string plain_addr)
{
	FILE *FILE_PLAIN;
	fstream FILE_CIPHER;

	FILE_PLAIN = fopen(plain_addr.c_str() , "r");
	FILE_CIPHER.open("EventHandle.txt", ios::out);

	while(	!feof(FILE_PLAIN) )
		PER_Plaintext += getc(FILE_PLAIN);

	PER_Plaintext = PER_HANDLE_PLAINTEXT(PER_Plaintext);
	PER_Ciphertext = PER_HANDLE_CODE( PER_Plaintext , PERMUTATION_F , PERMUTATION_D);

	FILE_CIPHER<<PER_Ciphertext;

	fclose(FILE_PLAIN);
	FILE_CIPHER.close();
}

void PERMUTATION::PER_FILE_DECODE(string cipher_addr)
{
	FILE *FILE_CIPHER;
	fstream FILE_PLAIN;
	
	FILE_CIPHER = fopen(cipher_addr.c_str() , "r");
	FILE_PLAIN.open("EventHandle.txt" , ios::out);

	while(	!feof(FILE_CIPHER) )
		PER_Ciphertext += getc(FILE_CIPHER);

	PER_DePlaintext = PER_HANDLE_CODE( PER_Ciphertext , PERMUTATION_TF , PERMUTATION_D);

	FILE_PLAIN<<PER_DePlaintext;

	fclose(FILE_CIPHER);
	FILE_PLAIN.close();
}