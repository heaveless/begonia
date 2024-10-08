#ifndef BEGONIA_SHARED_APPLICATION_HPP
#define BEGONIA_SHARED_APPLICATION_HPP

#include <memory>
#include "configuration.hpp"

class Application {
	private:
		Application();

		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

	public:
		static Application& create(std::unique_ptr<Configuration>);
	
		void running();
};

#endif 
