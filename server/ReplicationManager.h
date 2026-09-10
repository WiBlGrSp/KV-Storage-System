#pragma once
#include "KVStore.h"
#include "communication.h"
#include "protocol.h"
#include <memory>
#ifndef REPLICATION_MANAGER_H
#define REPLICATION_MANAGER_H
class ReplicationManager
{
private:
    //kv_store提供快照
    KVStore & kv_store_;
public:
    void sendFullSync(std::shared_ptr<Communication>conn,const Msg&msg);
    ReplicationManager(KVStore &kv_store):kv_store_(kv_store){};
};

#endif //!REPLICATIONMANAGER_H