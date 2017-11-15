#include <iostream>
#include "WSASession.h"
#include "TCPSocket.h"

int main() {

	try {
		WSASession session;
		TCPSocket socket;

		socket.Bind(19975);
		socket.Listen();
		socket.Accept();
		
		try {
			std::string buffor;
			while (true) {
				buffor = socket.Recieve(100);
				std::cout << buffor << std::endl;
				socket.Send(buffor);
			}
		}
		catch (ClosingConnectionException& ex) {
			std::cerr << ex.what() << std::endl;
		}

		socket.Shutdown();
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}