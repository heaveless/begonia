add_library(shared
	application.cpp
	configuration_factory.cpp
	client_configuration.cpp
	server_configuration.cpp
)

target_include_directories(shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
