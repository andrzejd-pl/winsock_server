#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

class TCPSocket
{
private:
	SOCKET sock;
	SOCKET client;
public:
	TCPSocket();
	~TCPSocket();

	void Bind(unsigned int port);
	void Listen();
	void Accept();
	std::string Recieve(const int& bufforLenght);
	void Send(const std::string& data);
	void Shutdown();
};

class ClosingConnectionException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "Connection closing...";
	}
};