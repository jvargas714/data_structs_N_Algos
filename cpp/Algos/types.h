
#ifndef CPP_TYPES_H
#define CPP_TYPES_H
#include<utility>

struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x) : val(x), next(nullptr) {}
};

typedef unsigned int uint;
static const int LINE_LIMIT = 30;
typedef std::pair<int, int> envelope;

#endif //CPP_TYPES_H
