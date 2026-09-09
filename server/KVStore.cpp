#include"KVStore.h"
#include "aof_persistence.h"
#include <mutex>
#include<iostream>
bool KVStore::get(const std::string&key,std::string&value)
{
    std::lock_guard<std::mutex> lo(mu_);
    if(auto it = kv_map_.find(key);it!=kv_map_.end())
    {
        value =  kv_map_[key];
        return true;
    }
    return false;
    
}
bool KVStore::put(const std::string&key,const std::string&value)
{
    std::lock_guard<std::mutex> lo(mu_);
    per_.appendPut(key,value);
    kv_map_[key] = value;
    return true;
}
bool KVStore::del(const std::string&key)
{
    std::lock_guard<std::mutex> lo(mu_);
    if(auto it = kv_map_.find(key);it!=kv_map_.end())   
    {
        per_.appendDel(key);
        kv_map_.erase(key);
        return true;
    }
    else {
        return false;
    }
}

KVStore::KVStore():per_([this](std::ostream& os)->void{
    for(const auto&[key,value] : kv_map_)
    {
        os << "P:" << key << ":" << value << "\n";
    };
}) 
{
    per_.load(kv_map_);
    per_.chechEvent();
}
KVStore::~KVStore() {
}
