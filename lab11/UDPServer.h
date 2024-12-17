#pragma once

#include <netinet/in.h>
#include "UDPSocket.h"

class UDPServer : public UDPSocket {
private:
    unsigned short mServerPort;
    struct sockaddr_in mServer;

public:
    UDPServer(unsigned short serverport = PORT);
    virtual ~UDPServer();
};
