#include <algorithm>
#include <cstdint>
#include "dynamic_problems.h"
#include "utility.h"

using std::vector;

int _climbStairs( int i, int n, std::vector<int>& memo ) {
    if (i > n) return 0;
    if (i == n) return 1;
    if (memo[i] > 0) return memo[i];
    memo[i] = _climbStairs(i+1, n, memo) + _climbStairs(i+2, n, memo);
    return memo[i];
}

// recursive solution using memoization
int climbStairs(int n) {
    std::vector<int> memo(n+1, 0);
    return _climbStairs(0, n, memo);
}

// iterative solution (faster) Tabulated Version
int climbStairsV2(int n) {
    std::vector<int> ways(n);
    ways[0] = 1;
    ways[1] = 2;
    for(int i = 2; i < n; i++)
        ways[i] = ways[i-1] + ways[i-2];
    return ways[n-1];
}

int maxProfit(std::vector<int>& prices) {
    int min = INT32_MAX;
    int profit = 0;
    for (auto& price : prices) {
        if (price - min > profit) profit = price - min;
        else if (price < min) min = price;
    }
    return profit;
}

// brute force O(n^2)
int maxSubArray(std::vector<int>& nums) {
    if (nums.size()==0)
        return 0;
    if (nums.size()==1)
        return nums[0];
    int sum = *max_element(nums.begin(), nums.end());
    int tmp = INT32_MIN;
    int cnt = 0;
    for(unsigned int i = 0; i < nums.size(); ++i) {
        for ( unsigned int j = i+1; j <= nums.size(); ++j) {
            tmp = accum(nums.begin()+i, nums.begin()+j);
            if (tmp > sum) {
                sum = tmp;
            }
            cnt++;
        }
    }
    return sum;
}

// 0(n) solution
int maxSubArray2(std::vector<int>& nums) {
    if (nums.empty())
        return 0;
    if (nums.size() == 1)
        return nums[0];

    int result = nums[0];
    int sum = 0;

    for (auto& el: nums) {
        sum += el;
        result = std::max(sum, result);
        sum = std::max(sum, 0);	 // if sum drops below zero then reset sum
    }
    return result;
}

/*
	dynamic programming version 0(n) solution
*/
int maxSubArray3(std::vector<int>& nums) {
    size_t n = nums.size();
    std::vector<int> dp(n, 0);
    dp[0] = nums[0];
    int sum = dp[0];

    for (int i = 1; i < n; i++) {
        dp[i] = nums[i] + ((dp[i-1] > 0) ? dp[i-1]:0);
        sum = std::max(sum, dp[i]);
    }
    return sum;
}

// max sum of a sub array that crosses the midpoint -->
// [* l * * (* * m * * *) * r * ] << max sum between [mid, l] and [mid+1, r] then combine to
// form the crossSum
void _maxCrossingSubArray(std::vector<int>& nums, int l, int mid, int r, int& _max) {
    std::cout << "\n" << std::endl;
    LOG << "l: " << l << " mid: " << mid << " r: " << r << " max: " << _max << std::endl;
    int leftSum = INT32_MIN;
    int sum = 0;
    // get sum from middle towards l --> [ * * * l * * <--- mid * * * * r]
    for (int i = mid; i >= l; i--) {
        sum += nums[i];
        if (sum > leftSum) {
            leftSum = sum;
        }
    }
    int rightSum = INT32_MIN;
    sum = 0;
    for (int i = mid+1; i <= r; i++) {
        sum += nums[i];
        if (sum > rightSum) {
            rightSum = sum;
        }
    }
    int crossSum = (leftSum+rightSum);
    LOG << "leftSum: " << leftSum << " rightSum: " << rightSum << " crossSum: " << crossSum << std::endl;

    // see if crossing sums are larger than current max value
    if (leftSum > rightSum && leftSum > crossSum && leftSum > _max) _max = leftSum;
    else if (rightSum > leftSum && rightSum > crossSum && rightSum > _max) _max = rightSum;
    else if (crossSum > _max) _max = crossSum;
}

// recurse div and conq
void _maxSubArray(std::vector<int>& nums, int l, int r, int& _max)  {
    using namespace std;
    LOG << "l: " << l << " r: " << r << " max: " << _max << endl;

    // base case one element
    if (l==r) {
        if (nums[l] > _max) _max = nums[l];
        return;
    }
    int mid = (l+r)/2;
    _maxSubArray(nums, l, mid, _max);
    _maxSubArray(nums, mid+1, r, _max);
    _maxCrossingSubArray(nums, l, mid, r, _max);
}

