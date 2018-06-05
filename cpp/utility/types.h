
#ifndef CPP_TYPES_H
#define CPP_TYPES_H
#include<utility>

#define ASCII_ZERO 48

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

typedef unsigned int uint;
static const int LINE_LIMIT = 20;
typedef std::pair<int, int> envelope;

#endif //CPP_TYPES_H
