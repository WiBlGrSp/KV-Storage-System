
#include"KVStore.h"
#include"net_servcer.h"
#include "service.h"

int main()
{
    KVStore store;
    Service service(store);
    NetServer server(service);
    return 0;
}
