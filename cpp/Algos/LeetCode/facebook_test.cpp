#include "facebook.h"
#include "types.h"
#include "utility.h"
#include <chrono>
#include <iostream>
#include <algorithm>
#include <map>
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
    string input = "abc";
    bool expected = false;
    LOG << "input: " << input << END;

    t1_bub = hrc::now();
    bool result = validPalindromeV2(input);
    t2_bub = hrc::now();

    LOG << "result: " << (result ? "valid":"invalid") << END;
    LOG << "expected: " << (expected ? "valid":"invalid") << END;
    showExeTime(__FUNCTION__);
    FUNCT_END;
}

void test_isANumber() {
    /*
     * "0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
" -90e3   " => true
" 1e" => false
"e3" => false
" 6e-1" => true
" 99e2.5 " => false
"53.5e93" => true
" --6 " => false
"-+3" => false
"95a54e53" => false
     */
    map<string, bool> nums = {
        {"0", true},
        {"1 ", true},
        {" 0.1 ", true},
        {"abc", false},
        {"1 a", false},
        {"2e10", true},
        {" -90e3   ", true},
        {" 1e", false},
        {"e3", false},
        {" 6e-1", true},
        {" 99e2.5 ", false},
        {"53.5e93", true},
        {" --6 ", false},
        {"-+3", false},
        {"95a54e53", false},
        {".123453564564567 ", true},
        {".", false},
        {". ", false},
        {" . ", false},
        {" .6 ", true},
        {" 0 6.5e10          ", false},
        {".e1", false},
        {".e-1", false},
        {".e-", false},
        {" ", false},
        {"   -e56", false},
        {" +-", false},
        {" -1e56", true},
        {"  -.5", true},
        {" -.", false},
        {" +0e-", false},
        {"6ee34", false},
        {"ee4", false},
        {"e", false},
        {"4e10e2", false},
        {" 005047e+6", true}
    };
    t1_bub = hrc::now();
    for (auto entry : nums) {
        bool res = isNumberV2(entry.first);
        if ( res == entry.second)
            LOG << "[" << entry.first << "]" <<
            " has been categorized correctly, your output => " << (res ? "true":"false") << END;
        else
            LOG << "XXXXXX :( " << "[" << entry.first << "]" <<
            " has been categorized incorrectly, your output => " << (res ? "true":"false") << END;
    }
    t2_bub = hrc::now();
    showExeTime(__FUNCTION__);
    FUNCT_END;
}

void test_minSubArray() {
	FUNCT_HEADER;
	std::vector<int> nums = {2,3,1,1,1,1,1};
	int target = 5;
	t1_bub = hrc::now();
	int answerKey = minSubArrayLen(target, nums);
	int result = minSubArrayLenV3(target, nums);
	t2_bub = hrc::now();

	LOG << "expected: " << answerKey << END;
	LOG << "result: " << result << END;
	showExeTime(__FUNCTION__);
	FUNCT_HEADER;
}

void test_maxSubArray() {
    FUNCT_HEADER;
//    std::vector<int> nums = {0, 0, 0};
//    int target = 0;
//    int expected = 3;
    std::vector<int> nums = {1, -1, 5, -2, 3};
    int target = 3;
    int expected = 4;

    LOG << "target: " << target << END;
    LOG << "input: \n";
    display(nums);
    t1_bub = hrc::now();
    int res = maxSubArrayLen(nums, target);
    t2_bub = hrc::now();
    LOG << "expected: " << expected << END;
    LOG << "result: " << res << END;
    showExeTime(__FUNCTION__);
    FUNCT_END;
}

// should return first element that compares >= target (like lower_bound)
void test_binarySearchLowerBound() {
    std::vector<int> nums;
    for (int i = 0; i < 20; i++)
        nums.push_back(i);
    for (int i = 0; i < nums.size(); i++) {
        LOG << "i=" << i << ", result --> " << binarySearchLowerBound(nums, i) << END;
        auto exp = std::lower_bound(nums.begin(), nums.end(), i);
        LOG << "i=" << i << ", expected result --> " << (exp==nums.end()? -1:*exp)  << "\n" << END;
    }
    LOG << "result --> " << binarySearchLowerBound(nums, 100) << END;
}

void test_reverseLinkedList() {
	FUNCT_HEADER;
	ListNode* lst = fillListNode({1, 2, 3, 4, 5, 6, 7});
	ListNode* res = reverseListV2(lst);
	LOG << "result: " << END;
	displayListNodes(res);
	FUNCT_END;
}

int main () {
	test_reverseLinkedList();
	return 0;
}