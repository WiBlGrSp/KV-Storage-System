
#include"KVStore.h"
#include"net_servcer.h"

int main()
{
    KVStore store;
    NetServer server(store);
    return 0;
}
