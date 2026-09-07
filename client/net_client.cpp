#include "net_client.h"
#include <cstdio>
#include <sys/types.h> 
#include <sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<cstring>

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
    char wbuf[128] = "";
    while(true)
    {
        //清空容器
        bzero(wbuf, sizeof(wbuf));
        //从终端获取数据
        fgets(wbuf, sizeof(wbuf), stdin);
        wbuf[strlen(wbuf)-1] = '\n'; //设定命令分割符
        //将数据发送给服务器
        if(send(cfd, wbuf, sizeof(wbuf), 0)==-1)
        {
            perror("send error");
            return ;
        }
        //接受服务器发送过来的消息
        if(recv(cfd, wbuf, sizeof(wbuf), 0)==0)
        {
            printf("对端已经下线\n");
        break;
        }
            printf("收到服务器消息为：%s\n", wbuf);
    }
    //5、关闭套接字
    close(cfd);
    return;	
}
