#include <sys/time.h>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "enum_types.h"

#define TIME_RESOLUTION 1000000	// time measuring resolution (us)

class Measure {
	long long unsigned initial_time;	// initial time to get the end-init
	std::vector<long long unsigned> measurements;			// measurements performed
	bool measuring;						// true after start is called and false after stop is called
	timeval t;							// holds the data of gettimeofday
	std::vector<Statistic> statistics;  // holds the report statistics
	std::map<Statistic,long long unsigned> results;	// map to hold the Statistic-value pair
	Error error;
	long long unsigned average;
	bool kbest_status = true;			// false - timeout; true - normal execution
	bool kbest_measure = false;

	long long unsigned getStatistic (Statistic);
	void errorReport (Error, const char*, const char*);
	long long unsigned getAverage (void);
	long long unsigned getMinimum (void);
	long long unsigned getMaximum (void);
	long long unsigned getStdDev (void);
	void reportVerbose (void);
	bool checkKbest (float, unsigned, long long unsigned);
	
public:
	Measure (void);
	Measure (std::vector<Statistic>);
	Measure (Statistic);
	void start (void);
	long long unsigned stop (void);
	long long unsigned kbest (void (*function)(void), float, unsigned, unsigned, unsigned);
	std::map<Statistic,long long unsigned> report (Report);
	bool addStatistic (Statistic);
};