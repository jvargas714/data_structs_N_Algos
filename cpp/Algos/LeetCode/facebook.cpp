#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <cctype>
#include <cstring>
#include <cstdint>
#include <climits>
#include "facebook.h"

// ================================================ helper functions ===================================================
// =====================================================================================================================

/*
	in: [ 0, 1, 0, 3, 12 ]
	out: [1, 3, 12, 0, 0]
    as we traverse the array j holds the index that will be
    overwritten by num[i], once overwritten we increment j.
    This effectively pushes non-zero values towards the front of the array,
    the duplicates will be written as zeros in the second for loop.
    before the second for loop we had: [1,3,12,3,12]
    after the second for loop we come to: [1, 3, 12, 0, 0]
 */
void moveZeroes(std::vector<int> &nums) {
	if (nums.empty()) return;
	int j = 0;
	for (int i = 0; i < nums.size(); i++)
		if (nums[i]!=0)
			nums[j++]=nums[i];
	for (int i = j; i < nums.size(); i++)
		nums[i] = 0;
}

/*
 optimized solution
 Example 2:
	Input: a = "1010", b = "1011"
	Output: "10101"

  111011  -- b
    1110  --
   -----

    Approach:
        1. two pointer approach
        2. add up to the shorter of the two strings (keep track of carries)
        3. find if they are different lengths or not
        3a. if they are different lengths get a reference to the longer one and its index (where it left off)
        3a. add remainder of longer string to the result (consider carry)
        3b. if not different just check for one more carry and apply it
        4. check for one more carry
        5. reverse result

    10111
     1110

 stack --> 11101
 */
std::string addBinary(std::string& a, std::string& b) {
    std::string result;
    int ia=(int)a.size()-1, ib=(int)b.size()-1;
    bool carry = false;

    while (ia >= 0 && ib >= 0) {
        if (a[ia]=='0' && b[ib]=='0') {
            if (carry) result += '1';
            else result += '0';
            carry = false;
        } else if (a[ia]=='1' && b[ib]=='1') {
            if (carry) result += '1';
            else result += '0';
            carry = true;
        } else {
            if (carry) result += '0';
            else result += '1';
        }
        ia--;
        ib--;
    }

    // handle if lengths are different
    if (b.size() != a.size()) {
        std::string& tmp = (ia<0)? b:a;
        int ind = (ia>=0? ia:ib);
        while (ind >= 0) {
            if (carry) {
                result += (tmp[ind] == '1') ? '0':'1';
                carry = (tmp[ind] == '1');
            } else
                result += tmp[ind];
            --ind;
        }
    } else {
        if (carry) result += '1';
        carry = false;
    }
    if (carry) result += '1';
    std::reverse(result.begin(), result.end());
    return result;
}

/*
    Example 1:
    Input: nums1 = [1,2,2,1], nums2 = [2,2]
    Output: [2,2]

    Example 2:
    Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
    Output: [4,9]

    complexity:
        O(n) space
        O(n) time
 */
std::vector<int> intersect(std::vector<int> &nums1, std::vector<int> &nums2) {
    if (nums1.empty()||nums2.empty()) return {};
    std::vector<int> result;
    std::unordered_map<int, int> numsMap;
    for (const auto& el : nums1)
        numsMap[el]++;

    for (const auto& el : nums2) {
        if (numsMap.find(el) != numsMap.end()) {
            if (numsMap[el] > 0) {
                result.push_back(el);
                numsMap[el]--;
            }
        }
    }
    return result;
}

/*
Example:
    Given array nums = [-1, 0, 1, 2, -1, -4],
    A solution set is:
    [
    [-1, 0, 1],
    [-1, -1, 2]
    ]
    loop through nums up to -2 before end
    set j = i + 1
        k = nums.len - 1
		[* * * i j * * * * * k]    --> sorted vector
		 - j and k will converge towards one another (inner while loop)
		 - if sum is > 0 we bring k towards j so the sum decreases
		 - if sum os < 0 we increase the value of j by j++ (since vector is already sorted)
		 - if sum == 0 then we record that result
 */
