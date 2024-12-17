#include "UDPServer.h"
#include <cstring>
#include <iostream>

UDPServer::UDPServer(unsigned short serverport) : UDPSocket() {
    mServerPort = serverport;

    mServer.sin_family = AF_INET;
    mServer.sin_addr.s_addr = INADDR_ANY;
    mServer.sin_port = htons(mServerPort);

    if (bind(s, (struct sockaddr*)&mServer, sizeof(mServer)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
}

UDPServer::~UDPServer() {}
