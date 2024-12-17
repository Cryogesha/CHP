#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // For close()
#include <cstring>  // For memset()
#include <iostream> // For std::cerr

#include "UDPSocket.h"

UDPSocket::UDPSocket() {
    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
}

UDPSocket::~UDPSocket() {
    close(s);
}

int UDPSocket::SendDatagram(char* msg, unsigned int msglen, struct sockaddr* si_dest, unsigned int slen) {
    if (sendto(s, msg, (int)msglen, 0, si_dest, slen) < 0) {
        perror("sendto() failed");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int UDPSocket::RecvDatagram(char* buf, unsigned int buflen, struct sockaddr* si_dest, int* slen) {
    if (recvfrom(s, buf, BUFLEN, 0, si_dest, reinterpret_cast<socklen_t *>(slen)) < 0) {
        perror("recvfrom() failed");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int UDPSocket::WSAInit() {
    return 0;
}
