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

// Problem #168 100% 0ms 
std::string excel_column_title( int n );

// Problem #59
std::vector<int> count_bits( int num );

bool operator > ( envelope& env1, envelope& env2 );

// problem: 70. Climbing Stairs
int climbingSteps(int, int, std::vector<int>&);

// problem #53
int maxSubArray(std::vector<int>& nums);
int maxSubArray2(std::vector<int>& nums);
int maxSubArray3(std::vector<int>& nums);

// problem #66
std::vector<int> plusOne(std::vector<int>& digits);

// problem #283
void moveZeros(std::vector<int>& nums);
void moveZerosV2(std::vector<int>& nums);

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

// problem #387
int firstUniqChar(std::string s);
int firstUniqCharV2(std::string s);
int firstUniqCharV3(std::string s);

// problem #242
bool validAnaGram(std::string& s, std::string& t);
bool validAnaGramV2(std::string& s, std::string t);

// problem #125
// empty strings are considered valid
bool validPalindrome(std::string& s);

// problem #8 medium 
// result: 27.15%  34 ms
int myAtoi(const std::string& str);
int myAtoiV2(const std::string& str);

// problem #28 98%  6ms
int strStr(std::string haystack, std::string needle);

// problem #
// find nth term of the count and say sequence and output to string 
//1 1
//2.11
//3.21
//4.1211
//5.111221
// reading it 
//1 is read off as "one 1" or 11.
//11 is read off as "two 1s" or 21.
//21 is read off as "one 2, then one 1" or 1211.
// result: 4ms 79.17%
std::string countAndSay(int n);

// delete provided node from linked list it exists in
// problem #237
// 72.38% 14ms
void deleteNode(ListNode* node);

// problem #19
// Given a linked list, remove the n-th node from the end of list and return its head.
// result: 11ms 35.03%
ListNode* removeNthFromEnd(ListNode* head, int n);
ListNode* removeNthFromEndV2(ListNode* head, int n);

// reverse linked list
// problem #206
// result: iterative: 16ms 7.13%
ListNode* reverseList(ListNode* head);
ListNode* reverseListV2(ListNode* head);

// helpers
void _reverseRecursive(ListNode* curr, ListNode* prev, ListNode** head);
void _reverseIterative(ListNode** head);
int _cleanStrToInt(const std::string& str, int pwr, int sign);
bool _checkRows(const SudokuBoard& board);
void _addColsElement(SudokuColumns& cols, const SudokuRow& row, int colIndex);
bool _checkSquares(SudokuBoard &board);
bool _checkDuplicate(const std::vector<char>& rw);
void _rotateLayer(IntMatrix& matrix, uint32_t layer);
void _genCntNSay(std::string& currTerm, std::string& nextTerm);
int _getCount(const std::string& str, const int& offset);


#endif //ALGOS_SHORT_ALGOS_H
