#pragma once
#ifndef AOF_PERSISTENCE_H
#define AOF_PERSISTENCE_H
#include<string>
#include<list>
#include"KV.h"
#include<mutex>
#include<functional>
class AOFPersistence
{
private:
    //aof文件名
    std::string aof_file_= "aof";
    std::string aof_tmp_file_ = "aof.tmp";
    std::list<std::string> aof_buf_;    //aof写缓冲区
    std::list<std::string> aof_rewrite_buf_;    //aof重写缓冲区
    bool is_rewritting_ = false; //正在重写
    unsigned long sync_counter_=0;    //同步计数器
    const unsigned long SYNC_COUNTER_BOUNDERY = 0;  //同步计数器上界  
    std::mutex mu_;    //保护aof文件和缓冲区的锁
    unsigned long aof_base_size=0;    //aof文件上次重写记录数
    unsigned long aof_cur_size=0;     //aof文件当前记录数
    std::function<void(std::ostream&)> dump_func_;
public:
    explicit AOFPersistence(std::function<void(std::ostream&)> dump_func);
    AOFPersistence();
    ~AOFPersistence();
    //写入日志
    bool appendPut(const Key& key ,const Value& value);
    bool appendDel(const Key& key);
    //同步aof_buf-->aof
    bool sync();
    //重写aof
    bool rewrite(const std::function<void(std::ostream&)>dump_snapshot);
    //将aof_rewrite_buf写入临时AOF文件
    void rewriteBuf();
    //重放aof-->内存
    bool load(DataMap&data_map);
    //定时检查时间发生,触发时间
    void chechEvent();
};

#endif //!AOF_PERSISTENCE_H