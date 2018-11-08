#include <stack>
#include <vector>
#include <iostream>
#include "linkedlist_problems.h"

/*
 * swap every two nodes, must only swap nodes and not modify them
 * return pointer to the head
 * For example,
 * Given 1->2->3->4, you should return the list as 2->1->4->3.
 #todo
 */
ListNode* swapPairs(ListNode* head) {
    ListNode* tmp = head;
    ListNode* nxt;
    while(tmp) {
        nxt = tmp->next;
        tmp->next = tmp;
        tmp = nxt;
    }
    return nullptr;
}

// 1->2->3->4->5
// say node is 3 we should get 1->2->4->5 after deletion
void deleteNode(ListNode* node) {
    if (!node||!node->next) return;
    ListNode* tmp = node->next;
    node->val = tmp->val;
    node->next = tmp->next;
}

// get this in one pass
// 1->2->3->4->5
// n is assumed to be valid
ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (!head) return nullptr;
    std::vector<ListNode*> ptrs;
    ListNode* tmp = head;
    while(tmp) {
        ptrs.push_back(tmp);
        tmp = tmp->next;
    }

    ListNode* toBeRem = ptrs[ptrs.size() - n]; // node to be removed

    // remove node from list
    if (n==ptrs.size()) {  // removing head
        std::cout <<"removing head"<<std::endl;
        head->val = head->next->val;
        head->next = head->next->next;
    } else { // all others
        std::cout << "all others: " << std::endl;
        tmp = toBeRem->next;
        ptrs[ptrs.size()-(n+1)]->next = tmp;
    }
    return head;
}

ListNode* removeNthFromEndV2(ListNode* head, int n) {
    ListNode *p = head;
    ListNode *pre = head;

    // finds node pointer to remove
    while (n > 0) {
        p = p->next;
        n--;
    }

    // if we reached end of list that means we are removing the head from the list so return its next element
    if (p == nullptr) {
        return head->next;
    }

    // from this element to the end we just copy the next pointer to eliminate the one to be removed
    // 1->2->3->(4)->5->6
    // 1->2->3->5->6   <<< p = p->next
    while (p->next != nullptr) {
        p = p->next;
        pre = pre->next;
    }
    // pre in the while loop started at the head, it ends as the element before the one to be removed
    // when the loop ends the next element must point to the nexe->next element ie. 3->5 (must point to 5)
    pre->next = pre->next->next;
    return head;
}

void _reverseRecursive(ListNode* curr, ListNode* prev, ListNode** head) {
    // if last node set reference to LL head ptr to the tail node of the original LL
    if (!curr->next) {
        *head = curr;
        curr->next = prev;
        return;
    }
    ListNode *next = curr->next;
    curr->next = prev;
    _reverseRecursive(next, curr, head);
}

void _reverseIterative(ListNode** head) {
    ListNode* curr = *head;
    ListNode* prev = nullptr;
    ListNode* next = nullptr;
    while(curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
}

// recursive sol
ListNode* reverseList(ListNode* head) {
    if (!head) return nullptr;
    _reverseRecursive(head, nullptr, &head);
    return head;
}

// iterative solution
ListNode* reverseListV2(ListNode* head) {
    _reverseIterative(&head);
    return head;
}

// Input: 1->2->4, 1->3->4
// Output: 1->1->2->3->4->4
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    ListNode* tmp1 = l1;
    ListNode* tmp2 = l2;
    ListNode* result = nullptr;
    ListNode* tmp3 = nullptr;

    while ((tmp1 != nullptr)||(tmp2 != nullptr)) {
        if (tmp1&&tmp2) {
            if ((tmp1->val < tmp2->val)) {
                if (!result) {
                    result = new ListNode(tmp1->val);
                    tmp3 = result;
                } else {
                    tmp3->next = new ListNode(tmp1->val);
                    tmp3 = tmp3->next;
                }
                tmp1 = tmp1->next;
            } else if ((tmp2->val < tmp1->val)) {
                if (!result) {
                    result = new ListNode(tmp2->val);
                    tmp3 = result;
                } else {
                    tmp3->next = new ListNode(tmp2->val);
                    tmp3 = tmp3->next;
                }
                tmp2 = tmp2->next;
            } else {   // both are equal
                if (!result) {
                    result = new ListNode(tmp1->val);
                    result->next = new ListNode(tmp2->val);
                    tmp3 = result->next;
                } else {
                    tmp3->next = new ListNode(tmp1->val);
                    tmp3->next->next = new ListNode(tmp2->val);
                    tmp3 = tmp3->next->next;
                }
                tmp1 = tmp1->next;
                tmp2 = tmp2->next;
            }
        } else if (tmp1) {      // l1
            tmp3->next = new ListNode(tmp1->val);
            tmp3 = tmp3->next;
            tmp1 = tmp1->next;
        } else {                // l2
            tmp3->next = new ListNode(tmp2->val);
            tmp3 = tmp3->next;
            tmp2 = tmp2->next;
        }
    }
    return result;
}

ListNode* mergeTwoListsV2(ListNode* l1, ListNode* l2) {

    auto* dummy  =  new ListNode(-1);
    ListNode* cur = dummy;

    while(l1!=nullptr && l2!=nullptr){
        if(l1->val<l2->val) {
            cur->next = l1;
            l1 = l1->next;
        } else {
            cur->next = l2;
            l2 = l2->next;
        }
        cur = cur->next;
    }
    cur->next = l1?l1:l2;
    return dummy->next;  // << this leaks mem
}

