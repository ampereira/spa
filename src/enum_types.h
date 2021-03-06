// switch comparisons must be performed with the respective
// id to be compatible with intel compilers
#ifndef SPA_ENUM_TYPES
#define SPA_ENUM_TYPES

#include <type_traits>

enum class Statistic {
	Average=0,
	Minimum=1,
	Maximum=2,
	StdDev=3,
	KBest=4
};

enum class Error {
	Statistic=10,
	Measurement=11,
	OUT_OF_BOUNDS=12
};

enum class Report {
	Verbose=20,
	Csv=21
};

template <typename Enumeration>
auto as_integer(Enumeration const value)
	-> typename std::underlying_type<Enumeration>::type
{
	return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

#endif
