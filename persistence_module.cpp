#include "persistence_module.h"
#include <fstream>
#include <string>
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
void PersistenceModule::save(const kvstore::DataMap& data_map){

    std::ofstream of;
    of.open(file_,std::ios::out | std::ios::trunc);
    //将repos中数据保存到磁盘文件中 每一行存储一个键值对 key:value\n
    for(const auto&kv:data_map)
    {
        of << serilize(kv) << '\n';
    }
    of.close();
}
kvstore::DataMap PersistenceModule::load() {
    kvstore::DataMap result;
    std::ifstream ifs;
    ifs.open(file_,std::ios::in);
    //从文件中逐行读取kv对
    std::string line;
    while(std::getline(ifs,line))
    {
        if(!line.empty()){
            auto [key,value] = deserilize(line);
            result[key] = value;
        }
    }
    ifs.close();
    return result;
}

bool PersistenceModule::appendPut(const kvstore::Key& key ,const kvstore::Value& value) {

    std::ofstream of;
    of.open(file_,std::ios::out | std::ios::app);
    of << "P:" << serilize({key,value}) << '\n'; 
    of.close();
    return true;
}
bool PersistenceModule::appendDel(const kvstore::Key& key) {
    std::ofstream of;
    of.open(file_,std::ios::out | std::ios::app);
    of << "D:" << key << '\n'; 
    of.close();
    return true;
}
kvstore::DataMap PersistenceModule::replay() {
    kvstore::DataMap result;
    std::ifstream ifs;
    ifs.open(file_,std::ios::in);
    //从文件中逐行读取日志,重放日志
    std::string line;
    while(std::getline(ifs,line))
    {
        if(!line.empty()){
            auto it = line.find(':');
            std::string op = line.substr(0,it);
            if(op == "P")
            {
                auto [key,value] = deserilize(line.substr(it+1));
                result[key] = value;            
            }else if(op == "D")
            {
                std::string key = line.substr(it+1);
                result.erase(key);
            }
        }
    }
    ifs.close();
    return result;
}