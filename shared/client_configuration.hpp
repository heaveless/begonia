#ifndef BEGONIA_SHARED_CLIENT_CONFIGURATION_HPP
#define BEGONIA_SHARED_CLIENT_CONFIGURATION_HPP

#include "configuration_factory.hpp"

class ClientConfiguration : public ConfigurationFactory {
	private:
		EventHandler* handler_;

	public:
		virtual ~ClientConfiguration() = default;
		
		int setup_fd_sets() override;
		void handle_events(const struct timeval*) override;
		void dispatch_event_handlers() override;

		void connect();
};

#endif
