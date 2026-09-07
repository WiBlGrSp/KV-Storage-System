
#include "service.h"

void Service::handle(const Request &request,Response &response) {
    std::string op=request.op_;
    std::string key=request.key_;
    std::string value=request.value_;

    //业务分发

    if(op == "quit")
    {
        response = "server quit";
    }else
    if(op == "get")
    {
        if(key.empty() )
        {
            response = "key empty error";
        }else
        if (store_.get(key,value))
        {
            response = "value:" + value;
        }else {
            response = "key:"+key +" not found";
        }
        
    }
    else if (op == "put")
    {
        if(key.empty() || value.empty())
        {
            response = "key or value empty error";
        }else
        if (store_.put(key,value))
        {
            response = "put success";
        }else {
            response= "put error";
        }
    }else if(op == "del")
    {
        if(key.empty())
        {
            response = "key empty error";
        }else
        if (store_.del(key))
        {
            response = "delete success";

        }else {
            response = "delete error";
        }
    }else {
        response = "请求不合法";
    }
}
