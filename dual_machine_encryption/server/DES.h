#include "string"
#include "fstream"
#include "stdlib.h"
using namespace std;

class DES
{
public:
	string plaintext;
	string key;
	string deplaintext;
	string CIPHERTEXT;
	string deCipher;
	int ciphertext[64];
	int server_cph[64];
	//***密钥处理的相关变量声明***//
	int trkey[64];		//64位密钥存储数组
	int PC1_key[56];	//经过PC1块压缩后的密钥
	int C[28];
	int D[28];			//密钥拆分的两个数组
	int PC2_key[48];	//经过PC2块压缩后的密钥
	//***明文(密文)处理的相关变量声明***//
	int trplt[64];		//64位明文存储数组
	int L[32];
	int R[32];			//明文(密文)拆分的两个数组
	int E[48];
	int S[32];
	int P[32];			//明文(密文)经过E/S/P盒后的数组

	void Binary_change(string point);
	void PC_1();
	void Divide();
	void LeftShift(int temp);
	void RightShift(int temp);
	void PC_2();
	void Binary_plaintext();
	void Expermutation(int k[64]);
	void DivideLR(int temp[64]);
	void E_box();
	int ChgBinary(int a[],int length);
	void ChgDecimal(int temp[4],int hkey);
	void S_box();
	void P_box();
	void Permutation();

	void INCODE();
	void DECODE();
	void StringIncode();
	void StringDecode();
	void FileIncode(string plain_addr);
	void FileDecode(string cipher_addr);

	~DES(){}
};

//*********************密钥处理部分*********************//
//阶段1：生成64位密钥
void DES::Binary_change(string point)
{
	int i,j,k,count,flag;
	int ring=0;
	int temp[56]={0};
	int quotient,remainder;//商、余数
	for(count=0;count<7;count++)//将point串字符转换成二进制存入temp
	{
		i=0;
		quotient=point[count];
		while(quotient!=0)
		{
			remainder=quotient%2;
			quotient=quotient/2;
			temp[7-i+ring]=remainder;
			i++;
		}
		ring+=8;
	}
	for(j=0;j<8;j++)//奇校验密钥拓展成64位密钥存入trkey
	{
		flag=0;
		for(k=0;k<7;k++)
		{
			trkey[8*j+k]=temp[7*j+k];
			if(temp[7*j+k]==1)
				flag++;
		}
		if(flag%2==0)
			trkey[8*j+7]=1;
	}
}
//阶段2：PC1块的处理
void DES::PC_1()
{
	const int pc_1[56]={
		57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
		10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
		14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4};
	int i;
	for(i=0;i<56;i++)
		PC1_key[i]=trkey[pc_1[i]-1];
}
//阶段3：将密钥等分2份
void DES::Divide()
{
	int i=0;
	for(;i<56;i++)
	{
		if(i<28)
			C[i]=PC1_key[i];
		else
			D[i-28]=PC1_key[i];
	}
}
//阶段4：密钥子组循环左移
void DES::LeftShift(int temp)	//参数temp为左移的位数
{
	int i;
	int C1[28];
	int D1[28];
	for(i=0;i<28;i++)
	{
		C1[i]=C[i];
		D1[i]=D[i];
	}
	for(i=0;i<28;i++)
	{
		C[i]=C1[(i+temp)%28];
		D[i]=D1[(i+temp)%28];
	}
}
//密钥子组循环右移
void DES::RightShift(int temp)
{
	int i,z;
	int C1[28];
	int D1[28];
	for(i=0;i<28;i++)
	{
		C1[i]=C[i];
		D1[i]=D[i];
	}
	for(i=0;i<28;i++)
	{
		z=i-temp;
		if(z<0)
			z+=28;
		C[i]=C1[z%28];
		D[i]=D1[z%28];
	}
}
//阶段5：PC2块的处理
void DES::PC_2()
{
	const int pc_2[48]={
		14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
		23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
		41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
		44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};
	int temp[56];
	int i;
	for(i=0;i<56;i++)
	{
		if(i<28)
			temp[i]=C[i];
		else
			temp[i]=D[i-28];
	}
	for(i=0;i<48;i++)
		PC2_key[i]=temp[pc_2[i]-1];
}
//******************************************************//

