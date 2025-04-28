#include <iostream>
#include <sys/socket.h>	// socket()
#include <arpa/inet.h>	// htons()

// #include <netinet/in.h>	// sockaddr_in
int main()
{
	std::cout << "This is a cool test\n";
	int socketFD = socket(AF_INET, SOCK_STREAM, 0);
	uint16_t testInt = htons(257);
	std::cout << "Socket value: " << socketFD << "\n";
	std::cout << "Testint value: " << testInt << "\n";
}