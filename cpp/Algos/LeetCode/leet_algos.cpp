#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstring>
#include <deque>            // std::deque
#include <iomanip>
#include <map>
#include <numeric>          // std::accumulate
#include <queue>            // std::priority_queue
#include <sstream>          // string stream
#include <unordered_map>    // std::unordered_map
#include <set>

#include "leet_algos.h"
#include "utility.h"

// globals
std::vector<bool> g_versions;
int g_nVersions;
int g_badVersion;
static int cnt = 0;

/* Problem: #168 */
std::string excel_column_title( int n ) {
    std::string res;
    while ( true ) {
        int mod_res = n % 26;

        if (n <= 26) {
            res += (char)(n + 64);
            break;
        }
        else if( mod_res == 0 ) {
            res += 'Z';
            n = (n / 26) - 1;
            continue;
        }
        else {
            res += (char)(mod_res + 64);
        }
        n /= 26;
    }
    std::reverse(res.begin(), res.end());
    return res;
}

int _climbStairs( int i, int n, std::vector<int>& memo ) {
    if (i > n) return 0;
    if (i == n) return 1;
    if (memo[i] > 0) return memo[i];
    memo[i] = _climbStairs(i+1, n, memo) + _climbStairs(i+2, n, memo);
    return memo[i];
}

// recursive solution using memoization 
int climbStairs(int n) {
    std::vector<int> memo(n+1, 0);
    return _climbStairs(0, n, memo);
}

// iterative solution (faster) Tabulated Version 
int climbStairsV2(int n) {
    std::vector<int> ways(n);
    ways[0] = 1;
    ways[1] = 2;
    for(int i = 2; i < n; i++)
        ways[i] = ways[i-1] + ways[i-2];
    return ways[n-1];
}

// brute force O(n^2)
int maxSubArray(std::vector<int>& nums) {
    if (nums.size()==0)
        return 0;
    if (nums.size()==1)
        return nums[0];
    int sum = *max_element(nums.begin(), nums.end());
    int tmp = INT32_MIN;
    int cnt = 0;
    for(unsigned int i = 0; i < nums.size(); ++i) {
        for ( unsigned int j = i+1; j <= nums.size(); ++j) {
            tmp = accum(nums.begin()+i, nums.begin()+j);
            if (tmp > sum) {
                sum = tmp;
            }
            cnt++;
        }
    }
    return sum;
}

// 0(n) solution
int maxSubArray2(std::vector<int>& nums) {
    if (nums.empty())
        return 0;
    if (nums.size() == 1)
        return nums[0];

    int result = nums[0];
    int sum = 0;

    for (auto& el: nums) {
        sum += el;
        result = std::max(sum, result);
        sum = std::max(sum, 0);	 // if sum drops below zero then reset sum
    }
    return result;
}

/*
	dynamic programming version 0(n) solution
*/
int maxSubArray3(std::vector<int>& nums) {
    size_t n = nums.size();
    std::vector<int> dp(n, 0);
    dp[0] = nums[0];
    int sum = dp[0];

    for (int i = 1; i < n; i++) {
        dp[i] = nums[i] + ((dp[i-1] > 0) ? dp[i-1]:0);
        sum = std::max(sum, dp[i]);
    }
    return sum;
}

// max sum of a sub array that crosses the midpoint -->
// [* l * * (* * m * * *) * r * ] << max sum between [mid, l] and [mid+1, r] then combine to
// form the crossSum
void _maxCrossingSubArray(std::vector<int>& nums, int l, int mid, int r, int& _max) {
    std::cout << "\n" << std::endl;
    LOG << "l: " << l << " mid: " << mid << " r: " << r << " max: " << _max << std::endl;
    int leftSum = INT32_MIN;
    int sum = 0;
    // get sum from middle towards l --> [ * * * l * * <--- mid * * * * r]
    for (int i = mid; i >= l; i--) {
        sum += nums[i];
        if (sum > leftSum) {
            leftSum = sum;
        }
    }
    int rightSum = INT32_MIN; 
    sum = 0;
    for (int i = mid+1; i <= r; i++) {
        sum += nums[i];
        if (sum > rightSum) {
            rightSum = sum;
        }
    }
    int crossSum = (leftSum+rightSum);
    LOG << "leftSum: " << leftSum << " rightSum: " << rightSum << " crossSum: " << crossSum << std::endl;

    // see if crossing sums are larger than current max value
    if (leftSum > rightSum && leftSum > crossSum && leftSum > _max) _max = leftSum;
    else if (rightSum > leftSum && rightSum > crossSum && rightSum > _max) _max = rightSum;
    else if (crossSum > _max) _max = crossSum;
}

