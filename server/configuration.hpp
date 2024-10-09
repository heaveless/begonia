#ifndef BEGONIA_SERVER_CONFIGURATION_HPP
#define BEGONIA_SERVER_CONFIGURATION_HPP

#include "../shared/server_configuration.hpp"

class Configuration : public ServerConfiguration {
	public:
		sockaddr_in setup() override;
		void handle_read(int) override;
    void handle_write(int) override;
		void handle_exception(int) override;
};

#endif