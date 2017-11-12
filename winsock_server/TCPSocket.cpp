#include "TCPSocket.h"
#include <system_error>


TCPSocket::TCPSocket() {
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
		throw std::system_error(WSAGetLastError(), std::system_category(), "Error opening socket");
}


TCPSocket::~TCPSocket() {
	closesocket(client);
}

void TCPSocket::Bind(unsigned int port) const {
	sockaddr_in add;
	add.sin_family = AF_INET;
	add.sin_addr.s_addr = htonl(INADDR_ANY);
	add.sin_port = port;
	int ret = bind(sock, reinterpret_cast<SOCKADDR *>(&add), sizeof(add));
	if (ret == SOCKET_ERROR)
		throw std::system_error(WSAGetLastError(), std::system_category(), "Bind failed");
}

void TCPSocket::Listen() const {
	int ret = listen(sock, SOMAXCONN);
	if (ret == SOCKET_ERROR)
		throw std::system_error(WSAGetLastError(), std::system_category(), "Listen failed");

}

SOCKET TCPSocket::Accept() const {
	SOCKET client = accept(sock, NULL, NULL);
	if (client == INVALID_SOCKET)
		throw std::system_error(WSAGetLastError(), std::system_category(), "Accept failed");
	return client;
}

std::string TCPSocket::Recieve() const {
	char b[100];

	int ret = recv(client, b, 100, 0);
	if (ret < 0)
		throw std::system_error(WSAGetLastError(), std::system_category(), "Receive failed");
	if (ret == 0)
		throw ClosingConnectionException();

	std::string buff(std::begin(b), std::end(b));
	return buff;
}

void TCPSocket::Send(const std::string& data) const {
	int ret = send(client, data.c_str(), data.size(), 0);
	if (ret == SOCKET_ERROR)
		throw std::system_error(WSAGetLastError(), std::system_category(), "Send failed");
}

void TCPSocket::Shutdown()
{
	int ret = shutdown(client, SD_SEND);
	if(ret == SOCKET_ERROR)
		throw std::system_error(WSAGetLastError(), std::system_category(), "Shutdown failed");
}
