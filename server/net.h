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
struct Response
{
    std::string msg_;
    Response operator=(const Response&other)
    {
        this->msg_ = other.msg_;
        return *this;
    }
    Response operator=(const char*str)
    {
        this->msg_ = str;
        return *this;
    }
    Response operator=(const std::string&str)
    {
        this->msg_ = str;
        return *this;
    }
};

#endif //!NET_H