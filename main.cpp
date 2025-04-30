#include <iostream>
#include <sys/socket.h>	// socket()
#include <arpa/inet.h>	// htons()
#include <netinet/in.h>	// sockaddr_in
#include <stdexcept> 
#include <unistd.h>

// #include <netinet/in.h>	// sockaddr_in
int main(int argc, char** argv)
{
	if (argc != 2)
		throw std::runtime_error("Wrong arg count!");
	int port = atoi(argv[1]);

	// Socket creation
	int socketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFD == -1)
		throw std::runtime_error("socket() failed!");
	std::cout << "Socket value: " << socketFD << "\n";

	// Definining address
	sockaddr_in address;
	address.sin_port = htons(port);
	address.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
	std::cout << "Address set." << "\n";

	// Binding the socket
		// 2. Arg type is sockaddr_ which works for sockaddr_in and sockaddr_in6
		// 3. Arg is just size 
	int ret = bind(socketFD, (struct sockaddr*)&address, sizeof(address));
	if (ret == -1)
		throw std::runtime_error("bind() failed!");
	std::cout << "Socket bound." << "\n";
	
	// Start listening
		// second arg is size of waiting room (how many incoming connections are queued if i have
		// yet accepted the last one)
	ret = listen(socketFD, 0);
	if (ret == -1)
		throw std::runtime_error("listen() failed!");
	std::cout << "Socket listening." << "\n";

	// First client
	{
		// Preparing client address
		sockaddr_in clientAddress;
		socklen_t client_len = sizeof(clientAddress);

		// Accepting client connection
		int client_fd = accept(socketFD, (struct sockaddr*)&clientAddress, &client_len);
		if (client_fd == -1)
			throw std::runtime_error("accept() failed!");
		std::cout << "Client connected.\n";

		// Reverse engineering client details
		{
			char buf[16];
			inet_ntop(AF_INET,  &(clientAddress.sin_addr), buf, INET_ADDRSTRLEN); 
			std::cout << "\tSocket value: " << client_fd << "\n"
			<< "\tIP address: " << buf << "\n"
			<< "\tPort: " << ntohs(clientAddress.sin_port) << "\n";
		}
		// Printing request
		{
			char buffer[4096];
			int bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
			buffer[bytes] = '\0'; // Null-terminate it!
			std::cout << buffer << std::endl; // See the browser's HTTP request!
		}
		// Responding 
		write(client_fd, "HTTP/1.1 200 OK\nContent-Length: 13\n\nHello, world!\n", 50);
	}

	// Second client
	{
		// Preparing client address
		sockaddr_in clientAddress;
		socklen_t client_len = sizeof(clientAddress);

		// Accepting client connection
		int client_fd = accept(socketFD, (struct sockaddr*)&clientAddress, &client_len);
		if (client_fd == -1)
			throw std::runtime_error("accept() failed!");
		std::cout << "Client connected.\n";

		// Reverse engineering client details
		{
			char buf[16];
			inet_ntop(AF_INET,  &(clientAddress.sin_addr), buf, INET_ADDRSTRLEN); 
			std::cout << "\tSocket value: " << client_fd << "\n"
			<< "\tIP address: " << buf << "\n"
			<< "\tPort: " << ntohs(clientAddress.sin_port) << "\n";
		}
		// Printing request
		{
			char buffer[4096];
			int bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
			buffer[bytes] = '\0'; // Null-terminate it!
			std::cout << buffer << std::endl; // See the browser's HTTP request!
		}
		// Responding 
		write(client_fd, "HTTP/1.1 200 OK\nContent-Length: 13\n\nHello, girls!\n", 50);
	}
}