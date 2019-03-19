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

#endif //DATASTRUCTS_N_ALGOS_MATH_PROBLEMS_H
