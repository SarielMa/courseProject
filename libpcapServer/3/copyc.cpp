#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#define PORT 1234   /*listen port*/
#define MAXSIZE 32
struct user
{
    char name[20];
    char passwd[20];
}u;
int main ( )
{
        int sockfd,num;
        struct hostent *he;
        struct sockaddr_in server;

    char buf[MAXSIZE];
    char dir[50];

    FILE *fd;
        
         /*get ip address*/
        if((he = gethostbyname("localhost")) == NULL)
        {
                printf("gethostbyname error\n");
                return 0;

        }
        if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
                printf("socket() error \n");
                return 0;
        }
        bzero(&server, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(PORT);
        server.sin_addr = *((struct in_addr *)he->h_addr);

        if(connect(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1)
        {
                printf("connetc() error\n");
                return 0;
        }


    printf("connect success.\n");
    printf("Please input your name:");

   // printf("Please input file's directory\n");
   // scanf("%s",dir);
    fd = fopen("netfile.txt","rb");

    while((num=fread(buf,1,MAXSIZE,fd))>0)
    {
        send(sockfd,buf,num,0);
    }
    fclose(fd);
    close(sockfd);
    return 1;
}

