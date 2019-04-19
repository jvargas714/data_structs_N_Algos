#include <map>
#include <cmath>
#include "math_problems.h"
#include "utility.h"

// ====================================================== HELPERS ========================================================================
/*
        recursive helper:
            when building the powerset we can either add or remove an element from
            the set. there we only have two choices to make each recursion
            Each index i represents a point in the input nums where we decide whether 
            to add or remove it from the selected set, once each element has been
            visited we add the built set. this particular solution does not consider 
            duplicate values in the set!
            
            O(n decisions) * O(2^n)  << each call spawns 2 more decisions and 
            those 2 spawn two more and so on, hence the exponent
            
            time: O(n*2^n), 
                where n is the size of nums
    */
    static void open_sets(std::vector<int>& nums, int i, std::vector<int>& selected, std::vector<std::vector<int>>& powerset) {
        if (nums.size() == i) {
            powerset.push_back(selected);
            return;
        }
        // start by the adding decision first
        selected.push_back(nums[i]);
        open_sets(nums, i+1, selected, powerset);
        
        // next we remove from the set 
        selected.erase(selected.end()-1);
        open_sets(nums, i+1, selected, powerset);
        
        // at the end of this call each element would have been added and removed from set 
    }

// ====================================================== Problems ================================================================

// counts the number of prime numbers less than n
int countPrimes(int n) {
    std::vector<bool> notPrime(static_cast<size_t>(n), false);
    int cnt = 0;
    for (uint32_t i = 2; i < n; i++) {
        if (!notPrime[i]) {
            cnt++;
            if (i * i < n) {
                for (uint32_t j = 2; j * i < n; ++j)
                    notPrime[i * j] = true;
            }
        }
    }
    return cnt;
}

// determine if n is a power of three or not
bool isPowerOfThree(int n) {
    if (n < 3) return false;
    LOG << "enter: n=" << n << END;
    while (n!=1 && n%3==0) {
        n/=3;
        LOG << "n: " << n << END;
    }
    return n==1;
}

/*
 *  I can be placed before V (5) and X (10) to make 4 and 9.
    X can be placed before L (50) and C (100) to make 40 and 90.
    C can be placed before D (500) and M (1000) to make 400 and 900.
 */
int romanToInt(std::string& rnum) {
    const std::map<char, int> rmap = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
    };
    int result = 0;
    char prev = '\0';
    for (const auto& ch: rnum) {
        result += rmap.at(ch);
        if (prev == '\0') {
            prev = ch;
            continue;
        }
        if (prev == 'I' && (ch == 'X' || ch == 'V')) {
            result-=2;
            prev = '\0';
        } else if (prev == 'X' && (ch == 'L' || ch == 'C')) {
            result-=20;
            prev = '\0';
        } else if (prev == 'C' && (ch == 'D' || ch == 'M')) {
            result -= 200;
            prev = '\0';
        } else {
            prev = ch;
        }
    }
    return result;
}

int romaToIntV2(const std::string& rnum) {
    int rmap[89] = {0};
    rmap[(int)'I'] = 1;
    rmap[(int)'V'] = 5;
    rmap[(int)'X'] = 10;
    rmap[(int)'L'] = 50;
    rmap[(int)'C'] = 100;
    rmap[(int)'D'] = 500;
    rmap[(int)'M'] = 1000;
    int result = 0;
    char prev = '\0';
    for (const auto& ch: rnum) {
        result += rmap[ static_cast<int>(ch) ];
        if (prev == '\0') {
            prev = ch;
            continue;
        }
        if (prev == 'I' && (ch == 'X' || ch == 'V')) {
            result-=2;
            prev = '\0';
        } else if (prev == 'X' && (ch == 'L' || ch == 'C')) {
            result-=20;
            prev = '\0';
        } else if (prev == 'C' && (ch == 'D' || ch == 'M')) {
            result -= 200;
            prev = '\0';
        } else {
            prev = ch;
        }
    }
    return result;
}

