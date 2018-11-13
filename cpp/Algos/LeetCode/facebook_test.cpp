#include "facebook.h"
#include "utility.h"
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;
typedef high_resolution_clock hrc;
typedef hrc::time_point t_point;
t_point t1_bub, t2_bub, t3_bub, t4_bub;

static void showExeTime() {
	std::cout << "\n+-+-+-+-+-+-+-+-+-+-+" << END;
	auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
	auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
	std::cout << "time of execution -->\n" << milli_sec << "msec\n" << micro_sec << "usec" << END;
	std::cout << "+-+-+-+-+-+-+-+-+-+-+" << END;
}
void test_addBinary() {
	FUNCT_HEADER;
	string a("11");
	string b("1");
	string result = addBinary(a,b);
	LOG << "result: " << result << endl;
	FUNCT_END;
}

int main () {
	test_addBinary();
	return 0;
}