#include "server_configuration.hpp"

void ServerConfiguration::handle_events(const struct timeval* timeout) {
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

int ServerConfiguration::setup_fd_sets() {
	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	FD_ZERO(&efds);

	FD_SET(sockfd_, &rfds);
	int maxfd = sockfd_;

	for (const auto &h : handlers_) {
    FD_SET(h.first, &rfds);
    FD_SET(h.first, &wfds);
    FD_SET(h.first, &efds);

    if (h.first > maxfd) {
	    maxfd = h.first;
    }
  }

	return maxfd;
}

void ServerConfiguration::dispatch_event_handlers() {
	if (FD_ISSET(sockfd_, &rfds)) {
		int clientfd = accept();
		if (clientfd >= 0) {
			handlers_.insert(std::make_pair(clientfd, this));
		}
	}

	for (auto it = handlers_.begin(); it != handlers_.end();) {
    if (FD_ISSET(it->first, &rfds)) {
      it->second->handle_read(it->first);
    }
    if (FD_ISSET(it->first, &wfds)) {
      it->second->handle_write(it->first);
    }
    if (FD_ISSET(it->first, &efds)) {
      it->second->handle_exception(it->first);
    }
	}
}

void ServerConfiguration::bind() { 
	if (::bind(sockfd_, (struct sockaddr*)&address_, sizeof(address_)) == -1) {
    std::runtime_error("Bind sock");
    ::close(sockfd_);
    exit(EXIT_FAILURE);
  }
}

void ServerConfiguration::listen() {
	if (::listen(sockfd_, 5) == -1) {
    std::runtime_error("Listen sock");
    ::close(sockfd_);
    exit(EXIT_FAILURE);
  }
 }

int ServerConfiguration::accept() { 
	struct sockaddr_in client_address;
  socklen_t client_len = sizeof(client_address);
  int client_sockfd = ::accept(sockfd_, (struct sockaddr*)&client_address, &client_len);
  if (client_sockfd == -1) {
    std::runtime_error("Accept error");
    ::close(sockfd_);
    exit(EXIT_FAILURE);
  }

	return client_sockfd;
}