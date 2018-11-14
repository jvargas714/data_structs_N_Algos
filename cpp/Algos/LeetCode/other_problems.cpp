#include <algorithm>
#include <map>
#include <unordered_map>
#include <stack>
#include <numeric>
#include "utility.h"
#include "other_problems.h"

// ============================================Helper Functions=========================================================
static int _calcNum(int n) {
    int tmp;
    int result = 0;
    while (n > 0) {
        tmp = n % 10;
        n/=10;
        result += tmp*tmp;
    }
    return result;
}

// checks to see if str is valid open and close parenths
static bool isVaildParenth(const std::string& str) {
    int balance = 0;
    for (const auto& ch : str) {
        if (ch == '(')
            balance++;
        else
            balance--;
        if (balance<0) return false;
    }
    return (balance==0);
}


static void _genParenth(int n, int openCnt, int closeCnt, const std::string& currStr,
                                        std::unordered_map<std::string, std::string>& validMap) {
    if (openCnt > n || closeCnt > n) return;
    if (currStr.size() == n*2) {
        if (validMap.find(currStr)==validMap.end() && isVaildParenth(currStr))
            validMap[currStr]=currStr;
        return;
    }
    _genParenth(n, openCnt+1, closeCnt, "("+currStr, validMap);
    _genParenth(n, openCnt+1, closeCnt, currStr+"(", validMap);
    _genParenth(n, openCnt, closeCnt+1, currStr+")", validMap);
}

static void _permute(std::vector<int>& nums, std::vector<std::vector<int>>& result, int lvl) {
    if (lvl == nums.size()) {
        result.push_back(nums);
        return;
    }
    for (int i = lvl; i < (int)nums.size(); i++) {
        swap(nums[lvl], nums[i]);
        _permute(nums, result, lvl+1);
        swap(nums[lvl], nums[i]);
    }
}

// =====================================================================================================================

// Write a function that takes an unsigned integer and returns
// the number of '1' bits it has (also known as the Hamming weight).
int hammingWeight(uint32_t n) {
    int cnt = 0;
    uint8_t byte;
    uint8_t mask = 0x1;
    for (int i = 0; i < 4; i++) {
        byte = *((uint8_t*)(&n)+i);
        for (int j = 0; j < 8; j++) {
            if (byte & (mask<<j))
                cnt++;
        }
    }
    return cnt;
}

int hammingWeightV2(uint32_t n) {
    int cnt = 0;
    uint32_t mask = 0x1;
    for (int j = 0; j < 32; j++) {
        if (n&mask)
            cnt++;
        mask <<= 1;
    }
    return cnt;
}

int hammingDistance(int x, int y) {
    int dist = 0;
    int mask = 0x1;
    for (int i = 0; i < 32; i++) {
        if ((int)(x&mask) != (int)(y&mask)) dist++;
        mask <<= 1;
    }
    return dist;
}

// Reverse bits of a given 32 bits unsigned integer
uint32_t reverseBits(uint32_t n) {
    std::vector<int> bits;
    uint32_t result = 0;
    for (int i = 0; i < 32; i++)
        bits.push_back( (n >> i) & 1 );
    for (int i = 0; i < 32; i++)
        result += bits[31-i] * (1<<i);
    return result;
}

/*
Input: 5
Output:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
*/
std::vector<std::vector<int>> generatePascalsTriangle(int numRows)
{
    std::vector<std::vector<int>> triangle(numRows);
    for (int i = 0; i < numRows; i++) {
        std::vector<int>& tmp = triangle[i];
        for (int j = 0; j < (i + 1); j++) {
            if (j == 0 || j == i ) {
                tmp.push_back(1);
                continue;
            }
            tmp.push_back( (triangle[i - 1][j-1] + triangle[i - 1][j]) );
        }
    }
    return triangle;
}

// {[]}
bool isValidParenthesisStr(std::string& str) {
    if (str.empty()) return true;
    if (str.size() % 2) return false;
    std::stack<char> stkOpen, stkClose;
    char tmp;

    for (const auto& ch : str) {
        if (ch == '[' || ch == '(' || ch == '{')
            stkOpen.push(ch);
        else {  // closing character
            if (!stkOpen.empty())
                tmp = stkOpen.top();
            else return false;

            if (tmp == '[' && ch == ']')
                stkOpen.pop();
            else if (tmp == '(' && ch == ')')
                stkOpen.pop();
            else if (tmp == '{' && ch == '}')
                stkOpen.pop();
            else {
                stkClose.push(ch);
            }
        }
    }
    if (stkOpen.size() != stkClose.size()) return false;
    for (size_t j = 0; j < stkClose.size(); j++) {
        if (stkClose.top() != stkOpen.top()) return false;
    }
    return true;
}

bool isValidParethesisStrV2(std::string s) {
    std::stack<char> stkOpen;
    for (const auto& ch : s) {
        if (ch == '{' || ch == '[' || ch == '(') {
            stkOpen.push(ch);
        } else if (!stkOpen.empty()) {
            if (ch == ']' && stkOpen.top() != '[') return false;
            else if (ch == '}' && stkOpen.top() != '{') return false;
            else if (ch == ')' && stkOpen.top() != '(') return false;
            stkOpen.pop();
        } else
            return false;
    }
    if (!stkOpen.empty()) return false;
    return true;
}

