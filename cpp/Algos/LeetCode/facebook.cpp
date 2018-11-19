#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "facebook.h"

/*
 * jdebug :: back up
 * bool validPalindromeV2(std::string& s) {
    if (s.size()==1 || s.size()==2) return true;
    int l = 0, r = (int)s.size()-1, removedInd=-1;
    bool removedl = false, removedr = false;
    while (l < r) {
        if (s[l]!=s[r]) {
            if (removedl && removedr) return false;

            // determine whether to remove l or r
            if (r-l == 1) return true;  // by removing one the element left will be the center
            if (s[r-1] == s[l] && !removedr) { // check removing r first helps the situation
                s.erase(s.begin()+r);
                removedr = true;
            }
            else if (s[l+1] == s[r] && !removedl) {  // check removing l instead
                s.erase(s.begin() + l);
                removedl = true;
            }
            else
                return false;
            r--;                // length changed
            continue;
        }
        l++;
        r--;
    }
    return true;
}


 *
 */
// ================================================ helper functions ===================================================
// jdebug :: fix me
bool _validPalindromeRecursive(std::string& orig, std::string& s, bool& removedl, bool& removedr, bool& result) {
    int l = 0, r = (int)s.size()-1;
    while (l < r) {
        if (s[l]!=s[r]) {
            if (removedl && removedr) return false;

            // determine whether to remove l or r
            if (r-l == 1) return true;  // by removing one the element left will be the center

            if (s[r-1] == s[l] && !removedr) { // check removing r first helps the situation
                s.erase(s.begin()+r);
                removedr = true;
                _validPalindromeRecursive(orig, s, removedl, removedr, result);
            }
            else if (s[l+1] == s[r] && !removedl) {  // check removing l instead
                s.erase(s.begin() + l);
                removedl = true;
                _validPalindromeRecursive(orig, s, removedl, removedr, result);
            }
            else
                return false;
            r--;                // length changed
            continue;
        }
        l++;
        r--;
    }
    return true;
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

// optimized solution
/*
 *   * * * * * * * * 0 * *
 *   when processing the mismatch we check if the next element on the left side is
 *   * * [*] * * [*] r * *  << [*] elements will now be compared, they would have to match,
 *   we can try this with removing l as well if that doesn't work
 *
 *   make recursive when swapping
 */
bool validPalindromeV2(std::string& s) {
    if (s.size()==1 || s.size()==2) return true;
    bool result = false;
    bool r = false, l = false;
    std::string tmp(s);
    _validPalindromeRecursive(s, tmp, l, r, result);
}

