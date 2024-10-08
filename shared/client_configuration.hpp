#ifndef BEGONIA_SHARED_CLIENT_CONFIGURATION_HPP
#define BEGONIA_SHARED_CLIENT_CONFIGURATION_HPP

#include "configuration.hpp"

class ClientConfiguration : public Configuration {
	public:
		void send() override;
    void receive() override;

		void connect();
};

#endif
