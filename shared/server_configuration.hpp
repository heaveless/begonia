#ifndef BEGONIA_SHARED_SERVER_CONFIGURATION_HPP
#define BEGONIA_SHARED_SERVER_CONFIGURATION_HPP

#include "configuration_factory.hpp"

class ServerConfiguration : public ConfigurationFactory {
	public:
		virtual ~ServerConfiguration() = default;

		void bind();
		void listen();
		void accept();
};

#endif
