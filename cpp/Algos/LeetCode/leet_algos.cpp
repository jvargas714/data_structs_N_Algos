#include <algorithm>
#include <cstdint>
#include <map>
#include "leet_algos.h"
#include "utility.h"


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

/* Problem: #59 */
std::vector<int> count_bits( int num ) {
    std::vector<int> result( 1,0 );
    int mask;
    int cnt = 0;

    for( uint i = 1; i <= num; i++ ) {
        cnt = 0;
        mask = 0x1;
        for( uint j = 0; j < 8*sizeof( int ); j++ ) {
            if( mask & i )
                cnt++;
            mask <<= 1;
        }
        result.push_back( cnt );
    }
    return result;
}

bool operator > ( envelope& env1, envelope& env2 ) {
    return (env1.first > env2.first) && (env1.second > env2.second);
}

int maxEnvelopes(std::vector<envelope>& envelopes) {
    sort( envelopes.begin(), envelopes.end());
    // display( envelopes );
    bool first_fit = false;
    int cnt = 0;

    for( int i = 0; i < envelopes.size()-1; ++i ) {
        if( !first_fit && envelopes[i+1] > envelopes[i] ) {
            cnt+=2;
            first_fit = true;
        }

        if( first_fit && envelopes[i+1] > envelopes[i] ) {
            cnt++;
        }
    }
    return cnt;
}

void display( std::vector<envelope>& envs ) {
    for(auto& el : envs ) {
        std::cout << " (" << el.first << ", " << el.second << "), ";
    }std::cout << std::endl;
}

int climbingSteps( int i, int n, std::vector<int>& memo ) {
    if (i > n) return 0;
    if (i == n) return 1;
    if (memo[i] > 0) return memo[i];
    memo[i] = climbingSteps(i+1, n, memo) + climbingSteps(i+2, n, memo);
    return memo[i];
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

/*
	Divide and conquer solution 0(n)
	Recursive
*/
int maxSubArray4() {
    return 0;
}

/*
 * swap every two nodes, must only swap nodes and not modify them
 * return pointer to the head
 * For example,
 * Given 1->2->3->4, you should return the list as 2->1->4->3.
 */
ListNode* swapPairs(ListNode* head) {
    size_t i = 0;
    ListNode* tmp = head;
    ListNode* nxt;
    while(tmp) {
        nxt = tmp->next;
        tmp->next = tmp;
        tmp = nxt;
    }
	return nullptr;
}

std::vector<int> plusOne(std::vector<int>& digits) {
	int len = digits.size();
	if (len == 1) {
		if (digits[0] < 9) {
			digits[0]++;
			return digits;
		}
		else {
			digits.insert(digits.begin(), 1);
			digits[1] = 0;
			return digits;
		}
	}

	// for larger numbers 
	digits[len - 1]++;
	if (digits[len - 1] < 10)
		return digits;
	else {
		_carry(digits, (len - 1));
	}
	return digits;
}

void moveZeroes(std::vector<int>& nums) {
	int moves = 0;
	int i = 0;
	size_t len = nums.size();
	if (nums.empty())
		return;
	int tmp;
	while (i<(len-1) && (moves<len)) {
		if (!nums[i]) {
			nums.push_back(nums[i]);
			nums.erase((nums.begin() + i));
			moves++;
			continue;
		}
		else {
			i++;
		}
	}
}

// brute force method 0(n^2)
std::vector<int> twoSums(std::vector<int> &nums, int target) {
    size_t len = nums.size();
    for (size_t i = 0; i < len; ++i) {
        for ( size_t j = i+1; j < (len); ++j) {
            if ( (nums[i]+nums[j]) == target )
                return {(int)i, (int)j};
        }
    }
    return {};
}

// [3, 2, 4]
std::vector<int> twoSumsV2(std::vector<int> &nums, int target) {
    int x;
    std::map<int, int>::iterator it;
    std::map<int, int> mp;
    int len = nums.size();

    for (int i = 0; i < len; i++)
        mp[nums[i]] = i;

    for(int i = 0; i < len; i++) {
        x = target - nums[i];
        it = mp.find(x);
        if (it!=mp.end() && it->second!=i)
            return {i, it->second};
    }
    return {};
}

bool _checkRows(const SudokuBoard& board) {

}

bool _checkRow(const std::vector<char>& rw) {
    char el = rw[0];
    for(int i = 1; i < rw.size(); i++) {
        std::cout << "i: " << i << std::endl;
        if ((el == '.') || (rw[i] == '.')) {
            el = rw[i];
            continue;
        }
        if (el == rw[i])
            return false;
        el = rw[i];
    }
    std::cout << "Row is valid" << std::endl;
    return true;
}

bool isValidSudoku(SudokuBoard& board) {
    for(int i = 0; i < board.size(); i++) {
        if( !_checkRow(board[i]) )
            return false;
    }
    return false;
}


