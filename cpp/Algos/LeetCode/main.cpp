#include <iostream>
#include <types.h>
#include "utility.h"
#include "leet_algos.h"

int main()
{
    ListNode* node = fillListNode( {1, 2, 3, 4, 5, 6, 7, 8, 9, 10} );
    swapPairs(node);
    ListNode* tmp = node;
    int cnt = 0;
    while(tmp) {
        std::cout << tmp->val << " ";
        cnt++;
        tmp = tmp->next;
    }
    std::cout << std::endl;
    deallocateLList(node);
    return 0;
}
