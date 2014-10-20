// switch comparisons must be performed with the respective
// id to be compatible with intel compilers

enum class Statistic {
	Average=0,
	Minimum=1,
	Maximum=2,
	StdDev=3,
	KBest=4
};

enum class Error {
	Statistic=10,
	Measurement=11
};

enum class Report {
	Verbose=20,
	Csv=21
};