std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
	if (nums.size() < 3) return {};
	std::vector<std::vector<int>> result;
	std::sort(nums.begin(), nums.end());
    int j=0, k=0;
	for (int i = 0; i < (int)nums.size() - 2; i++) {
		/*
		 * if nums[i] > 0 then there is no way to get it down to zero as the array is sorted and the subsequent
		 * values will only be greater than or equal nums[i]
		 */
		if (nums[i] > 0) break;
		// skip duplicate scenario was handled previous iteration
        if (i > 0 && nums[i] == nums[i-1]) continue;
		j = i + 1;
		k = (int)nums.size()-1;

		// we have three pointers at this point [* * * i j * * * * * k]  <-- k will converge into j
		while ( j < k) {
		    // skip duplicate case (was previously handled last iteration
		    if (j > i + 1 && nums[j]==nums[j-1]) {
		        j++;
		        continue;
		    }
		    // check if sum is already positive if so break out not possible to bring it down to zero
		    if (nums[i] + nums[j] > 0) break;
			int sum = nums[i] + nums[j] + nums[k];
			if (sum < 0) j++;
			else if (sum > 0) k--;
			else {
				result.push_back({nums[i], nums[j], nums[k]});
				j++;
				k--;
			}
		}
	}
	return result;
}

// we can ignore white space
bool isPalindrome(std::string& s) {
    if (s.empty()) return true;
    int l = 0, r = (int)s.size()-1;
    // using transform is much faster than the for_each method
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    while (l < r) {
        if ((s[l] < 'a' || s[l] > 'z') && (s[l] < '0' || s[l] > '9')) {
            l++;
            continue;
        }
        if ((s[r] < 'a' || s[r] > 'z') && (s[r] < '0' || s[r] > '9')) {
            r--;
            continue;
        }
        if (s[l] != s[r]) return false;
        l++;
        r--;
    }
    return true;
}

/*
 * abca -->  we can remove the 'c' to make it valid
 * Approach:
 *      1. go through like isAPalindrome
 *      2. if we have a mismatch we start by removing the l element first
 *          if that does work try by removing the r element if that also doesnt work then
 *          return false
 *
 *   aabb d eebada
 */
bool validPalindrome(std::string& s) {
    if (s.size()==1 || s.size()==2) return true;
    int l=0, r=(int)s.size()-1;

    // lambda to check if valid
    auto _isPalindrome = [](const std::string& s) {
        int l=0, r=(int)s.size()-1;
        while (l < r) {
            if (s[l] != s[r])
                return false;
            l++; r--;
        }
        return true;
    };

    while (l < r) {
        if (s[l]!=s[r]) {
            std::string tmp(s);
            s.erase(s.begin()+l);
            if (_isPalindrome(s)) return true;
            tmp.erase(tmp.begin()+r);
            return _isPalindrome(tmp);
        }
        l++;
        r--;
    }
    return true;
}

/* optimized solution from discussion
 *  essentially this algo checks for a valid palindrome, if we have a mismatch then we need
 *  to check if removing either the left or right side fixes our issues if not then return false
 *  [x x l x x r x x]
 *  isPalindromeFptr(s, l-1, r): sets our palindrome check to [x l x x x r x x] --> then the first check
 *      ends up being [x x l x r x x x]  --> essentially skips forward the right side by one
 *
 *  where isPalindromeFptr(s, l, r+1): effectively skips the left side forward by 1 (since the while loop is
 *      using predecrementing/preincrementing
 * */
bool validPalindromeV2(std::string& s) {
    auto isPalindromeFptr = [](std::string str, int l, int r){
        while (++l < --r)
            if (str[l] != str[r]) return false;
        return true;
    };
    int l = -1, r = (int)s.size();
    while (++l < --r)
        if (s[l] != s[r])
            return isPalindromeFptr(s, l-1, r) || isPalindromeFptr(s, l, r+1);
    return true;
}

