#include <iostream>
#include<string>
#include"KVStore.h"
void log(const std::string&s)
{
    std::cout << s << std::endl;
}
int main()
{
    KVStore s;
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
            if (s.get(key,value))
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
            if (s.put(key,value))
            {
            log("put success");
            }else {
                log("put error");
            }
        }else if(op == "del")
        {
            std::cout << "[SYSTEM]input key"<< std::endl;
            std::cin >> key;
            if (s.del(key))
            {
                log("delete success");

            }else {
                log("delete error");
            }
        }
    };
    return 0;
}