// recurse div and conq 
void _maxSubArray(std::vector<int>& nums, int l, int r, int& _max)  {
    using namespace std;
    LOG << "l: " << l << " r: " << r << " max: " << _max << endl;

    // base case one element
    if (l==r) {
        if (nums[l] > _max) _max = nums[l];
        return;
    }
    int mid = (l+r)/2;
    _maxSubArray(nums, l, mid, _max);
    _maxSubArray(nums, mid+1, r, _max);
    _maxCrossingSubArray(nums, l, mid, r, _max);
}
/*
	Divide and conquer solution 0(n)
	Recursive
*/
int maxSubArray4(std::vector<int>& nums) {
    if (nums.size()==1) return nums[0];
    int max = INT32_MIN;
    _maxSubArray(nums, 0, (int)nums.size()-1, max);
    return max;
}

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


bool _checkRows(const SudokuBoard& board) {
    for (const auto& row: board) {
        if(!_checkDuplicate(row))
            return false;
    }
    return true;
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

    ListNode* dummy  =  new ListNode(-1);
    ListNode* cur = dummy;

    while(l1!=NULL && l2!=NULL){
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
 *
[0,1,2,8,0,0]
4
[0,2]
2
 */
// merge nums2 in to nums1 it can be assumed that nums1 has m+n elements already
void mergeVectors(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
    if (nums2.empty()) return;
    int i1=0, i2=0;
    while (i1 < (m+i2) && i2 < n) {
        std::cout << "i1: " << i1 << ", i2: " << i2 << std::endl;
        if (nums2[i2] <= nums1[i1]) {
            nums1.erase(nums1.end()-1);
            nums1.insert(nums1.begin()+i1, nums2[i2++]);
            display(nums1);
        } else {
            i1++;
        }
    }
    std::cout << "Outside of loop: \n\ti1: " << i1 << ", i2: " << i2 << std::endl;

    // fill in the rest at the end
    for (; i1 < (m+n) && i2 < n; i1++, i2++)
        nums1[i1] = nums2[i2];
}

void mergeVectorsV2(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
    if (nums2.empty()) return;
    int cnt = 0;
    int mergeLen = m + n, i = 0, j = 0;
    bool inserted = false;
    while (j < n && i < mergeLen - 1) {
        int tmp = nums2[j];  // 2
        if (tmp > nums1[i] && tmp <= nums1[i + 1]) {
            nums1.insert(nums1.begin() + (i + 1), tmp);
            j++;
            cnt++;
            inserted = true;
        } else if (tmp < nums1[i]) {
            nums1.insert(nums1.begin()+i, tmp);
            inserted = true;
            j++;
        } else if (tmp == nums1[i]) { // equal
            nums1.insert(nums1.begin() + i, tmp);
            inserted = true;
            j++;
            cnt++;
        }
        i++;
        if (inserted) {
            nums1.erase(nums1.end() - 1);
            inserted = false;
        }
    }

    // fill in rest of elements from nums2 that didnt make it
    std::cout << "i: " << i << " j: " << j << std::endl;
    if (j == n - 1) {
        nums1[mergeLen - 1] = nums2[j];
    } else {
        for (int z = j; z < n; z++) {
            nums1[mergeLen - cnt -1] = nums2[z];
            cnt--;
        }
    }
}

// merge from behind version
void mergeVectorsV3(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
    if (nums2.empty()) return;
    while (m > 0 && n > 0) {
        if (nums1[m-1] > nums2[n-1]) {
            nums1[m + n - 1] = nums1[m-1];
            m--;
        } else {
            nums1[m + n - 1] = nums2[n-1];
            n--;
        }
    }

    // fill in rest
    while (n > 0) {
        nums1[n-1] = nums2[n - 1];
        n--;
    }
}

int firstBadVerison(int n) {
    int mid;
    int left = 1;
    int right = n;
    
    // binary search 
    while (left < right) {
        mid = left + (right-left)/2;
        if (isBadVersion(mid)) right = mid;
        else left = mid+1;
    }
    return left; 
}

bool isBadVersion(int v) {
    static size_t cnt = 0;
    cnt++;
    std::cout << "API call: " << cnt << std::endl; 
    if (v >= g_badVersion) return true;
    else return false;
}

// number version is based on first index being one
void initVersionVect(int badVersion, int numVersions) {
    g_badVersion = badVersion;
    g_nVersions = numVersions;
}

int maxProfit(std::vector<int>& prices) {
    int min = INT32_MAX; 
    int profit = 0;
    for (auto& price : prices) {
        if (price - min > profit) profit = price - min;
        else if (price < min) min = price;
    }
    return profit; 
}

void _robHouses() {

}

void _rob(std::vector<int>& nums, int start, int& robbed) {
    if (start >= nums.size())
        return;
    robbed += nums[start];
    start+=2;


}

/*
 * houses are situated in a row, a theif cannot rob two adjacent houses.
 *
 * dp[i] = max (hval[i] + dp[i-2], dp[i-1])
 *
 * hval[i] + dp[i-2] is the case when thief
 * decided to rob house i.
 *
 * In that situation max value will be the current value of house + maximum value stolen till last
 * robbery at house not adjacent to house i which will be house i-2.
 *
 * dp[i-1] is the case when theif decided not to rob house i. So he will check adjacent house for
 * max value stolen till now
 */
int rob(std::vector<int> &nums) {
    if (nums.empty()) return 0;
    size_t len = nums.size();
    if (len == 1) return nums[0];
    if (len == 2) return std::max(nums[0], nums[1]);
    std::vector<int> dp(len, 0);
    dp[0] = nums[0];
    dp[1] = std::max(nums[0], nums[1]);
    for (int i = 2; i < len; i++) {
        dp[i] = std::max(nums[i]+dp[i-2], dp[i-1]);
    }
    return dp[len-1];
}

// faster version, O(1) mem usage
int robV2(std::vector<int>& nums) {
    int lastRob = 0, lastNotRob = 0;
    int tmpRob  = 0, tmpNotRob  = 0;
    for (size_t i = 0; i < nums.size(); ++i) {
        tmpRob    = lastNotRob + nums[i];
        tmpNotRob = lastRob > lastNotRob ? lastRob : lastNotRob;
        lastRob    = tmpRob;
        lastNotRob = tmpNotRob;
    }
    return lastRob > lastNotRob ? lastRob : lastNotRob;
}

/*
 * arr[(i-1)/2] --> returns parent node
 * arr[(2i)+1] --> returns left child node
 * arr[(2i)+2] --> returns right child node
 * */
void MinStack::push(int x) {
    // first place element at the end of the data vector
    _data.push_back(x);
    _stk.push(x);
    _size++;

    if (_size == 1) return;
    size_t i = _size - 1;

    // find correct position within heap
    // if child node is smaller than parent then swap those
    while(i != 0 && _data[parent(i)] >= _data[i]) {
        swap(_data[parent(i)], _data[i]);
        i = parent(i);
    }
}

// pop top of stack and maintain heap properties
void MinStack::pop() {
    int tmp;
    if (!_stk.empty())
        tmp = _stk.top();
    else
        return;
    _stk.pop();
    std::ptrdiff_t i = std::distance(_data.begin(), std::find(_data.begin(), _data.end(), tmp));
    if (i < 0)
        return;
    deleteNode(i);
    heapify(i);
}

// restore heap properties starting at the sub tree if index i
void MinStack::heapify(size_t i) {
    size_t l = left(i);
    size_t r = right(i);
    size_t smallest = i;

    // check to see if l is smaller than parent node
    if (l < _size && _data[l] < _data[i])
        smallest = l;

    // check to see if r is smaller than parent node
    if (r < _size && _data[r] < _data[smallest])
        smallest = r;

    // this case indicates that either l or r were smaller
    // so swap the nodes and check up the next subtree
    if (smallest != i) {
        swap(_data[i], _data[smallest]);
        heapify(smallest);
    }
}

// deletes node at index i
// decreases that node smallest integer possible, which will bubble it to the root node
// then we can just call removeMin on it
void MinStack::deleteNode(size_t i) {
    if (_size <= 0) return;
    decreaseNode(i, INT32_MIN);
    _data[0] = _data[_size-1];
    _data.erase(_data.begin()+_size-1);
    _size--;
    heapify(0);
}

void MinStack::decreaseNode(size_t i, int val) {
    _data[i] = val;
    while (i != 0 && _data[parent(i)] > _data[i]) {
        swap(_data[parent(i)], _data[i]);
        i = parent(i);
    }
}

int MinStack::top() {
    if (_size == 0) return INT32_MAX;
    return _stk.top();
}

int MinStack::getMin() {
    if (_size == 0) return INT32_MAX;
    return _data[0];
}

// counts the number of prime numbers less than n
int countPrimes(int n) {
    std::vector<bool> notPrime(static_cast<size_t>(n), false);
    int cnt = 0;
    for (uint32_t i = 2; i < n; i++) {
        if (!notPrime[i]) {
            cnt++;
            if (i * i < n) {
                for (uint32_t j = 2; j * i < n; ++j)
                    notPrime[i * j] = true;
            }
        }
    }
    return cnt;
}

// determine if n is a power of three or not
bool isPowerOfThree(int n) {
    if (n < 3) return false;
    LOG << "enter: n=" << n << END;
    while (n!=1 && n%3==0) {
        n/=3;
        LOG << "n: " << n << END;
    }
    return n==1;
}

/*
 *  I can be placed before V (5) and X (10) to make 4 and 9.
    X can be placed before L (50) and C (100) to make 40 and 90.
    C can be placed before D (500) and M (1000) to make 400 and 900.
 */
int romanToInt(std::string& rnum) {
    const std::map<char, int> rmap = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
    };
    int result = 0;
    char prev = '\0';
    for (const auto& ch: rnum) {
        result += rmap.at(ch);
        if (prev == '\0') {
            prev = ch;
            continue;
        }
        if (prev == 'I' && (ch == 'X' || ch == 'V')) {
            result-=2;
            prev = '\0';
        } else if (prev == 'X' && (ch == 'L' || ch == 'C')) {
            result-=20;
            prev = '\0';
        } else if (prev == 'C' && (ch == 'D' || ch == 'M')) {
            result -= 200;
            prev = '\0';
        } else {
            prev = ch;
        }
    }
    return result;
}

int romaToIntV2(const std::string& rnum) {
    int rmap[89] = {0};
    rmap[(int)'I'] = 1;
    rmap[(int)'V'] = 5;
    rmap[(int)'X'] = 10;
    rmap[(int)'L'] = 50;
    rmap[(int)'C'] = 100;
    rmap[(int)'D'] = 500;
    rmap[(int)'M'] = 1000;
    int result = 0;
    char prev = '\0';
    for (const auto& ch: rnum) {
        result += rmap[ static_cast<int>(ch) ];
        if (prev == '\0') {
            prev = ch;
            continue;
        }
        if (prev == 'I' && (ch == 'X' || ch == 'V')) {
            result-=2;
            prev = '\0';
        } else if (prev == 'X' && (ch == 'L' || ch == 'C')) {
            result-=20;
            prev = '\0';
        } else if (prev == 'C' && (ch == 'D' || ch == 'M')) {
            result -= 200;
            prev = '\0';
        } else {
            prev = ch;
        }
    }
    return result;
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

// my original solution :: not good
std::vector<std::string> topKFrequent(std::vector<std::string> &words, int k) {
    if (words.size() == 1) return {words[0]};
    std::vector<std::string> result;
    std::map<std::string, int> freqMap;
    int cnt = 0;

    sort(words.begin(), words.end());

    for (const auto& word : words) {
        auto entry = freqMap.find(word);
        if (entry == freqMap.end())
            freqMap[word] = 1;
        else
            entry->second++;
    }

    std::string nextWord;
    while (cnt < k) {
        int maxCnt = 0;
        for (const auto& word : words) {
            auto entry  = freqMap.find(word);
            if (entry != freqMap.end() && entry->second > maxCnt) {
                maxCnt = entry->second;
                nextWord = entry->first;
            }
        }
        result.push_back(nextWord);
        freqMap.erase(nextWord);
        maxCnt = 0;
        cnt++;
    }
    return result;
}

/*
 optimized using a heap
 fill map <word, number of occurances>
 fill priority queue (max) each element being a
 std::pair with the word paired with its numOccurences from the vector
 the comparator for the queue MyPairCompGreater, the comparator ensures
 the order is from smallest to largest

 Elements are compares each word by number of occurences if they are equal the tie
 is broken by when word comes first in the alphabet
 this comparator determines the position in the pri queue
      if (p1.second != p2.second)
          return p1.second > p2.second;
      return p1.first < p2.first;

 an additional optimization is once the pri queue reaches size of k
 we pop the top (word with least occurences)

 After queue is filled we can fill k elements in to the array ending with
 element 0 to be the word with the most frequent appearances
 O( nlog(k) )
 */
std::vector<std::string> topKFrequentV2(const std::vector<std::string> &words, int k) {
    std::unordered_map<std::string, int> freqMap;

    // O(n)
    for (const auto& word : words)
        freqMap[word]++;

    // priority queue looks up O(1) with the element being the greatest
    std::priority_queue<std::pair<std::string, int>,
            std::vector<std::pair<std::string, int>>,
            MyPairCompGreater> heap;
    for (const auto& entry: freqMap) {
        if (heap.size() < k) {
            heap.push(std::make_pair(entry.first, entry.second));
        } else {
            auto temp = heap.top();
            if ( ((entry.second < temp.second) || entry.second)
                                              == (temp.second && (temp.first < entry.first)) )
                continue;
            heap.pop();   // keeps pri queue from exceeded k in size
            heap.push(std::make_pair(entry.first, entry.second));
        }
    }

    std::vector<std::string> result;
    while (!heap.empty()) {
        result.insert(result.begin(), heap.top().first);
        heap.pop();
    }
    return result;
}

struct TopFreqCompare {
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second < b.second;
    }
};

std::vector<int> topFrequentKIntegers(std::vector<int>& nums, int k) {
    std::vector<int> result;
    std::map<int, int> freqMap;
    std::priority_queue<std::pair<int, int>,
            std::vector<std::pair<int, int>>,
            TopFreqCompare> priQ;  // top element is most frequent

    // map word : numAppearences
    for (auto& el : nums)
        freqMap[el]++;

    // fill queue up with freq pairs, will order entries for us, most freq will be at the top
    for (auto& el : nums) {
        auto entry = freqMap.find(el);
        if (entry == freqMap.end()) continue;
        priQ.push({entry->first, entry->second});
        freqMap.erase(el);
        if (freqMap.empty()) break;
    }

    // fill result from pri-queue
    while (result.size() < k) {
        result.insert(result.begin(), priQ.top().first);
        priQ.pop();
    }
    return result;
}

template<typename T>
struct TopFreqCompareGreater {
    bool operator()(T& a, T& b) {
        return a.second<b.second;
    }
};

std::string frequencySort(std::string s) {
    std::string result;
    std::map<char, int> freqMap;
    std::priority_queue<std::pair<char, int>,
            std::vector<std::pair<char, int>>,
            TopFreqCompareGreater<std::pair<char, int>>> priQ;

    // fill map <char, numAppearences>
    // O(n)
    for (auto& ch : s)
        freqMap[ch]++;

    // fill queue keeps elements sorted by appearences (most appearences on top)
    for (auto& entry: freqMap) {
        priQ.push( {entry.first, entry.second} );
    }

    // fill result O(priQSize * n)
    while (!priQ.empty()) {
        char ch = priQ.top().first;
        for (int i = 0 ; i < priQ.top().second; i++)
            result+=ch;
        priQ.pop();
    }
    return result;
}

/*
 use binary search accounting for rotation
 [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]
 first find the number of rotations put on the array
 this is done by:
 1. find the mid index
 2a. if that value is larger than the hi index then we move the low index up 1 past the mid index
 2b. if that value is equal to or less then we set hi to the mid index
 3. when lo == hi we have found the lowest value and how many rotations occurred
 */
int searchSortedRotatedArray(std::vector<int>& nums, int target) {
    auto len = static_cast<int>(nums.size());
    int lo=0, hi=len-1;

    // finds the real lo and hi index accounting for the rotation
    while(lo<hi) {
        int mid = (lo+hi) / 2;
        if (nums[mid] > nums[hi]) lo = mid + 1;  // shrink the gap between lo and hi
        else hi = mid;
    }

    // lo == hi is the index of smallest value and the number of places rotated
    int numRot = lo;
    lo = 0;
    hi = len -1;

    // normal binary search accounting for rotation
    while (lo <= hi) {
        int mid = (lo+hi) / 2;
        int realMid = (mid+numRot) % len;
        if (nums[realMid]==target) return realMid;
        if (nums[realMid]<target) lo = mid+1;
        else hi = mid - 1;
    }
    return -1;  // not found
}

/*
 * finding number of rotations in this problem does not work
 * we must take this approach
 * steps:
 * 1.
 */
bool searchSortedRotatedArrayII(std::vector<int> &nums, int target) {
    int left = 0, right = static_cast<int>(nums.size()-1);
    int mid;

    while (left <= right) {
        LOG << "left: " << left << " right: " << right << "\n" << END;
        mid = (left + right) / 2;
        if (nums[mid] == target) return true;

        // for duplicate case we converge both left and right towards the center by one
        if (nums[left] == nums[mid] && nums[mid] == nums[right] ) {
            left++;
            right--;
        } else if (nums[left] <= nums[mid]) {  // left side of array is in order
            if ((nums[left] <= target) && (nums[mid] > target)) // left is < mid and less than target and mid > target
                right = mid - 1;  // since mid val is larger we bring in the right side
            else
                left = mid + 1; // move left up to mid our left side is larger
        } else {
            if ( (nums[mid] < target) && (nums[right] >= target) )
                left = mid + 1;  // normal case where we bring up the left side since mid < target
            else
                right = mid - 1;
        }
    }
    return false;
}

// not as fast as V1
bool searchSortedRotatedArrayIIV2(std::vector<int> &nums, int target) {
    int start=0,end=static_cast<int>(nums.size()-1);
    while(start<=end){
        int mid=start+(end-start)/2;
        if(nums[mid]==target) return true;
        if(nums[mid]==nums[start]) {
            start++;
        }
        else if(nums[start]<=nums[mid]) {
            if (nums[start] <= target && target <= nums[mid]) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }
        else {
            if (nums[mid] <= target && target <= nums[end]) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }
    }
    return false;
}



// each step we can either go right or down
// TODO :: has issues
void _uniquePaths(std::pair<int, int> currPos, const std::pair<int, int>& targetPos, int& numPaths) {

    // step right and check position
    if (currPos.first < targetPos.first) {
        currPos.first++;
        if (currPos==targetPos) {
            numPaths++;
        }
        _uniquePaths(currPos, targetPos, numPaths);
    }

    // step down and check position
    if (currPos.second < targetPos.second) {
        currPos.second++;
        if (currPos==targetPos) {
            numPaths++;
        }
        _uniquePaths(currPos, targetPos, numPaths);
    }
}

/*
    A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
    The robot can only move either down or right at any point in time.
    The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
    How many possible unique paths are there?
 */
// TODO :: has issues
int uniquePaths(int m, int n) {
    int numPaths = 0;
    std::pair<int, int> curPosition = {0, 0}; // (col, row)
    _uniquePaths(curPosition, {n-1, m-1}, numPaths);
    return numPaths;
}

/*
 * FYI: mxn matrix is m rows by n columns
    Since the robot can only move right and down, when it arrives at a point, there are only two possibilities:
    1. It arrives at that point from above (moving down to that point);
    2. It arrives at that point from left (moving right to that point).

    Thus, we have the following state equations: suppose the number of paths to arrive at a point (i, j)
    is denoted as P[i][j], it is easily concluded that P[i][j] = P[i - 1][j] + P[i][j - 1].

    The boundary conditions of the above equation occur at the leftmost column (P[i][j - 1] does not exist)
    and the uppermost row (P[i - 1][j] does not exist).
    These conditions can be handled by initialization (pre-processing)
    --- initialize P[0][j] = 1, P[i][0] = 1 for all valid i, j. Note the initial value is 1 instead of 0!

    Now we write the following unoptimized code ...
 */
int uniquePathsV2(int m, int n) {
    std::vector<std::vector<int> > path(m, std::vector<int> (n, 1));
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            path[i][j] = path[i - 1][j] + path[i][j - 1];
        }
    }
    return path[m - 1][n - 1];
}

