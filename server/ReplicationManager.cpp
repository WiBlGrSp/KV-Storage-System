
#include "ReplicationManager.h"

void ReplicationManager::sendFullSync(std::shared_ptr<Communication>conn,const Msg&msg) {
    //获取快照
    std::string snapshot;
    kv_store_.createSnapshot(snapshot);
    //发送快照
    conn->Send(snapshot);
}
