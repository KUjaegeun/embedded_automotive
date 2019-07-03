
#include "stdafx.h"
#include "server.h"

extern DWORD recvTimeout;

server::server()
{
}


server::~server()
{
}

int server::serverconnect(char* ip, char* port)
{
	
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0);
	clntSd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clntSd == INVALID_SOCKET);
	ZeroMemory(&srvAddr, sizeof(srvAddr));
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(atoi(port));
	srvAddr.sin_addr.s_addr = inet_addr(ip);
	addrLen = sizeof(srvAddr);
	if (connect(clntSd, (SOCKADDR *)&srvAddr, sizeof(srvAddr)) == SOCKET_ERROR) {
		return 0;//0이 반환되면 연결실패
	}
	setsockopt(clntSd, SOL_SOCKET, SO_RCVTIMEO, (char *)&recvTimeout, sizeof(recvTimeout));
	return 1;
}
