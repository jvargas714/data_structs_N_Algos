#ifndef DATASTRUCTS_N_ALGOS_FACEBOOK_H
#define DATASTRUCTS_N_ALGOS_FACEBOOK_H
#include <vector>
#include <string>
#include "utility.h"

// =-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- Structs =-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
class Node {
public:
	int val;
	Node* left;
	Node* right;

	Node() {}

	Node(int _val, Node* _left, Node* _right) {
		val = _val;
		left = _left;
		right = _right;
	}
};

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
 * Min size SubArray
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
// Runtime: 8 ms, faster than 98.32% (from discussion)
int minSubArrayLenV3(int s, std::vector<int>& nums);

/*
 * Maximum Size Subarray Sum Equals k
 * Given an array nums and a target value k, find the maximum length of a subarray that sums to k.
 * If there isn't one, return 0 instead.

Note:
The sum of the entire nums array is guaranteed to fit within the 32-bit signed integer range.

Example 1:
Input: nums = [1, -1, 5, -2, 3], k = 3
Output: 4
Explanation: The subarray [1, -1, 5, -2] sums to 3 and is the longest.

 Example 2:
Input: nums = [-2, -1, 2, 1], k = 1
Output: 2

Explanation: The subarray [-1, 2] sums to 1 and is the longest.

 Follow Up:
    Can you do it in O(n) time?
 */
// Runtime: 20 ms, faster than 98.30%
int maxSubArrayLen(std::vector<int>& nums, int k);
// Time limit exceeded
int maxSubArrayLenV2(std::vector<int>& nums, int k);

/*
  Valid Parentheses
  Given a string containing just the characters '(', ')', '{', '}', '[' and ']', 
  determine if the input string is valid.

	An input string is valid if:
	Open brackets must be closed by the same type of brackets.
	Open brackets must be closed in the correct order.
	Note that an empty string is also considered valid.
 */
// result: 100% 0ms
bool isValid(std::string s);

/*
 * Trapping Water
 *   Given n non-negative integers representing an elevation map where the width of each bar is 1,
 *   compute how much water it is able to trap after raining.
 */
int trap(std::vector<int>* rain);

// =-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= Linked Lists =-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
/*
	Input: 1->2->3->4->5->NULL
	Output: 5->4->3->2->1->NULL
	-- do this both iteratively and recursively
 */
ListNode* reverseList(ListNode* head);
ListNode* reverseListV2(ListNode* head);
ListNode* reverseListV3(ListNode* head);

/*
 * You are given two non-empty linked lists representing two non-negative integers.
 * The digits are stored in reverse order and each of their nodes contain a single digit.
 * Add the two numbers and return it as a linked list.
 * You may assume the two numbers do not contain any leading zero, except the number 0 itself.
 *
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 * Explanation: 342 + 465 = 807.
 */
// Your runtime beats 98.57 % of cpp submissions, 48ms
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);

/*
 * Given a linked list, remove the n-th node from the end of list and return its head.
 */
// result: 100% 4ms
ListNode* removeNthFromEnd(ListNode* head, int n);

/*
 * Write a program to find the node at which the intersection of two singly linked lists begins.
 *
 */
// result: 87.53%, 24ms
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB);

/*
    Given a binary tree, flatten it to a linked list in-place
*/
// result: 100% 4ms
void flatten(TreeNode* root);

/*
 * Given a linked list, determine if it has a cycle in it.

To represent a cycle in the given linked list, we use an integer pos which represents the position
 (0-indexed) in the linked list where tail connects to. If pos is -1, then there is no cycle in the linked list.
 */
bool hasCycle(ListNode *head);


// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= Trees and Graphs =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
/*
 * Given two binary trees, write a function to check if they are the same or not.
	Two binary trees are considered the same if they are structurally
    identical and the nodes have the same value.
 */
bool isSameTree(TreeNode* p, TreeNode* q);

/*
    Given a binary tree, determine if it is a valid binary search tree (BST).
    Assume a BST is defined as follows:
        The left subtree of a node contains only nodes with keys less than the node's key.
        The right subtree of a node contains only nodes with keys greater than the node's key.
        Both the left and right subtrees must also be binary search trees.
*/
// result: 100ms 4ms
bool isValidBST(TreeNode* root);

/*
	Given a binary tree, return all root-to-leaf paths.
	Note: A leaf is a node with no children.
	Example:
	Input:
	   1
	 /   \
	2     3
	 \
	  5
	Output: ["1->2->5", "1->3"]
	Explanation: All root-to-leaf paths are: 1->2->5, 1->3
 */
// 99.32% 4ms
std::vector<std::string> binaryTreePaths(TreeNode* root);

/*
	Given a binary tree, you need to compute the length of the diameter of the tree. The diameter of a binary tree
	is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

	Example:
	Given a binary tree
	          1
	         / \
	        2   3
	       / \
	      4   5
	Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].
	Note: The length of path between two nodes is represented by the number of edges between them.
 */
// result: %97.17 4ms
// todo :: optimize solution
int diameterOfBinaryTree(TreeNode* root);

/*
	 Given a binary tree, return the vertical order traversal of its nodes' values.
	 (ie, from top to bottom, column by column).

	If two nodes are in the same row and column, the order should be from left to right
	 Input: [3,9,8,4,0,1,7,null,null,null,2,5] (0's right child is 2 and 1's left child is 5)

	     3
	    /\
	   /  \
	   9   8
	  /\  /\
	 /  \/  \
	 4  01   7
	    /\
	   /  \
	   5   2

	Output:

	[
	  [4],
	  [9,5],
	  [3,0,1],
	  [8,2],
	  [7]
	]
 */
// result: %99.24
std::vector<std::vector<int>> verticalOrder(TreeNode* root);

/*
 * Given preorder and inorder traversal of a tree, construct the binary tree.

	Note:
	You may assume that duplicates do not exist in the tree.

	For example, given

	preorder = [3,9,20,15,7]
	inorder = [9,3,15,20,7]
	Return the following binary tree:

	    3
	   / \
	  9  20
	    /  \
	   15   7
 */
// 20% 32ms
TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder);
// 44.94% 12ms
TreeNode* buildTreeV2(std::vector<int>& preorder, std::vector<int>& inorder);

/*
 * Convert a BST to a sorted circular doubly-linked list in-place. Think of the left and right
 * pointers as synonymous to the previous and next pointers in a doubly-linked list.

	We want to transform this BST into a circular doubly linked list. Each node in a doubly linked list has a
    predecessor and successor. For a circular doubly linked list, the predecessor of the first element is the
    last element, and the successor of the last element is the first element.

	 Specifically, we want to do the transformation in place. After the transformation, the left pointer of the tree
	 node should point to its predecessor, and the right pointer should point to its successor. We should return the
	 pointer to the first element of the linked list.
 */
Node* treeToDoublyList(Node* root);
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= BackTracking =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- Sorting and Searching =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Dynamic Programming =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- Design =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- Others =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


#endif //DATASTRUCTS_N_ALGOS_FACEBOOK_H
