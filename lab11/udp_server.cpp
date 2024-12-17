#include "UDPServer.h"
#include <cstring>
#include <iostream>
#include <string>

int main() {
    struct sockaddr_in clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    char buffer[BUFLEN];

    UDPServer server(PORT);
    std::cout << "UDP Server running on port " << PORT << "..." << std::endl;

    while (true) {
        memset(buffer, 0, BUFLEN);
        server.RecvDatagram(buffer, BUFLEN, (struct sockaddr*)&clientAddr, &clientAddrLen);
        std::cout << "Received from client: " << buffer << std::endl;

        std::string response = "Server received: ";
        response += buffer;
        server.SendDatagram((char*)response.c_str(), response.length(), (struct sockaddr*)&clientAddr, clientAddrLen);
    }

    return 0;
}
