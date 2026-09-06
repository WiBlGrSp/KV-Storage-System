#pragma once
#ifndef KV_H
#define KV_H
#include<string>
#include<map>
//定义数据契约
namespace kvstore {
    using Key = std::string;
    using Value = std::string;
    using DataMap = std::map<Key,Value>;
    // using Key = std::string;

    // //定义基础值类型
    // using String = std::string;
    // using List = std::list<std::string>;
    // using Set = std::set<std::string,std::string>;
    // //定义一种通用的值存储类型 :字符串,列表,集合
    // class Value
    // {
    //     private:
    //     std::variant<String,List,Set> v_;
    // };

}
#endif //!KV_H