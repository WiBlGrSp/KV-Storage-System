
#include "aof_persistence.h"
#include <mutex>
#include<fstream>
#include <thread>
#include<unistd.h>
#include <sys/wait.h>
#include<sys/types.h>
#include"KV.h"
bool AOFPersistence::appendPut(const Key& key ,const Value& value) {
    std::lock_guard<std::mutex> lo(mu_);
    std::string log = "P:"+key + ":" + value+"\n";
    aof_buf_.push_back(log);
    sync_counter_++;
    if(sync_counter_>=SYNC_COUNTER_BOUNDERY)
        sync();
    if(is_rewritting_)
        aof_rewrite_buf_.push_back(log);
    return true;
}

bool AOFPersistence::appendDel(const Key& key) {
    std::lock_guard<std::mutex> lo(mu_);
    std::string log = "D:"+key+"\n";
    aof_buf_.push_back(log);
    sync_counter_++;
    if(sync_counter_>=SYNC_COUNTER_BOUNDERY)
        sync();
    if(is_rewritting_)
        aof_rewrite_buf_.push_back(log);
    return true;
}

bool AOFPersistence::sync() {
    //打开文件
    std::ofstream ofs;
    ofs.open(aof_file_,std::ios::out | std::ios::app);
    if(!ofs.is_open())
    {
        return false;
    }
    //逐行写入
    for(auto line : aof_buf_)
    {
        ofs << line;
        aof_cur_size++;
    }
    //关闭文件
    ofs.close();

    //清空缓冲区
    aof_buf_.clear();
    return true;
}

bool AOFPersistence::rewrite(const DataMap&data_map) {
    //开启aof_write_buf_
    is_rewritting_ = true;
    //创建子进程写新AOF日志
    pid_t pid = fork();
    if(pid == 0)
    {
        //创建临时AOF文件
        std::ofstream ofs;
        ofs.open(aof_tmp_file_,std::ios::out|std::ios::trunc);

        //内存数据写入临时AOF文件
        for(auto kv:data_map)
        {
            ofs << "P:" << serilize(kv) << "\n";
        }
        ofs.flush();
        ofs.close();
        //退出子进程,通知主进程
        exit(EXIT_SUCCESS);
    }else if(pid >0)
    {
        return true;
    }else
    {
        perror("fork error");
        return false;
    }
    return false;
}

bool AOFPersistence::load(DataMap&data_map) {
    aof_base_size=0;
    aof_cur_size=0;
    std::ifstream ifs;
    ifs.open(aof_file_,std::ios::in);
    //从文件中逐行读取日志,重放日志
    std::string line;
    while(std::getline(ifs,line))
    {
        if(!line.empty()){
            auto it = line.find(':');
            std::string op = line.substr(0,it);
            aof_base_size++;
            aof_cur_size++;
            if(op == "P")
            {
                auto [key,value] = deserilize(line.substr(it+1));
                data_map[key] = value;            
            }else if(op == "D")
            {
                std::string key = line.substr(it+1);
                data_map.erase(key);
            }
        }
    }
    ifs.close();
    return true;
}

void AOFPersistence::rewriteBuf() {

    std::lock_guard<std::mutex>lo(mu_); 
    //将aof_rewrite_buf追加写入临时AOF文件
    std::ofstream ofs;
    ofs.open(aof_tmp_file_,std::ios::out|std::ios::app);
    for(auto line:this->aof_rewrite_buf_)
    {
        ofs << line;
    }
    ofs.close();
    //用临时AOF文件替换原AOF文件
    std::rename(aof_tmp_file_.c_str(),aof_file_.c_str());

    //关闭并清空aof_rewrite_buf_
    is_rewritting_ = false;
    aof_rewrite_buf_.clear();
    //记录aof文件大小
    aof_base_size = aof_cur_size; 
}
AOFPersistence::AOFPersistence(DataMap&kv_map):kv_map_(&kv_map) {
}
AOFPersistence::~AOFPersistence() {

}
void AOFPersistence::chechEvent() {
    std::thread th([this](){
        while(true)
        {
            sleep(1);
            if(!is_rewritting_ && aof_cur_size-aof_base_size*1.5>0 && aof_base_size>5)
            {
                rewrite(*kv_map_);
            }
            pid_t pid = waitpid(-1,NULL,WNOHANG);
            if(pid >0 )
            {
                rewriteBuf();
            }
        }
    });
    th.detach();
}