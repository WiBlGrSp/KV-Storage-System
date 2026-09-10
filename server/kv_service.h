#pragma once
#ifndef KV_SERVICE_H
#define KV_SERVICE_H
#include<string>
#include"KVStore.h"
class KVService
{
private:
    KVStore& kv_store_;
public:
    void process(const std::string&req,std::string&res);
    int putHandler(const std::string& arg,std::string&res);
    int getHandler(const std::string& arg,std::string&value);
    int delHandler(const std::string&arg,std::string&res);
    KVService(KVStore&kv_store):kv_store_(kv_store){}
};

#endif //!KV_SERVICE_H