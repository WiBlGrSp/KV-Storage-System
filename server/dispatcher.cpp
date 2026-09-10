
#include "dispatcher.h"
#include"protocol.h"
void Dispatcher::dispatch(std::shared_ptr<Communication>com,const std::string&req,std::string&res) {
    Msg msg;
    msg.deserilize(req);
    std::string &op_no = msg.code_;
    std::string&content = msg.content_;
    if(op_no == "PSYNC")
    {
        replicationManager_.sendFullSync(com,msg);
    }else if(op_no == "get" || op_no =="put" || op_no =="del")
    {
        kv_service_.process(req,res);
        //发送消息
        com->Send(res);
    }
}
