#include "UDPServer.h"
#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <arpa/inet.h>

void handleClient(UDPServer& server, struct sockaddr_in clientAddr, int clientAddrLen, char* buffer) {
    std::cout << "Thread started for client: " << inet_ntoa(clientAddr.sin_addr)
              << ":" << ntohs(clientAddr.sin_port) << std::endl;
    std::string response = "Server received: ";
    response += buffer;
    server.SendDatagram((char*)response.c_str(), response.length(), (struct sockaddr*)&clientAddr, clientAddrLen);
    std::cout << "Thread ended for client: " << inet_ntoa(clientAddr.sin_addr)
              << ":" << ntohs(clientAddr.sin_port) << std::endl;
}

int main() {
    struct sockaddr_in clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    char buffer[BUFLEN];
    std::vector<std::thread> threads;

    UDPServer server(PORT);
    std::cout << "UDP Server running on port " << PORT << "..." << std::endl;

    while (true) {
        memset(buffer, 0, BUFLEN);
        server.RecvDatagram(buffer, BUFLEN, (struct sockaddr*)&clientAddr, &clientAddrLen);
        std::cout << "Received from client: " << buffer << std::endl;

        threads.emplace_back(handleClient, std::ref(server), clientAddr, clientAddrLen, strdup(buffer));
    }

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    return 0;
}
