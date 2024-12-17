#include "UDPSocket.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    struct sockaddr_in serverAddr;
    int serverAddrLen = sizeof(serverAddr);
    char buffer[BUFLEN];

    UDPSocket client;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER);

    std::cout << "UDP Client running. Sending messages to server at " << SERVER << ":" << PORT << "..." << std::endl;

    while (true) {
        std::cout << "Enter message: ";
        std::string message;
        std::getline(std::cin, message);

        if (message.empty()) {
            break;
        }

        client.SendDatagram((char*)message.c_str(), message.length(), (struct sockaddr*)&serverAddr, serverAddrLen);
        memset(buffer, 0, BUFLEN);
        client.RecvDatagram(buffer, BUFLEN, (struct sockaddr*)&serverAddr, &serverAddrLen);
        std::cout << "Received from server: " << buffer << std::endl;
    }
    return 0;
}
