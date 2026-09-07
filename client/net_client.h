#pragma once
#ifndef NET_CLIENT_H
#define NET_CLIENT_H
#define SER_PORT 8000
#define SER_IP "192.168.42.131"
class  NetClient
{
    void run();
public:
    NetClient();
    ~NetClient();
};

#endif //!NET_CLIENT_H