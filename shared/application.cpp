#include "application.hpp"

#include <iostream>
Application::Application(std::unique_ptr<ConfigurationFactory> config) {
	// sockfd_ = sockfd;
	config_ = std::move(config);
}

Application::~Application() { }

Application& Application::create(std::unique_ptr<ConfigurationFactory> config) {
  static Application instance(std::move(config));
  return instance;
}

// void Application::dispatch_event_handlers() {
	// int sockfd = context_->getSockfd();
	// auto config = context_->getConfig();
	// auto handlers = config_->getHandlers();

	// if (auto* client = dynamic_cast<ClientConfiguration*>(config.get())) {

	// } else if (auto* server = dynamic_cast<ServerConfiguration*>(config.get())) {
	// 	if (FD_ISSET(sockfd, &rfds)) {
	// 		int clientfd = config->accept(sockfd);
	// 		if (clientfd >= 0) {
	// 			handlers->insert(std::make_pair(clientfd, config));
	// 		}
	// 	}

	// 	for (auto it = handlers.begin(); it != handlers.end();) {
  //   	if (FD_ISSET(it->first, &rfds)) {
  //     	it->second->handle_read(it->first);
  //   	}
  //   	if (FD_ISSET(it->first, &wfds)) {
  //     	it->second->handle_write(it->first);
  //   	}
  //   	if (FD_ISSET(it->first, &efds)) {
  //     	it->second->handle_exception(it->first);
  //   	}
	// 	}
	// }
// }

// int Application::setup_fd_sets() {
// 	FD_ZERO(&rfds);
// 	FD_ZERO(&wfds);
// 	FD_ZERO(&efds);

// 	if (/*server*/) {
// 		for (const auto &h : handlers_) {
//     	FD_SET(h.first, &rfds);
//     	FD_SET(h.first, &wfds);
//     	FD_SET(h.first, &efds);

//     	if (h.first > maxfd) {
// 	      maxfd = h.first;
//     	}
//   	}
// 	} else {

// 	}

	// FD_SET(sockfd, &rfds);
	// int maxfd = sockfd;

	// auto handlers = context_->getHandlers();

	// for (const auto &h : handlers) {
  //   FD_SET(h.first, &rfds);
  //   FD_SET(h.first, &wfds);
  //   FD_SET(h.first, &efds);

  //   if (h.first > maxfd) {
  //     maxfd = h.first;
  //   }
  // }

	// return maxfd;
// 	return 0;
// }

// void Application::handle_events(const struct timeval* timeout) {
// 	struct timeval tv;
// 	struct timeval* tv_ptr = nullptr;
// 	if (timeout != nullptr) {
// 		tv = *timeout;
// 		tv_ptr = &tv;
// 	}

	// int maxfd = setup_fd_sets();

	// int count = select(maxfd + 1, &rfds, &wfds, &efds, tv_ptr);
	// if (count > 0) {
	// 	dispatch_event_handlers();
	// }
// }

void Application::running() {
	config_->init();
	config_->setup();

	if (auto* client = dynamic_cast<ClientConfiguration*>(config_.get())) {
		client->connect();
	} else if (auto* server = dynamic_cast<ServerConfiguration*>(config_.get())) {
		server->bind();
		server->listen();
	}

	struct timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	while(1) {
		config_->handle_events(&timeout);
	}

	config_->close();
}

