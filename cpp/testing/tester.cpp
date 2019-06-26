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
 * Approach:
 *      1. create a not prime vector setting all elements to false
 *      2. add i to result if element at i is false (prime)
 *      3. second for loop--> set all multiples of i up n to notprime we ensure that
 *
 *      runtime: O(n * sqrt(n)) --> O(n^(3/2))
 *      space: O(2n) --> O(n)
 */
vector<int> dumbBruteForce(int n) {
    vector<int> primes;
    deque<bool> is_prime(n+1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p <= n; ++p) {
        if (is_prime[p]) primes.emplace_back(p);
        // eliminate multiples start at a multiple of 2
        for (int i = p * 2; i <=n; i += p) {
            is_prime[i] = false;
        }
    }
    return primes;
}

// primes --> 2i+3
vector<long long> primes_sieve(int n) {
    vector<long long> primes;
    // n-3 removes 0, 1, 2 considering formula 2i+3, and removing evens so we can mult by 1/2
    long long size = static_cast<long long>(std::floor(.5 * (n-3))) + 1;
    deque<int> is_prime(n, true);
    for (int i = 0; i < size; i++) {
        if (is_prime[i]) {
            long long p = (2*i + 3);
            primes.emplace_back(p);
            // remove multiples
            for (long long j = 4 * i * i + 12 * i + 9; j < size; j += p) {
                is_prime[j] = false;
            }
        }
    }
    return primes;
}

/*
 * go from 2 to sqrt(n) check by division trial, we check if there is a remainder or not using modulo operator
 */
static bool testerIsPrime(size_t n) {
    auto goingTo = static_cast<size_t>(sqrt(n));
    size_t j = 2;
    while (j <= goingTo)
        if (n % j++ == 0) return false;
    return true;
}

bool IsValidSudoku(const vector<vector<int>>& board) {
	auto hasDups = [](const vector<int>& nums) -> bool {
		vector<bool> dups(nums.size()+1, false);
		for (const auto& el : nums) {
			if (el == 0) continue;
			if (dups[el]) {
				LOG << "failed in row testing, val: " << el << END;
				return true;
			}
			else dups[el] = true;
		}
		return false;
	};

	auto hasDupsInRegion = [board](int rowStart, int colStart) -> bool {
		vector<bool> dups(10, false);
		for (int row = rowStart; row < rowStart + 3; row++) {
			for (int col = colStart; col < colStart + 3; col++) {
				int val = board[row][col];
				if (val == 0) continue;
				if (dups[val]) {
					LOG << "failed in region testing, row: " << row << " col: " << col << " val: " << val << END;
					return true;
				}
				else dups[val] = true;
			}
		}
		return false;
	};

	// check for duplicates across all rows
	for (int row = 0; row < board.size(); row++) {
		if (hasDups(board[row])) return false;
	}

	vector<bool> dups(10, false);

	// check for dups across all columns
	for (int col = 0; col < board[0].size(); col++) {
		for (int row = 0; row < board.size(); row++) {
			int val = board[row][col];  // i->row n -> col
			if (val == 0) continue;
			LOG << "(" << row << "," << col << ") val: " << val << END;
			if (dups[val]) {
				LOG << "failed in column testing, row: " << row << " col: " << col << " val: " << val << END;
				return false;
			}
			else
				dups[val] = true;
		}
		cout << "======new col=====" << END;
		std::fill(dups.begin(), dups.end(), false);
	}

	// check 3x3 regions for duplicates
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (hasDupsInRegion(3*i, 3*j)) return false;  // (0, 0), (0, 3), (0, 6)
		}
	}
	return true;
}

vector<int> MatrixInSpiralOrder(vector<vector<int>> square_matrix) {
	auto pt = [square_matrix](size_t row, size_t col) {
		return square_matrix[row][col];
	};

	size_t n = square_matrix.size();
	size_t lvl=0;
	vector<int> res;
	int numlvls = n % 2 == 0 ? n/2 : n/2 + 1;
	// lock row with lvl

	while (lvl != numlvls) {
		// face 1
		for (int col = lvl; col < n - lvl; col++)
			res.push_back( pt(lvl, col) );

		// face 2
		for (int row = lvl+1; row < n-lvl; row++)
			res.push_back( pt(row, n-lvl-1) );

		// face 3
		for (int col = n - lvl - 2; col > lvl; col--)
			res.push_back( pt(n-lvl-1, col) );

		// face 4 up left vertical path
		for (int row = n - lvl - 1; row > lvl; row--)
			res.push_back( pt(row, lvl) );

		lvl++;
	}
	return res;
}

static string createNextEntry(const string& str) {
	if (str.empty()) return "1";
	map<char, int> cntMap;
	char prev = str[0];
	int cnt = 1;
	string res;
	char buff[256] = {0};
	for (auto it = str.begin()+1; it != str.end(); it++) {
		if (prev != *it) { // new char add to result str
			sprintf(buff, "%i%c", cnt, prev);
			res.append(buff);
			memset(buff, '\0', sizeof(buff));
			prev = *it;
			cnt = 1;
			continue;
		}
		cnt++;
	}
	if (cnt > 0) {
		sprintf(buff, "%i%c", cnt, prev);
		res.append(buff);
	}
	return res;
}

string LookAndSay(int n) {
	string res;
	int cnt = 1;
	while (cnt <= n) {
		res = createNextEntry(res);
		std::cout << "n: " <<  cnt << "=" << res << std::endl;
		cnt++;
	}
	return res;
}

int main() {
	ListNode* root = new ListNode(1);
	root->next = new ListNode(2);
	root->next->next = new ListNode(3);
	root->next->next->next = new ListNode(4);
	root->next->next->next->next = new ListNode(5);
	root->next->next->next->next->next = new ListNode(6);
	// p   a          b
	// 1->[2]->3->4->[5]->6->null
	display(root);
	ListNode* prev = root;
	ListNode* a = root->next;
	ListNode* b = root->next->next->next->next;

	prev->next = b;
	b->next = a->next;

	return 0;
}
