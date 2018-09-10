#include <stack>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include "types.h"

#ifndef ALGOS_SHORT_ALGOS_H
#define ALGOS_SHORT_ALGOS_H

//=+=+=+=+=+=+=+=+=+=+=+=+typedef and alias=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
typedef std::vector<std::vector<char>> SudokuBoard;
typedef std::vector<char> SudokuRow;
typedef std::map<int, SudokuRow> SudokuColumns;
typedef std::vector<std::vector<int>> IntMatrix;
typedef std::vector<std::vector<std::string>> StrMatrix;
typedef std::vector<std::vector<int>> VectOfVect;

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+Data Structs=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
struct MyPairCompGreater {
    bool operator()(std::pair<std::string, int>& p1, std::pair<std::string, int>& p2) {
        if (p1.second != p2.second)
            return p1.second > p2.second;
        return p1.first < p2.first;
    }
};

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

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

// problem: 3
// result: 2.58% 527ms (V1)
// result: 96.61% 20ms (V2)
// result: 77.85% 33ms (V3)
// Given a string, find the length of the longest substring without repeating characters
int lengthOfLongestSubstring(const std::string& str);
int lengthOfLongestSubstringV2(const std::string& str);
int lengthOfLongestSubstringV3(const std::string& str);

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

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+strings=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+Linked Lists=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%EASY%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// problem #24
ListNode* swapPairs(ListNode* head);

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

// problem #
// result: 42.63% 15ms
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2);
ListNode* mergeTwoListsV2(ListNode* l1, ListNode* l2);


// problem #234
// result: 96.66% 20ms
bool isPalindrome(ListNode*);

// problem: 141
// result: 98.7% 10ms
bool hasCycle(ListNode*);

// problem: 2
// result: 31.57% 67ms
// You are given two non-empty linked lists representing two non-negative integers.
// The digits are stored in reverse order and each of their nodes contain a single digit.
// Add the two numbers and return it as a linked list.
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);
ListNode* addTwoNumbersV2(ListNode* l1, ListNode* l2);

// problem:
// result: 99.88%
//
ListNode* intersectionOfTwoLinkedList(ListNode* headA, ListNode* headB);
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%MEDIUM%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// problem: 369
// result: 100ms
// add to linked list represented number --> 1->2->3  goes to 1->2->4
ListNode* plusOne(ListNode* head);

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+Binary Trees=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%EASY%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+Sort and Searching+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%EASY%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// problem: 88
// result: 67.41% 7ms
void mergeVectors(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n);
void mergeVectorsV2(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n);
void mergeVectorsV3(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n);

// problem: 278 
// result: 26.47% 3ms 
int firstBadVerison(int n);
bool isBadVersion(int);
void initVersionVect(int badVersion, int numVersions);

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%MEDIUM%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// problem: 692
// result: 9.16% 24ms
// result: 100% 8ms (V2)
// Given a non-empty list of words, return the k most frequent elements.
// Your answer should be sorted by frequency from highest to lowest
std::vector<std::string> topKFrequent(std::vector<std::string>& words, int k);
std::vector<std::string> topKFrequentV2(const std::vector<std::string>& words, int k);


// problem: 347
// result: 98.68 16ms
// Given a non-empty array of integers, return the k most frequent elements.
std::vector<int> topFrequentKIntegers(std::vector<int>& nums, int k);

// problem: 451
// result: 98.96% 12ms
// Given a string, sort it in decreasing order based on the frequency of characters.
std::string frequencySort(std::string s);

// problem: 33
// result: 99.98% 4ms
// Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand
// (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2])
// You are given a target value to search. If found in the array return its index, otherwise return -1
// You may assume no duplicate exists in the array
// Your algorithm's runtime complexity must be in the order of O(log n)
int searchSortedRotatedArray(std::vector<int>& nums, int target);

// problem: 81
// result: 99.93% 4ms
// Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
//(i.e., [0,0,1,2,2,5,6] might become [2,5,6,0,0,1,2]).
//You are given a target value to search. If found in the array return true, otherwise return false.
bool searchSortedRotatedArrayII(std::vector<int>& nums, int target);
bool searchSortedRotatedArrayIIV2(std::vector<int> &nums, int target);

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+Dynamic Programming=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
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

//+==+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+Design=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%EASY%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// problem #155
// result: 79.71% 29 ms
/*
 * arr[(i-1)/2] --> returns parent node
 * arr[(2i)+1] --> returns left child node
 * arr[(2i)+2] --> returns right child node
 *
 * ["MinStack","push","push","push","push","pop","getMin","pop","getMin","pop","getMin"]
[[],[512],[-1024],[-1024],[512],[],[],[],[],[],[]]
 * */
class MinStack {
public:
    MinStack(): _size(0){};
    void push(int x);
    void pop();
    int top();
    int getMin();
private:
    inline size_t parent(size_t i) const { return (i-1)/2; }
    inline size_t left(size_t i) const { return (2*i)+1; }
    inline size_t right(size_t i) const { return (2*i)+2; }
    void deleteNode(size_t i);
    void heapify(size_t i);
    void decreaseNode(size_t i, int val);
    size_t _size;
    std::stack<int> _stk;
    std::vector<int> _data;
};

// second version (much faster uses two stacks instead)
class MinStackV2 {
public:
    /** initialize your data structure here. */
    MinStackV2()=default;

    void push(int x) {
        stack1.push(x);
        if(stack2.empty())
            stack2.push(x);
        else {
            if(stack2.top() > x)
                stack2.push(x);
            else
                stack2.push(stack2.top());
        }
    }

    void pop() {
        if(!stack1.empty() && !stack2.empty()){
            stack1.pop();
            stack2.pop();
        }
    }

    int top() {
        if(!stack1.empty()) return stack1.top();
        else return -1;
    }

    int getMin() {
        if(!stack2.empty()) return stack2.top();
        else return -1;
    }
private:
    std::stack<int> stack1;
    std::stack<int> stack2;
};

/*
Write a program that outputs the string representation of numbers from 1 to n.
But for multiples of three it should output “Fizz” instead of the number and for the multiples
 of five output “Buzz”. For numbers which are multiples of both three and five output “FizzBuzz”.
*/
std::vector<std::string> fizzBuzz(const int& n);





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

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=Other=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
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

bool operator > ( envelope& env1, envelope& env2 );

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

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+Helpers=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
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
ListNode* _revList(ListNode* head);
TreeNode* _insertData(int l, int r, std::vector<int>& data);

// check if string is a valid open and closed parenth combinations () (()) ()() etc etc
bool isVaildParenth(const std::string& str);
#endif //ALGOS_SHORT_ALGOS_H
