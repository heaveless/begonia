#include "application.hpp"
#include "client_configuration.hpp"
#include "server_configuration.hpp"

Application::Application() { }

Application& Application::create(std::unique_ptr<Configuration> config) {
	config->create();
	config->setup();

	if (auto* client = dynamic_cast<ClientConfiguration*>(config.get())) {
		client->connect();
		client->send();
		client->recieve();
	} else if (auto* server = dynamic_cast<ServerConfiguration*>(config.get())) {
		server->bind();
		server->listen();
		server->accept();
		server->send();
		server->recieve();
	}

	config->close();

  static Application instance;
  return instance;
}

void Applciation::dispatch_event_handlers() {
	dispatching_ = true;

	if (FD_ISSET(makeup_pipe_[0], &rfds)) {
		handle_wakeup();
	}
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
	if (cout > 0) {
		dispatch_event_handlers();
	}
}

void Application::running() {
	struct timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

	while(1) {
		handle_events(&timeout);
	}
}

