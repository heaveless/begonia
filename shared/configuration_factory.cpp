#include "configuration_factory.hpp"

int ConfigurationFactory::init() {
    int sock_instance = socket(AF_INET, SOCK_STREAM, 0);
    // if (sock_instance == -1)
    // std::cout << "Initt";

		return sock_instance;
}

void ConfigurationFactory::close() { }

