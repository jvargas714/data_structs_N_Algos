#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "types.h"

#ifndef ALGOS_SHORT_ALGOS_H
#define ALGOS_SHORT_ALGOS_H

// typedef and alias
typedef std::vector<std::vector<char>> SudokuBoard;
typedef std::vector<char> SudokuRow;
typedef std::map<int, SudokuRow> SudokuColumns;
typedef std::vector<std::vector<int>> IntMatrix;

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

// problem #36
// my submission
bool isValidSudoku(SudokuBoard& board);
// average submission
bool isValidSudokuV2(SudokuBoard& board);
// fastest submission
bool isValidSudokuV3(SudokuBoard& board);
// short solution using bitwise
bool isValidSudokuV4(SudokuBoard& board);

/*
 * problem #48
 * rotate matrix clockwise (90 degrees)
 * Given input matrix =
[
  [ 5, 1, 9,11],
  [ 2, 4, 8,10],
  [13, 3, 6, 7],
  [15,14,12,16]
],

rotate the input matrix in-place such that it becomes:
[
  [15,13, 2, 5],
  [14, 3, 4, 1],
  [12, 6, 8, 9],
  [16, 7,10,11]
]
 */
void rotate(IntMatrix& matrix);
void rotateV2(IntMatrix& matrix);


// problem #344
std::string reverseString(std::string);
// helpers
bool _checkRows(const SudokuBoard& board);
void _addColsElement(SudokuColumns& cols, const SudokuRow& row, int colIndex);
bool _checkSquares(SudokuBoard &board);
bool _checkDuplicate(const std::vector<char>& rw);
void _rotateLayer(IntMatrix& matrix, uint32_t layer);

#endif //ALGOS_SHORT_ALGOS_H
