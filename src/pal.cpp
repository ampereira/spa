#ifdef PAPI_SUPPORT

#include "spa.h"

using namespace std;

namespace Hardware {
	std::vector<Measure> measurements;

	int newMeasure (vector<string> counters) {

		PAPI_library_init(PAPI_VER_CURRENT);
		
		EventSet ev (counters);
		Measure mm (ev);

		measurements.push_back(mm);

		return measurements.size() - 1;
	}

	bool start (unsigned m_id) {
		return measurements[m_id].start();
	}

	bool stop (unsigned m_id) {
		return measurements[m_id].stop();
	}

	void report (unsigned m_id) {
		measurements[m_id].report();
	}
}
#endif