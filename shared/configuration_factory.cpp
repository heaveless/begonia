#include "configuration_factory.hpp"

void ConfigurationFactory::init() {
	sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd_ == -1) {
    std::runtime_error("Init sock");
    exit(EXIT_FAILURE);
  }
}

void ConfigurationFactory::close() { 
	::close(sockfd_);
}

