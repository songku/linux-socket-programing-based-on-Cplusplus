# 写在前面
本编程基于c语言，但部分语法比如sstream用到了c++语言，因此程序编译注意使用g++编译器。
经过操作系统作业的检验，原linux大作业都运行失败。因此又修改编辑了最新版tcpserver.cpp和tcpclient.cpp。

`g++ -o client tcpclient.cpp`

`g++ -o server tcpserver.c`

或
`g++ tcpserver.cpp -o tcpserver`
# client运行方法
程序运行方法为 `./client get current var_temp`
其中`./client`应视个人编译程序名字而定。
# server运行方法
`./server`
之后输入个人设定的var_temp即可等待连接。

# 改进
同学通过threading和socket实现了客户端和服务器端互相接收和发送任何消息。后续有待补充。
