#ifndef BEGONIA_SHARED_EVENT_HANDLER_HPP
#define BEGONIA_SHARED_EVENT_HANDLER_HPP

class EventHandler {
	public:
		virtual ~EventHandler() = default;

		virtual void handle_read(int) = 0;
		virtual void handle_write(int) = 0;
		virtual void handle_exception(int) = 0;
};

#endif
