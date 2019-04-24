#ifndef DATASTRUCTS_N_ALGOS_BINARY_TREE_PROBLEMS_H
#define DATASTRUCTS_N_ALGOS_BINARY_TREE_PROBLEMS_H
#include <vector>
#include <string>
#include <utility>
#include "types.h"

// typedefs
typedef std::vector<std::vector<int>> VectOfVect;

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%EASY%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// problem:
// result: 8.81% 11ms
// result: 100% 4ms (V3)
int maxDepth(TreeNode*);
int maxDepthV2(TreeNode* root);
int maxDepthV3(TreeNode *root);

// problem: 98
// result: 99.55% 10ms
bool isValidBST(TreeNode*);

// problem:
// result:
// descr:
bool isSymmetric(TreeNode*);

// problem: 102
// result: 27.17% (v1) 99.88% 4ms (V3)
// descr: Given a binary tree, return the level order traversal
// of its nodes' values (ie, from left to right, level by level).
VectOfVect levelOrder(TreeNode* root);
VectOfVect levelOrderV2(TreeNode* root);
VectOfVect levelOrderV3(TreeNode* root);

// problem 108
// result: 26.78% 18ms
// descr: Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
// a height balanced tree is defined as a binary tree in which the depth of the two subtrees of every node never
// differ by more than 1.
TreeNode* sortedArrayToBST(std::vector<int>& data);

// problem 103
// result: 100% 0ms
// Given a binary tree, return the zigzag level order traversal of its nodes' values.
// (ie, from left to right, then right to left for the next level and alternate between).
VectOfVect zigzagLevelOrder(TreeNode* root);

// problem: 100
// result: 100% 0ms
// return whether trees are the same
// TODO :: get implementation from website
bool isSameTree(TreeNode* p, TreeNode* q);

// problem: 669
// result: 97.28 % 12ms
//
TreeNode* trimBST(TreeNode* root, int L, int R);

// problem:
// result:
// Given a binary tree, find the length of the longest path where each node in the path has the same value
// This path may or may not pass through the root
// Note: The length of path between two nodes is represented by the number of edges between them
// google
int longestUnivaluePath(TreeNode* root);

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%MEDIUM%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// problem:
// result:
//
std::vector<int> inorderTraversal(TreeNode* root);

// problem: 399
// result:
// Equations are given in the format A / B = k, where A and B are variables represented as strings,
// and k is a real number (floating point number). Given some queries, return the answers.
// If the answer does not exist, return -1.0.
//
//Example:
//Given a / b = 2.0, b / c = 3.0.
//queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? .
//return [6.0, 0.5, -1.0, 1.0, -1.0 ].
//
//The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries ,
// where equations.size() == values.size(), and the values are positive. This represents the equations.
// Return vector<double>
std::vector<double> calcEquation(std::vector<std::pair<std::string, std::string>> equations,
                                    std::vector<double>& values,
                                    std::vector<std::pair<std::string,
                                    std::string>> queries);

/*
 *
 * Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.
 *
 * Note:
 * You may assume k is always valid, 1 ≤ k ≤ BST's total elements.
 */
int kthSmallest(TreeNode* root, int k);
int kthSmallestV2(TreeNode* root, int k);

#endif //DATASTRUCTS_N_ALGOS_BINARY_TREE_PROBLEMS_H
