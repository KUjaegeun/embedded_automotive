
#pragma once
#define BUFSIZ 512

class server
{
private:
	WSADATA wsa;
	SOCKADDR_IN srvAddr;
	int addrLen;
public:
	SOCKET clntSd;

	server();
	~server();

	int serverconnect(char* ip, char* port);
};