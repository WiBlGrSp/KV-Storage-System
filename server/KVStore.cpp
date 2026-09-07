#include"KVStore.h"
#include "persistence_module.h"
bool KVStore::get(const std::string&key,std::string&value)
{
    if(auto it = kv_map_.find(key);it!=kv_map_.end())
    {
        value =  kv_map_[key];
        return true;
    }
    return false;
    
}
bool KVStore::put(const std::string&key,const std::string&value)
{
    per_.appendPut(key,value);
    kv_map_[key] = value;
    per_.autoCompact(kv_map_);
    return true;
}
bool KVStore::del(const std::string&key)
{
    if(auto it = kv_map_.find(key);it!=kv_map_.end())   
    {
        per_.appendDel(key);
        kv_map_.erase(key);
        per_.autoCompact(kv_map_);
        return true;
    }
    else {
        return false;
    }
}
void KVStore::restore() {
    // kv_map_ = PersistenceModule("data.txt").load();
    // kv_map_ = PersistenceModule("wal.txt").replay();
    per_.restore(kv_map_);
}

KVStore::KVStore():per_("snapshot.txt","wal.txt") {
    restore();
}
KVStore::~KVStore() {
}
