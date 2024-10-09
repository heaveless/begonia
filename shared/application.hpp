#ifndef BEGONIA_SHARED_APPLICATION_HPP
#define BEGONIA_SHARED_APPLICATION_HPP

#include <sys/select.h>
#include <memory>
#include <array>
#include <map>
#include <utility>
#include <atomic>
#include <stdexcept>
#include <unistd.h>
#include "configuration_factory.hpp"

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

		fd_set rfds, wfds, efds;
		std::array<int, 2> wakeup_pipe_;
		std::atomic_bool dispatching_;

		std::unique_ptr<ConfigurationFactory> config_;
		std::map<int, EventHandler*> read_event_handlers_;
		std::map<int, EventHandler*> write_event_handlers_;
		std::map<int, EventHandler*> exception_event_handlers_;

		void register_event_handler(int, EventHandler*, unsigned int);
		void unregister_event_handler(int, unsigned int);
		void handle_events(const struct timeval*);
  	void dispatch_event_handlers();
		void unblock();
		void send_wakeup();
		void handle_wakeup();
		int setup_fd_sets();

	public:
		~Application();

		static Application& create(std::unique_ptr<ConfigurationFactory>);
	
		void running();
};

#endif 
