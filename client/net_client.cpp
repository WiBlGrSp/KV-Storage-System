#include "net_client.h"
#include <cstdio>
#include <sys/types.h> 
#include <sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<cstring>
#include"communication.h"
#include "protocol.h"
#include<iostream>
NetClient::NetClient() {
    run();
}

NetClient::~NetClient() {
}

void NetClient::run() {
    //创建用于通信的客户端套接字文件描述符
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    if(cfd == -1)
    {
        perror("socket error");
        return;
    }
    printf("socket success cfd = %d\n", cfd);

    //连接服务器
    struct sockaddr_in sin;
    sin.sin_family = AF_INET; //通信域
    sin.sin_port = htons(SER_PORT); //端口号
    sin.sin_addr.s_addr = inet_addr(SER_IP); //服务器ip地址
    //3.2 连接工作
    if(connect(cfd, (struct sockaddr*)&sin, sizeof(sin)) == -1)
    {
        perror("connect error");
        return ;
    }
    printf("连接服务器成功\n");
    //4、数据收发
    Communication com(cfd,SER_IP,SER_PORT);
    while(true)
    {
        std::string code;
        std::string arg;
        std::cin >> code;
        std::getline(std::cin,arg);
        Msg msg;
        msg.code_ = code;
        msg.content_ = arg;
        std::string req ;
        msg.serilize(req);
        com.Send(req);
        //接受服务器发送过来的消息
        std::string res;
        if(com.Recv(res)==0)
        {
            printf("服务端下线\n");
            break;
        }else {
            printf("服务端发送消息为:%s\n",res.c_str());
        }
    }

    return;	
}
