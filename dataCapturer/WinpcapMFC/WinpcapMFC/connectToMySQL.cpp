#include "stdafx.h"
using namespace std; 
int connectToMySQL(struct mysqlData* sqlDataCopy,int sum,const char*dbName)
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
        sprintf(buffer1, "create table %s (id int(4) ,network_layer char(6),transport_layer char(5),app_layer char(5),source_mac char(20),dest_mac char(20),source_ip varchar(18),dest_ip varchar(18),source_port int ,dest_port int)",dbName);// CHARACTER SET utf8");//构造SQL语句 新建一张表 
        

        if(mysql_query(sock,buffer1))//执行Dsql语句,并判断是否出错 
        { 
           // printf("Can't create table: %s \n",mysql_error(sock));

        }
		else
		{
			//printf("Create table datatable successed.\n"); 
		}
		int num=0;
		while(num<sum)
		{
			sprintf(buffer1,"insert into %s values(%d,'%s','%s','%s','%s','%s','%s','%s',%d,%d)",
				dbName,
				sqlDataCopy->count,
				sqlDataCopy->networkLayer,
				sqlDataCopy->transportLayer,
				sqlDataCopy->appLayer,
				sqlDataCopy->source_mac,
				sqlDataCopy->dest_mac,
				sqlDataCopy->source_ip,
				sqlDataCopy->dest_ip,
				sqlDataCopy->source_port,
				sqlDataCopy->dest_port				
				); //向datatable这个表插入数据 
			num++;
			sqlDataCopy++;
			if(mysql_query(sock, buffer1)) 
			{ 
				printf("Can't insert data to table %s.\n",mysql_error(sock)); 
				mysql_close( sock) ; 
				return -1 ; 
			} 
		}
		printf("Insert data to table complete.\n");

	}
    mysql_close(sock);//断开连接 
    return 0; 
}
