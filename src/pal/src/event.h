#ifndef EVENT
#define EVENT

#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

namespace Hardware {
	class Event {
		std::string name;
		int code;
		std::vector<long long unsigned> measurements;

	public: 
		Event (char*, int);
		std::string getName (void);
		int getCode (void);
		void addResult (long long unsigned);
		long long unsigned getMin (void);
		long long unsigned getAverage (void);
		long long unsigned getStdDev (void);
	};
}

#endif
