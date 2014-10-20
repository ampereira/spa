#include "measure.h"

using namespace std;

namespace Timer {

	Measure::Measure (void) {
		average = 0;
		measuring = false;
		statistics.push_back(Statistic::Minimum);
	}

	Measure::Measure (vector<Statistic> _statistics) {
		average = 0;
		measuring = false;

		// avoids duplicates
		for (auto s1 : _statistics) {
			bool insert = true;

			for (auto s2 : statistics) {
				if (s1 == s2)
					insert = false;
			}

			if (insert)
				statistics.push_back(s1);
		}
	}

	Measure::Measure (Statistic _statistic) {
		average = 0;
		measuring = false;
		statistics.push_back(_statistic);
	}

	bool Measure::addStatistic (Statistic stat) {
		bool insert = true;

		for (auto s1 : statistics) {
			if (stat == s1)
				insert = false;
		}

		if (insert)
			statistics.push_back(stat);

		return insert;
	}

	inline
	void Measure::errorReport (Error error, const char* file, const char* func) {
		string err;

		switch (error) {
			case 10 :
				err = "Statistic";
				break;
			case 11 :
				err = "Measurement";
				break;
			default :
				err = "Unknown error";
				break;
		}

		cerr << err << " in " << file << ":" << func << endl;
	}

	long long unsigned Measure::getAverage (void) {
		long long unsigned sum = 0; 

		for (auto &val : measurements)
			sum += val;

		average =  sum / measurements.size();

		if (!average)
			errorReport(Error::Statistic, __FILE__, __func__);

		return average;
	}

	long long unsigned Measure::getMinimum (void) {
		long long unsigned min = 0;

		for (auto meas : measurements)
			if (meas < min || min == 0)
				min = meas;

		if (!min)
			errorReport(Error::Statistic, __FILE__, __func__);

		return min;
	}

	long long unsigned Measure::getMaximum (void) {
		long long unsigned max = 0;

		for (auto meas : measurements)
			if (meas > max)
				max = meas;

		if (!max)
			errorReport(Error::Statistic, __FILE__, __func__);

		return max;
	}

	long long unsigned Measure::getStdDev (void) {

		if (!average)
			getAverage();

		long long unsigned accum = 0.0;
		std::for_each (measurements.begin(), measurements.end(), [&](const long long unsigned d) {
			accum += (d - average) * (d - average);
		});

		long long unsigned stdev = sqrt(accum / (measurements.size() - 1));

		return stdev;
	}


	void Measure::start (void) {
		gettimeofday(&t, NULL);
		initial_time = t.tv_sec * TIME_RESOLUTION + t.tv_usec;
	}


	long long unsigned Measure::stop (void) {
		gettimeofday(&t, NULL);
		long long unsigned final_time = t.tv_sec * TIME_RESOLUTION + t.tv_usec;

		measurements.push_back(final_time - initial_time);

		return measurements.back();
	}

	bool Measure::checkKbest (float th, unsigned k, long long unsigned best) {
		long long unsigned magnitude = best * (1 + th);
		unsigned counter = 0;

		for (auto meas : measurements)
			if (meas <= magnitude)
				++counter;

		return counter >= k;
	}

	long long unsigned Measure::kbest (void (*function)(void), 
									   float th, unsigned k, unsigned min, unsigned max) {
		bool found_k = false;
		long long unsigned best_time = 0;
		unsigned i;

		kbest_measure = true;

		if (th <= 0 || th > 1) {
			errorReport(Error::Measurement, __FILE__, __func__);
			cerr << "KBest threshold must be between 0 and 1" << endl;

			exit(0);
		}

		for (i = 0; i < max && !found_k; ++i) {
			start();

			function();

			stop();

			if (measurements[i] < best_time || !best_time)
				best_time = measurements[i];

			if (i >= min)
				found_k = checkKbest(th, k, best_time);
		}

		if (i == max)
			kbest_status = false;

		results[Statistic::KBest] = best_time;

		return best_time;
	}

	//inline
	long long unsigned Measure::getStatistic (Statistic stat) {
		long long unsigned result = 0;

		switch (stat) {
			case 0 :
				result = getAverage(); break;
			case 1 :
				result = getMinimum(); break;
			case 2 :
				result = getMaximum(); break;
			case 3 :
				if (measurements.size() == 1)
					errorReport(Error::Statistic, __FILE__, __func__);
				else
					result = getStdDev();
				break;
			default :
				errorReport(Error::Statistic, __FILE__, __func__); break;
		}

		return result;
	}

	void Measure::reportVerbose (void) {
		cout << "**********************************" << endl;
		cout << "******* Measurement Report *******" << endl;
		cout << "**********************************" << endl;
		cout << endl;

		if (!kbest_measure)
			for (auto stat : statistics) {
				switch (stat) {
					case 0 : 
						cout << " => Average: ";
						break;
					case 1 : 
						cout << " => Minimum: ";
						break;
					case 2 : 
						cout << " => Maximum: ";
						break;
					case 3 : 
						cout << " => StdDev: ";
						break;
				}

				cout << results[stat] << " us" << endl;
			}
		else {
			cout << " => KBest: ";
			cout << results[Statistic::KBest] << " us ";

			if (!kbest_status)
				cout << "(timeout)";

			cout << endl;
		}
	}

	// To be finished
	map<Statistic,long long unsigned> Measure::report (Report type) {
		for (auto stat : statistics)
			results[stat] = getStatistic(stat);

		switch (type) {
			case 20 : reportVerbose(); break;
			case 21 : break;
		}

		return results;
	}
}