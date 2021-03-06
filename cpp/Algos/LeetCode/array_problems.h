#ifndef  DATASTRUCTS_N_ALGOS_ARRAY_PROBLEMS_H
#define DATASTRUCTS_N_ALGOS_ARRAY_PROBLEMS_H
#include <vector>
#include <string>
#include <map>

#include "types.h"

// types
typedef std::vector<std::vector<int>> IntMatrix;
typedef std::vector<std::vector<std::string>> StrMatrix;
typedef std::vector<std::vector<char>> CharMatrix;
typedef std::vector<std::vector<char>> SudokuBoard;
typedef std::vector<char> SudokuRow;
typedef std::map<int, SudokuRow> SudokuColumns;

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+arrays=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%EASY%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
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

// problem: #905 Sort Array By Parity 
// result: 28 ms faster than 98.86%, Mem: 8.6 MB less than 99.68% 
std::vector<int> sortArrayByParity(std::vector<int>& A);
std::vector<int> sortArrayByParityV2(std::vector<int>& A);

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%MEDIUM%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
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
// result: 99.6% (not my solution)
// Suppose you have a random list of people standing in a queue. 
// Each person is described by a pair of integers (h, k), 
// where h is the height of the person and k is the number of people in front of 
// this person who have a height greater than or equal to h. Write an algorithm to reconstruct the queue.
// Example
// Input:
// [[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]
// Output:
// [[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
std::vector<std::pair<int, int>> reconstructQueue(std::vector<std::pair<int, int>>& people);

// problem: 739
// result: V1(3.51%), V2(96.56%)
// V2: concept was takeOn from discussion implementation was mine
//Given a list of daily temperatures T, return a list such that, for each day in the input,
// tells you how many days you would have to wait until a warmer temperature.
// If there is no future day for which this is possible, put 0 instead.
//For example, given the list of temperatures T = [73, 74, 75, 71, 69, 72, 76, 73],
// your output should be [1, 1, 4, 2, 1, 1, 0, 0].
std::vector<int> dailyTemperatures(std::vector<int>& T);
std::vector<int> dailyTemperaturesV2(std::vector<int> &T);

// problem: 162
// result: 99%
// A peak element is an element that is greater than its neighbors.
// Given an input array nums, where nums[i] ≠ nums[i+1], find a peak element and return its index.
// The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.
// You may imagine that nums[-1] = nums[n] = -∞. Should have a logarithmic solution
// Input: nums = [1,2,3,1]
// Output: 2
// Explanation: 3 is a peak element and your function should return the index number 2.
int findPeakElement(std::vector<int>& nums);

// problem: 200
// result: 98.93% (took concept from discussion)
// Given a 2d grid map of '1's (land) and '0's (water), count the number of islands.
// An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
// You may assume all four edges of the grid are all surrounded by water.
//
//Example 1:
//Input:
//11110
//11010
//11000
//00000
//Output: 1
int numIslands(std::vector<std::vector<char>>& grid);

// problem: 78
// result:
//Given a set of distinct integers, nums, return all possible subsets (the power set).
//Note: The solution set must not contain duplicate subsets.
// hint: backtracking problem type
std::vector<std::vector<int>> subsets(std::vector<int>& nums);
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%HARD%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/*
 * There is a garden with N slots. In each slot, there is a flower. The N flowers will bloom one by one in N days.
 * In each day, there will be exactly one flower blooming and it will be in the status of blooming since then.

Given an array flowers consists of number from 1 to N. Each number in the array represents
 the place where the flower will open in that day.

For example, flowers[i] = x means that the unique flower that blooms at day i
 will be at position x, where i and x will be in the range from 1 to N.

Also given an integer k, you need to output in which day there exists two
 flowers in the status of blooming, and also the number of flowers between them is k
 and these flowers are not blooming.

If there isn't such day, output -1.
   Also given an integer k, you need to output in which day there exists two flowers in the status of blooming,
   and also the number of flowers between them is k and these flowers are not blooming.
   example: (expected answer=3)
   [5,4,1,3]
	2
*/
int kEmptySlots(std::vector<int>& flowers, int k);

/*
    975. Odd Even Jump
    Descr:
    You are given an integer array A.  From some starting index, you can make a series of jumps.
    The (1st, 3rd, 5th, ...) jumps in the series are called odd numbered jumps, and the (2nd, 4th, 6th, ...)
    jumps in the series are called even numbered jumps.

	You may from index i jump forward to index j (with i < j) in the following way:

	During odd numbered jumps (ie. jumps 1, 3, 5, ...), you jump to the index j such that A[i] <= A[j] and A[j]
	 is the smallest possible value.  If there are multiple such indexes j, you can only jump to the smallest such index j.
	During even numbered jumps (ie. jumps 2, 4, 6, ...), you jump to the index j such that A[i] >= A[j] and A[j] is the
	 largest possible value.  If there are multiple such indexes j, you can only jump to the smallest such index j.
	(It may be the case that for some index i, there are no legal jumps.)
	A starting index is good if, starting from that index, you can reach the end of the array (index A.length - 1)
	 by jumping some number of times (possibly 0 or more than once.)

		Return the number of good starting indexes.
 */
int oddEvenJumps(std::vector<int>& A);
#endif // DATASTRUCTS_N_ALGOS_ARRAY_PROBLEMS_H