/*  " .1 " ==> true
    " 0.1 " => true
    "abc" => false
    "1 a" => false
    "2e10" => true

    rules:
        Numbers 0-9
        Exponent - "e"
        Positive/negative sign - "+"/"-"
        Decimal point - "."
 */
bool isNumber(std::string s) {
    // gotta process at least one number
    bool procNum = false;

    // found a decimal pt
    bool hasDecimalPt = false;

    // there is an exponential symbol
    bool hasExp = false;

    // minus sign after exponential
    bool minusExp = false;
    int i = 0;

    // strip preceeding whitespace
    while (true) {
        if (!std::isspace(s[i])) break;
        else i++;
    }

    // check first character to be invalid
    if (s.empty()||s[i]=='e'|| i==s.size()) return false;

    // check if '.' is placed correctly cannot have a space right after a '.'
    if (s[i] == '.') {
        if (i == s.size()-1) return false;
        if (i+1 < s.size() && (std::isspace(s[i+1])||s[i+1]=='e')) return false;
    }

    // handle sign in front of number if its there
    if (s[i]=='-'||s[i]=='+') {
        if (s.size()==1) return false;
        i++;
        if (i < s.size()) {
            if (s[i]=='e') return false;
        }
    }

    for (; i < (int)s.size(); i++) {
        char ch = s[i];
        if (!std::isdigit(ch)) {
            if (ch == '.') {
                if (hasExp || hasDecimalPt) return false;
                else hasDecimalPt = true;
            } else if (ch == 'e') {
                if (hasExp) return false;
                hasExp = true;
                procNum = false; // must have a number after 'e'
            } else if (ch == '-' || ch == '+') {
                if (i > 0 && s[i-1]!='e') return false;
            } else if (std::isspace(ch)) {
                break;
            } else {
                    return false;
            }
        } else
            procNum = true;
    }

    if (!procNum) return false;

    // check if whitespace after 'e'
    if (i > 0 && s[i-1]=='e') return false;

    // check for chars after whitespace
    for (; i < s.size(); i++)
        if (!std::isspace(s[i])) return false;
    return true;
}

// optimized solution (kind of a waste of time)
bool isNumberV2(std::string s) {
    int i = 0;
    // skip over whitespace first
    while(s[i] == ' ') i++;

    // if first char is a sign (+|-) this is valid
    if(s[i] == '+' || s[i] == '-') i++;

    int n_nm = 0, n_pt = 0;

    // n_nm keeps track of digits counted, n_pt decimal points
    while(isdigit(s[i]) || s[i] == '.') {
        s[i] == '.' ? n_pt++ : n_nm++;
        i++;
    }
    // bad case if we have more than one '.' or no numbers
    if(n_pt > 1 || n_nm < 1) return false;

    // at this point we def have at least one number
    if(s[i]=='e') {
        i++;
        if(s[i] == '+' || s[i] == '-') i++;  // 3e+6 --> would be valid to have a '+' or '-' after 'e'
        n_nm = 0;

        // count digits after the 'e'
        while(isdigit(s[i])) {
            n_nm++;
            i++;
        }
        // if no digits return false
        if(n_nm < 1) return false;
    }
    // blast through whitespace
    while(s[i] == ' ') i++;

    // returns false if there is still a non whitespace at the end of the string
    return s[i] == '\0';
}

/*
    size of min array that sums to s, all integers will be positive, go for O(n),
    array must be contigueous (in a row)

    Example:
        Input: s = 7, nums = [2,3,1,2,4,3]
        Output: 2

    Approach:
        1. dumb bruteforce use two pointers go through
        2. [i * j * * * * k * *]
 */
int minSubArrayLen(int s, std::vector<int> &nums) {
	if (nums.empty()) return 0;
	if (nums.size()==1) return (nums[0]==s ? 1:0);
	int result = INT_MAX;
	int len = (int)nums.size();

	for (int i = 0; i < len; i++) {
		int sum = 0;
		for (int j = i; j < len; j++) {
			sum += nums[j];
			if (nums[j]==s) return 1;
			if (sum >= s) {
				result = std::min(result, j-i+1);
				break;
			}
		}
	}
	return result;
}

