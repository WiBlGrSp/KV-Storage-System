#pragma once
#include <cstdint>
#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include<string>
//通信实体,用于收发一条报文信息
class Communication
{
private:
    int fd_; //用于收发消息的文件描述符
    std::string ip_;
    uint16_t port_;
    std::string buf_;   //输入缓冲区
public:
    Communication(int fd,std::string ip,uint16_t port);
    ~Communication();
    int Recv(std::string&msg);
    int Send(std::string&msg);
};


#endif //!COMMUNICATION_H