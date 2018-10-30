#include <vector>
#include <string>
#include <map>

#include "types.h"

// types
typedef std::vector<std::vector<int>> IntMatrix;
typedef std::vector<std::vector<std::string>> StrMatrix;
typedef std::vector<std::vector<char>> SudokuBoard;
typedef std::vector<char> SudokuRow;
typedef std::map<int, SudokuRow> SudokuColumns;

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+arrays=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%EASY%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// problem:
// result:
// rotate array by k places 
void rotateVector(std::vector<int>& nums, int k);

// problem:
// result:
// remove duplicates of sorted array inplace (not my solution)
// // using the length returned by your function, it prints the first len elements
size_t removeDuplicates(std::vector<int>& nums);
int removeDuplicatesV2(std::vector<int>& nums);

// problem #66
std::vector<int> plusOne(std::vector<int>& digits);

// problem #283
// result: 100% 8ms (V3)
// Given an array nums, write a function to move all 0's to the end of it
// while maintaining the relative order of the non-zero elements.
void moveZeros(std::vector<int>& nums);
void moveZerosV2(std::vector<int>& nums);
void moveZerosV3(std::vector<int>& nums);

// problem #1
// result:
// Given an array of integers, return indices of the two numbers such that they add up to a specific target.
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
 */
void rotate(IntMatrix& matrix);
void rotateV2(IntMatrix& matrix);


// problem:
// result:
//
int removeElement(std::vector<int>& nums, int val);

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%MEDIUM%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// problem: 15  
// result: 63.34% 118ms 
// Given an array nums of n integers, are there elements a, b, c in nums
// such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
std::vector<std::vector<int>> threeSum(std::vector<int>& nums);

// problem: 73
// result: 82.88% 56ms
// Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in-place.
void setZeroes(IntMatrix& matrix);

// problem: 49
// result: 39.03% 41ms (V1)
// Given an array of strings, group anagrams together
StrMatrix groupAnagrams(std::vector<std::string>& strs);
StrMatrix groupAnagramsV2(std::vector<std::string>& strs);

// problem: 186
// result: did not place 118 ms V1
// result: did not place 98 ms V2
// Given an input string , reverse the string word by word.
// sample input: ["t","h","e"," ","s","k","y"," ","i","s"," ","b","l","u","e"]
// samele output: ["b","l","u","e"," ","i","s"," ","s","k","y"," ","t","h","e"]
void reverseWords(std::vector<char>& str);
void reverseWordsV2(std::vector<char>& str);
void reverseWordsV3(std::vector<char>& str);

// problem: 414
// result: 98.73% 7ms
// Given a non-empty array of integers, return the third maximum number in this array.
// If it does not exist, return the maximum number
// runtime must be O(n)
int thirdMax(const std::vector<int>& nums);

// problem: 349
// result: 70.98% 8ms
// result: 100% (V2)
// Given two arrays, write a function to compute their intersection.
// each element in the result must be unique, result can be in any order
std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2);
std::vector<int> intersectionsV2(std::vector<int>& nums1, std::vector<int>& nums2);

// problem: 443
// result: 55.04% 9ms
// Given an array of characters, compress it in-place
int compressString(std::vector<char>& chars);

// problem: 42
// result: 66.82% 14ms (not mine)
// Given n non-negative integers representing an elevation map where the width of each bar is 1,
// compute how much water it is able to trap after raining
int trapRainWater(const std::vector<int>& height);

// problem: 54
// result: 97.41% 3ms
// Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.
std::vector<int> spiralOrder(IntMatrix& matrix);

// problem: 55
// result:
// Given an array of non-negative integers, you are initially positioned at the first index of the array.
//Each element in the array represents your maximum jump length at that position.
//Determine if you are able to reach the last index.
bool canJump(std::vector<int>& nums);

// problem: 406
// result: 
// Suppose you have a random list of people standing in a queue. 
// Each person is described by a pair of integers (h, k), 
// where h is the height of the person and k is the number of people in front of 
// this person who have a height greater than or equal to h. Write an algorithm to reconstruct the queue.
// Example
// Input:
// [[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

// Output:
// [[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]

