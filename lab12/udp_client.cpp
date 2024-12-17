#include "UDPSocket.h"
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <arpa/inet.h>

void sendMessages(const std::string& message, int threadId, int numMessages, const struct sockaddr_in& serverAddr, int serverAddrLen) {
    UDPSocket client;

    for (int i = 0; i < numMessages; ++i) {
        std::string msg = "Thread " + std::to_string(threadId) + ": " + message + " " + std::to_string(i + 1);
        client.SendDatagram((char*)msg.c_str(), msg.length(), (struct sockaddr*)&serverAddr, serverAddrLen);

        char buffer[BUFLEN];
        memset(buffer, 0, BUFLEN);
        client.RecvDatagram(buffer, BUFLEN, (struct sockaddr*)&serverAddr, (int*)&serverAddrLen);

        std::cout << "Thread " << threadId << " received: " << buffer << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER);

    int numThreads = 3;
    int messagesPerThread = 5;
    std::string message = "Hello from client";

    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(sendMessages, message, i + 1, messagesPerThread, serverAddr, sizeof(serverAddr));
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "All threads finished." << std::endl;
    return 0;
}
