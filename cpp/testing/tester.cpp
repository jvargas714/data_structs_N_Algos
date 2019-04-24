#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cfloat>
#include <string>
#include <cstdint>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <iomanip>
#include <map>
#include <queue>
#include <random>
#include <chrono>
#include "../utility/utility.h"

using namespace std;
using namespace std::chrono;
typedef high_resolution_clock hrc;
typedef hrc::time_point t_point;
t_point t1_bub, t2_bub;


static void showExeTime(const string& label) {
	std::cout << "\n+-+-+-+-+-+-+-+-+-+-+" << END;
	auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
	auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
	std::cout << label << " time of execution -->\n" << milli_sec << "msec\n" << micro_sec << "usec" << END;
	std::cout << "+-+-+-+-+-+-+-+-+-+-+" << END;
}

// A utility funtion to find maximum of two integers
int max(int a, int b) { return (a > b)? a : b; }

// A utility funtion to find maximum of three integers
int max(int a, int b, int c) { return max(max(a, b), c); }

// Find the maximum possible sum in arr[] auch that arr[m] is part of it
int maxCrossingSum(int arr[], int l, int m, int h) {
	LOG << "l: " << l << " mid: " << m << " r: " << h << endl;
	// Include elements on left of mid.
	int sum = 0;
	int left_sum = INT32_MIN;
	for (int i = m; i >= l; i--)
	{
		sum = sum + arr[i];
		if (sum > left_sum)
			left_sum = sum;
	}

	// Include elements on right of mid
	sum = 0;
	int right_sum = INT32_MIN;
	for (int i = m+1; i <= h; i++)
	{
		sum = sum + arr[i];
		if (sum > right_sum)
			right_sum = sum;
	}
	LOG << "left sum: " << left_sum << " right sum: " << right_sum << endl;
	LOG << "cross sum: " << (left_sum+right_sum) << endl;
	// Return sum of elements on left and right of mid
	return left_sum + right_sum;
}

// Returns sum of maxium sum subarray in aa[l..h]
int maxSubArraySum(int arr[], int l, int h) {
	LOG << "l: " << l << " r: " << h << endl;
	// Base Case: Only one element
	if (l == h)
		return arr[l];

	// Find middle point
	int m = (l + h)/2;

	/* Return maximum of following three possible cases
       a) Maximum subarray sum in left half
       b) Maximum subarray sum in right half
       c) Maximum subarray sum such that the subarray crosses the midpoint */
	return max(maxSubArraySum(arr, l, m),
			   maxSubArraySum(arr, m+1, h),
			   maxCrossingSum(arr, l, m, h));
}

size_t removeDups(std::vector<int>& nums) {
	if (nums.empty()) return 0;
	int tmp = nums[0];
	int offset = 1;
	while (offset < nums.size()) {
		if (tmp == nums[offset]) {
			nums.erase(nums.begin() + offset);
			// offset++;
		} else {  // move to next element to remove
			tmp = nums[offset++];
		}
	}
	return nums.size();
}

void rotate(vector<int>& nums, int k) {
	unsigned int ind;
	size_t n = nums.size();
	unsigned int offset = k % n;
	for (unsigned int i=0; i<n; i++) {
		ind = i + offset;
		if (ind>=n) {
			LOG << "i: " << i << " ind: " << ind << END;
			ind-=n;
		}
		LOG << "swapping ==> ==>" << "i: " << i << " ind: " << ind << "\n" << END;
		nums[i]=nums[ind];
	}
}

struct MyComp {
	bool operator() (const int& a, const int& b){
		return !(a < b);
	}
};

// when swapping pointer from a string we must deref them for the swap to work
void mySwap(char* ch1, char* ch2) {
    char tmp = *ch1;
    *ch1 = *ch2;
    *ch2 = tmp;
}

// using pointers space : O(1), time: O(n)
void reverseString(std::string& str) {
    // of course there is std::reverse(str.begin(), str.end());
    for (int i = 0, j = str.length()-1; i < str.size()/2; i++, j--) {
        mySwap(&str[i], &str[j]);
    }
    std::cout << "result: " << str << std::endl;
}

// using map O(n) time and space :( where n is the size of the larger vector
int find_missing(const std::vector<int>& vect1, const std::vector<int>& vect2) {
    const std::vector<int>& larger = (vect1.size() > vect2.size() ? vect1:vect2);
    const std::vector<int>& smaller = (vect1.size() < vect2.size() ? vect1:vect2);
    std::map<int, int> valMap;
    for (const auto& el : smaller) valMap[el]++;
    for (const auto& el : larger)
        if (valMap.find(el) == valMap.end()) return el;
    return -1;
}

// xor verison time O(1), space O(n)
int find_missingV2(const std::vector<int>& vect1, const std::vector<int>& vect2) {
    const std::vector<int>& larger = (vect1.size() > vect2.size() ? vect1:vect2);
    const std::vector<int>& smaller = (vect1.size() < vect2.size() ? vect1:vect2);
    int res = 0;
    for (int i = 0; i < larger.size(); i++) {
        res ^= larger[i];
        if (i < smaller.size())
            res ^= smaller[i];
    }
    return res;
}

uint64_t fact(int n) {
	uint64_t res = 1;
	for (int i = 2; i <= n; i++) res *= i;
	return res;
}

// * * * *  * * * *
// returns vector indicating which bit positions have a 1 bit flipped
template<typename T>
std::vector<int> findBitPositions(T val) {
	T mask = 1;
	std::vector<int> res;
	for (int shiftBy = 0; shiftBy < sizeof(T)*8; shiftBy++) {
		if ((val & mask) > 0) res.push_back(shiftBy);
        mask <<= 1;
	}
	return res;
}

/*
 *  returns all combinations of a set of size n
 *  n <= 64
 *  generates indexes from 0 - n-1
 *  so if n=3 then indices in the combinations will range between 0-2
 */
std::vector<std::vector<int>> combinationsBinCnt(int n) {
	if (n > 64) return {};
	std::vector<std::vector<int>> combos;
	uint64_t binary = 0;    // max n can be 64 bits
	const uint64_t numSubSets = (uint64_t) std::pow(2, n);
	for (uint64_t cnt = 0; cnt < numSubSets; cnt++) combos.push_back( findBitPositions(binary++) );
    return combos;
}

void test_primeGeneration(uint64_t numPrimes) {
	// generate 50k prime numbers
	t1_bub = hrc::now();
	std::vector<uint64_t> primes2 = genPrimesV2(numPrimes);
	t2_bub = hrc::now();
	showExeTime("PrimeGenV2");

	LOG << "V1: output\n";
	display(primes2);
}

/*
 * write a program that takes a 64 bit unsigned int and returns its bits reversed
 * 0b10011101010101100010011000100010110100000 output should be
 * 0b10110100010001100100011010101011100100000000000000000000000
 * 0b10110100010001100100011010101011100100000000000000000000000


 * res: 1 --> 10
 * res:
 */
unsigned long long ReverseBits(unsigned long long x) {
    unsigned long long res = 0;
    for (int i = 1; i < sizeof(unsigned long long)*8; i++) {
        res |= (x&1);
        res <<= 1;
        x >>=1;
    }
    std::cout << "my output: " << res << std::endl;
    return res;
}


int main(int argc, char* argv[]) {
    // 10e --> 0001 0000 1110
    unsigned long long val = 0b10011101010101100010011000100010110100000;
    cout << ReverseBits(val) << endl;
	return 0;
}


