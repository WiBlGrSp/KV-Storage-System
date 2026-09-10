#pragma once
#include "dispatcher.h"
#include <functional>
#ifndef SERVER_H
#define SERVER_H
#include<string>
#include <cstdint>
#include<netinet/in.h>
#include"kv_service.h"
#define SER_PORT 8000
#define SER_IP "192.168.42.131"
//服务器,对外提供kv存储服务
class Server
{
private:
    Dispatcher& dispatcher_;
private:
    //监听连接,执行通信
    int startListen(const std::string&ip,uint16_t port,const std::function<void(int fd,sockaddr_in cin)>&createConnection);
    void communicationTask(int fd,sockaddr_in cin);
    
public:
    void run();
    Server(Dispatcher&dispatch_):dispatcher_(dispatch_)
    {}
};
#endif //!SERVER_H