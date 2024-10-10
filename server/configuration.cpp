#include "configuration.hpp"
#include <iostream>
#include <cstring>
sockaddr_in Configuration::setup() {
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(8080);
  address.sin_addr.s_addr = INADDR_ANY;

  return address;
}

void Configuration::handle_read(int sockfd) {
    char buffer[1024];
    int bytes_read = read(sockfd, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        std::cout << "Client " << sockfd << ": " << buffer;
    } else if (bytes_read == 0) {
        std::cout << "Client " << sockfd << " disconnected\n";
        ::close(sockfd); // Cerramos la conexión
    } else {
        perror("Error reading from client");
    }
}

void Configuration::handle_write(int sockfd) {
  const char *message = "Message from server\n";
  write(sockfd, message, strlen(message));
}

void Configuration::handle_exception(int sockfd) {
    std::cout << "Exception on client " << sockfd << "\n";
}
