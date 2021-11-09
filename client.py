# coding=utf-8
import threading
import socket
ip=input("input the ip addr you want to connect:")
clientfd = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
ip_port = (ip, 1600)# 设置端口
clientfd.connect(ip_port)# 方法打开一个 TCP 连接到主机
isok = True
def receieve(clientfd):
    global isok
    while isok:
        try:
            t = clientfd.recv(1024).decode("utf8")  # 客户端也同理
            if t == "exit":
                isok = False
                print("Exit......")
                clientfd.close()
                exit(0) #子线程退出，父线程依然在运行
            else:
                print("receieve form server:{}".format(t))
        except Exception as e:
            print(e)
            exit(0)
thread = threading.Thread(target=receieve, args=(clientfd,))
thread.start()#被创建的线程，一直在while循环接收消息

while isok:#父线程一直发送消息
    t = input("client>")
    try:
        clientfd.send(t.encode('utf8'))
        if t == "exit":
            isok = False
    except Exception as e:
        print(e)
        exit(0)
clientfd.close()