#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include "types.h"

#ifndef ALGOS_SHORT_ALGOS_H
#define ALGOS_SHORT_ALGOS_H

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

#endif //ALGOS_SHORT_ALGOS_H
