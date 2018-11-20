#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <cctype>
#include "facebook.h"

/*
jdebug :: great solution --> in java translate to c++ as V3 solution 
    public boolean validPalindrome(String s) {
        int l = -1, r = s.length();
        while (++l < --r) 
            if (s.charAt(l) != s.charAt(r)) return isPalindromic(s, l, r+1) || isPalindromic(s, l-1, r);
        return true;
    }

    public boolean isPalindromic(String s, int l, int r) {
        while (++l < --r) 
            if (s.charAt(l) != s.charAt(r)) return false;
        return true;
    }

 */

// ================================================ helper functions ===================================================
// divide and conquer to find correct sum
static void _minSubRec(int s, const std::vector<int>& nums, int l, int r) {
    
}

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

 */
int minSubArrayLen(int s, std::vector<int> &nums) {
    if (nums.empty()) return 0;
    if (nums.size()==1) return (nums[0]==s ? 1:0);
    _minSubRec(s, nums, 0, nums.size()-1);

}

