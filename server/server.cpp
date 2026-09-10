#include"server.h"
#include <memory>
#include <sys/types.h> 
#include <sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <unistd.h>
#include"communication.h"
#include"dispatcher.h"
#include "kv_service.h"
int Server::startListen(const std::string&ip,uint16_t port,const std::function<void(int fd,sockaddr_in cin)>&createCommunication) {
    //创建socket
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd == -1){
        perror("socket error");
        return -1;
    }
    printf("socket:%d\n",sfd);
    //设置端口快速重用
    int opt = 1;
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    //绑定ip和端口
    struct sockaddr_in sin;
    sin.sin_family = AF_INET; //通信域
    sin.sin_port = htons(port); //端口号
    sin.sin_addr.s_addr = inet_addr(ip.c_str()); //ip地址
    socklen_t sin_len = sizeof(sin);
    int res = bind(sfd,(struct sockaddr*)&sin,sin_len);
    if(res == -1){
        perror("bind error");
        return -1;
    }
    printf("bind success\n");
    //监听
    if(listen(sfd,64) == -1)
    {
        perror("listen error");
        return -1;
    }
    printf("listen success\n");
    //循环服务器
    while(true)
    {
        struct sockaddr_in cin;
        socklen_t newfd_len = sizeof(cin);
        int new_fd = accept(sfd,(struct sockaddr*)&cin,&newfd_len);
        if(new_fd == -1)
        {
            perror("accept error");
            return -1;
        }
        printf("[%s:%d]:已连接成功!!!!\n", inet_ntoa(cin.sin_addr),ntohs(cin.sin_port));
        //创建通信
        createCommunication(new_fd,cin);
    }
    close(sfd);
}
void Server::communicationTask(int fd,sockaddr_in cin) {
    auto com = std::make_shared<Communication>(fd,inet_ntoa(cin.sin_addr),ntohs(cin.sin_port));
    std::thread th([this,com,fd,cin](){
        //创建通信实体
        while(true)
        {
        //接受消息
        std::string req;
        if(com->Recv(req)==0)
            break;
        
        //处理消息
        std::string res;
        dispatcher_.dispatch(com,req,res);

        }
    });
    th.detach();
}
void Server::run() {
    startListen(SER_IP,SER_PORT,[this](int fd,sockaddr_in cin){this->communicationTask(fd,cin);});
}

