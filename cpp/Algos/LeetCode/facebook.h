#ifndef DATASTRUCTS_N_ALGOS_FACEBOOK_H
#define DATASTRUCTS_N_ALGOS_FACEBOOK_H
#include <vector>
#include <string>

// =-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- Arrays and Strings =-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/*
 * move zeros to end of the array
 */
// result: 100%
void moveZeroes(std::vector<int>& nums);

/*
	Given two binary strings, return their sum (also a binary string).
	The input strings are both non-empty and contains only characters 1 or 0.

	Example 1:
	Input: a = "11", b = "1"
	Output: "100"

	Example 2:
	Input: a = "1010", b = "1011"
	Output: "10101"
 */
// result: V1(100%)
std::string addBinary(std::string& a, std::string& b);

/*
    Given two arrays, write a function to compute their intersection.

    Example 1:
    Input: nums1 = [1,2,2,1], nums2 = [2,2]
    Output: [2,2]

    Example 2:
    Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
    Output: [4,9]
    Note:

    Each element in the result should appear as many times as it shows in both arrays.
    The result can be in any order.

    Follow up:
    1. What if the given array is already sorted? How would you optimize your algorithm?
    A: we take a two pointer approach.
        - if we get a match we add that element to the result and ++ both indices
        - if i is less than j the we move i up and not j
        - if nums[i] > nums[j] j continues to move and i remains stationary
        ex:
        nums1: 1 2 3 3 4 5  <-- i
        nums2: 1 2 2 2 3 3  <-- j
        it1: i=0 j=0 ==> i=1 j=1 [1]
        it2: i=1 j=1 ==> i=2 j=2 [1 2]
        it3: i=2 j=2 ==> i=2 j=3 [1 2]
        it4: i=2 j=3 ==> i=2 j=4 [1 2]
        it5: i=2 j=4 ==> i=3 j=5 [1 2 3]
        it6: i=3 j=5 ==> i=4 j=6 [1 2 3 3]
        done b/c j > nums.size()-1


    func intersect(_ nums1: [Int], _ nums2: [Int]) -> [Int] {
    var nums1 = nums1.sorted()
    var nums2 = nums2.sorted()
    var res = [Int]()
    var i = 0, j = 0

    while i < nums1.count && j < nums2.count {
        if nums1[i] == nums2[j] {
            res.append(nums1[i])
            i += 1 ; j += 1
        } else if nums1[i] < nums2[j] {
            i += 1
        } else {
            j += 1
        }
    }
    return res
}

    2. What if nums1's size is small compared to nums2's size? Which algorithm is better?
    A: ??

    3. What if elements of nums2 are stored on disk, and the memory is limited such that you
            cannot load all elements into the memory at once?
        A: If only nums2 cannot fit in memory, put all elements of nums1 into a HashMap, read chunks of
            array that fit into the memory, and record the intersections.

            If both nums1 and nums2 are so huge that neither fit into the memory, sort them individually
            (external sort), then read 2 elements from each array at a time in memory, record intersections.

    result: V1(100%)
 */
// result: V1(100%)
std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2);



/*
Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0?
 Find all unique triplets in the array which gives the sum of zero.
Note:
The solution set must not contain duplicate triplets.

Example:
Given array nums = [-1, 0, 1, 2, -1, -4],
A solution set is:
[
[-1, 0, 1],
[-1, -1, 2]
]
 */
// result: 54% 124ms
std::vector<std::vector<int>> threeSum(std::vector<int>& nums);

/*
 * check if a string is a valid palindrome or not
 */
// result: 100% 4ms
bool isPalindrome(std::string& s);

/*EASY
 * Valid Palindrome II
 * Given a non-empty string s, you may delete at most one character.
 * Judge whether you can make it a palindrome.
 *
 * Input: "abca"
 *   Output: True
 *   Explanation: You could delete the character 'c'
 * Note: The string will only contain lowercase characters a-z. The maximum length of the string is 50000.
 */
// result: 48.57% 88ms
bool validPalindrome(std::string& s);
// result: 98.69% 76ms (from discussion)
bool validPalindromeV2(std::string& s);

/*HARD
 * Validate if a given string can be interpreted as a decimal number
 *
 * some rules:
 * Note: It is intended for the problem statement to be ambiguous.
 * You should gather all requirements up front before implementing one. However,
 * here is a list of characters that can be in a valid decimal number:
    Numbers 0-9
    Exponent - "e"
    Positive/negative sign - "+"/"-"
    Decimal point - "."
 */
// result: 47.73% 20ms
bool isNumber(std::string s);

// best result: 97.65% 16ms (from discussion)
bool isNumberV2(std::string s);

/*
 * Given an array of n positive integers and a positive integer s, find the minimal length of a
 * contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.

Example:
    Input: s = 7, nums = [2,3,1,2,4,3]
    Output: 2
    Explanation: the subarray [4,3] has the minimal length under the problem constraint.

Follow up:
    If you have figured out the O(n) solution,
    try coding another solution of which the time complexity is O(n log n)
 */
// result: 4.83% 196ms
int minSubArrayLen(int s, std::vector<int>& nums);
int minSubArrayLenV2(int s, std::vector<int>& nums);

// =-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= Linked Lists =-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= Trees and Graphs =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= BackTracking =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- Sorting and Searching =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Dynamic Programming =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- Design =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- Others =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


#endif //DATASTRUCTS_N_ALGOS_FACEBOOK_H
