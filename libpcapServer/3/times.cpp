#include <time.h>
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

#define BACKLOG 10
#define Port 3331

int main()
{
   int      sock_fd,client_fd;
   time_t   now;
   int      Ret,res;
   int		n;
   socklen_t     sin_size;
   char		temp[100];
   char     buf[10];
   struct   sockaddr_in my_addr;
   struct   sockaddr_in remote_addr;
   struct   tm   *timenow;
   FILE     *out=fopen("IP-time","wb");

   if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0))   == -1)
   {
      perror("socket failed with error %d\n");
      exit(1);
   }
   my_addr.sin_family = AF_INET;//tcp/ip协议簇
   my_addr.sin_port = htons(Port);
   my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  // my_addr.sin_addr.s_addr = INADDR_ANY;

   bzero(&(my_addr.sin_zero),8);
  if(bind(sock_fd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))==-1)
{
     perror("Bind Error!");exit(1);
}
  if(listen(sock_fd,BACKLOG)==-1)
{
    perror("Listen Error!");
    exit(1);
}


  while(1)
     {
    sin_size = sizeof(struct sockaddr_in);

    if((client_fd=accept(sock_fd,(struct sockaddr *)&remote_addr,&sin_size))==-1)
            {
       perror("Accept Error!");
       continue;
            }
    printf("received a connetction from %s\n",inet_ntoa(my_addr.sin_addr));
    if(!fork())//申请进程
         {
        if((res=recv(client_fd,buf,10,0))==-1)
                 {
         perror("reciever error!");
         exit(1);
                   }
      if(*buf==0)
              {
        printf("Receive the request of current time from the clients!\n");

        now=time(NULL);
       timenow=localtime(&now);
        strcpy(temp,asctime(timenow));

        n=strlen(temp);
        printf("Local time is %s\n",temp);
        if ((Ret = send(client_fd, temp,  n , 0)) == -1)
                   {
           perror("Send Error!");
           exit(0);
                  }
        printf("Send %d byte(s).\n", Ret);

       printf("Store the information of requested IP~~~~\n\n");
       if(!out)
           printf("Write in error!");

       fprintf(out,"IP:%s",inet_ntoa(my_addr.sin_addr));
       fprintf(out,"\t\t\tTime:%s",temp);
       fputs("\n",out);
       printf("Store Sucess!\n\n");
            break;
            }
      }

close(client_fd);
    }


   printf("close.\n");







return 0;
}


