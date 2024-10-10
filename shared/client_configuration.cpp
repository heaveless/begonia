#include "client_configuration.hpp"

void ClientConfiguration::handle_events(const struct timeval* timeout) {
	struct timeval tv;
	struct timeval* tv_ptr = nullptr;
	if (timeout != nullptr) {
		tv = *timeout;
		tv_ptr = &tv;
	}

	int maxfd = setup_fd_sets();

	int count = select(maxfd + 1, &rfds, &wfds, &efds, tv_ptr);
	if (count > 0) {
		dispatch_event_handlers();
	}
}

int ClientConfiguration::setup_fd_sets() {
	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	FD_ZERO(&efds);
	
	FD_SET(sockfd_, &rfds);
  FD_SET(sockfd_, &wfds);
  FD_SET(sockfd_, &efds);
	
	return sockfd_;
}

void ClientConfiguration::dispatch_event_handlers() {
	if (FD_ISSET(sockfd_, &rfds)) {
    handle_read(sockfd_);
  }
  if (FD_ISSET(sockfd_, &wfds)) {
    handle_write(sockfd_);
  }
  if (FD_ISSET(sockfd_, &efds)) {
    handle_exception(sockfd_);
  }
}

void ClientConfiguration::connect() { 
	if (::connect(sockfd_, (struct sockaddr*)&address_, sizeof(address_)) == -1) {
    std::runtime_error("Connect sock");
    ::close(sockfd_);
    exit(EXIT_FAILURE);
  }
}