/*
	Divide and conquer solution 0(n)
	Recursive
*/
int maxSubArray4(std::vector<int>& nums) {
    if (nums.size()==1) return nums[0];
    int max = INT32_MIN;
    _maxSubArray(nums, 0, (int)nums.size()-1, max);
    return max;
}

void _rob(std::vector<int>& nums, int start, int& robbed) {
    if (start >= nums.size())
        return;
    robbed += nums[start];
    start+=2;


}

/*
 * houses are situated in a row, a theif cannot rob two adjacent houses.
 *
 * dp[i] = max (hval[i] + dp[i-2], dp[i-1])
 *
 * hval[i] + dp[i-2] is the case when thief
 * decided to rob house i.
 *
 * In that situation max value will be the current value of house + maximum value stolen till last
 * robbery at house not adjacent to house i which will be house i-2.
 *
 * dp[i-1] is the case when theif decided not to rob house i. So he will check adjacent house for
 * max value stolen till now
 */
int rob(std::vector<int> &nums) {
    if (nums.empty()) return 0;
    size_t len = nums.size();
    if (len == 1) return nums[0];
    if (len == 2) return std::max(nums[0], nums[1]);
    std::vector<int> dp(len, 0);
    dp[0] = nums[0];
    dp[1] = std::max(nums[0], nums[1]);
    for (int i = 2; i < len; i++) {
        dp[i] = std::max(nums[i]+dp[i-2], dp[i-1]);
    }
    return dp[len-1];
}

// faster version, O(1) mem usage
int robV2(std::vector<int>& nums) {
    int lastRob = 0, lastNotRob = 0;
    int tmpRob  = 0, tmpNotRob  = 0;
    for (size_t i = 0; i < nums.size(); ++i) {
        tmpRob    = lastNotRob + nums[i];
        tmpNotRob = lastRob > lastNotRob ? lastRob : lastNotRob;
        lastRob    = tmpRob;
        lastNotRob = tmpNotRob;
    }
    return lastRob > lastNotRob ? lastRob : lastNotRob;
}

// each step we can either go right or down
// TODO :: has issues
void _uniquePaths(std::pair<int, int> currPos, const std::pair<int, int>& targetPos, int& numPaths) {

    // step right and check position
    if (currPos.first < targetPos.first) {
        currPos.first++;
        if (currPos==targetPos) {
            numPaths++;
        }
        _uniquePaths(currPos, targetPos, numPaths);
    }

    // step down and check position
    if (currPos.second < targetPos.second) {
        currPos.second++;
        if (currPos==targetPos) {
            numPaths++;
        }
        _uniquePaths(currPos, targetPos, numPaths);
    }
}

/*
    A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
    The robot can only move either down or right at any point in time.
    The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
    How many possible unique paths are there?
 */
// TODO :: has issues
int uniquePaths(int m, int n) {
    int numPaths = 0;
    std::pair<int, int> curPosition = {0, 0}; // (col, row)
    _uniquePaths(curPosition, {n-1, m-1}, numPaths);
    return numPaths;
}

/*
 * FYI: mxn matrix is m rows by n columns
    Since the robot can only move right and down, when it arrives at a point, there are only two possibilities:
    1. It arrives at that point from above (moving down to that point);
    2. It arrives at that point from left (moving right to that point).

    Thus, we have the following state equations: suppose the number of paths to arrive at a point (i, j)
    is denoted as P[i][j], it is easily concluded that P[i][j] = P[i - 1][j] + P[i][j - 1].

    The boundary conditions of the above equation occur at the leftmost column (P[i][j - 1] does not exist)
    and the uppermost row (P[i - 1][j] does not exist).
    These conditions can be handled by initialization (pre-processing)
    --- initialize P[0][j] = 1, P[i][0] = 1 for all valid i, j. Note the initial value is 1 instead of 0!

    Now we write the following unoptimized code ...
 */
int uniquePathsV2(int m, int n) {
    std::vector<std::vector<int> > path(m, std::vector<int> (n, 1));
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            path[i][j] = path[i - 1][j] + path[i][j - 1];
        }
    }
    return path[m - 1][n - 1];
}