int minSubArrayLenV2(int s, std::vector<int>& nums) {
    int n = nums.size();
    if (n == 0)
        return 0;
    int ans = INT_MAX;
    std::vector<int> sums(n);
    sums[0] = nums[0];
    for (int i = 1; i < n; i++)
        sums[i] = sums[i - 1] + nums[i];

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int sum = sums[j] - sums[i] + nums[i];
            if (sum >= s) {
                ans = std::min(ans, (j - i + 1));
                break; //Found the smallest subarray with sum>=s starting with index i, hence move to next index
            }
        }
    }
    return (ans != INT_MAX) ? ans : 0;

}

/*
 * jdebug :: study this solution
 * optimized approach (binary search approach) best solution
 * Time Complexity: O(nlogn)
 * Space Complexity: O(n)
 *
 * sample data:
 *  nums: [2, 3, 1, 2, 4, 3]
 *  s = 10
 *  expect : 5
 *
 *  Approach:
 *      1. create a cumulative sum vector
 *          - start with sums[i=0]=0
 *          - end with [0, 2, 5, 6, 8, 12, 15]
 *      2. use binary search to find i that makes sum >= s
 *          - iterate to find index that is not lower than s-sums[i] in the sums
 *          - std::lower_bound function returns first element in range that does not eval less than target
 */
int minSubArrayLenV3(int s, std::vector<int>& nums) {
    if (nums.empty()) return 0;
    if (nums.size()==1) return (nums[0]==s ? 1:0);
    int len = (int)nums.size();
    int result = INT_MAX;
    std::vector<int> sums(len+1, 0);

    // build cumulative sums vector [0, 2, 5, 6, 8, 12, 15]
    for (int i = 1; i <= len; i++)
        sums[i] = sums[i-1] + nums[i-1];

    for (int i = 1; i <= len; i++) {
        /*
         * target = 10 + sums[2] = 10 + 5 = 15
         * target = 10 + [2, 3, * * * *] --> the stars starts if the range exists
         *                                      would be the range that we meets out sum requirements
         * input: nums: [2, 3, 1, 2, 4, 3]
         *  s = 10
         *
         * iterations:
         * i=1 :: target = 10 + sums[1-1] = 10 + 0 = 10 --> exactly the single value we look for
         * lower_bound returns iterator 10 or 5th index of sums
         * checking result -> 5 - 0 = 5  --> [2, 3, 1, 2, 4, *] add up to 10
         *
         * i = 2 :: target = 10 + sums[2-1] = 10 + 2 = 12, same outcome as i=1
         *
         * i = 3 :: target = 10 + sums[3-1] = 10 + 5 = 15 --> bound = 15 so [2 3 1 2 4 3], so range is 6 long
         * i = 4 :: break
         *
         *  rationale ::
         *      target = s + sums[i-1]
         *      want this to be true --> sum > s, but to consider the offset ie sums in between ends  of the vector
         *      we can say s < target - sums[i-1], the difference subtracts a portion of the range out of the sum
         *
         *      for example :: build cumulative sums vector [0, 2, 5, 6, 8, 12, 15]
         *          target = 7 + sums[3-1] --> 7 <= target - sums[3-1] = target - sums[2]
         *          we look at target - sums[i-1] --> for i = 3 its target - sum[2 3]  << sum of first elements of input
         *          so target = 7 + 5 = 12, we check if s <= target - sums[i-1] --> 7 <= 12 - sums[2] --> 7 <= 7
         *          --> 12 - sums[2] is the range [* * 1 2 4 *], our len is 3
         */
        int target = s + sums[i-1];
        if (target > sums[len]) break;
        // we search for that first target cumlative range that doesn't evaluate to less than target
        auto bound = lower_bound(sums.begin(), sums.end(), target);
        if (bound != sums.end()) {
            result = std::min(result, static_cast<int>(bound - (sums.begin() + i - 1)));
        }
    }
    return result != INT_MAX ? result:0;
}

