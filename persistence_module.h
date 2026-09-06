#pragma once
#ifndef PERSISTENCE_MODULE_H
#define PERSISTENCE_MODULE_H
#include <fstream>
#include"KV.h"
class PersistenceModule
{
private:
    std::string file_;
public:
    PersistenceModule(std::string file_path);
    ~PersistenceModule();
    void save(const kvstore::DataMap& data_map);
    kvstore::DataMap load();
    bool appendPut(const kvstore::Key& key ,const kvstore::Value& value);
    bool appendDel(const kvstore::Key& key);
    kvstore::DataMap replay();  //重放日志
};
#endif //!PERSISTENCE_MODULE_H