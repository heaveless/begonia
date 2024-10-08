#ifndef BEGONIA_SHARED_CONFIGURATION_HPP
#define BEGONIA_SHARED_CONFIGURATION_HPP

class Configuration {
	public:
		virtual ~Configuration() = default;
		
		void create();
		void setup();
		void close();

		virtual void send() = 0;
		virtual void receive() = 0;
};

#endif
