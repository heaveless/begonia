#ifndef BEGONIA_SHARED_CLIENT_CONFIGURATION_HPP
#define BEGONIA_SHARED_CLIENT_CONFIGURATION_HPP

#include "configuration_factory.hpp"

class ClientConfiguration : public ConfigurationFactory {
	public:
		virtual ~ClientConfiguration() = default;
		
		void connect();
};

#endif
