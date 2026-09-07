#pragma once
#ifndef NET_H
#define NET_H
#include<string>
#include<sstream>
//定义请求数据对象
struct Request 
{
    std::string op_;
    std::string key_;
    std::string value_;
    void deserilize(const std::string& msg)
    {
        std::istringstream ss(msg);
        ss >> op_ >> key_ >> value_;   
    }
};

//定义响应数据对象
typedef std::string Response;

#endif //!NET_H