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
    PersistenceModule per("wal.txt");
    per.appendPut(key,value);
    kv_map_[key] = value;
    return true;
}
bool KVStore::del(const std::string&key)
{
    if(auto it = kv_map_.find(key);it!=kv_map_.end())   
    {
        PersistenceModule per("wal.txt");
        per.appendDel(key);
        kv_map_.erase(key);
        return true;
    }
    else {
        return false;
    }
}
void KVStore::restore() {
    // kv_map_ = PersistenceModule("data.txt").load();
    kv_map_ = PersistenceModule("wal.txt").replay();
}
void KVStore::snapshot() {
    PersistenceModule("data.txt").save(kv_map_);
}
KVStore::KVStore() {
    restore();
}
KVStore::~KVStore() {
    // snapshot();
}
