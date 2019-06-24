#include <chrono>
#include <iostream>
#include "dynamic_problems.h"
#include "utility.h"


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

void test_change() {
	FUNCT_HEADER;
	vector<int> coins{1, 2, 5};
	int targetAmt = 5;
	int expected = 4;
	cout << "result: " << change(targetAmt, coins) << ", expected: " << expected << endl;
	FUNCT_END;
}

void test_coinChange1() {
    FUNCT_HEADER;
    vector<int> coins{1};
    int target = 0;
    int res = calcChange(target, coins);
    cout << "res: " << res << endl;
    FUNCT_END;
}

void test_mincostTickets() {
    FUNCT_HEADER;
    vector<int> days = {1,4,6,7,8,20};
    vector<int> costs = {2, 7, 15};
    int res = mincostTickets(days, costs);
    cout << "res: " << res << END;
    FUNCT_END;
}

int main(int argc, char** argv) {
    test_mincostTickets();
	return 0;
}