/*
 * optimized :: (from discussion)
 *  similar approach to MinSubArrayLen
 *  Approach:
 *      1. use an unordered_map<sum, index> sums
 *      2. add to cumulative sum
 *      3. check if current sum is k
 *      4. if not check if sum-k is in the map as well
 *          this covers subarray where the sum starts from an index > 0
 *      5. insert current sum to map if it doesnt exists
 *      6. return answer if not INT_MIN else return 0
 */
int maxSubArrayLen(std::vector<int>& nums, int k) {
	if (nums.empty()) return 0;
	if (nums.size()==1) return (nums[0]==k)? 1:0;
	int len = (int)nums.size();
	int res = INT_MIN;
	int sum = 0;
	std::unordered_map<int, int> sums;

	/*
	 *  1. add next value to cumulative sum
	 *  2. check if the current sum adds to k
	 *  2a. true: update result by the size of the subarray i + 1
	 *  2b. else if sums[sum-k] exists in the map:
	 *      # sum-k   [* * * * *] - k ==> would check the subarray for the difference as the sum option
	 *      # if sum-k already exists in the sum map then that would cover a subarray [* * i * * * j *]
	 *      i to j where j is the current index
	 */
	for (int i = 0; i < len; i++) {
		sum += nums[i];
		if (sum==k)
			res = i + 1;
		else if (sums.find(sum-k) != sums.end())
			res = std::max(res, i - sums[sum-k]);  // sub-array not starting from 0-i instead [* * i * * * j *]

		// add to map if this sum is not already in there
		if (sums.find(sum) == sums.end())
			sums[sum] = i;
	}
	return res == INT_MIN ? 0:res;
}

/* slow solution O(n^2)
 * obvious straight forward solution (non-optimized)
 * TIME LIMIT EXCEEDED on large inputs
 * Approach:
 *      0. a two pointer solution
 *      1. a cumulative sums map
 *      2. loop through get sum ranges check for equivalence
 *      2a. [* * i * * * * * * j]
 */
int maxSubArrayLenV2(std::vector<int>& nums, int k) {
	if (nums.empty()) return 0;
	if (nums.size()==1) return (nums[0]==k) ? 1:0;
	int len = (int)nums.size();
	std::unordered_map<int, int> sums;  // <index, sum>
	sums[0] = 0;
	int res = INT_MIN;

	// 1. cumulative map first index is first index of nums
	for (int i = 1; i <= len; i++) sums[i] = sums[i-1] + nums[i-1];

	for (int i = 0; i < len; i++) {
		for (int j = len; j >= i+1; j--) {
			int sum = sums[j] - sums[i];
			if (sum == k) {
				res = std::max(res, j - i);
			}
		}
	}
	return res==INT_MIN ? 0:res;
}

/*
 * Slow Solution O(n)
    An input string is valid if:
	Open brackets must be closed by the same type of brackets.
	Open brackets must be closed in the correct order.
	Note that an empty string is also considered valid.

	Input: "{[]}"
	Output: true

    RunTime: O(n)  --> loop through all chars of input string once
    Space: O(n) --> space allocated for the stack
 */
bool isValid(const std::string& s) {
	if (s.empty()) return true;
	if (s[0] == ']' || s[0] == '}' || s[0] == ')') return false;
	std::stack<char> stk;
	for (const auto& ch : s) {
		if (ch == '(' || ch == '[' || ch == '{')
			stk.push(ch);
		else {
			if (stk.empty()) return false;
			switch(ch) {
				case ']':
					if (stk.top() != '[') return false;
					break;
				case '}':
					if (stk.top() != '{') return false;
					break;
				case ')':
					if (stk.top() != '(') return false;
			}
			stk.pop();
		}
	}
	return stk.empty();
}

