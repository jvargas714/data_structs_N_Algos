#ifndef DATASTRUCTS_N_ALGOS_DYNAMIC_PROBLEMS_H
#define DATASTRUCTS_N_ALGOS_DYNAMIC_PROBLEMS_H
#include <vector>
#include "types.h"


// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%EASY%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// problem: 70
// result: 29.32% 4ms
int climbStairs(int n);
int climbStairsV2(int n);

// problem: 121
// result: 11.12% 13ms
int maxProfit(std::vector<int>& prices);

// problem #53
// result: TLE
int maxSubArray(std::vector<int>& nums);
// result: 33.02% 14ms
int maxSubArray2(std::vector<int>& nums);
// result: 95.85% 12ms
int maxSubArray3(std::vector<int>& nums);
// result: 61.40% 13ms
int maxSubArray4(std::vector<int>& nums);

// problem: 198
// result: 14.42% 4ms
int rob(std::vector<int>& nums);
int robV2(std::vector<int>& nums);

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%MEDIUM%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// problem: 62
// result: 100% 0ms (V4 from discussion)
// A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
//The robot can only move either down or right at any point in time.
// The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
//How many possible unique paths are there?
int uniquePaths(int m, int n);
int uniquePathsV2(int m, int n);
int uniquePathsV3(int m, int n);
int uniquePathsV4(int m, int n);

// problem: 56
// result:
// Given a collection of intervals, merge all overlapping intervals.
std::vector<Interval> mergeIntervals(std::vector<Interval>& intervals);

// problem: 518
// result:
// You are given coins of different denominations and a total amount of money. Write a function to
// compute the number of combinations that make up that amount. You may assume that you have
// infinite number of each kind of coin.
// Runtime: 20 ms, faster than 41.13%
// Memory Usage: 20 MB, less than 20.77%
int change(int amount, std::vector<int>& coins);
int changeV2(int amount, std::vector<int>& coins);

#endif //DATASTRUCTS_N_ALGOS_DYNAMIC_PROBLEMS_H
