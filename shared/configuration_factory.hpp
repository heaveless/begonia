#ifndef BEGONIA_SHARED_CONFIGURATION_FACTORY_HPP
#define BEGONIA_SHARED_CONFIGURATION_FACTORY_HPP

#include <netinet/in.h>
#include "event_handler.hpp"

class ConfigurationFactory : public EventHandler {
	public:
		virtual ~ConfigurationFactory() = default;

		virtual sockaddr_in setup() = 0;

		int init();
		void close();
};

#endif
