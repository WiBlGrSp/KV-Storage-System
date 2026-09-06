#pragma once
#ifndef MEMORY_REPOSITRY_H
#define MEMORY_REPOSITRY_H
#include<string>
#include<map>
//内存kv存储
typedef std::map<std::string,std::string> kv_map_type;
class MemoryRepositry
{
private:
    //红黑树存储键值对
    kv_map_type kv_map_;
public:
    //核心接口
    bool get(const std::string&key,std::string&value);
    bool put(const std::string&key,const std::string&value);
    bool del(const std::string&key);
    const kv_map_type& get_map()const
    {
        return kv_map_;
    }
};


#endif //!MEMORY_REPOSITRY_H