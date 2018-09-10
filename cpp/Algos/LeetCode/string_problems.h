#ifndef DATASTRUCTS_N_ALGOS_STRING_PROBLEMS_H
#define DATASTRUCTS_N_ALGOS_STRING_PROBLEMS_H
#include <string>

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

// problem: 5
// result: 7.76% 584ms (V1 brute force)
// result: 77.72% 16ms
//Longest Palindromic Substring
std::string longestPalindrome(std::string& s);
std::string longestPalindromeV2(std::string& s);


// problem:
// result:
// todo :: implement me
std::string longestCommonSubString(std::string& str1, std::string& str2);


// problem: 686
// result: 85.99% 8ms
/*
Given two strings A and B, find the minimum number of times A has to be
repeated such that B is a substring of it. If no such solution, return -1.
For example, with A = "abcd" and B = "cdabcdab".
Return 3, because by repeating A three times (“abcdabcdabcd”),
B is a substring of it; and B is not a substring of A repeated two times ("abcdabcd").
Note:
The length of A and B will be between 1 and 10000.
 */
int repeatedStringMatch(std::string A, std::string B);

// problem: 388
// result: 0ms 100%
// The string "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext" represents:
// dir
//     subdir1
//        file1.ext
//        subsubdir1
//     subdir2
//        subsubdir2
//           file2.ext
// The directory dir contains two sub-directories subdir1 and subdir2.
// subdir1 contains a file file1.ext and an empty second-level sub-directory subsubdir1.
// subdir2 contains a second-level sub-directory subsubdir2 containing a file file2.ext.
//We are interested in finding the longest (number of characters) absolute path to a file within our file system.
// For example, in the second example above, the longest absolute path is "dir/subdir2/subsubdir2/file2.ext",
// and its length is 32 (not including the double quotes).
//Given a string representing the file system in the above format, return the length of
// the longest absolute path to file in the abstracted file system.
// length is determined by number of characters and not how deep the file goes
// If there is no file in the system, return 0.
int lengthLongestPath(const std::string&);

// problem: 482
// result: 98.42% 8ms
// You are given a license key represented as a string S which consists only alphanumeric character and dashes.
// The string is separated into N+1 groups by N dashes.
//Given a number K, we would want to reformat the strings such that each group contains exactly K characters,
// except for the first group which could be shorter than K, but still must contain at least one character.
// Furthermore, there must be a dash inserted between two groups and all lowercase letters
// should be converted to uppercase.
//Given a non-empty string S and a number K, format the string according to the rules described above.
std::string licenseKeyFormatting(std::string S, int K);



#endif  // DATASTRUCTS_N_ALGOS_STRING_PROBLEMS_H
