
#include"KVStore.h"
#include"net_servcer.h"
#include <cstdint>
#include <cstdio>
#include<iostream>
#include <string>
int main(int argc,const char*argv[])
{
    uint16_t port =8000;
    std::string role;
    if(argc<=2)
    {
        std::cout << "please input ./build -role -port" <<std::endl;
        return -1;
    }else
    {
        role = argv[1]+1;
        port = std::stoul(argv[2]+1);
    }
    printf("role = %s,port = %d\n",role.c_str(),port);
    KVStore store;
    NetServer server(role,port,store);
    return 0;
}
