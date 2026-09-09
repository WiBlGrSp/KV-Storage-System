#include"KV.h"

std::string serilize(const std::pair<std::string,std::string>& kv)
{

    return kv.first + ":"+ kv.second;
}
std::pair<std::string,std::string> deserilize(const std::string& kv_s)
{

    std::string key,value;
    auto it = kv_s.find(':');
    return std::make_pair(kv_s.substr(0,it), kv_s.substr(it+1));
}

