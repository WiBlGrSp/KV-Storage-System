#include <iostream>
#include<map>
#include<string>
//内存kv存储
class MemoryRepositry
{
private:
    //红黑树存储键值对
    std::map<std::string,std::string> kv_map_;
public:
    //核心接口
    bool get(const std::string&key,std::string&value);
    bool put(const std::string&key,const std::string&value);
    bool del(const std::string&key);
};
bool MemoryRepositry::get(const std::string&key,std::string&value)
{
    if(auto it = kv_map_.find(key);it!=kv_map_.end())
    {
        value =  kv_map_[key];
        return true;
    }
    else {
        return false;
    }
}
bool MemoryRepositry::put(const std::string&key,const std::string&value)
{
    kv_map_[key] = value;
    return true;
}
bool MemoryRepositry::del(const std::string&key)
{
    if(auto it = kv_map_.find(key);it!=kv_map_.end())   
    {
        std::cout << "del success:" << key << ":"<<kv_map_[key] << std::endl;
        kv_map_.erase(key);
        return true;
    }
    else {
        std::cerr << "del:key not found";
        return false;
    }
}
void log(const std::string&s)
{
    std::cout << s << std::endl;
}
int main()
{
    MemoryRepositry r;

    std::string op;
    std::string key;
    std::string value;
    while(true){
        std::cout << "[SYSTEM]input get,put,del or quit" << std::endl;
        std::cin >> op;

        if(op == "quit")
        {
            break;
        }else
        if(op == "get")
        {
            std::cout << "[SYSTEM]input key"<< std::endl;
            std::cin >> key;
            if (r.get(key,value))
            {
                std::cout << "value :" << value << std::endl;
            }else {
                log("key not found");
            }
            
        }
        else if (op == "put")
        {
            std::cout << "[SYSTEM]input key and value"<< std::endl;
            std::cin >> key >> value;
            if (r.put(key,value))
            {
            log("put success");
            }else {
                log("put error");
            }
        }else if(op == "del")
        {
            std::cout << "[SYSTEM]input key"<< std::endl;
            std::cin >> key;
            if (r.del(key))
            {
                log("delete success");

            }else {
                log("delete error");
            }
        }
    };
    return 0;
}