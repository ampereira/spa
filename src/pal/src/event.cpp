#include "event.h"

using namespace std;

namespace Hardware {
	Event::Event (char* nam, int ev) {
		name.append(nam);
		code = ev;
	}

	string Event::getName (void) {
		return name;
	}

	int Event::getCode (void) {
		return code;
	}

	void Event::addResult (long long unsigned value) {
		measurements.push_back(value);
	}

	long long unsigned Event::getMin (void) {
		long long unsigned min = measurements[0];

		for (auto val : measurements)
			if (val < min)
				min = val;

		return min;
	}

	long long unsigned Event::getAverage (void) {
		long long unsigned sum = 0;

		for (auto val : measurements)
			sum += val;

		return sum / measurements.size();
	}

	long long unsigned Event::getStdDev (void) {
		long long unsigned average = getAverage();

		long long unsigned accum = 0;
		std::for_each (measurements.begin(), measurements.end(), [&](const long long unsigned d) {
			accum += (d - average) * (d - average);
		});

		long long unsigned stdev = sqrt(accum / (measurements.size() - 1));

		return stdev;
	}
}