/*
 * Approach:
 *  - check for size == 1 case, just return 0
 *  - use a stack
 *  - in while loop:
 *      >> if our stack is empty or the cavity goes deeper
 *          >>> increase depth by pushing index to stack (a deeper depth)
 *      >> else top element in the stack would be the bottom
 *          pop stack, max water at the bottom is  -->
 *          (std::min(height[stk.top()], height[i]) - height[bottom]) * (height[bottom]) calcuates height
 *          i - stk.top()-1 calculates the width  for the volume of water trapped
 *
 *      RunTime: O(n)  --> one pass through input vector
 *      Space Complexity: --> use of stack worst case filled with n elements
 */
int trap(std::vector<int>& height) {
	if (height.size()==1 || height.empty()) return 0;
	std::stack<int> stk;
	int i = 0, maxWater = 0, maxBotWater = 0;
	while (i < (int)height.size()) {
		// push to stack only if current depth is deeper than top of stack or empty
		if (stk.empty() || height[i] < height[stk.top()]) {
			stk.push(i++);
		} else {  // current height is higher altitude then top depth in stack
			int bottom = stk.top();  // lowest point
			stk.pop();
			// calculating volume of water --> height x width
			maxBotWater = stk.empty() ?
			              0 :
			              (std::min(height[stk.top()], height[i]) - height[bottom]) * (i - stk.top()-1);
			maxWater += maxBotWater;
		}
	}
	return maxWater;
}

/*
 * Input: 1->2->3->4->5->NULL
 * Output: 5->4->3->2->1->NULL
 * iterative approach
 * Time: O(n)  --> one pass through list
 * Space: O(n)  --> fills stack with ints
 */
ListNode* reverseList(ListNode* head) {
	if (!head) return head;
	ListNode* tmp = head;
	std::stack<int> stk;

	// find end first
	while (tmp != NULL) {
		std::cout << "tmp pushing: " << tmp->val << std::endl;
		stk.push(tmp->val);
		tmp = tmp->next;
	}

	tmp = head;
	std::cout << "stack size: " << stk.size() << std::endl;
	std::cout << "tmp points to: " << tmp->val << std::endl;

	while (!stk.empty()) {
		tmp->val = stk.top();
		std::cout << "tmp: " << tmp->val << ", popping: " << stk.top() << std::endl;
		tmp = tmp->next;
		stk.pop();
	}
	return head;
}

//func recursiveReverse(Node**):
//struct Node* first;
//struct Node* rest;
//
///* empty list */
//if (*head_ref == NULL)
//return;
//
///* suppose first = {1, 2, 3}, rest = {2, 3} */
//first = *head_ref;
//rest  = first->next;
//
///* List has only one node */
//if (rest == NULL)
//return;
//
///* reverse the rest list and put the first element at the end */
//recursiveReverse(&rest);
//first->next->next  = first;
//
///* tricky step -- see the diagram */
//first->next  = NULL;
//
///* fix the head pointer */
//*head_ref = rest;
// [* * * * f r] null
static void _revLstRecursive(ListNode** head) {
	if (*head==nullptr)
		return;
	ListNode* first = *head;
	ListNode* rest = first->next;
	if (rest == nullptr) return;
	_revLstRecursive(&rest);  //   [* * * * * f *]
	first->next->next = first;  // [* * * * * * * f]
	first->next = nullptr;
	*head = rest;
}

/*
 * recursive approach
 */
ListNode* reverseListV2(ListNode* head) {
	ListNode* tmp = head;
	_revLstRecursive(&head);
	return head;
}

/*
 * Straight forward solution
    Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
	Output: 7 -> 0 -> 8
	Explanation: 342 + 465 = 807

    say val = 12
    12 % 10 --> 2
 */
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	ListNode* tmp1 = l1;
	ListNode* tmp2 = l2;
	int carry = 0;

	// init head of list first
	int val = tmp1->val + tmp2->val;
	ListNode* res = new ListNode((val)%10);
	if (val >= 10) carry = 1;
	ListNode* resTmp = res;
	tmp1 = tmp1->next;
	tmp2 = tmp2->next;

	// add rest of number
	while (tmp1 && tmp2) {
		val = tmp1->val + tmp2->val + carry;
		carry = 0;
		if (val >= 10) carry = 1;
		else carry = 0;
		resTmp->next = new ListNode(val%10);
		resTmp = resTmp->next;
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}

	// check if there is a carry or remaining digits to add
	ListNode* tmp3 = (tmp1 != nullptr ? tmp1 : (tmp2 != nullptr ? tmp2:nullptr));
	while (tmp3) {
		val = tmp3->val + carry;
		if (val == 10) carry = 1;
		else carry = 0;
		resTmp->next = new ListNode(val%10);
		resTmp = resTmp->next;
		tmp3 = tmp3->next;
	}
	if (carry==1) resTmp->next = new ListNode(1);
	return res;
}

