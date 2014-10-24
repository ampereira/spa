#ifdef PAPI_SUPPORT

#ifndef MEASURE
#define MEASURE

#include "eventset.h"
#include <string>
#include <vector>

// GCC hacks for optimizing conditional blocks
#define likely(x)	__builtin_expect(!!(x), 1)	// likely for the condition to be true
#define unlikely(x)	__builtin_expect(!!(x), 0)	// unlikely for the condition to be true

namespace Hardware {
	class Measure {
		EventSet eventset;
		unsigned event_number;
		unsigned event_rep;
		unsigned repetitions;
		bool predefined_reps;

	public:
		Measure (EventSet&, unsigned);
		Measure (EventSet&);
		Measure (std::vector<std::string>);
		bool start (void);
		bool stop (void);
		void report (void);
		unsigned iterations (void);
		void addResult(unsigned, long long unsigned);
		EventSet getEventset(void) const;
	};
}

#endif
#endif