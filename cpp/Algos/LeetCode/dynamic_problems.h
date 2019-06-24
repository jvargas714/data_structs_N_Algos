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
// You are given coins of different denominations and a total amount of money. Write a function to
// compute the number of combinations that make up that amount. You may assume that you have
// infinite number of each kind of coin.
// result:
//      Runtime: 20 ms, faster than 41.13%
//      Memory Usage: 20 MB, less than 20.77%
int change(int amount, std::vector<int>& coins);
int changeV2(int amount, std::vector<int>& coins);


/* 
problem: 322
Description: 
    You are given coins of different denominations and a total amount of money amount. Write a function to compute the 
    fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any 
    combination of the coins, return -1.

Result:
    Runtime: 36 ms, faster than 90.36%
    Space: Memory Usage: 12.5 MB, less than 68.98%

 Complexity:
    runtime: O(coins * amount)
    space: O(amount)
*/
int calcChange(int amount, std::vector<int>& coins);

/*
 * problem: 983
 *
 * Description:
 *      In a country popular for train travel, you have planned some train travelling one year in advance.
 *      The days of the year that you will travel is given as an array days.  Each day is an integer from 1 to 365.
        Train tickets are sold in 3 different ways:

        a 1-day pass is sold for costs[0] dollars;
        a 7-day pass is sold for costs[1] dollars;
        a 30-day pass is sold for costs[2] dollars.
        The passes allow that many days of consecutive travel.
        For example, if we get a 7-day pass on day 2, then we can travel
        for 7 days: day 2, 3, 4, 5, 6, 7, and 8.

        Return the minimum number of dollars you need to travel every day in the given list of days.

 * Result:
 *
 * Complexity:
 *  runtime:
 *  space:
 */
int mincostTickets(std::vector<int>& days, std::vector<int>& costs);

#endif //DATASTRUCTS_N_ALGOS_DYNAMIC_PROBLEMS_H
