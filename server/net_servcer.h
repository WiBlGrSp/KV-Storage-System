#pragma once
#ifndef NET_SERVCER_H
#define NET_SERVCER_H
#include<string>
#include"KVStore.h"
#include"KVStore.h"
#include<netinet/in.h>
#include"service.h"
#define SER_PORT 8000
#define SER_IP "192.168.42.131"
/*
网络服务器,负责接收客户端连接,与客户端通信
*/
class NetServer
{
private:
    Service &service_;
private:
    //启动服务器
    void run();

    //线程体函数,执行通信任务
    void task(int fd,sockaddr_in cin);
    //数据解析+业务分发
    void service(const std::string& request,std::string&response);

public:
    NetServer(Service &service):service_(service)
    {
        run();
    }
    ~NetServer();

};
#endif //!NET_SERVCER_H