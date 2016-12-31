#include "stdafx.h"
using namespace std; 


int getResult(struct mysqlData* sqlDataCopy,int sum,const char*dbName)
{
	//连接参数设置connectionparams 
    char *host = "localhost"; 
    char *user = "root"; 
    char *pass = "123456";//你的mysql服务器密码 
    char *db = "testdb"; //使用的数据库
    unsigned int port = 3306; //server port  
	MYSQL *sock; 
    MYSQL_RES *res; 
    MYSQL_FIELD * fd; 
    MYSQL_ROW row; 
    char buffer1[500]=""; 
	int i; 

	sock=mysql_init(0);

    if(sock && mysql_real_connect(sock,host,user,pass,db,0,NULL,0)) 
    { //连接数据库
        printf("connect mysql succeed!\n");

        mysql_query(sock, "set names gb2312"); 

	}
    mysql_close(sock);//断开连接 
    return 0; 
}
