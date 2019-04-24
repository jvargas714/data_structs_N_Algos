#ifndef DATASTRUCTS_N_ALGOS_MATH_PROBLEMS_H
#define DATASTRUCTS_N_ALGOS_MATH_PROBLEMS_H
#include <string>
#include <vector>

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=Math=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%EASY%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// result: 71.14% 29ms
// problem: 204
int countPrimes(int n);

// problem: 326
// result: 69.50% 80ms
bool isPowerOfThree(int n);

// problem: 13
// result: 78.02% 121ms (using V2)
int romanToInt(std::string&);
int romaToIntV2(const std::string&);

// problem: 69
// result: 100% 12ms
// find integer sqr root of x
int mySqrt(int x);

// problem:  238
// result: 99.07% 32ms
// Given an array nums of n integers where n > 1,
// return an array output such that output[i] is equal to the
// product of all the elements of nums except nums[i].
std::vector<int> productExceptSelf(std::vector<int>& nums);

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%MEDIUM%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// problem: 866 
// Find the smallest prime palindrome greater than or equal to N.
// Runtime: 80 ms, faster than 55.30%
// Memory Usage: 8.6 MB, less than 30.77%
int primePalindrome(int N);

/*
problem: 78 Subsets
Input: nums = [1,2,3]
Output:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
  todo :: optimize this 
 Approach:
  - binary counting subset generation (please refer to section 14.5 in Skiena Algorithm Design
  result:
    Runtime: 12 ms, faster than 32.24%
    Memory Usage: 9.4 MB, less than 32.31%
  
  Optimization from discussion ==> https://leetcode.com/problems/subsets/discuss/122645/3ms-easiest-solution-no-backtracking-no-bit-manipulation-no-dfs-no-bullshit
 */
std::vector<std::vector<int>> subsets(std::vector<int> &nums);

/*
  todo :: optimize this
  Approach:
    - recursive approach
  result:
    Runtime: 12 ms, faster than 32.24%
    Memory Usage: 12.5 MB, less than 17.27%
*/
std::vector<std::vector<int>> subsetsV2(std::vector<int> &nums);

/*
 * iterative solution
 * result:
 *      Runtime: 12 ms, faster than 32.28%
 *      Memory Usage: 8.9 MB, less than 99.19%
 */
std::vector<std::vector<int>> subsetsV3(std::vector<int> &nums);

#endif //DATASTRUCTS_N_ALGOS_MATH_PROBLEMS_H