/*
    The following is the same code as above (V2) but optimized
    It can be observed that each tiime when we update path[i][j] we only need path[i-1][j] (at the same column)
    and path[i][j-1] (at the left column). So it is enough to maintain two columns
    (the current column and the left column) instead of maintaining the full mxn matrix.
    Code is optimized to have O(min(m, n)) space complexity

    Inspecting the code below we find that keeping two columns is used to recover pre[i], which is just
    cur[i] before its update. So there is even no need to use two vectors and one is just enough.
    Space is further saved and the code gets shorter as well.

    Since we are only going right and down the column and the column to the left are all that matter
    * * *
    * 0 *
    * * *
    in the matrix above ^ ... to get to the cell with 0 we only care about the 2nd column (current) and
    the first column (prev) no need to keep entire matrix in mem
 */
int uniquePathsV3(int m, int n) {
    if (m > n) return uniquePathsV3(n, m);  // ensure space complexity is O(min(m,n))
    std::vector<int> pre(m, 1);
    std::vector<int> cur(m, 1);
    for (int j = 1; j < n; j++) {
        for (int i = 1; i < m; i++) {
            cur[i] = cur[i-1] + pre[i];
        }
        std::swap(pre, cur);
    }
    return pre[m-1];
}

/*
    Further inspecting V3 we see that there is no need to keep two vectors as prev[i] is cur[i] before its update
 */
