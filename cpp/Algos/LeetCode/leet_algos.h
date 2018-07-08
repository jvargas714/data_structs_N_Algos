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

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+misc=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// Problem #59
std::vector<int> count_bits( int num );

// Problem #168 100% 0ms 
std::string excel_column_title( int n );

bool operator > ( envelope& env1, envelope& env2 );




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
// Given two arrays, write a function to compute their intersection.
// each element in the result must be unique, result can be in any order
std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2);

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

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+strings=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%EASY%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// problem #344
std::string reverseString(std::string);

// problem #387
// result: 99.22% 24ms (v4 : original solution
// Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.
int firstUniqChar(std::string s);
int firstUniqCharV2(std::string s);
int firstUniqCharV3(std::string s);
int firstUniqCharV4(std::string s);


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


//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+Binary Trees=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%EASY%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// problem: 
// result: 8.81% 11ms 
int maxDepth(TreeNode*);
int maxDepthV2(TreeNode* root);

// problem: 98 
// result: 99.55% 10ms 
bool isValidBST(TreeNode*);

// problem: 
// result:
// descr:  
bool isSymmetric(TreeNode*);

// problem: 102
// result: 27.17% 
// descr: 
VectOfVect levelOrder(TreeNode* root);
VectOfVect levelOrderV2(TreeNode* root);

// problem 108
// result: 26.78% 18ms
// descr: Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
// a height balanced tree is defined as a binary tree in which the depth of the two subtrees of every node never 
// differ by more than 1.
TreeNode* sortedArrayToBST(std::vector<int>& data);





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
// result:
// Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand
// (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2])
// You are given a target value to search. If found in the array return its index, otherwise return -1
// You may assume no duplicate exists in the array
// Your algorithm's runtime complexity must be in the order of O(log n)
int searchSortedRotatedArray(std::vector<int>& nums, int target);
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

// #problem: 198
// result: 14.42% 4ms
int rob(std::vector<int>& nums);
int robV2(std::vector<int>& nums);





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
// Given a string containing just the characters
// '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
// rules: 1. Open brackets must be closed by the same type of brackets.
//		  2. Open brackets must be closed in the correct order.
bool isValidParenthesisStr(std::string&);

// problem: 268
// result: 91.26% 24ms
// Given an array containing n distinct numbers taken
// from 0, 1, 2, ..., n, find the one that is missing from the array
int missingNumber(std::vector<int>& nums);





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
#endif //ALGOS_SHORT_ALGOS_H
