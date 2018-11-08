#ifndef DATASTRUCTS_N_ALGOS_OTHER_PROBLEMS_H
#define DATASTRUCTS_N_ALGOS_OTHER_PROBLEMS_H
#include <cstdint>
#include <string>
#include <vector>
#include "types.h"

/*
 * Other problem types, greedy, dynamic, etc etc ....
 */
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%EASY%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// problem: 191
// result: 89.95% 5ms (using V2)
int hammingWeight(uint32_t n);
int hammingWeightV2(uint32_t n);

// problem: 461
// result: 72.58% 6ms
int hammingDistance(int x, int y);

// problem: 190
// result: 62.28% 6ms
// Reverse bits of a given 32 bits unsigned integer.
uint32_t reverseBits(uint32_t n);

// problem:
// result:
int hammingDistance(int x, int y);

// problem: 118
// result: 96.52% 3ms
// Given a non-negative integer numRows, generate the first numRows of Pascal's triangle.
std::vector<std::vector<int>> generatePascalsTriangle(int numRows);

// problem: 20
// result: 95.53% 4ms
// result:  100% 0ms (V2, original)
// Given a string containing just the characters
// '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
// rules: 1. Open brackets must be closed by the same type of brackets.
//		  2. Open brackets must be closed in the correct order.
bool isValidParenthesisStr(std::string&);
bool isValidParethesisStrV2(std::string s);

// problem: 268
// result: 91.26% 24ms
// Given an array containing n distinct numbers taken
// from 0, 1, 2, ..., n, find the one that is missing from the array
int missingNumber(std::vector<int>& nums);

// problem: 202
// result: 100% 0ms
// A happy number is a number defined by the following process:
// Starting with any positive integer,
// replace the number by the sum of the squares of its digits,
// and repeat the process until the number equals 1 (where it will stay),
// or it loops endlessly in a cycle which does not include 1.
// Those numbers for which this process ends in 1 are happy numbers.
bool isHappy(int n);

// Problem #59
std::vector<int> count_bits( int num );

// problem: 168
// result: 100% 0ms
// Given a positive integer, return its corresponding column
// title as appear in an Excel sheet.
std::string excel_column_title( int n );



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%MEDIUM%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// problem: 22
// result: 0% 204ms
//Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
std::vector<std::string> generateParenthesis(int n);
std::vector<std::string> generateParenthesisV2(int n);

// problem: 46
// result: 99.92 %  8ms
// Given a collection of distinct integers, return all possible permutations.
std::vector<std::vector<int>> permute(std::vector<int>& nums);
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%HARD%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// problem: 239
// result: 21.86% 88ms (V1)
// result V2: needs fixing
// result V3: 99.52% 44ms O(n)
// Given an array nums, there is a sliding window of size k which is moving from the very
// left of the array to the very right. You can only see the k numbers in the window.
// Each time the sliding window moves right by one position. Return the max sliding window.
std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k);
std::vector<int> maxSlidingWindowV2(const std::vector<int>& nums, int k);
std::vector<int> maxSlidingWindowV3(const std::vector<int> &nums, int k);


// 354. Russian Doll Envelopes
// result:
// You have a number of envelopes with widths and heights given as a pair of integers (w, h).
// One envelope can fit into another if and only if both the width and height of one envelope
// is greater than the width and height of the other envelope.
//
// What is the maximum number of envelopes can you Russian doll? (put one inside other)
// Note:
// Rotation is not allowed
bool operator > ( envelope& env1, envelope& env2 );
int maxEnvelopes(std::vector<envelope>& envelopes);
#endif //DATASTRUCTS_N_ALGOS_OTHER_PROBLEMS_H
