#ifndef BEGONIA_SHARED_REACTOR_HPP
#define BEGONIA_SHARED_REACTOR_HPP

#include <sys/select.h>
#include <atomic>
#include <array>
#include <map>
#include "event_handler.hpp"

enum EventType {
	kReadEvent = 1,
	kWriteEvent = 2,
	kExceptionEvent = 3
};

class Reactor {
	private:
		struct EventHandlerMapEntry {
			EventHandler* event_handler_;
			bool one_shot_;
		};

		fd_set rfds, wfds, efds;

		std::array<int,2> wakeup_pipe_;
		std::atomic_bool dispatching_;
		
		std::map<int,EventHandlerMapEntry> read_event_handlers_;
		std::map<int,EventHandlerMapEntry> write_event_handlers_;
		std::map<int,EventHandlerMapEntry> exception_event_handlers_;

		void dispatch_event_handlers();
		int setup_fd_sets();
		void send_wakeup();
		void handle_wakeup();

	public:
		Reactor();
		~Reactor();

		void register_event_handler(int, EventHandler*, unsigned int, bool);
		void unregister_event_handler(int, unsigned int);
		void handle_events(const struct timeval*);
		void unblock();
};

#endif