// needs to run in linear runtime with 0(1) mem complexity
int missingNumber(std::vector<int>& nums) {
    auto el = std::find_if(nums.begin(), nums.end(), [](auto el){ return el == 0; });
    if (el == nums.end())
        return 0;
    LOG << "el: " << *el << END;
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    LOG << "sum: " << sum << END;
    int targetSum = 0;
    int val = 1;
    for (int i = 1; i < nums.size()+1; i++) {
        targetSum += val++;
    }
    LOG << "targetSum: " << targetSum << END;
    return targetSum-sum;
}

bool isHappy(int n) {
    int val = n;
    std::map<int, int> nums;
    while (val!=1) {
        val = _calcNum(val);
        auto entry = nums.find(val);
        if (entry != nums.end()) return false;
        nums[val] = val;
    }
    return true;
}

/* Problem: #59 */
std::vector<int> count_bits( int num ) {
    std::vector<int> result( 1,0 );
    int mask;
    int cnt = 0;

    for( uint i = 1; i <= num; i++ ) {
        cnt = 0;
        mask = 0x1;
        for( uint j = 0; j < 8*sizeof( int ); j++ ) {
            if( mask & i )
                cnt++;
            mask <<= 1;
        }
        result.push_back( cnt );
    }
    return result;
}

bool operator > ( envelope& env1, envelope& env2 ) {
    return (env1.first > env2.first) && (env1.second > env2.second);
}

int maxEnvelopes(std::vector<envelope>& envelopes) {
    sort( envelopes.begin(), envelopes.end());
    // display( envelopes );
    bool first_fit = false;
    int cnt = 0;

    for( int i = 0; i < envelopes.size()-1; ++i ) {
        if( !first_fit && envelopes[i+1] > envelopes[i] ) {
            cnt+=2;
            first_fit = true;
        }

        if( first_fit && envelopes[i+1] > envelopes[i] ) {
            cnt++;
        }
    }
    return cnt;
}

std::vector<std::string> generateParenthesis(int n) {
    if (n == 0) return {};
    std::unordered_map<std::string, std::string> validMap;
    std::vector<std::string> result;

    // recurse through other potential solutions
    _genParenth(n, 1, 0, "(", validMap);
    for (auto& entry: validMap) result.push_back(entry.second);
    return result;
}

// optimized solution
void generateParenthesisHelper(int left, int right, int n, std::vector<std::string>& res, std::string str) {
    if (left == n && right == n) {
        res.push_back(str);
    } else if (right > left || right > n || left > n) {
        //created invalid sequence
        return;
    } else {
        generateParenthesisHelper(left+1, right, n, res, str + "(");
        generateParenthesisHelper(left, right+1, n, res, str + ")");
    }
}

std::vector<std::string> generateParenthesisV2(int n) {
    std::vector<std::string> res;
    std::string s;
    generateParenthesisHelper(0, 0, n, res, s);
    return res;
}

std::vector<std::vector<int>> permute(std::vector<int> &nums) {
    if (nums.empty()) return {};
    std::vector<std::vector<int>> result;
    _permute(nums, result, 0);
    return result;
}

/*
 * Window position              Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
 output: [3, 3, 5, 5, 6, 7]
 */
// brute force !!
// O( k*(n-k+1) )
std::vector<int> maxSlidingWindow(std::vector<int> &nums, int k) {
    std::vector<int> result;
    if (nums.empty() || nums.size() < k) return {};
    if (nums.size() == 1 || k == 1) return nums;

    int i = 0, j = k - 1;
    auto len = static_cast<int>(nums.size());
    while (j < len) {
        result.push_back(
                maxElement<std::vector<int>::iterator, int>(nums.begin()+i, nums.begin()+j)
        );
        i++;
        j++;
    }
    return result;
}

// optimized solution
// O(n)
// TODO :: still some issues
std::vector<int> maxSlidingWindowV2(const std::vector<int> &nums, int k) {
    if (nums.empty() || nums.size() < k) return {};
    if (nums.size() == 1 || k == 1) return nums;

    std::vector<int> result;
    std::pair<int , int> prevMaxVal = {INT32_MIN, INT32_MIN};   // val, index
    std::pair<int , int> maxVal = {INT32_MIN, INT32_MIN};   // val, index

    for (int i = 0; i < (int)nums.size(); i++) {
        int el = nums[i];
        // save max and previous max
        if (el > maxVal.first) {
            prevMaxVal = maxVal;
            maxVal.first = el;
            maxVal.second = i;
        } else if (el > prevMaxVal.first) {
            prevMaxVal.first = el;
            prevMaxVal.second = i;
        }
        if (i>=k-1) {
            result.push_back(maxVal.first);
            // check if prev Max index falls out of window next iteration
            if ( maxVal.second <= i - k + 1 ) {
                maxVal = prevMaxVal;
                prevMaxVal = {INT32_MIN, INT32_MIN};
            } else if (prevMaxVal.second <= i - k + 1) {
                prevMaxVal = {nums[i-1], i-1};
            }
        }
    }
    return result;
}

// solution using a deque
// amortized O(n) solution (from discussion)
std::vector<int> maxSlidingWindowV3(const std::vector<int> &nums, int k) {
    if (nums.empty() || k <= 0) return {};
    int n = (int)nums.size();
    std::vector<int> result(n-k+1, 0);
    int ri = 0;
    std::deque<int> dq;
    for (int i = 0; i < n; i++) {
        // removes numbers out of range k
        while (!dq.empty() && dq.front() < i - k + 1) dq.pop_front();

        // remove smaller numbers in k range as they are useless
        while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();

        // q contains index
        dq.push_back(i);
        if (i >= k -1) result[ri++] = nums[dq.front()];
    }
    return result;
}

