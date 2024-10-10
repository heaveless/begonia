#include "configuration.hpp"

sockaddr_in Configuration::setup() {
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(8080);
  address.sin_addr.s_addr = INADDR_ANY;

  return address;
}

void Configuration::handle_read(int sockfd) {

}

void Configuration::handle_write(int sockfd) {

}

void Configuration::handle_exception(int sockfd) {

}
