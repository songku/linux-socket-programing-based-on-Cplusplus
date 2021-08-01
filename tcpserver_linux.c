/*
 * @Description: 
 * @Author: dive668
 * @Date: 2021-07-29 09:22:52
 * @LastEditTime: 2021-08-01 19:40:39
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/termios.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <string>
#include <iostream>
#include <sstream>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <memory.h>
#include <stdarg.h>
#include <math.h>
#define MAXLINE 80
#define SERV_PROT 6666
#define INET_ADDRSTRLEN 16
using namespace std;
int main(void)
{
    std::stringstream out;
    struct sockaddr_in servaddr,cliaddr; //定义通信进程的地址
    socklen_t cliaddr_len; //定义addr的长度
    int listenfd,connfd; //创建两个socket的文件描述符
    char buf[MAXLINE]; 
    char str[INET_ADDRSTRLEN];
    int i,n,var_temp=0;
    char temp_string[MAXLINE];
    listenfd=socket(AF_INET,SOCK_STREAM,0); 
    bzero(&servaddr,sizeof(servaddr)); 
    servaddr.sin_family=AF_INET; 
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(SERV_PROT); 
    bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)); 
    listen(listenfd,20);
    printf("give the current var_temp:");
    scanf("%d",&var_temp);
    printf("Accepting connections...\n");
    while(1)
    {
        cliaddr_len=sizeof(cliaddr);
        connfd=accept(listenfd,(struct sockaddr *)&cliaddr,&cliaddr_len);
        n=recv(connfd,buf,MAXLINE,0); 
        printf("received from %s at PORT %d\n",inet_ntop(AF_INET,&cliaddr.sin_addr,str,sizeof(str)),ntohs(cliaddr.sin_port));
        if(strcmp(buf,"get current var_temp")==0)//strcmp字符串比较
        {
            if(var_temp!=0)
                {
                    std::stringstream out;
                    var_temp=var_temp-1;
                    out<<var_temp;
                    out>>temp_string;
                    strcpy(buf,temp_string);
                }
            else
                {
                    strcpy(buf,"error!"); 
                    break;
                }
        }
        else
        {
            printf("Haven't receive get current var_temp");
        }
        send(connfd,buf,n,0); 
        close(connfd);
    }
    return 0;
}