int uniquePathsV4(int m, int n) {
    if (m > n) uniquePathsV4(n, m);
    std::vector<int> cur(m,1);
    for (int j =1; j < n; j++) {
        for (int i = 0; i < m; i++) {
            cur[i] += cur[i-1];
        }
    }
    return cur[m-1];
}

std::vector<Interval> mergeIntervals(std::vector<Interval> &intervals) {
    std::vector<Interval> result;
    // sort by starting point, neighboring intervals will be potential overlappers
    std::sort(intervals.begin(),
              intervals.end(),
              [](auto& a, auto& b){ return a.start < b.start; });
    for (auto& intv : intervals) {
        /*
         * if the list of the merged intervals is empty or if the current interval does not overlap
         * with the previous, simply append it
         */
        if ( result.empty() || (result.end()-1)->end < intv.start )
            result.push_back(intv);
        else // otherwise there is overlap, so we merge the current and previous intervals
            (result.end()-1)->end = std::max((result.end()-1)->end, intv.end);
    }
    return result;
}

// using bin search
int mySqrt(int x) {
    if (0 == x) return 0;
    int left = 1, right = x/2, ans;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (mid <= x / mid) {
            left = mid + 1;
            ans = mid;
        } else {
            right = mid - 1;
        }
    }
    return ans;
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




