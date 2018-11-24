
#ifndef CPP_TYPES_H
#define CPP_TYPES_H
#include<utility>
#include <iostream>

#define ASCII_ZERO 48
#define ERROR -1

struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x) : val(x), next(nullptr) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};
//std::ostream& operator<<(std::ostream& os, const Interval& iv) {
//    os << "(" << iv.start << "," << iv.end << ")";
//    return os;
//}


typedef unsigned int uint;
static const int LINE_LIMIT = 20;
typedef std::pair<int, int> envelope;

#endif //CPP_TYPES_H
