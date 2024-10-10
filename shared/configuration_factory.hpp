#ifndef BEGONIA_SHARED_CONFIGURATION_FACTORY_HPP
#define BEGONIA_SHARED_CONFIGURATION_FACTORY_HPP

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <map>
#include <utility>
#include <stdexcept>
#include "event_handler.hpp"

class ConfigurationFactory : public EventHandler {
	protected:
		fd_set rfds, wfds, efds;
		int sockfd_;
		sockaddr_in address_;

		virtual int setup_fd_sets() = 0;
		virtual void dispatch_event_handlers() = 0;

	public:
		virtual ~ConfigurationFactory() = default;

		virtual sockaddr_in setup() = 0;
		virtual void handle_events(const struct timeval*) = 0;

		void init();
		void close();
};

#endif
