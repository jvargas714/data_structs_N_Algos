#include <chrono>
#include <iostream>
#include "string_problems.h"
#include "utility.h"

using namespace std::chrono;
using namespace std;
typedef high_resolution_clock hrc;
typedef hrc::time_point t_point;

// declarations
void test_licenseKeyFormatting();






// run !!!
int main() {
	test_licenseKeyFormatting();
	return 0;
}






// -------------------------------------test methods---------------------------------------
void test_licenseKeyFormatting() {
	FUNCT_HEADER;
	t_point t1_bub, t2_bub;
	int K = 2;
	std::string key = "2-5g-3-J";
	std::string expected = "2-5G-3J";

	// show input
	cout << "input: " << "lic: " << key << ", K: " << K << endl;

	t1_bub = hrc::now();
	auto result = licenseKeyFormatting(key, K);
	t2_bub = hrc::now();

	std::cout << "result: " << result << std::endl;
	std::cout << "expected: " << expected << std::endl;
	auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
	auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
	std::cout << "time of execution V1 -->\n" << milli_sec << "msec\n" << micro_sec << "usec" << std::endl;
	FUNCT_END;
}

