
#ifndef DATASTRUCTS_N_ALGOS_LINKEDLIST_PROBLEMS_H
#define DATASTRUCTS_N_ALGOS_LINKEDLIST_PROBLEMS_H
#include "types.h"

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

#endif //DATASTRUCTS_N_ALGOS_LINKEDLIST_PROBLEMS_H
