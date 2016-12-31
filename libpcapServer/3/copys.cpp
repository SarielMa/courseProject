#include<stdio.h>  
#include<unistd.h>  
#include<sys/stat.h>  
#include<fcntl.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include<arpa/inet.h>  
#include<time.h>  
#include<netdb.h>  
#include<stdlib.h>  
#include<string.h>  
#define PORT 1234  
#define BACKLOG 5  
 
struct user  
{  
    char name[20];  
    char passwd[20];  
}u,u1;  
int main()  
{  
        int listenfd, connectfd,num;  
        struct sockaddr_in server;  
        struct sockaddr_in client;  
        socklen_t addrlen;  
  
        char buf[32];  
        char dir[50];  

 
    FILE * fd;  
  
        if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)  
        {  
                perror("socket() error.");  
                return 0;  
        }  
  
        //int opt = SO_REUSEADDR;  
       // setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));  
        bzero(&server, sizeof(server));  
        server.sin_family = AF_INET;  
        server.sin_port = htons(PORT);  
        server.sin_addr.s_addr = htonl(INADDR_ANY);  
        if(bind(listenfd, (struct sockaddr *)&server, sizeof(server)) == -1)  
        {  
                perror("bind() error.");  
                return 0;  
  
        }  
        if(listen(listenfd, BACKLOG) == -1)  
        {  
                perror("listen() error.");  
                return 0;  
        }  
  
        addrlen = sizeof(client);  
        if((connectfd = accept(listenfd, (struct sockaddr *)&client, &addrlen )) == -1)  
        {  
                perror("accept() error.");  
                return 0;  
        }  
    else  
        printf("It's Connected\n");  
//  recv(connectfd,u1.name,20,0);  
//  recv(connectfd,u1.passwd,20,0);  
//  printf("%s",u1.name);  
 //   printf("Please input directory of copy\n");  
   // scanf("%s",dir);  
    fd=fopen("renetfile.txt","wb");  
    while(num=recv(connectfd,buf,1,0)>0)  
    {  
        fwrite(buf,1,num,fd);  
    }  
      
    fclose(fd);  
    close(connectfd);  
    return 1;  
}  
