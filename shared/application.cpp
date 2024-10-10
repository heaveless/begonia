#include "application.hpp"

Application::Application(std::unique_ptr<ConfigurationFactory> config) {
	config_ = std::move(config);
}

Application::~Application() { }

Application& Application::create(std::unique_ptr<ConfigurationFactory> config) {
  static Application instance(std::move(config));
  return instance;
}

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

