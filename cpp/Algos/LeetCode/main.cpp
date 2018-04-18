#include <iostream>
#include <chrono>
#include <types.h>
#include "utility.h"
#include "leet_algos.h"

using namespace std::chrono;
typedef high_resolution_clock hrc;
typedef hrc::time_point t_point;
int main()
{
    std::string str("- 321 ");
    t_point t1_bub, t2_bub;
    t1_bub = hrc::now();
    std::cout << "result: ";
    std::cout << myAtoi(str) << std::endl;
    t2_bub = hrc::now();
    std::cout << "\n\n----------------------------------------------------------------------\n\n" << std::endl;
    //displayMatrix(matrix);
    auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
	std::cout << "time of execution -->\n" << milli_sec << "msec\n" << micro_sec << "usec\n" << std::endl;

#ifdef WIN_32
	std::cout << "\n\npress any key to exit" << std::endl;
	char hold; 
	std::cin >> hold;
#endif
    return 0;
}
