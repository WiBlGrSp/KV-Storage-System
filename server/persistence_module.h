#pragma once
#include <cstdint>
#ifndef PERSISTENCE_MODULE_H
#define PERSISTENCE_MODULE_H
#include <fstream>
#include"KV.h"
class PersistenceModule
{
private:
    std::string snapshot_file_;
    std::string wal_file_;
    uint32_t counter_;  //操作计数
    constexpr static uint32_t boundary_ = 3;  //日志数上限
public:
    PersistenceModule(const std::string snapshot_file,const std::string &wal_file);
    ~PersistenceModule();
    //将内存数据保存到快照中
    void save(const DataMap& data_map);

    bool appendPut(const Key& key ,const Value& value);
    bool appendDel(const Key& key);
    //从快照和日志中恢复数据
    void restore(DataMap&data_map);
    //将日志压缩到快照中
    void compact(const DataMap&data_map);
    void autoCompact(const DataMap&data_map);

private:
    //加载快照
    void load(DataMap&data_map);
    //重放日志
    void replay(DataMap&data_map);
    //清空日志文件
    void clearWal();
    //自动更新
};
#endif //!PERSISTENCE_MODULE_H