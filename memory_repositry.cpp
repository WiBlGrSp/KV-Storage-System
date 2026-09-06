#include"memory_repositry.h"
bool MemoryRepositry::get(const std::string&key,std::string&value)
{
    if(auto it = kv_map_.find(key);it!=kv_map_.end())
    {
        value =  kv_map_[key];
        return true;
    }
    return false;
    
}
bool MemoryRepositry::put(const std::string&key,const std::string&value)
{
    kv_map_[key] = value;
    return true;
}
bool MemoryRepositry::del(const std::string&key)
{
    if(auto it = kv_map_.find(key);it!=kv_map_.end())   
    {
        kv_map_.erase(key);
        return true;
    }
    else {
        return false;
    }
}