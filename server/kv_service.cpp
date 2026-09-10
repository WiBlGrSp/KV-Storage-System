
#include "kv_service.h"
#include"protocol.h"
#include<sstream>
int KVService::getHandler(const std::string& arg,std::string&res) {
    std::istringstream iss(arg);
    std::string key,value;
    iss >> key;
    if(key.empty())
    {
        res = "input error";
    }else
    if (kv_store_.get(key,value))
    {
        res = "value=" + value;
    }else {
        res = "key:"+key +" not found";
    }
    return 0;
}
int KVService::putHandler(const std::string& arg,std::string&res) {
    std::istringstream iss(arg);
    std::string key,value;
    iss >> key >> value;
    if(key.empty() || value.empty())
    {
        res = "input error";
    }else
    if (kv_store_.put(key,value))
    {
        res = "put success";
    }else {
        res = "put error";
    }
    return 0;
}
int KVService::delHandler(const std::string&arg,std::string&res) {
    std::istringstream iss(arg);
    std::string key,value;
    iss >> key;
    if(key.empty())
    {
        res = "input error";
    }else
    if (kv_store_.del(key))
    {
        res = "del success";
    }else {
        res = "del error";
    }
    return 0;
}
void KVService::process(const std::string&req,std::string&res) {
    Msg msg;msg.deserilize(req);
    std::string &op_no = msg.code_;
    std::string&content = msg.content_;
    //业务分发
    if(op_no == "get")
    {
        getHandler(content,res);
    }else if(op_no == "put")
    {
        putHandler(content,res);
    }else if(op_no=="del")
    {
        delHandler(content,res);
    }else{
        res = std::string("ERROR\0op not exist"); 
    }
}