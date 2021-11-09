/*
 * @Description: 
 * @Author: dive668
 * @Date: 2021-07-28 22:39:28
 * @LastEditTime: 2021-11-09 15:22:22
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
    if(argc!=2) //如果参数数量不为2，即没有带一个参数运行此程序
    {
        fputs("usage:./programname get\n",stderr);
        exit(1);
    }
    else
    {
        printf("the number of the parameter is right!\n");
    }
    strcpy(var_temp,argv[1]); 
    sockfd=socket(AF_INET,SOCK_STREAM,0);//地址类型为AF_INET，连接为TCP，采用默认协议
    //用于打开网络通讯端口，调用成功则返回一个文件描述符，调用失败则返回-1
    bzero(&servaddr,sizeof(servaddr)); //结构体清零
    servaddr.sin_family=AF_INET; //设置地址类型为AF_INET
    inet_pton(AF_INET,"192.168.17.139",&servaddr.sin_addr);
    servaddr.sin_port=htons(SERV_PORT); //设置端口号为宏定义的端口SERV_PORT
    if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))==-1)
    {
        printf("connect error\n");
        exit(0);
    }
    //用于客服端，向服务器端发送请求，类似于bind,调用成功则返回0，否则返回-1
    if(send(sockfd,var_temp,strlen(var_temp),0)<0)
    {
        printf("send message error: %s errno : %d\n",strerror(errno),errno);
        exit(0);
    }
    //向处于连接状态的套接字中发送数据
    //connfd为接收端的socket⽂件描述符
    //buf为要发送的缓冲区中的数据长度
    //flag表示调用的执行方式，设为0则可用write代替send函数
    bzero(buf,MAXLINE); //清空缓冲区
    n=recv(sockfd,buf,MAXLINE,0);
    if(strcmp(buf,"error!")==0)
    //如果buf收到的是error!
    {
        printf("Response error from server\n");
        printf("exit...........:\n");
        exit(0);
    }
    else //从已连接的套接字中接收信息，若调用成功则返回读到的字节数
    {
        printf("Response from server:");//write把buf指定的内存写入n个字节，放入到指定的socket文件内
        write(STDOUT_FILENO,buf,n);
        printf("\n");
        printf("%s\n",buf);
        close(sockfd);
    }
    return 0;
}