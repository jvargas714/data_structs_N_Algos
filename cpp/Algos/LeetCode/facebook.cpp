#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "facebook.h"

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
 Example 2:
	Input: a = "1010", b = "1011"
	Output: "10101"

    1011  -- b
    1110  --
   -----

    stack --> 11001    --> "11001"

 */
std::string addBinary(std::string a, std::string b) {
	std::string result;
	std::stack<char> binStack;

	int alen = (int)a.size();
	int blen = (int)b.size();
	bool carry = false;

	// add up starting at the least sig fig
	int ia = alen-1;
	int ib = blen-1;

	while (ia >= 0 && ib >= 0) {
		if (a[ia]=='0' && b[ib]=='0') {
			if (carry) binStack.push('1');
			else binStack.push('0');
			carry = false;
		} else if (a[ia]=='1' && b[ib]=='1') {
			if (carry) binStack.push('1');
			else binStack.push('0');
			carry = true;
		} else {  // adding 0 and 1
			if (carry) binStack.push('0');
			else binStack.push('1');
		}
		ia--;
		ib--;
	}

	// handle final carry and if strings are different lengths
	if (alen != blen) {
		std::string& tmp = (alen > blen) ? a:b;
		int tmpInd = (ia>=0) ? ia:ib;
		while (tmpInd >= 0) {
			char binval = tmp[tmpInd];
			if (carry) {
				binStack.push(binval == '1' ? '0' : '1');
				carry = (binval == '1');
			}
			else
				binStack.push(binval);
			tmpInd--;
		}
	}

	if (carry) binStack.push('1');

	while (!binStack.empty()) {
		result += binStack.top();
		binStack.pop();
	}
	return result;
}

/*
 optimized solution from V1
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
std::string addBinaryV2(std::string& a, std::string& b) {
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

	for (int i = 0; i < (int)nums.size() - 2; i++) {
		/*
		 * if nums[i] > 0 then there is no way to get it down to zero as the array is sorted and the subsequent
		 * values will only be greater than or equal nums[i]
		 */
		if (nums[i] > 0) break;
		int j = i + 1;
		int k = (int)nums.size()-1;

		// we have three pointers at this point [* * * i j * * * * * k]  <-- k will converge into j
		while ( j < k) {
			if (i > 0 && nums[i] == nums[i-1]) continue;
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

