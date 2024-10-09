#include <memory>
#include "../shared/application.hpp"
#include "configuration.hpp"

int main() {
	auto config = std::make_unique<Configuration>();
	Application& app = Application::create(std::move(config));

	app.running();

	return 0;
}
