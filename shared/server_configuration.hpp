#ifndef BEGONIA_SHARED_SERVER_CONFIGURATION_HPP
#define BEGONIA_SHARED_SERVER_CONFIGURATION_HPP

#include "configuration.hpp"

class ServerConfiguration : public Configuration {
	public:
		void send() override;
    void receive() override;

		void bind();
		void listen();
		void accept();
};

#endif