// [24,12,8,6]
std::vector<int> productExceptSelf(std::vector<int> &nums) {
    int len = static_cast<int>(nums.size());
    if (len == 1) return nums;
    if (nums.empty()) return {};
    std::vector<int> result(len);
    std::vector<int> fromLeft(len);
    std::vector<int> fromRight(len);

    // first element of fromLeft is 1
    fromLeft[0] = 1;

    // last element of from right will always be 1
    fromRight[len-1] = 1;

    // product up to nums[i] for each iteration
    for (int i = 1; i < len; i++)
        fromLeft[i] = fromLeft[i-1] * nums[i-1];

    // product up to nums[i] for each iteration but from right side of nums
    for (int i = len-2; i >= 0; i--)
        fromRight[i] = fromRight[i+1]*nums[i+1];

    // result would be multipication of product up to nums[i] from left and right
    for (int i = 0; i < len; i++)
        result[i] = fromLeft[i]*fromRight[i];
    return result;
}



void _backtrackParen(std::vector<std::string>& result, std::string curr, int openCnt, int closeCnt, int maxCnt) {
    if (curr.size() == maxCnt * 2) {
        result.push_back(curr);
        return;
    }
    if (openCnt < maxCnt)
        _backtrackParen(result, curr+"(", openCnt, closeCnt, maxCnt);
    if (closeCnt < openCnt)
        _backtrackParen(result, curr + ")", openCnt, closeCnt+1, maxCnt);
}



