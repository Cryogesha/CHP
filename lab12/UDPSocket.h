#pragma once
#include <stdio.h>
#ifndef _WIN32
using SOCKET = int;
#endif

#define SERVER "127.0.0.1"	
#define BUFLEN 	1024		
#define PORT 8888			

class UDPSocket
{
protected:
	SOCKET s;

public:
	static int WSAInit();

	UDPSocket();
	virtual ~UDPSocket();

	int SendDatagram(char* msg, unsigned int msglen, struct sockaddr* si_dest, unsigned int slen);
	int RecvDatagram(char* buf, unsigned int buflen, struct sockaddr* si_dest, int *slen);
};
