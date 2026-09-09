#include "persistence_module.h"
#include <cstdio>
#include <fstream>
#include <ostream>
#include <string>


#include"KV.h"
PersistenceModule::PersistenceModule(const std::string snapshot_file,const std::string &wal_file)
{
    snapshot_file_ = snapshot_file;
    wal_file_ = wal_file;
    counter_ = 0;
}
PersistenceModule::~PersistenceModule() {
}
//将内存数据刷入快照文件
void PersistenceModule::save(const DataMap& data_map){

    //先刷入临时文件
    std::string tmp = snapshot_file_+".tmp";
    std::ofstream of;
    of.open(tmp,std::ios::out | std::ios::trunc);
    //将repos中数据保存到磁盘文件中 每一行存储一个键值对 key:value\n
    for(const auto&kv:data_map)
    {
        of << serilize(kv) << '\n';
    }
    of.close();
    //用临时文件替换快照文件
    std::rename(tmp.c_str(),snapshot_file_.c_str());
}



bool PersistenceModule::appendPut(const Key& key ,const Value& value) {

    std::ofstream of;
    of.open(wal_file_,std::ios::out | std::ios::app);
    of << "P:" << serilize({key,value}) << '\n'; 
    of.close();
    counter_++;
    return true;
}
bool PersistenceModule::appendDel(const Key& key) {
    std::ofstream of;
    of.open(wal_file_,std::ios::out | std::ios::app);
    of << "D:" << key << '\n'; 
    of.close();
    counter_++;
    return true;
}

//对内存数据执行重放操作
void PersistenceModule::replay(DataMap&data_map)
{
    std::ifstream ifs;
    ifs.open(wal_file_,std::ios::in);
    //从文件中逐行读取日志,重放日志
    std::string line;
    counter_=0;
    while(std::getline(ifs,line))
    {
        if(!line.empty()){
            auto it = line.find(':');
            std::string op = line.substr(0,it);
            if(op == "P")
            {
                auto [key,value] = deserilize(line.substr(it+1));
                data_map[key] = value;            
                counter_++;
            }else if(op == "D")
            {
                std::string key = line.substr(it+1);
                data_map.erase(key);
                counter_++;

            }
        }
    }
    ifs.close();
}

void PersistenceModule::load(DataMap&data_map) {
    std::ifstream ifs;
    ifs.open(snapshot_file_,std::ios::in);
    //从文件中逐行读取kv对
    std::string line;
    while(std::getline(ifs,line))
    {
        if(!line.empty()){
            auto [key,value] = deserilize(line);
            data_map[key] = value;
        }
    }
    ifs.close();
}

void PersistenceModule::restore(DataMap&data_map)
{
    this->load(data_map);
    this->replay(data_map);
}

void PersistenceModule::compact(const DataMap&data_map)
{
    //将内存数据刷入快照文件
    this->save(data_map);
    //清空日志文件
    this->clearWal();
    counter_=0;
}
void PersistenceModule::clearWal()
{
    std::ofstream osf;
    osf.open(wal_file_,std::ios::out | std::ios::trunc);
}
void PersistenceModule::autoCompact(const DataMap&data_map)
{
    if(counter_>boundary_)
    {
        compact(data_map);
    }
}