// using bin search
int mySqrt(int x) {
    if (0 == x) return 0;
    int left = 1, right = x/2, ans =- 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (mid <= x / mid) {
            left = mid + 1;
            ans = mid;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}

// [24,12,8,6]
std::vector<int> productExceptSelf(std::vector<int> &nums) {
    int len = static_cast<int>(nums.size());
    if (len == 1) return nums;
    if (nums.empty()) return {};
    std::vector<int> result(len);
    std::vector<int> fromLeft(len);
    std::vector<int> fromRight(len);

    // first element of fromLeft is 1
    fromLeft[0] = 1;

    // last element of from right will always be 1
    fromRight[len-1] = 1;

    // product up to nums[i] for each iteration
    for (int i = 1; i < len; i++)
        fromLeft[i] = fromLeft[i-1] * nums[i-1];

    // product up to nums[i] for each iteration but from right side of nums
    for (int i = len-2; i >= 0; i--)
        fromRight[i] = fromRight[i+1]*nums[i+1];

    // result would be multipication of product up to nums[i] from left and right
    for (int i = 0; i < len; i++)
        result[i] = fromLeft[i]*fromRight[i];
    return result;
}
// 0 1 10 11 100
static bool is_prime(int n) {
    if (n <= 3) return n > 1;
    if (!(n&1) || !(n%3)) return false;
    for (int i = 5; i*i <= n; i+=6)
        if (!(n%i) || !(n%(i+2))) return false;
    return true;
}

static bool isPalindrome(int n) {
    using namespace std;
    if (n < 10) return true;
    int orig=n, reversedInteger=0;
    while (n>0) {
        reversedInteger = reversedInteger*10 + n%10;
        n/=10;
    }
    return reversedInteger==orig;
}
/*
    Note:
        - all palindromes with an even number of digits are divisible by 11, 
            and are therefore not prime! (Except for 11.)
        - therefore all palandromic primes have odd number of digits 
        !(isPrime(N) && isPalindrome(N))
    discussion solution ==> https://leetcode.com/articles/prime-palindrome/
*/
// generate palindromes of even and odd length palindromes and check
// if prime and >= N 
// see https://leetcode.com/articles/prime-palindrome/
int primePalindrome(int N) {
    for (int L = 1; L <= 5; ++L) { // loop through length of palindrome to be generated 
        // check for odd length palindromes
        for (int root = std::pow(10, L-1); root < std::pow(10, L); root++) {
            std::string tmp(std::to_string(root));
            for (int k = L-2; k >= 0; k--) tmp.append(1, tmp.at(k));
            int val = atoi(tmp.c_str());
            if (val >= N && is_prime(val)) return val;

        }

        // check for even length palindromes 
        for (int root = std::pow(10, L-1); root < std::pow(10, L); root++) {
            std::string tmp(std::to_string(root));
            for (int k = L-1; k >= 0; k--) tmp.append(1, tmp.at(k));
            int val = atoi(tmp.c_str());
            if (val >= N && is_prime(val)) return val;
        }
    }
    return -1;
}

/*
 *  returns all combinations of a set of size n where vector maps to indices in a vector -->
 *  if n = 4 then we return subset combinations of [0, 1, 2, 3]
 *  n <= 64
 *  generates indexes from 0 - n-1
 *  so if n=3 then indices in the combinations will range between 0-2
 */
std::vector<std::vector<int>> combinationsBinCnt(int n) {
    if (n > 64) return {};
    std::vector<std::vector<int>> combos;
    uint64_t binary = 0;    // max n can be 64 bits
    const uint64_t numSubSets = (uint64_t) std::pow(2, n);
    for (uint64_t cnt = 0; cnt < numSubSets; cnt++)
        combos.push_back( findBitPositions(binary++) );
    return combos;
}

std::vector<int> buildSolutionVect(const std::vector<int>& indMap,
                                   const std::vector<int>& data) {
    if (indMap.size() > data.size())
        return {};
    std::vector<int> res;
    for (auto ind : indMap) res.push_back(data[ind]);
    return res;
}

// using binary counting method
// time compexity: O(n2^n)
// space complexity: O(
std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
    std::vector<std::vector<int>> res;
    int n = (int)nums.size();
    std::vector<std::vector<int>> indexMaps = combinationsBinCnt(n);

    // build solution vectors
    for (auto indMapping: indexMaps) res.push_back(buildSolutionVect(indMapping, nums));
    return res;
}

// for good video see --> https://www.youtube.com/watch?time_continue=2&v=3dEVYiyFKac
// recursive solution
std::vector<std::vector<int>> subsetsV2(std::vector<int>& nums) {
    std::vector<std::vector<int>> powerset;
    std::vector<int> selected;
    open_sets(nums, 0, selected, powerset);
    return powerset;
}

/*
 * Approach:
 *  1. iterative solution
 *  2. start with empty set [[]]
 *  3.
 */
std::vector<std::vector<int>> subsetsV3(std::vector<int> &nums) {
    std::vector<std::vector<int>> res({});

}

