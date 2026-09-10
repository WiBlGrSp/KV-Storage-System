
#include "communication.h"
#include <cstdint>
#include <cstring>
#include <netinet/in.h>
#include <string>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

Communication::Communication(int fd,std::string ip,uint16_t port):fd_(fd),ip_(ip),port_(port){
}

Communication::~Communication() {
    close(fd_);
}
//接收一条报文,去除2B长度前缀
int Communication::Recv(std::string&msg) {
    msg.clear();
    char buf[1024];
    uint16_t size = 0;  //报文体长度
    bool get_len = false;
    //循环取到2字节长度前缀
    while(true)
    {
        //接收字节流
        bzero(buf,sizeof(buf));
        int len = recv(fd_,buf,sizeof(buf),0);
        if(len == 0)
        {
            printf("对端[%s:%d]已经下线!\n",ip_.c_str(),port_);
            return 0;
        }
        //追加到输入缓冲区
        buf_.append(buf,len);
        //提取长度前缀
        if(!get_len&&buf_.size()>=2)
        {
            uint16_t tmp;
            std::memcpy(&tmp,buf_.data(),sizeof(uint16_t));
            size = ntohs(tmp);
            buf_.erase(0,sizeof(uint16_t));
            get_len = true;
        }
        if(get_len && buf_.size() >=size)
        {
            msg = buf_.substr(0,size);
            buf_.erase(0,size);
            break;
        }
    }
    return msg.size();
}
//发送一条报文,添加2B长度前缀
int Communication::Send(std::string&msg) {

    //构建发送报文
    uint16_t len_net = htons(static_cast<uint16_t>(msg.size()));
    char head[2];
    memcpy(head, &len_net, sizeof(uint16_t));
    std::string packet;
    packet.append(head,sizeof(uint16_t));
    packet +=msg;
    //响应数据
    if(send(fd_,packet.c_str(),packet.size(),0)==-1){
        perror("send error");
        return -1;
    }
    printf("send success\n");
    return 0;
}
