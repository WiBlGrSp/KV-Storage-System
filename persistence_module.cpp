#include "persistence_module.h"
#include <csignal>
#include <cstdio>
#include <fstream>
#include <memory>
#include <string>
#include <utility>
//键值对序列化和反序列化
static std::string serilize(const std::pair<std::string,std::string>& kv)
{

    return kv.first + ":"+ kv.second;
}
static std::pair<std::string,std::string> deserilize(const std::string& kv_s)
{

    std::string key,value;
    auto it = kv_s.find(':');
    return std::make_pair(kv_s.substr(0,it), kv_s.substr(it+1));
}


PersistenceModule::PersistenceModule(std::string file_path) {
    file_ = file_path;
}
PersistenceModule::~PersistenceModule() {
}
void PersistenceModule::save(const std::shared_ptr<MemoryRepositry>& repos) {
    std::ofstream of;
    of.open(file_,std::ios::out | std::ios::trunc);
    //将repos中数据保存到磁盘文件中 每一行存储一个键值对 key:value\n
    for(const auto&kv:repos->get_map())
    {
        of << serilize(kv) << '\n';
    }
    of.close();
}
std::shared_ptr<MemoryRepositry> PersistenceModule::load() {
    std::shared_ptr<MemoryRepositry> repos = std::make_shared<MemoryRepositry>();
    std::ifstream ifs;
    ifs.open(file_,std::ios::in);
    //从文件中逐行读取kv对
    while(!ifs.eof())
    {
        std::string buf;
        std::getline(ifs,buf);
        if(!buf.empty()){
            auto [key,value] = deserilize(buf);
            repos->put(key,value);
        }
    }
    ifs.close();
    return repos;
}