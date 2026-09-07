#pragma once
#ifndef KVSTORE_H
#define KVSTORE_H
#include<string>
#include<map>
#include"KV.h"
#include"persistence_module.h"
//顶层模块
class KVStore
{
private:
    //红黑树存储键值对
    kvstore::DataMap kv_map_;
    //持久化模块
    PersistenceModule per_;
public:
    KVStore();
    ~KVStore();
    //核心接口
    bool get(const std::string&key,std::string&value);
    bool put(const std::string&key,const std::string&value);
    bool del(const std::string&key);
    //从快照中恢复
    void restore();

};


#endif //!KVSTORE_H
