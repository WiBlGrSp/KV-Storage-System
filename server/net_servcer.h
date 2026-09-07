#pragma once
#ifndef NET_SERVCER_H
#define NET_SERVCER_H
#include<string>
#include"KVStore.h"
#include"KVStore.h"
#define SER_PORT 8000
#define SER_IP "192.168.42.131"
/*
网络服务器,负责接收客户端连接,与客户端通信
*/
class NetServer
{
private:
    KVStore& store_;
private:
    //启动服务器
    void run();
    //数据解析+业务分发
    void service(const std::string& request,std::string&response);

public:
    NetServer(KVStore& store):store_(store)
    {
        run();
    }
    ~NetServer();

};
#endif //!NET_SERVCER_H