ListNode* _revList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    ListNode* next = nullptr;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
    return head;
}
// try to get in O(n)
bool isPalindrome(ListNode* head) {
    if (!head||!head->next) return true;
    ListNode* slow = head;
    ListNode* fast = head;
    ListNode* midNode = nullptr;
    int cnt = 0;

    // find center node using two pointers
    while (fast&&fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        cnt++;
    }
    midNode = slow;
    // reverse elements from center to end
    ListNode* revList = _revList(slow->next);
    midNode->next = revList;
    fast = head;
    while(revList) {
        if (revList->val != fast->val)
            return false;
        revList = revList->next;
        fast = fast->next;
    }
    return (fast->val == midNode->val);
}

bool hasCycle(ListNode *head) {
    if (!head||!head->next) return false;
    ListNode* fast = head;
    ListNode* slow = head;
    while (fast&&slow&&fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if ((fast == slow) && (fast)) {
            return true;
        }
    }
    return false;
}

/*
    Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
    Output: 7 -> 0 -> 8
    Explanation: 342 + 465 = 807.
 */
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int sum;
    int carry = 0;
    ListNode* result = nullptr;
    ListNode* resTmp = nullptr;

    // initialize first element of the result
    sum = l1->val + l2->val + carry;
    if (sum<10) {
        resTmp = new ListNode(sum);
        carry = 0;
    } else {  // carry ops
        resTmp = new ListNode(sum - 10);
        carry = 1;
    }
    l1 = l1->next;
    l2 = l2->next;
    result = resTmp;
    while (l1||l2) {
        if (l1 && l2) {
            sum = l1->val + l2->val + carry;
            l1 = l1->next;
            l2 = l2->next;
        }
        else if (l1 && !l2) {
            sum = l1->val + carry;
            l1 = l1->next;
        }
        else {
            sum = l2->val + carry;
            l2 = l2->next;
        }

        if (sum<10) {
            resTmp->next = new ListNode(sum);
            carry = 0;
        } else {  // carry ops
            resTmp->next = new ListNode(sum - 10);
            carry = 1;
        }
        resTmp = resTmp->next;
    }
    if (carry==1)
        resTmp->next = new ListNode(carry);
    return result;}

ListNode *addTwoNumbersV2(ListNode *l1, ListNode *l2) {
    int temp=l1->val +l2->val, overhead=temp/10, l1_valid, l2_valid;
    auto result= new ListNode(temp%10);
    ListNode* result_cursor= result;

    ListNode* l1_list_block=l1; //copy for safety
    ListNode* l2_list_block=l2;

    while(l1_list_block->next !=NULL || l2_list_block->next !=NULL || overhead){
        (l1_list_block->next)?(l1_list_block=l1_list_block->next,l1_valid=1):(l1_valid=0);
        (l2_list_block->next)?(l2_list_block=l2_list_block->next,l2_valid=1):(l2_valid=0);
        temp =(l1_list_block->val)*l1_valid +(l2_list_block->val)*l2_valid +overhead;
        overhead =temp/10;
        ListNode* tempNode= new ListNode(temp%10);
        result_cursor->next = tempNode;
        result_cursor = result_cursor->next;
    }

    return result;
}

ListNode* intersectionOfTwoLinkedList(ListNode* headA, ListNode* headB) {
    if (!headA||!headB) return nullptr;
    ListNode* tmpa = headA;
    ListNode* tmpb = headB;
    int cnta = 0, cntb = 0, cnt = 0;

    // find lengths, lists must be same distance from common point first
    while (tmpa) {
        cnta++;
        tmpa = tmpa->next;
    }
    while (tmpb) {
        cntb++;
        tmpb = tmpb->next;
    }

    // reset ptrs
    tmpa = headA;
    tmpb = headB;

    // set distance to common node to be the same
    if (cnta > cntb) {
        while (cnt < (cnta - cntb)) {
            tmpa = tmpa->next;
            cnt++;
        }
    } else if (cntb > cnta) {
        while (cnt < (cntb - cnta)) {
            tmpb = tmpb->next;
            cnt++;
        }
    }

    // find common node
    while (tmpa && tmpb) {
        if (tmpa == tmpb) return tmpa;
        tmpa = tmpa->next;
        tmpb = tmpb->next;
    }
    return nullptr;
}

ListNode* plusOne(ListNode* head) {
    std::stack<ListNode *> nodeStk;
    if (!head) return nullptr;

    // reference to head
    ListNode *node = head;

    // find last node, build stack incase of carry operation
    while (node->next) {
        node = node->next;
        nodeStk.push(node);
    }

    // single digit number
    if (nodeStk.empty()) {
        head->val++;
        // carry MSD
        if (head->val == 10) {
            head->val = 0;
            ListNode *tmp = new ListNode(1);
            tmp->next = head;
            return tmp;
        } else
            return head;
    }

    // already have ptr to last non-null node
    nodeStk.pop();

    // node is pointing to the tail in the list
    node->val++;

    // check for carry operation
    if (node->val == 10) {
        // perform carry operation
        node->val = 0;
        while (!nodeStk.empty()) {
            ListNode *tmp = nodeStk.top();
            tmp->val++;
            if (tmp->val == 10) {
                tmp->val = 0;
                nodeStk.pop();
            } else
                return head;
        }
        head->val++;

        // carry MSD
        if (head->val == 10) {
            head->val = 0;
            ListNode *tmp = new ListNode(1);
            tmp->next = head;
            return tmp;
        }
    }
    return head;
}
