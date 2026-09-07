#include "net_servcer.h"
#include <cstdio>
#include <sys/types.h> 
#include <sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<string>
#include<cstring>
#include <sstream>

NetServer::~NetServer() {
}

void NetServer::run() {
    //创建socket
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd == -1){
        perror("socket error");
        return ;

    }
    printf("socket:%d\n",sfd);
    //设置端口快速重用
    int opt = 1;
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    //绑定ip和端口
    struct sockaddr_in sin;
    sin.sin_family = AF_INET; //通信域
    sin.sin_port = htons(SER_PORT); //端口号
    sin.sin_addr.s_addr = inet_addr(SER_IP); //ip地址
    socklen_t sin_len = sizeof(sin);
    int res = bind(sfd,(struct sockaddr*)&sin,sin_len);
    if(res == -1){
        perror("bind error");
        return;
    }
    printf("bind success\n");
    //监听
    if(listen(sfd,64) == -1)
    {
        perror("listen error");
        return ;
    }
    printf("listen success\n");
    //接收连接
    struct sockaddr_in cin;
    socklen_t newfd_len;
    int new_fd = accept(sfd,(struct sockaddr*)&cin,&newfd_len);
    if(new_fd == -1)
    {
        perror("accept error");
        return;
    }
    printf("[%s:%d]:已连接成功!!!!\n", inet_ntoa(cin.sin_addr),ntohs(cin.sin_port));
    char buf[1024];
    while(true)
    {
        //接收数据
        bzero(buf,sizeof(buf));
        int len = recv(new_fd,buf,sizeof(buf),0);
        if(len == 0)
        {
            printf("对端[%s:%d]已经下线!",inet_ntoa(cin.sin_addr),ntohs(cin.sin_port));
            break;
        }else {
            printf("客户端发来消息:%s\n",buf);
        }
    //调用业务逻辑
        std::string result;
        service(std::string(buf), result);
    //响应数据
        if(send(new_fd,result.c_str(),result.size(),0)==-1){
            perror("send error");
            break;
        }
        printf("send success");
    }
    //关闭连接
    close(new_fd);
    close(sfd);
}
void NetServer::service(const std::string& request,std::string&response) 
{

    //数据解析
    std::string op;
    std::string key;
    std::string value;
    std::istringstream ss(request);
    ss >> op >> key >> value;

    //业务分发

    if(op == "quit")
    {
        response = "server quit";
    }else
    if(op == "get")
    {
        if(key.empty() )
        {
            response = "key empty error";
        }else
        if (store_.get(key,value))
        {
            response = "value:" + value;
        }else {
            response = "key:"+key +" not found";
        }
        
    }
    else if (op == "put")
    {
        if(key.empty() || value.empty())
        {
            response = "key or value empty error";
        }else
        if (store_.put(key,value))
        {
            response = "put success";
        }else {
            response= "put error";
        }
    }else if(op == "del")
    {
        if(key.empty())
        {
            response = "key empty error";
        }else
        if (store_.del(key))
        {
            response = "delete success";

        }else {
            response = "delete error";
        }
    }else {
        response = "请求不合法";
    }

}