#ifndef BEGONIA_CLIENT_CONFIGURATION_HPP
#define BEGONIA_CLIENT_CONFIGURATION_HPP

#include "../shared/client_configuration.hpp"

class Configuration : public ClientConfiguration {
	public:
		sockaddr_in setup() override;
		void handle_read(int) override;
    void handle_write(int) override;
		void handle_exception(int) override;
};

#endif