/*
    The following is the same code as above (V2) but optimized
    It can be observed that each tiime when we update path[i][j] we only need path[i-1][j] (at the same column)
    and path[i][j-1] (at the left column). So it is enough to maintain two columns
    (the current column and the left column) instead of maintaining the full mxn matrix.
    Code is optimized to have O(min(m, n)) space complexity

    Inspecting the code below we find that keeping two columns is used to recover pre[i], which is just
    cur[i] before its update. So there is even no need to use two vectors and one is just enough.
    Space is further saved and the code gets shorter as well.

    Since we are only going right and down the column and the column to the left are all that matter
    * * *
    * 0 *
    * * *
    in the matrix above ^ ... to get to the cell with 0 we only care about the 2nd column (current) and
    the first column (prev) no need to keep entire matrix in mem
 */
int uniquePathsV3(int m, int n) {
    if (m > n) return uniquePathsV3(n, m);  // ensure space complexity is O(min(m,n))
    std::vector<int> pre(m, 1);
    std::vector<int> cur(m, 1);
    for (int j = 1; j < n; j++) {
        for (int i = 1; i < m; i++) {
            cur[i] = cur[i-1] + pre[i];
        }
        std::swap(pre, cur);
    }
    return pre[m-1];
}

/*
    Further inspecting V3 we see that there is no need to keep two vectors as prev[i] is cur[i] before its update
 */
int uniquePathsV4(int m, int n) {
    if (m > n) uniquePathsV4(n, m);
    std::vector<int> cur(m,1);
    for (int j =1; j < n; j++) {
        for (int i = 0; i < m; i++) {
            cur[i] += cur[i-1];
        }
    }
    return cur[m-1];
}

std::vector<Interval> mergeIntervals(std::vector<Interval> &intervals) {
    std::vector<Interval> result;
    // sort by starting point, neighboring intervals will be potential overlappers
    std::sort(intervals.begin(),
              intervals.end(),
              [](auto& a, auto& b){ return a.start < b.start; });
    for (auto& intv : intervals) {
        /*
         * if the list of the merged intervals is empty or if the current interval does not overlap
         * with the previous, simply append it
         */
        if ( result.empty() || (result.end()-1)->end < intv.start )
            result.push_back(intv);
        else // otherwise there is overlap, so we merge the current and previous intervals
            (result.end()-1)->end = std::max((result.end()-1)->end, intv.end);
    }
    return result;
}

/*
    Problem: 518 

    Description:
        You are given coins of different denominations and a total amount of money. Write a 
        function to compute the number of combinations that make up that amount. 
        You may assume that you have infinite number of each kind of coin.

    Approach:
        we create a dp table to keep track of our decision making. This problem is similar to the 0|1 Knapsack
        problem. At each cell we have a choice whether we decide to include a new coin or not.
        We start with no coins (empty set []), at each column we ask ourselves can I make change for 0, .. 1, ...2 etc etc 
        If you can make change you add one to the previous value in that row.

    Example:
    coins = [1, 2, 5]
    amount = 5
    result: 5=5
            5=2+2+1
            5=2+1+1+1
            5=1+1+1+1+1
    =========================

    rows: coins to consider top to bottom
    cols: 0 to amount (amount of change holding at a given time)
                 0 1 2 3 4 5   --> targetAmt
                 -----------
coinType --> []| 1 0 0 0 0 0   
          [-1-]| 1 1 1 1 1 1
       [1, -2-]| 1 1 2 2 3 3
    [1, 2, -5-]| 1 1 2 2 3 4

    complexity:
        time:  O(numCoins * amount)
        space: O(numCoins * amount)
*/
int change(int amount, vector<int>& coins) {
    if (coins.empty() && amount == 0) return 1;
    const int numCoins = coins.size()+1;
    vector<vector<int>> dp(numCoins, vector<int>(amount+1, 0));
    dp[0][0]=1;
    for (int coinType = 1; coinType < dp.size(); coinType++) {
        for (int targetAmt = 0; targetAmt <= amount; targetAmt++) {
            // dp[coinType][targetAmt] = (numcombos where we do coin case) + (numcombos where we dont use coin case);
            int tmp = (targetAmt) - coins[coinType-1];
            dp[coinType][targetAmt] = (tmp >= 0 ?  dp[coinType][tmp] : 0) + dp[coinType-1][targetAmt];
        }
    }
    return dp[numCoins-1][amount];
}

// optimize for space and time
int changeV2(int amount, std::vector<int> &coins) {

}

