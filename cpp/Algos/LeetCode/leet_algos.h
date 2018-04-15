#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "types.h"

#ifndef ALGOS_SHORT_ALGOS_H
#define ALGOS_SHORT_ALGOS_H

// typedef and alias
typedef std::vector<std::vector<char>> SudokuBoard;

// problem #24
ListNode* swapPairs(ListNode* head);

// Problem #168
std::string excel_column_title( int n );

// Problem #59
std::vector<int> count_bits( int num );

// Problem #122
int best_time_to_buy_and_sell_stock( std::vector<int>& prices );


bool operator > ( envelope& env1, envelope& env2 );

// problem #
int maxProfit(std::vector<int>& prices);

// problem: 70. Climbing Stairs
int climbingSteps(int, int, std::vector<int>&);

// problem #53
int maxSubArray(std::vector<int>& nums);
int maxSubArray2(std::vector<int>& nums);
int maxSubArray3(std::vector<int>& nums);

// problem #66
std::vector<int> plusOne(std::vector<int>& digits);

// problem #283
void moveZeroes(std::vector<int>& nums);
void moveZeroesV2(std::vector<int>& nums);

// problem #1
std::vector<int> twoSums(std::vector<int>& nums, int target);
std::vector<int> twoSumsV2(std::vector<int> &nums, int target);

// problem #
bool isValidSudoku(SudokuBoard& board);
bool _checkRow(const std::vector<char>& rw);

#endif //ALGOS_SHORT_ALGOS_H
