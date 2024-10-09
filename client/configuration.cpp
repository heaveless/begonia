#include "configuration.hpp"

sockaddr_in Configuration::setup() {
  struct sockaddr_in address;
  // address.sin_family = AF_INET;
  // address.sin_port = htons(8080);
  // address.sin_addr.s_addr = inet_addr("127.0.0.1");

  return address;
}

void Configuration::handle_read(int handle) {

}

void Configuration::handle_write(int handle) {

}

void Configuration::handle_exception(int handle) {

}
