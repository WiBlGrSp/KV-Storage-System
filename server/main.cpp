
#include "ReplicationManager.h"
#include "dispatcher.h"
#include"kv_service.h"
#include"KVStore.h"
#include"server.h"
#include <cstdio>
// int main(int argc,const char*argv[])
// {
//     uint16_t port =8000;
//     std::string role;
//     if(argc<=2)
//     {
//         std::cout << "please input ./build -role -port" <<std::endl;
//         return -1;
//     }else
//     {
//         role = argv[1]+1;
//         port = std::stoul(argv[2]+1);
//     }
//     printf("role = %s,port = %d\n",role.c_str(),port);
//     KVStore store;
//     NetServer server(role,port,store);
//     return 0;
// }

int main()
{
    KVStore kv_store;
    KVService service(kv_store);
    ReplicationManager replicationManager(kv_store);
    Dispatcher dispatcher(service,replicationManager);
    Server server(dispatcher);
    server.run();
    return 0;
}
