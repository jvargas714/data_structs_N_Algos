#ifndef DATASTRUCTS_N_ALGOS_SORT_SEARCH_PROBLEMS_H
#define DATASTRUCTS_N_ALGOS_SORT_SEARCH_PROBLEMS_H
#include <vector>
#include <string>
#include "types.h"

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Structs%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
struct MyPairCompGreater {
    bool operator()(std::pair<std::string, int>& p1, std::pair<std::string, int>& p2) {
        if (p1.second != p2.second)
            return p1.second > p2.second;
        return p1.first < p2.first;
    }
};

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

// problem: 253 -- Meeting Rooms II --
// result:
// Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei),
// find the minimum number of conference rooms required.
//
// Example 1:
// Input: [[0, 30],[5, 10],[15, 20]]
// Output: 2
//
// Example 2:
// Input: [[7,10],[2,4]]
// Output: 1
int minMeetingRooms(std::vector<Interval>& intervals);
int minMeetingRoomsV2(std::vector<Interval>& intervals);

#endif //DATASTRUCTS_N_ALGOS_SORT_SEARCH_PROBLEMS_H
