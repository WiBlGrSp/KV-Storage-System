#pragma once
#include "ReplicationManager.h"
#include "communication.h"
#include "kv_service.h"
#include <memory>
#ifndef DISPATCHER_H
#define DISPATCHER_H
class Dispatcher
{
    KVService&kv_service_;
    ReplicationManager& replicationManager_;
public:
Dispatcher(KVService&kv_service,ReplicationManager&replicationManager):kv_service_(kv_service),replicationManager_(replicationManager)
{}
void dispatch(std::shared_ptr<Communication>com,const std::string&req,std::string&res);

};

#endif //!DISPATCHER_H