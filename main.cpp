#include <iostream>
#include <sys/socket.h>	// socket()
#include <arpa/inet.h>	// htons()
#include <netinet/in.h>	// sockaddr_in

// #include <netinet/in.h>	// sockaddr_in
int main()
{
	std::cout << "This is a cool test\n";

	int socketFD = socket(AF_INET, SOCK_STREAM, 0);
	std::cout << "Socket value: " << socketFD << "\n";

	sockaddr_in address;
	address.sin_port = htons(8080);
	address.sin_family = AF_INET;
	address.sin_addr = INADDR_ANY;

	
}