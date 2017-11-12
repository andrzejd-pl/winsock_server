#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

class TCPSocket
{
private:
	SOCKET sock;
public:
	TCPSocket();
	~TCPSocket();

	void Bind(unsigned int port) const;
	void Listen() const;
	SOCKET Accept() const;
	std::string Recieve(SOCKET& client);
	void Send(SOCKET& client, const std::string& data) const;
};

class ClosingConnectionException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "Connection closing...";
	}
};