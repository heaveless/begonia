#include "configuration.hpp"
#include <iostream>
#include <cstring>
sockaddr_in Configuration::setup() {
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(8080);
  address.sin_addr.s_addr = inet_addr("127.0.0.1");

  return address;
}

void Configuration::handle_read(int sockfd) {
    char buffer[1024];
    int bytes_read = read(sockfd, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        std::cout << "Server: " << buffer;
    } else if (bytes_read == 0) {
        std::cout << "Server closed the connection\n";
        ::close(sockfd); // Cerramos la conexión
        exit(0);
    } else {
        perror("Error reading from server");
    }
}

void Configuration::handle_write(int sockfd) {
    const char *message = "Hello from client\n";
    write(sockfd, message, strlen(message));
}

void Configuration::handle_exception(int sockfd) {
 std::cout << "Exception on server socket " << sockfd << "\n";
}
