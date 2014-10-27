#include "measure.h"

#ifdef PAPI_SUPPORT

#include "pal_measure.h"
#include <cstdlib>
#include <string>
#include <papi.h>


namespace Hardware {

	int newMeasure (std::vector<std::string>);
	bool start (unsigned);
	bool stop (unsigned);
	void report (unsigned);
}

#endif