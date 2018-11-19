#include "facebook.h"
#include "types.h"
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
    LOG << "V1 result: " << result << endl;
	FUNCT_END;
}

/*
 * Input:
    [-2,0,0,2,2]
    Output:
    [[-2,0,2],[-2,0,2]]
    Expected:
    [[-2,0,2]]
 *
 */
void test_3sum() {
	FUNCT_HEADER;
	// expected result: [-1 0 -1], [-1 -1 2]
	vector<int> nums = {-2,0,0,2,2};
    LOG << "input: " << END;
    display(nums);
	t1_bub = hrc::now();
	vector<vector<int>> result = threeSum(nums);
	t2_bub = hrc::now();

	showExeTime(__FUNCTION__);
	cout << endl;
	LOG << "result: " << END;
	displayMatrix(result);
	FUNCT_END;
}

void test_isApalindrome() {
    FUNCT_HEADER;
    string input = "A man, a plan, a canal: Panama";
    string input2 = "0P";
    LOG << "input ==> " << input << END;
    t1_bub = hrc::now();
    bool result = isPalindrome(input);
    t2_bub = hrc::now();

    LOG << "result: " << (result ? "valid":"invalid") << END;
    showExeTime(__FUNCTION__);
    FUNCT_END;
}

void test_validPalindrome() {
    FUNCT_HEADER;
    string input = "ebcbbececabbacecbbcbe";
    bool expected = true;
    LOG << "input: " << input << END;

    t1_bub = hrc::now();
    bool result = validPalindromeV2(input);
    t2_bub = hrc::now();

    LOG << "result: " << (result ? "valid":"invalid") << END;
    LOG << "expected: " << (expected ? "valid":"invalid") << END;
    showExeTime(__FUNCTION__);
    FUNCT_END;
}

int main () {
    test_validPalindrome();
	return 0;
}