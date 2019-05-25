#include <algorithm>
#include <memory>
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
#include <array>
#include "../utility/utility.h"

using namespace std;
using namespace std::chrono;
using std::map;
using std::unordered_map;
typedef high_resolution_clock hrc;
typedef hrc::time_point t_point;
t_point t1_bub, t2_bub;
static std::random_device rd;
constexpr int NUMELEMENTS = 10;

using std::vector;
typedef enum {
	kRed, kWhite, kBlue
} Color;


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

double Power(double x, int y) {
    if (y == 0) return 1;
    x = y < 0 ? 1/x:x;
    double res = x;
    bool odd = false;
    y = abs(y);

    if (y % 2 == 0) {
        y /= 2;
    } else {
        y--;
        y /= 2;
        odd = true;
    }
    res = x*x;
    while (y > 1) {
//        cout << "res: " << res << " y: " << y << endl;
        res *= (x*x);
        y-=1;
    }
    res *= (odd?x:1);
    return res;
}

long long Reverse(int x) {
    long long res = 0;
    long long dig;
    bool neg = x < 0;
    x = std::abs(x);

    // get how many places our number will be
    int pwr = std::pow(10, static_cast<int>(std::log10(x)));
    cout << "pwr: " << pwr << endl;
    while (pwr) {
        dig = x % 10;
        x /= 10;
        res += pwr * dig;
        pwr /= 10;
    }
    return res * (neg ? -1:1);
}

void overloaded( int const &arg ) { std::cout << "by lvalue\n"; }
void overloaded( int && arg ) { std::cout << "by rvalue\n"; }

template< typename t >
/* "t &&" with "t" being template param is special, and  adjusts "t" to be
   (for example) "int &" or non-ref "int" so std::forward knows what to do. */
void forwarding( t && arg ) {
	std::cout << __FUNCTION__ << "(): via std::forward: ";
	overloaded( std::forward< t >( arg ) );
	std::cout << "via std::move: ";
	overloaded( std::move( arg ) ); // conceptually this would invalidate arg
	std::cout << "by simple passing: ";
	overloaded( arg );
}

/*
 * Approach:
 *      1. first start by placing elements smaller than the pivot in the front of the array
 *      2.
 */
void DutchFlagPartition(int pivot_index, vector<int> *A_ptr) {
    auto& nums = *A_ptr;
    int pivot = nums[pivot_index];
    int smaller=0, unclass=0, larger=nums.size()-1;
    while (unclass < larger) {
        if (nums[unclass] > pivot) {
            swap(nums[unclass++], nums[larger--]);
        } else if (nums[unclass] == pivot) {
            unclass++;
        } else {
            swap(nums[unclass++], nums[smaller]);
        }
    }
}
template<class KeyType, class DataType>
struct HashTableNode {
    KeyType key;
    DataType data;
    HashTableNode* next;
    HashTableNode() : key(), data(), next(nullptr) {}
    HashTableNode(string key, int val) : key(key), data(val), next(nullptr) {}
    ~HashTableNode() {
    	LOG << "dtor called" << END;
    	if (next) delete next;
    }
};

using Node = HashTableNode<string, int>;

void displayLL(Node* nd) {
	LOG << END;
    Node* ptr = nd;
    while (ptr) {
        cout << ptr->data << " ";
        ptr = ptr->next;
    }cout << END;
}

// [curr]->[nxt]->[]->[]
static void fillData(Node* rt) {
	// Node* root = new Node("firstOne", 456);
	Node* tmp = rt;

    // [curr]->[nxt]->[]->[]
    for (int i = 0; i < NUMELEMENTS; i++) {
        tmp->next = new Node(std::to_string(rd()), rd());
        tmp = tmp->next;
    }
    cout << END;
}

void appendNode(Node* ptr, string str, int val) {
	LOG << END;
	if (!ptr) {
		ptr = new Node(str, val);
		return;
	}
	Node* tmp = ptr;
	while (tmp) {
		;
	}

}

int DeleteDuplicates(vector<int>* A_ptr) {
    if (!A_ptr) return 0;
    vector<int>& nums = *A_ptr;
    if (nums.empty()) return 0;
    size_t i = 0, j = 1, len = nums.size();
    while (i < len && j < len) {
        if (nums[i] == nums[j]) {
            j++;
        } else if (j - i > 1) {
            nums[++i] = nums[j];
        } else {
            ++i;
            ++j;
        }
    }
    return i+1;
}

double BuyAndSellStockTwice(const vector<double>& prices) {
    double bestProfit = 0.0, secondBest = 0.0;
    size_t buy = 0, sell = 1, len = prices.size();
    while (buy < len && sell < len) {
        if (prices[sell] > prices[buy]) {
            cout << "buying: " << prices[buy] << " and selling at " << prices[sell] << endl;
            double tmp = prices[sell] - prices[buy];
            if (tmp >= bestProfit) {
                secondBest = bestProfit;
                bestProfit = tmp;
                buy++, sell++;
            } else if (tmp > secondBest) {
                secondBest = tmp;
                buy++, sell++;
            }
            cout << "best: " << bestProfit << " second: " << secondBest << "\n" << endl;
        } else if (prices[sell] < prices[buy]) {
            buy = sell;
        }
        sell++;
    }
    return bestProfit + secondBest;
}



/*
 * [-8, -7, -6, -5, -5, -4, -3, -1, -1, 0, 0, 2, 2, 2, 4]

Failure info
	expected: [-8, -7, -6, -5, -4, -3, -1, 0, 2, 4]
	result:   [-8, -7, -6, -5, -4, -3, -1, 0, 2]
 */
int main() {
    // expected 25.6
    /*
     *  First transaction buy at 0.1 and sell first at 13.6, and second transaction buy at 0.4 and sell at 13.6
     */
    vector<double> nums = {10.6, 11.5, 9.2, 7.0, 2.1, 8.5, 5.2, 2.4, 5.3, 8.2, 4.2, 1.2, 2.3, 3.5,
                           12.7, 2.3, 2.7, 5.5, 11.1, 13.0, 11.7, 9.1, 10.9, 1.7, 13.2, 5.5, 4.3, 6.6,
                           2.4, 11.5, 11.1, 10.1, 3.3, 12.6, 7.4, 5.0, 3.3, 13.6, 10.3, 8.6, 4.3, 7.8,
                           10.1, 8.2, 4.9, 5.4, 3.7, 8.0, 0.5, 4.0, 3.4, 12.6, 13.5, 3.1, 13.2, 9.7, 7.2,
                           11.2, 6.1, 2.5, 10.6, 5.8, 5.0, 12.3, 1.6, 7.3, 6.9, 0.2, 4.9, 7.1, 1.6, 0.7,
                           12.7, 0.4, 0.9, 8.7, 12.3, 1.4, 0.1, 0.8, 8.9, 13.6, 6.5, 9.6, 6.3, 11.7, 6.9,
                           7.2, 11.9, 3.1, 0.4, 10.9, 2.8, 9.8, 13.6, 12.5, 6.9, 12.4, 7.0, 1.6, 1.5, 8.4,
                           1.2, 9.1, 9.8, 5.2, 3.8, 1.3, 7.9, 8.1, 3.4, 2.3, 9.3, 4.5, 1.0, 11.9, 3.6, 4.9,
                           10.5, 4.7, 10.6, 3.4, 6.4, 7.9, 8.3, 8.0, 10.0, 6.4, 11.6, 2.5, 4.1, 8.7, 5.0, 4.7,
                           6.9, 6.1};
    double res = BuyAndSellStockTwice(nums);
    cout << "result: " << res << endl;
	return 0;
}
