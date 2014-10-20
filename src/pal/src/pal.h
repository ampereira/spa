#ifndef PAL_LIB
#define PAL_LIB

#include "pal_measure.h"
#include <cstdlib>
#include <string>
#include <papi.h>

#ifndef MAIN
	#define SCOPE extern
#else
	#define SCOPE
#endif

namespace Hardware {

	int newMeasure (std::vector<std::string>);
	bool start (unsigned);
	bool stop (unsigned);
	void report (unsigned);
}

#endif
