/*
 * @Description: 
 * @Author: dive668
 * @Date: 2021-07-29 09:22:52
 * @LastEditTime: 2021-11-09 15:35:59
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
    bzero(&servaddr,sizeof(servaddr)); //寝宫结构体
    servaddr.sin_family=AF_INET; 
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(SERV_PROT); 
    bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)); 
    listen(listenfd,20);
    printf("give the current var_temp:"); //初始服务器端存储的var_temp数据
    scanf("%d",&var_temp);
    printf("Accepting connections...\n");
    while(1)//循环服务器，实现监听多个客户端的请求
    {
        bzero(buf,MAXLINE); //清空缓冲区
        cliaddr_len=sizeof(cliaddr);
        connfd=accept(listenfd,(struct sockaddr *)&cliaddr,&cliaddr_len);
        n=recv(connfd,buf,MAXLINE,0); 
        if(strcmp(buf,"get")==0)//从客户端接收到get
        {
            printf("received get from %s at PORT %d\n",inet_ntop(AF_INET,&cliaddr.sin_addr,str,sizeof(str)),ntohs(cliaddr.sin_port));
            if(var_temp!=0)//var_temp值不为0，减一再发送
            {
                std::stringstream out;
                var_temp=var_temp-1;
                out<<var_temp;
                out>>temp_string;
                strcpy(buf,temp_string);
                send(connfd,buf,n,0); 
                close(connfd);
            }
            else//var_temp值为0，报错，不能在发送
            {
                printf("var_temp error!\n");
                std::stringstream out;
                out<<"error";
                out>>temp_string;
                strcpy(buf,temp_string); 
                send(connfd,buf,n,0); 
                close(connfd);
                break;
            }
        }
        else//从客户端接收到的不是get请求，输出其请求的buf内容
        {
            printf("received %s from %s at PORT %d\n",buf,inet_ntop(AF_INET,&cliaddr.sin_addr,str,sizeof(str)),ntohs(cliaddr.sin_port));
            send(connfd,buf,n,0); 
            close(connfd);
        }
    }
    return 0;
}