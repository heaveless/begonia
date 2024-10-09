#include "application.hpp"
#include "client_configuration.hpp"
#include "server_configuration.hpp"
#include <iostream>
Application::Application(std::unique_ptr<ConfigurationFactory> config): dispatching_(false) {
	config_ = std::move(config);

	int ret = pipe(wakeup_pipe_.data());
	if (ret != 0) {
		std::runtime_error("pipe");
	}
}

Application::~Application() {
	unblock();
	close(wakeup_pipe_[0]);
	close(wakeup_pipe_[1]);
}

Application& Application::create(std::unique_ptr<ConfigurationFactory> config) {
	handle_ = config->init();
	config->setup();

	if (auto* client = dynamic_cast<ClientConfiguration*>(config.get())) {
		client->connect();
	} else if (auto* server = dynamic_cast<ServerConfiguration*>(config.get())) {
		server->bind();
		server->listen();
	}

  static Application instance(std::move(config));
  return instance;
}

void Application::register_event_handler(int handle, EventHandler* event_handler, unsigned int event_type) {
	if (event_type & EventType::kReadEvent) {
		read_event_handlers_.insert(std::make_pair(handle, event_handler));
	}
	if (event_type & EventType::kWriteEvent) {
		write_event_handlers_.insert(std::make_pair(handle, event_handler));
	}
	if (event_type & EventType::kExceptionEvent) {
		exception_event_handlers_.insert(std::make_pair(handle, event_handler));
	}

	if (!dispatching_) {
    send_wakeup();
  }
}

void Application::unregister_event_handler(int handle, unsigned int event_type) {
	size_t count = 0;
	if (event_type & EventType::kReadEvent) {
		count += read_event_handlers_.erase(handle);
	}
	if (event_type & EventType::kWriteEvent) {
		count += write_event_handlers_.erase(handle);
	}
	if (event_type & EventType::kExceptionEvent) {
		count += exception_event_handlers_.erase(handle);
	}

  if (count > 0 && !dispatching_) {
    send_wakeup();
  }
}

void Application::dispatch_event_handlers() {
	dispatching_ = true;

	if (FD_ISSET(wakeup_pipe_[0], &rfds)) {
    handle_wakeup();
  }

	for (auto it = read_event_handlers_.begin(); it != read_event_handlers_.end();) {
		int handle = it->first;
		auto entry = it->second;

		if (FD_ISSET(handle, &rfds)) {
			entry->handle_read(handle);
		}

		++it;
	}

	for (auto it = write_event_handlers_.begin(); it != write_event_handlers_.end();) {
		int handle = it->first;
		auto entry = it->second;

		if (FD_ISSET(handle, &wfds)) {
			entry->handle_write(handle);
		}
		
		++it;
	}

	for (auto it = exception_event_handlers_.begin(); it != exception_event_handlers_.end();) {
		int handle = it->first;
		auto entry = it->second;

		if (FD_ISSET(handle, &efds)) {
			entry->handle_exception(handle);
		}
		
		++it;
	}

	dispatching_ = false;
}

int Application::setup_fd_sets() {
	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	FD_ZERO(&efds);

	FD_SET(wakeup_pipe_[0], &rfds);
	int maxfd = wakeup_pipe_[0];

	for (const auto& p : read_event_handlers_) {
		FD_SET(p.first, &rfds);
		maxfd = std::max(maxfd, p.first);
	}

	for(const auto& p : write_event_handlers_) {
		FD_SET(p.first, &wfds);
		maxfd = std::max(maxfd, p.first);
	}

	for(const auto& p : exception_event_handlers_) {
		FD_SET(p.first, &efds);
		maxfd = std::max(maxfd, p.first);
	}

	return maxfd;
}

void Application::handle_events(const struct timeval* timeout) {
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

void Application::unblock() {
	send_wakeup();
}

void Application::send_wakeup() {
	int ret;
	char dummy;

	ret = write(wakeup_pipe_[1], &dummy, sizeof(dummy));
	if (ret != sizeof(dummy)) {
		std::runtime_error("write");
	}
}

void Application::handle_wakeup() {
	int ret;
	char dummy;

	ret = read(wakeup_pipe_[0], &dummy, sizeof(dummy));
	if (ret != sizeof(dummy)) {
		std::runtime_error("read");
	}
}

void Application::running() {
	struct timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

	// while(1) {

		handle_events(&timeout);
	// }
}

