#include "stdafx.h"
using namespace std; 


int getResult(struct mysqlData* sqlDataCopy,int sum,const char*dbName)
{
	//���Ӳ�������connectionparams 
    char *host = "localhost"; 
    char *user = "root"; 
    char *pass = "123456";//���mysql���������� 
    char *db = "testdb"; //ʹ�õ����ݿ�
    unsigned int port = 3306; //server port  
	MYSQL *sock; 
    MYSQL_RES *res; 
    MYSQL_FIELD * fd; 
    MYSQL_ROW row; 
    char buffer1[500]=""; 
	int i; 

	sock=mysql_init(0);

    if(sock && mysql_real_connect(sock,host,user,pass,db,0,NULL,0)) 
    { //�������ݿ�
        printf("connect mysql succeed!\n");

        mysql_query(sock, "set names gb2312"); 

	}
    mysql_close(sock);//�Ͽ����� 
    return 0; 
}
