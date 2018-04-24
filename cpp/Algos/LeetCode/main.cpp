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
    t_point t1_bub, t2_bub;
    ListNode* l1 = fillListNode({1, 2, 4});
    ListNode* l2 = fillListNode({1, 3, 4, 5, 6, 7});

	t1_bub = hrc::now();
	ListNode* result = mergeTwoLists(l1, l2);
	t2_bub = hrc::now();


	std::cout << "Linked List after reversal: " << std::endl;
   	displayListNodes(result);
   	deallocateLList(result);

	std::cout << "\n\n----------------------------------------------------------------------\n\n" << std::endl;
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
