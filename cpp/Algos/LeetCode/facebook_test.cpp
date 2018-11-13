#include "facebook.h"
#include "utility.h"
#include <chrono>
#include <iostream>
#include <random>
using namespace std;
using namespace std::chrono;
typedef high_resolution_clock hrc;
typedef hrc::time_point t_point;
t_point t1_bub, t2_bub, t3_bub, t4_bub;

static void showExeTime(const string& label) {
	std::cout << "\n+-+-+-+-+-+-+-+-+-+-+" << END;
	auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
	auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
	std::cout << label << " time of execution -->\n" << milli_sec << "msec\n" << micro_sec << "usec" << END;
	std::cout << "+-+-+-+-+-+-+-+-+-+-+" << END;
}

static string genBinNum(size_t len) {
    string output;
    random_device rd;
    for (int i = 0; i < len; i++)
        output += rd() % 2;
    return output;
}


void test_addBinary() {
	FUNCT_HEADER;
	string a = genBinNum(10000);
	string b = genBinNum(34568);

	t1_bub = hrc::now();
	string result = addBinary(a,b);
	t2_bub = hrc::now();
	// LOG << "result: " << result << endl;
	showExeTime("V1");

    t1_bub = hrc::now();
    string resultv2 = addBinaryV2(a,b);
    t2_bub = hrc::now();
    // LOG << "V2 result: " << resultv2 << END;
    showExeTime("V2");
    LOG << ((result==resultv2) ? ":)":":(") << END;
	FUNCT_END;
}

int main () {
	test_addBinary();
	return 0;
}