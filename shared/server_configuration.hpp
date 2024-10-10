#ifndef BEGONIA_SHARED_SERVER_CONFIGURATION_HPP
#define BEGONIA_SHARED_SERVER_CONFIGURATION_HPP

#include "configuration_factory.hpp"

class ServerConfiguration : public ConfigurationFactory {
	private:
			std::map<int, EventHandler*> handlers_;

	public:
		virtual ~ServerConfiguration() = default;

		int setup_fd_sets() override;
		void handle_events(const struct timeval*) override;
		void dispatch_event_handlers() override;

		void bind();
		void listen();
		int accept();
};

#endif
