#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <netdb.h>

#define Port 3331


int main()
{
   int sock_fd,recvbytes;
  
   int       Ret;
   int	     n;
   int      sin_size;
   char     buf[100];
   char     buffer[10];
   struct   hostent *host; 
   struct   sockaddr_in serv_addr;
   if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0))   == -1)
   {
      perror("socket failed with error \n");
      exit(1);
   }
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(Port);    
   serv_addr.sin_addr.s_addr =inet_addr("127.0.0.1");
   bzero(&(serv_addr.sin_zero),8);

   printf("Prepare connecting %s:%d...\n",inet_ntoa(serv_addr.sin_addr), htons(serv_addr.sin_port));
   if(connect(sock_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr))==-1)
     {
     perror("connect error!");
     exit(1);
       }
    printf("Connect Success!\n\n");
    printf("Send the request of the current time!\n\n");
    *buffer=0;
    if ((Ret = send(sock_fd, buffer  ,10 , 0)) == -1)
        {   
      perror("Send Error!");
      exit(0);
        }      
   if((recvbytes=recv(sock_fd,buf,100,0))==-1)
{
    perror("reciever error!");
    exit(1);
 }
    buf[recvbytes]='\0';
    printf("Recieved: %s\n",buf);
close(sock_fd);
return 0;
}