//*********************明文处理部分*********************//
//阶段1：生成64位明文
void DES::Binary_plaintext()
{
	int i,count;
	int ring=0;
	int quotient,remainder;//商、余数
	for(count=0;count<64;count++)//置位
		trplt[count]=0;
	for(count=0;count<8;count++)
	{
		i=0;
		quotient=plaintext[count];
		while(quotient!=0)
		{
			remainder=quotient%2;
			quotient=quotient/2;
			trplt[7-i+ring]=remainder;
			i++;
		}
		ring+=8;
	}
}
//初始置换
void DES::Expermutation(int k[64])
{
	int i;
	int temp[64];
	const int IT[64]={
		58, 50, 42, 34, 26, 18, 10,  2,
		60, 52, 44, 36, 28, 20, 12,  4,
		62, 54, 46, 38, 30, 22, 14,  6,
		64, 56, 48, 40, 32, 24, 16,  8,
		57, 49, 41, 33, 25, 17,  9,  1,
		59, 51, 43, 35, 27, 19, 11,  3,
		61, 53, 45, 37, 29, 21, 13,  5,
		63, 55, 47, 39, 31, 23, 15,  7};
	for(i=0;i<64;i++)
		temp[i]=k[i];
	for(i=0;i<64;i++)
		k[i]=temp[IT[i]-1];
}
//阶段2：将明(密)文等分为2份
void DES::DivideLR(int temp[64])
{
	int i=0;
	for(;i<64;i++)
	{
		if(i<32)
			L[i]=temp[i];
		else
			R[i-32]=temp[i];
	}
}
//阶段3：E盒的拓展与异或操作
void DES::E_box()
{
	const int ebox[48]={
		32,  1,  2,  3,  4,  5,
		 4,  5,  6,  7,  8,  9,
		 8,  9, 10, 11, 12, 13,
		12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21,
		20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29,
		28, 29, 30, 31, 32,  1};
	int i;
	for(i=0;i<48;i++)
		E[i]=R[ebox[i]-1];
	for(i=0;i<48;i++)	//将明文与对应的密钥进行异或操作
		E[i]=(E[i]+PC2_key[i])%2;
}
//阶段4：S盒的操作
int DES::ChgBinary(int a[],int length)//将数组a转化为十进制数
{
	int result=a[0];
	for(int i=1;i<length;i++)
		result=result*2+a[i];
	return result;
}
void DES::ChgDecimal(int temp[4],int hkey)//将数key转化为二进制数存入temp数组
{
	int i=0;
	int quotient,remainder;
	quotient=hkey;
	while(quotient!=0&&i<4)
	{
		remainder=quotient%2;
		quotient=quotient/2;
		temp[3-i]=remainder;
		i++;
	}
}
void DES::S_box()
{
	const int S1[4][16]={
		{14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
		{ 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
		{ 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
		{15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}};
	const int S2[4][16]={
		{15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
		{ 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
		{ 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2,  5},
		{13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}};
	const int S3[4][16]={
		{10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
		{13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
		{13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
		{ 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}};
	const int S4[4][16]={
		{ 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
		{13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
		{10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
		{ 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}};
	const int S5[4][16]={
		{ 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
		{14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
		{ 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
		{11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}};
	const int S6[4][16]={
		{12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
		{10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
		{ 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
		{ 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}};
	const int S7[4][16]={
		{ 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
		{13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
		{ 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
		{ 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12}};
	const int S8[4][16]={
		{13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
		{ 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
		{ 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
		{ 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}};
	int column,row,index,i,j,k,result;
	int Co[2];
	int Ro[4];
	int temp[6];
	int flag[4]={0};
	const int *Sbox[8]; 
	Sbox[0]=&S1[0][0];Sbox[1]=&S2[0][0];Sbox[2]=&S3[0][0];Sbox[3]=&S4[0][0];
	Sbox[4]=&S5[0][0];Sbox[5]=&S6[0][0];Sbox[6]=&S7[0][0];Sbox[7]=&S8[0][0];
	i=0;k=0;
	while(i<48&&k<8)
	{
		for(j=0;j<6;j++)
			temp[j]=E[i+j];
		Co[0]=temp[0];Co[1]=temp[5];
		Ro[0]=temp[1];Ro[1]=temp[2];Ro[2]=temp[3];Ro[3]=temp[4];
		column=ChgBinary(Co,2);
		row=ChgBinary(Ro,4);
		index=column*16+row;
		result=*(Sbox[k]+index);
		ChgDecimal(flag,result);
		for(j=0;j<4;j++)
		{
			S[4*k+j]=flag[j];
			flag[j]=0;	//释放
		}
		i+=6;
		k++;
	}
}
//阶段5：P盒的操作
void DES::P_box()
{
	const int pbox[32]={
			16,  7, 20, 21,
			29, 12, 28, 17,
			 1, 15, 23, 26,
		 	 5, 18, 31, 10,
			 2,  8, 24, 14,
			32, 27,  3,  9,
			19, 13, 30,  6,
			22, 11,  4, 25};
	int i;
	for(i=0;i<32;i++)
		P[i]=S[pbox[i]-1];
	for(i=0;i<32;i++)	//将明文与对应的密钥进行异或操作
		P[i]=(P[i]+L[i])%2;
}
//******************************************************//

//加密最后一步：再次置换
void DES::Permutation()
{
	const int IT[64]={
		40,  8, 48, 16, 56, 24, 64, 32,
		39,  7, 47, 15, 55, 23, 63, 31,
		38,  6, 46, 14, 54, 22, 62, 30,
		37,  5, 45, 13, 53, 21, 61, 29,
		36,  4, 44, 12, 52, 20, 60, 28,
		35,  3, 43, 11, 51, 19, 59, 27,
		34,  2, 42, 10, 50, 18, 58, 26,
		33,  1, 41,  9, 49, 17, 57, 25};
	int temp[64];
	int i;
	for(i=0;i<64;i++)
		temp[i]=ciphertext[i];
	for(i=0;i<64;i++)
		ciphertext[i]=temp[IT[i]-1];
}

//加密总函数
void DES::INCODE()
{
	int i;
	int num=0;
	int temp[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
	Binary_change(key);
	PC_1();
	Divide();
	Binary_plaintext();
	Expermutation(trplt);
	DivideLR(trplt);
	while(num<16)
	{
		LeftShift(temp[num]);
		PC_2();
		E_box();
		S_box();
		P_box();
		for(i=0;i<32;i++)
		{
			L[i]=R[i];
			R[i]=P[i];
		}
		num++;
	}
	for(i=0;i<64;i++)
	{
		if(i<32)
			ciphertext[i]=R[i];	//加密最后一步需要左右对调
		else
			ciphertext[i]=L[i-32];
	}
	Permutation();

	for(i=0;i<64;i++)
		CIPHERTEXT += ciphertext[i] + '0';
}
//解密总函数
void DES::DECODE()
{
	int i,j;
	char c;
	int num=0;
	int temp[8];
	int extemp[16]={0,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
	Binary_change(key);
	PC_1();
	Divide();
	Expermutation(server_cph);
	DivideLR(server_cph);
	while(num<16)
	{
		RightShift(extemp[num]);
		PC_2();
		E_box();
		S_box();
		P_box();
		for(i=0;i<32;i++)
		{
			L[i]=R[i];
			R[i]=P[i];
		}
		num++;
	}
	for(i=0;i<64;i++)
	{
		if(i<32)
			ciphertext[i]=R[i];	//加密最后一步需要左右对调
		else
			ciphertext[i]=L[i-32];
	}
	Permutation();
	i=0;
	deplaintext="\0";
	while(i<64)
	{
		for(j=0;j<8;j++)
			temp[j]=ciphertext[i+j];
		c=ChgBinary(temp,8);
		deplaintext+=c;
		i+=8;
	}
	//cout<<"The plaintext is:"<<endl<<deplaintext<<endl;
}

void DES::StringIncode()
{
	INCODE();
}

void DES::StringDecode()
{
	int i;
	for(i=0;i<64;i++)
	{
		server_cph[i]=deCipher[i] - '0';
	}
	DECODE();
}

void DES::FileIncode(string plain_addr)
{
	FILE *FILE_PLAIN;
	fstream FILE_CIPHER;

	FILE_PLAIN = fopen(plain_addr.c_str() , "r");
	FILE_CIPHER.open("EventHandle.txt", ios::out);

	while(	!feof(FILE_PLAIN) )
	{
		plaintext += getc(FILE_PLAIN);
	}
	
	INCODE();

	FILE_CIPHER<<CIPHERTEXT;


	fclose(FILE_PLAIN);
	FILE_CIPHER.close();
}

void DES::FileDecode(string cipher_addr)
{
	FILE *FILE_CIPHER;
	fstream FILE_PLAIN;
	
	FILE_CIPHER = fopen(cipher_addr.c_str() , "r");
	FILE_PLAIN.open("EventHandle.txt" , ios::out);

	while(	!feof(FILE_CIPHER) )
		deCipher += getc(FILE_CIPHER);

	StringDecode();

	FILE_PLAIN<<deplaintext;

	fclose(FILE_CIPHER);
	FILE_PLAIN.close();
}