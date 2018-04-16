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
    IntMatrix matrix = generateNxNMatrix(4);
    //displayMatrix(matrix);
    t_point t1_bub, t2_bub;
    t1_bub = hrc::now();
	std::cout << "First unqiue char V1: " << firstUniqChar("loveleetcode") << std::endl;
    t2_bub = hrc::now();
    std::cout << "\n\n----------------------------------------------------------------------\n\n" << std::endl;
    //displayMatrix(matrix);
    auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
	std::cout << "time of execution -->\n" << milli_sec << "msec\n" << micro_sec << "usec\n" << std::endl;

	// V2 attempt 
	t1_bub = hrc::now();
	std::cout << "First unqiue char V2: " << firstUniqCharV2("loveleetcode") << std::endl;
	t2_bub = hrc::now();
	std::cout << "\n\n----------------------------------------------------------------------\n\n" << std::endl;
	//displayMatrix(matrix);
	milli_sec = duration_cast<milliseconds>(t2_bub - t1_bub).count();
	micro_sec = duration_cast<microseconds>(t2_bub - t1_bub).count();
    std::cout << "time of execution -->\n" << milli_sec << "msec\n" << micro_sec << "usec\n" << std::endl;
#ifdef WIN_32
	char hold; 
	std::cin >> hold;
#endif
    return 0;
}
