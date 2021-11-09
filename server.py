# coding=utf-8
import threading
import socket
serverfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)# 创建 socket 对象,选择 AF_INET 的目的就是使用 IPv4 进行通信,SOCK_STREAM提供面向连接的稳定数据传输
#ip_port = ("127.0.0.1", 1600)# 仅接收来自127.0.0.1的请求
ip_port = ("", 1600)# 可以接收请求和自己的静态ip连接的请求

serverfd.bind(ip_port)# 绑定端口
serverfd.listen(5)
try:
    connection, address = serverfd.accept()# 建立客户端连接
except Exception as e:
    print(e)
    exit(0)
print("%s 已连接" % address[0])
connection.send('hello'.encode())
isok = True
def receieve(connection):
    global isok
    while isok:
        try:
            recv_data = str(connection.recv(1024), encoding="utf-8")
            if recv_data == 'exit':
                isok = False
                print("Exit......")
                serverfd.close()
                exit(0) #子线程退出，然而父进程没有退出
            elif recv_data=="":
                print("client is not ready")
            else:
                print("receieve from client:{}".format(recv_data))
        except Exception as e:
            print(e)
            exit(0)
thread = threading.Thread(target=receieve, args=(connection,))
thread.start() #被创建的线程一直在while循环接收消息

while isok:#父线程一直在发送消息
    send_d = input("server>")
    try:
        connection.sendall(bytes(send_d, encoding='utf-8'))
        if send_d == 'exit':
            isok = False
    except Exception as e:
        print(e)
        exit(0)
serverfd.close()
