#pragma once
#include <winsock2.h>
#pragma comment (lib, "Ws2_32.lib")

class WSASession
{
private:
	WSAData data;
public:
	WSASession();
	~WSASession();
};

