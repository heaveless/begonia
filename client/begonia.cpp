#include <memory>
#include "../shared/application.hpp"
#include "configuration.hpp"
#include <iostream>
int main() {
	auto config = std::make_unique<Configuration>();
	Application& app = Application::create(std::move(config));
	std::cout << "Hello, World from Client!" << std::endl;
	// app.running();

	return 0;
}
