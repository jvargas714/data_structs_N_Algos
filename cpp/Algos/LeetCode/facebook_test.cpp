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

string genBinNum(size_t len) {
    string output;
    char tmp;
    random_device rd;
    for (int i = 0; i < len; i++) {
        tmp = ((rd() % 2) == 0 ? '0' : '1');
        output += tmp;
    }
    return output;
}

/*
 * "1010"
"1011"
 */
void test_addBinary() {
	FUNCT_HEADER;
	string a = genBinNum(751230);
	string b = genBinNum(552340);
//    string a("1100");
//    string b("1101");
//    string a("11");
//    string b("1");
//    string a("1010");
//    string b("1011");
//    string a("1111");
//    string b("1111");
//	LOG << "input a: " << a << END;
//	LOG << "input b: " << b << END;

	t1_bub = hrc::now();
	string result = addBinary(a,b);
	t2_bub = hrc::now();
	showExeTime("V1");

    t1_bub = hrc::now();
    string resultv2 = addBinaryV2(a,b);
    t2_bub = hrc::now();
    cout << endl;
//    LOG << "V1 result: " << result << endl;
//    LOG << "V2 result: " << resultv3 << END;
    showExeTime("V2");
    cout << endl;
    LOG << ((result==resultv2) ? ":)":":(") << END;
	FUNCT_END;
}

int main () {
	test_addBinary();
	return 0;
}