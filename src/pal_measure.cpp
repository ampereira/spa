#ifdef PAPI_SUPPORT

#include "pal_measure.h"

using namespace std;

namespace Hardware {
	Measure::Measure (EventSet &es, unsigned rp) {
		eventset = es;
		event_number = 0;
		event_rep = 0;
		predefined_reps = true;
		repetitions = rp;
	}

	Measure::Measure (EventSet &es) {
		eventset = es;
		event_number = 0;
		event_rep = 0;
		predefined_reps = false;
		repetitions = 0;
	}

	Measure::Measure (vector<string> counters) {
		eventset.create(counters);
		event_number = 0;
		event_rep = 0;
		predefined_reps = false;
		repetitions = 0;
	}

	// cada vez que se executa o par start stop mede um evento
	// para ja so mede uma vez cada evento
	bool Measure::start (void) {
		int retval;
		char *error;

		retval = PAPI_start(eventset[event_number]);

		if (unlikely(retval != PAPI_OK)) {
			error = PAPI_strerror(retval);

			cerr << "PAL | Measure: error measuring event - " << error << endl;
			cerr << "PAL | Measure: skipping event." << endl;

			return false;
		} else {
			return true;
		}
	}

	bool Measure::stop (void) {
		int retval;
		char *error;
		long long int counter_value [eventset.size()];

		retval = PAPI_stop(eventset[event_number], counter_value);

		if (unlikely(retval != PAPI_OK)) {
			error = PAPI_strerror(retval);

			cerr << "PAL | Measure: error measuring event - " << error << endl;
			cerr << "PAL | Measure: skipping event." << endl;

			++event_number;
			return false;
		} else {

			for (unsigned i = 0; i < eventset.size(); ++i) {
				eventset.addResult(event_number + i, (long long unsigned) counter_value[i]);
			}

			if (predefined_reps) {
				if (event_rep < repetitions)
					++event_rep;
				else {
					event_rep = 0;
					++event_number;
				}
			} else {
				if (event_number < eventset.size() - 1){
					++event_number;
				} 

				if (event_number == eventset.size() - 1) {
					++repetitions;
					event_number = 0;
				}
			}

			return true;
		}
	}

	void Measure::report (void) {
		cout << endl << endl << endl;
		cout << "\tPAPI Abstraction Library" << endl << endl;
		cout << "Presenting measurements results" << endl << endl;
		cout << "Counter\t\tMin\tAverage\tStandard Deviation" << endl;

		for (unsigned i = 0; i < (unsigned) eventset.size(); ++i) {
			Event evt = eventset.getEvent(i);
			cout << evt.getName() << "\t" << evt.getMin() << "\t";
			cout << evt.getAverage() << "\t" << evt.getStdDev() << endl;
		}
	}

	unsigned Measure::iterations (void) {
		return eventset.numberOfEvents() * repetitions;
	}

	void Measure::addResult(unsigned index, long long unsigned value){
		eventset.addResult(index, value);
	}

	EventSet Measure::getEventset(void) const {
		return eventset;
	}
}
#endif