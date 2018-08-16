#include <iostream>
#include <chrono>
#include <types.h>
#include "utility.h"
#include "leet_algos.h"
using namespace std::chrono;
typedef high_resolution_clock hrc;
typedef hrc::time_point t_point;

void testBinTree();
void minStackTesting();
void testPrimeGeneration();

int main(int argc, char* argv[])
{
    /*
"aaaaaaaaaaaaaaaaaaaaaab"
"ba"

     */
    t_point t1_bub, t2_bub, t3_bub, t4_bub;
    std::vector<int> nums = {1,2,3};
    std::string a = "aaaaaaaaaaaaaaaaaaaaaab";
    std::string b = "ba";
    LOG << "a: " << a << "\nb: " << b << END;
    t1_bub = hrc::now();
    auto result = repeatedStringMatch(a, b);
    t2_bub = hrc::now();

    LOG << "\n\n----------------------------------------------------------------------\n\n" << END;

//    t3_bub = hrc::now();
//    LOG << "V3 Longest substring in " << "word " << " is --> " << lengthOfLongestSubstringV3(word) << END;
//    t4_bub = hrc::now();
//      LOG << "V1 result: " << END;
      LOG << "V1 result: " << result << END;
//    LOG << "V1 result: " << ( (result) ? "found it":"did not find it" )  << END;
//        LOG << ((result) ? "can":"can not") << " make it" << END;
//    LOG << "V1 result: Expected: 9 9 10 10 10 10 10 10 10 9 9 9 8 8\n";
//    display(result);
//    LOG << "matrix size: " << result.size() << END;
//      displayMatrix(result);
//    LOG << "V2 there are " << result2 << " 1's in the bin rep of " << n << END;

	std::cout << "\n\n----------------------------------------------------------------------\n\n" << END;
    auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
	LOG << "time of execution V1 -->\n" << milli_sec << "msec\n" << micro_sec << "usec\n" << END;

//    LOG << "\n\n----------------------------------------------------------------------\n\n" << END;
//    milli_sec = duration_cast<milliseconds>( t4_bub - t3_bub ).count();
//    micro_sec = duration_cast<microseconds>( t4_bub - t3_bub ).count();
//    LOG << "time of execution V2 -->\n" << milli_sec << "msec\n" << micro_sec << "usec\n" << END;

#ifdef WIN_32
	std::cout << "\n\npress any key to exit" << std::endl;
	char hold; 
	std::cin >> hold;
#endif
    return 0;
}



void testBinTree() {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    TreeNode *binTree = allocateBinTreeFromVect(data);
    std::vector<int> inOrderTrav = inOrderTraversal(binTree);
    std::vector<int> postOrderTrav = postOrderTraversal(binTree);
    std::vector<int> preOrderTrav = preOrderTraversal(binTree);
    std::cout << "InOrder Traversal" << std::endl;
    for (const auto &el: inOrderTrav) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    std::cout << "preOrder Traversal" << std::endl;
    for (const auto &el : preOrderTrav) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    std::cout << "postOrder Traversal" << std::endl;
    for (const auto &el : postOrderTrav) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

void minStackTesting() {
    MinStack minStack;
    minStack.push(2147483646);
    minStack.push(2147483646);
    minStack.push(2147483647);
    LOG << "top: " << minStack.top() << END;
    minStack.pop();
    LOG << "min: " << minStack.getMin() << END;
    minStack.pop();
    LOG << "min: " << minStack.getMin() << END;
    minStack.pop();
    minStack.push(2147483647);
    LOG << "top: " << minStack.top() << END;
    LOG << "min: " << minStack.getMin() << END;
    // minStack.push(-2147483648);
    LOG << "top: " << minStack.top() << END;
    LOG << "min: " << minStack.getMin() << END;
    minStack.pop();
    LOG << "min: " << minStack.getMin() << END;
}

void testPrimeGeneration() {

    t_point t1_bub, t2_bub;

    t1_bub = hrc::now();
    std::vector<uint64_t> primes = genPrimes(1000);
    t2_bub = hrc::now();

    display(primes);
    std::cout << "\n\n----------------------------------------------------------------------\n\n" << std::endl;
    auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    std::cout << "time of execution V1 -->\n" << milli_sec << "msec\n" << micro_sec << "usec\n" << std::endl;

    t1_bub = hrc::now();
    std::vector<uint64_t> primes_v2 = genPrimesV2(1000);
    t2_bub = hrc::now();

    display(primes);
    std::cout << "\n\n----------------------------------------------------------------------\n\n" << std::endl;
    milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    std::cout << "time of execution V2 -->\n" << milli_sec << "msec\n" << micro_sec << "usec\n" << std::endl;
}