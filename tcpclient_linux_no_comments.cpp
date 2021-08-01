/*
 * @Description: 
 * @Author: dive668
 * @Date: 2021-08-01 19:52:27
 * @LastEditTime: 2021-08-01 19:57:48
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <stdarg.h>
#include <math.h>
#include <sys/termios.h>
#define MAXLINE 80
#define SERV_PORT 6666
int main(int argc,char *argv[])
{
    struct sockaddr_in servaddr; //定义通信进程的地址
    char buf[MAXLINE]; //定义缓冲区，用于存放数据
    int sockfd,n; //创建两个socket的文件描述符
    char var_temp[MAXLINE]; //定义用户字符输入
    if(argc!=4) //如果参数数量不为2，即没有带一个参数运行此程序
    {
        fputs("usage:./programname get current var_temp\n",stderr);
        exit(1);
    }
    else
    {
        printf("the number of the parameter is right!\n");
    }
    strcpy(var_temp,"get current var_temp"); 
    sockfd=socket(AF_INET,SOCK_STREAM,0);//地址类型为AF_INET，连接为TCP，采用默认协议
    bzero(&servaddr,sizeof(servaddr)); //结构体清零
    servaddr.sin_family=AF_INET; //设置地址类型为AF_INET
    inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);
    servaddr.sin_port=htons(SERV_PORT); //设置端口号为宏定义的端口SERV_PORT
    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    send(sockfd,var_temp,strlen(var_temp),0);
    n=recv(sockfd,buf,MAXLINE,0);
    if(strcmp(buf,"error!")==0)
    {
        printf("Response error from server\n");
        printf("exit...........:\n");
        exit(0);
    }
    else
    {
        printf("Response from server:\n");
        write(STDOUT_FILENO,buf,n);
        printf("\n");
        printf("%s\n",buf);
        close(sockfd);
    }
    return 0;
}