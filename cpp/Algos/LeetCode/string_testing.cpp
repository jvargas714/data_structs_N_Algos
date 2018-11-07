#include <chrono>
#include <iostream>
#include "string_problems.h"
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

void test_licenseKeyFormatting() {
    FUNCT_HEADER;
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

// 2:"abc" 3:"def" 4:"ghi" 5:"jkl", 6:"mno" 7:"pqrs" 8:"tuv" 9:"wxyz"
void test_letterCombinations() {
    FUNCT_HEADER;
//    std::string digitsDialed = "279794567654";
    std::string digitsDialed = "7";
//    std::string digitsDialed = "529827427";  // jayvargas
    // expected :: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
    t1_bub = hrc::now();
    auto result = letterCombinationsV4(digitsDialed);
    t2_bub = hrc::now();
    LOG << "result: \n";
    display(result);
    cout << END;
    showExeTime();
    FUNCT_END;
}

void test_numUniqueEmails() {
    FUNCT_HEADER;
    vector<string> input = {"test.email+alex@leetcode.com",
                            "test.e.mail+bob.cathy@leetcode.com",
                            "testemail+david@lee.tcode.com"};
    int expected = 2;
    t1_bub = hrc::now();
    auto result = numUniqueEmailsV3(input);
    t2_bub = hrc::now();
    LOG << "result: " << result << END;
    LOG << "expected: " << expected << END;
    showExeTime();
    FUNCT_END;
}
// run !!!
int main() {
    test_numUniqueEmails();
	return 0;
}






// -------------------------------------test methods---------------------------------------
