#ifndef BEGONIA_SHARED_APPLICATION_HPP
#define BEGONIA_SHARED_APPLICATION_HPP

#include <sys/select.h>
#include <memory>
#include <array>
#include <atomic>
#include "configuration_factory.hpp"
#include "client_configuration.hpp"
#include "server_configuration.hpp"

enum EventType {
  kReadEvent = 1,
  kWriteEvent = 2,
  kExceptionEvent = 3
};

class Application {
	private:
		Application(std::unique_ptr<ConfigurationFactory>);

		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		std::unique_ptr<ConfigurationFactory> config_;

	public:
		~Application();

		static Application& create(std::unique_ptr<ConfigurationFactory>);
	
		void running();
};

#endif 
