#pragma once
#ifndef SERVICE_H
#define SERVICE_H
#include"net.h"
#include"KVStore.h"
//定义业务处理
class Service
{
private:
    KVStore & store_;
public:
    Service(KVStore & store):store_(store)
    {
        
    }
    void handle(const Request &request,Response& response);
};

#endif //!SERVICE_H