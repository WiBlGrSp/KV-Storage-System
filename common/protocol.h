#pragma once
#ifndef PROTOCOL_H
#define PROTOCOL_H
#include<string>
class Msg
{
private:
    static constexpr int CODE_SIZE = 6; //码占位长
public:
    std::string code_;  //操作码 or 应答码
    std::string content_; //消息正文
    void serilize(std::string&str);    //序列化
    void deserilize(const std::string&str);  //反序列化
};
#endif //!PROTOCOL_H