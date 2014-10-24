#ifdef PAPI_SUPPORT

#ifndef EVENTSET 
#define EVENTSET 

#include <papi.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "enum_types.h"
#include "event.h"


namespace Hardware {
	class EventSet {
		int *events;
		unsigned eventset_size = 0;	// amount of eventsets
		unsigned total_events;  // amount of events
		std::vector<Event> event_list;

	public:
		EventSet ();
		EventSet (int);
		EventSet (std::vector<std::string>);
		bool create (std::vector<std::string>);
		int operator[] (unsigned);
		inline unsigned size (void) {return event_list.size(); }
		Event getEvent (unsigned);
		unsigned numberOfEvents (void);
		void addResult(unsigned, long long unsigned);
	};
}

#endif
#endif