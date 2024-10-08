#ifndef BEGONIA_SHARED_EVENT_HANDLER_HPP
#define BEGONIA_SHARED_EVENT_HANDLER_HPP

class EventHandler {
	public:
		virtual ~EventHandler() = default;

		virtual void handle_read(int handle) {}
		virtual void handle_write(int handle) {}
		virtual void handle_exception(int handle) {}
};

#endif