/*
 * Optimized Iterative Approach
 * Time O(n)
 * Space O(1)
 * [1]->[2]->[3]->[4]->null
 * Note:
 *  use a pointer to a pointer when we need change which element the head pointer points to, otherwise we endup
 *  changing its address and it would no longer be linked to the rest of the list
 */
static void _revLLIter(ListNode** head) {
    if (!head) return;
    ListNode* prev = nullptr;
    ListNode* next = nullptr;
    ListNode* curr = *head;
    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head  = prev;
}
ListNode* reverseListV3(ListNode* head) {
    _revLLIter(&head);
    return head;
}



/*
 * non optimized solution
 * [* * * * * *]
 *
 *  Given linked list: 1->2->3->4->5, and n = 2.
 *	After removing the second node from the end, the linked list becomes 1->2->3->5.
 *	n always valid
 *
 *	Approach:
 *	1. create a vector of pointers
 *	2. from there we can find the right index to remove in one pass
 *
 * */
ListNode* removeNthFromEnd(ListNode* head, int n) {
	ListNode* tmp = head;
	std::vector<ListNode*> nodes;
	while(tmp) {
		nodes.push_back(tmp);
		tmp = tmp->next;
	}
	// [* * * * * (* {*} *) *] if n = 3, len = 9, remove i = 6,
	// we need to link 5 --> 7
	int len = (int)nodes.size();
	if (n==1) {  // remove end
		if (len == 1 || nodes.empty()) return nullptr;
		tmp = nodes[len - n - 1];
		tmp->next = nullptr;
	} else if (len - n == 0) {  // must remove the first element
		head = head->next;
	} else {
		ListNode* tmp_right = nodes[len-n+1]; // len - 1 - n is the target
		ListNode* tmp_left = nodes[len-n-1];
		tmp_left->next = tmp_right;
	}
	return head;
}

/*
		 A:          a1 → a2
		                   ↘
		                     c1 → c2 → c3
		                   ↗
		B:     b1 → b2 → b3
		should run in O(n) time and O(1) space
 */
ListNode* getIntersectionNode(ListNode *headA, ListNode *headB) {
	ListNode* tmpa = headA;
	ListNode* tmpb = headB;
	int cnta = 0, cntb = 0;

	// first find the offset between the two lists
	// [* * *]      --> at 3 we would want to start
	// [* * * * *]  -->
	// return incase we find it beforehand
	while (tmpa||tmpb) {
		if (tmpa==tmpb) return tmpa;
		if (tmpa) {
			cnta++;
			tmpa = tmpa->next;
		}
		if (tmpb) {
			cntb++;
			tmpb = tmpb->next;
		}
	}
	// reset pointers
	tmpa = headA;
	tmpb = headB;


	// offset if neg the cnt b is longer
	int offset = cnta - cntb;

	// offset the longer list
	if (offset == 0) {
		return nullptr;
	} else if (offset < 0) {
		for (int i = 0; i < std::abs(offset); i++)
			tmpb = tmpb->next;
	} else {
		for (int i = 0; i < offset; i++)
			tmpa = tmpa->next;
	}

	// find intersection
	while (tmpa && tmpb) {
		if (tmpa==tmpb) return tmpa;
		tmpa = tmpa->next;
		tmpb = tmpb->next;
	}
	return nullptr;
}

ListNode *getIntersectionNodeV2(ListNode *headA, ListNode *headB) {

}
