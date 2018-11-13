#include <stack>
#include <algorithm>
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
        1. reverse both
        2. find shortest string
        3. add them up to length of the shortest so we dont go over

    10111
     1110

     reversed

    11101
    0111
    ------

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

    jdebug :: time is much faster but getting incorrect answer
 */
std::string addBinaryV2(std::string& a, std::string& b) {
	std::string result;
    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    int ia=0, ib=0;
    bool carry = false;

    while (ia < a.size() && ib < b.size()) {
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
        ia++;
        ib++;
    }

    // handle if lengths are different
    if (b.size() != a.size()) {
        const std::string& longerStr = (a.size()>b.size()) ? a:b;
        for (const auto& binval : longerStr) {
            if (carry) {
                result += (binval == '1') ? '0':'1';
                carry = (binval == '1');
            }
        }
    } else {
        if (carry) result += "1";
    }
    return result;
}
