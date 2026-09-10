#pragma once
#include <cstdint>
#ifndef NET_SERVCER_H
#define NET_SERVCER_H
#include<netinet/in.h>

#include"net.h"
#include "KVStore.h"

#define SER_PORT 8000
#define SER_IP "192.168.42.131"
/*
网络服务器,负责接收客户端连接,与客户端通信
*/
class NetServer
{
private:
    uint16_t ser_port_;
    std::string role_;  //master or slave
    KVStore &store_;
private:
    //启动服务器
    void run();
    //线程体函数,执行通信任务
    void task(int fd,sockaddr_in cin);
    void clientHandler(const Request &request,Response &response); 
    void clientHandlerSlave(const Request &request,Response &response);
public:
    NetServer(const std::string& role,uint16_t ser_port,KVStore &store):role_(role),ser_port_(ser_port),store_(store)
    {
        if(role_ != "master" && role_ !="slave")
        {
            printf("role is error");
            return;
        }
        run();
    }
    ~NetServer();

};
#endif //!NET_SERVCER_H