#include <algorithm>
#include <cstddef>
#include <cstring>
#include <deque>            // std::deque
#include <iomanip>
#include <map>
#include <numeric>          // std::accumulate
#include <queue>            // std::priority_queue
#include <sstream>          // string stream
#include <unordered_map>    // std::unordered_map

#include "leet_algos.h"
#include "utility.h"

// globals
std::vector<bool> g_versions;
int g_nVersions;
int g_badVersion;


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

std::vector<int> plusOne(std::vector<int>& digits) {
	int len = (int)digits.size();
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

// my solution 20ms
void moveZeros(std::vector<int>& nums) {
	int moves = 0;
	int i = 0;
	size_t len = nums.size();
	if (nums.empty())
		return;
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

// optimized solution 16ms
// [* * 0 0 * * 0]
void moveZerosV2(std::vector<int>& nums) {
    int i = 0, j = 0;
    for (i = 0; i < nums.size(); ++i) {
        if (0 == nums[i])
            continue;

        nums[j] = nums[i];
        ++j;
    }

    // replace back portion of array with zeros
    for (; j < nums.size(); ++j)
        nums[j] = 0;
}

// best version 100%
void moveZerosV3(std::vector<int>& nums) {
    if (nums.empty()) return;
    int j = 0;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (nums[i] != 0)
            nums[j++] = nums[i];
    }
    for (int i = j; i < nums.size(); i++)
        nums[i] = 0;
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

    // fill map up with {element : index}
    for (int i = 0; i < len; i++)
        mp[nums[i]] = i;

    // x = target - el;
    // search for x in input array
    for(int i = 0; i < len; i++) {
        x = target - nums[i];
        it = mp.find(x);
        if (it!=mp.end() && it->second!=i)
            return {i, it->second};
    }
    return {};
}

bool _checkRows(const SudokuBoard& board) {
    for (const auto& row: board) {
        if(!_checkDuplicate(row))
            return false;
    }
    return true;
}

bool _checkDuplicate(const std::vector<char>& rw) {
    std::map<char, char> valMap;
    for(const auto& el : rw) {
        auto mapIt = valMap.find(el);
        if (mapIt == valMap.end()) {
            valMap[el] = el;
        } else {
            if (mapIt->second != '.')
                return true;
        }
    }
    return false;
}

void _addColsElement(SudokuColumns& cols, const SudokuRow& row, int colIndex) {
    unsigned int i = 0;
    for(auto el: row)
        cols[i++].push_back(el);
}

void _initColMap(std::map<int, SudokuRow>& cols) {
    for (int i = 0; i < 9; i++)
        cols[i] = SudokuRow(9, '.');
}

bool _checkCols(std::map<int, SudokuRow>& cols) {
    LOG << "checking columns" << std::endl;
    for(const auto& col: cols) {
        if (_checkDuplicate(col.second))
            return false;
    }
    return true;
}

bool _checkSquares(SudokuBoard &board) {
    LOG << std::endl;
    SudokuRow flattenedBox;
    int box = 1;
    int colOffset = 0;
    int rowOffset = 0;
    while(box<=9) {
        LOG << "row offset: " << rowOffset << " col Offset: " << colOffset << " box: " << box << std::endl;
        for(int i = rowOffset; i < (rowOffset+3); i++) {
            for(int j = colOffset; j < (colOffset+3); j++) {
                flattenedBox.push_back( board[i][j] );
            }
        }
        display(flattenedBox, 3);
        if (_checkDuplicate(flattenedBox)) {
            LOG << "invalid " << std::endl;
            return false;
        };
        flattenedBox.clear();
        box++;

        // reset which box is targeted
        if (colOffset == 6) {
            colOffset = 0;
            rowOffset += 3;
        } else {
            colOffset += 3;
        }
    }
    return true;
}

// my submission
bool isValidSudoku(SudokuBoard& board) {
    LOG << std::endl;
    displayMatrix(board);
    std::map<int, SudokuRow> cols;
    _initColMap(cols);
    for(int i = 0; i < board.size(); i++) {
        _addColsElement(cols, board[i], i);
        if( _checkDuplicate(board[i]) )  // check for valid condition on rows
            return false;
    }
    // check for valid condition on cols
    if(!_checkCols(cols))
        return false;

    // check for valid squares
    return _checkSquares(board);
}

// average speed submission
bool isValidSudokuV2(SudokuBoard &board) {

    bool seen_digits[9];
    for (int i = 0; i < 9; i++) {
        seen_digits[i] = false;
    }

    // Check rows
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char c = board[i][j];
            if (c == '.') {
                continue;
            }
            int index = c - '0' - 1;
            if (seen_digits[index]) {
                return false;
            }
            seen_digits[index] = true;
        }
        for (int i = 0; i < 9; i++) {
            seen_digits[i] = false;
        }
    }



    // Check columns
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char c = board[j][i];
            if (c == '.') {
                continue;
            }
            int index = c - '0' - 1;
            if (seen_digits[index]) {
                return false;
            }
            seen_digits[index] = true;
        }
        for (int i = 0; i < 9; i++) {
            seen_digits[i] = false;
        }
    }

    for (int i = 0; i < 9; i++) {
        seen_digits[i] = false;
    }

    // Check boxes
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    char c = board[x * 3 + i][y * 3 + j];
                    if (c == '.') {
                        continue;
                    }
                    int index = c - '0' - 1;
                    if (seen_digits[index]) {
                        return false;
                    }
                    seen_digits[index] = true;
                }
            }
            for (int i = 0; i < 9; i++) {
                seen_digits[i] = false;
            }
        }
    }

    return true;
}

// fastest c/c++ submission
bool isValidSudokuV3(SudokuBoard& board) {

    std::vector<int> check = {1,2,3,4,5,6,7,8,9};
    for (int i = 0; i <board.size(); i++) {
        std::vector<int> checkrow = check;
        for (int j = 0; j < board[0].size() ; ++j) {
            if (board[i][j] != '.') {
                if (checkrow[board[i][j] - '1'] == board[i][j] - '0') {
                    checkrow[board[i][j] - '1'] = 0;
                } else {
                    return false;
                }
            }
        }
    }

    for (int j = 0; j < board[0].size() ; ++j) {
        std::vector<int> checkcol = check;
        for (int i = 0; i <board.size(); i++) {
            if (board[i][j] != '.') {
                if (checkcol[board[i][j] - '1'] == board[i][j] - '0') {
                    checkcol[board[i][j] - '1'] = 0;
                } else {
                    return false;
                }
            }
        }
    }

    for (int r = 0; r <board.size(); r = r + 3) {
        for (int l = 0; l < board[0].size() ; l = l + 3) {
            std::vector<int> checkblock = check;
            for (int i = r ; i < r + 3 ; ++i) {
                for (int j = l; j < l + 3; ++j) {
                    if (board[i][j] != '.') {
                        if (checkblock[board[i][j] - '1'] == board[i][j] - '0') {
                            checkblock[board[i][j] - '1'] = 0;
                        } else {
                            return false;
                        }
                    }
                }
            }

        }
    }

    return true;
}

// short solution using bitwise ops
bool isValidSudokuV4(SudokuBoard& board) {
    std::vector<short> col(9, 0);
    std::vector<short> block(9, 0);
    std::vector<short> row(9, 0);
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            if (board[i][j] != '.') {
                int idx = 1 << (board[i][j] - '0');
                if (row[i] & idx || col[j] & idx || block[i/3 * 3 + j / 3] & idx)
                    return false;
                row[i] |= idx;
                col[j] |= idx;
                block[i/3 * 3 + j/3] |= idx;
            }
        }
    return true;
}

// rotate an nxn matrix inplace clockwise
// my submission 6ms
void rotate(IntMatrix& matrix) {
    auto len = static_cast<uint32_t>( matrix[0].size());
    uint32_t numLayers = len / 2;
    for (uint32_t i = 0; i < numLayers; i++)
        _rotateLayer(matrix, i);
}

// fastest submission 4ms
void rotateV2(IntMatrix& matrix) {
    int start = 0, end = static_cast<int>(matrix.size()-1);
    while(start<end){
        for(int i=start; i<end; i++){
            int offset = i-start;
            int tmp = matrix[start][i];
            matrix[start][i] = matrix[end-offset][start];
            matrix[end-offset][start] = matrix[end][end-offset];
            matrix[end][end-offset] = matrix[start+offset][end];
            matrix[start+offset][end] = tmp;
        }
        start++; end--;
    }
}

// rotates layer of a matrix
// faces --> face1: first row; face2: right vertical; face3: last row; face4: left vertical
void _rotateLayer(IntMatrix& matrix, uint32_t layer) {
    size_t i;
    uint32_t cnt = 0;
    size_t n = matrix[0].size();
    size_t numRotations = n-1-2*layer;
    do {
        // values to save from the shifts
        int ur = matrix[layer][n-1-layer];
        int br = matrix[n-1-layer][n-1-layer];
        int bl = matrix[n-1-layer][layer];

        // rotate face 1 (top horiz)
        for (i = (n-1-layer); i > layer; i--)
            matrix[layer][i] = matrix[layer][i - 1];

        // rotate face 2 (vert right)
        for (i = (n-1-layer); i > (layer+1); i--)
            matrix[i][n-1-layer] = matrix[i-1][n-1-layer];
        matrix[layer+1][n-1-layer] = ur;

        // rotate face 3 (bottom horiz)
        for (i = layer; i < (n-1-layer); i++)
            matrix[n-1-layer][i] = matrix[n-1-layer][i+1];
        matrix[n-1-layer][n-2-layer] = br;

        // rotate face 4 (ver left)
        for (i = layer; i < (n-1-layer); i++)
            matrix[i][layer] = matrix[i+1][layer];
        matrix[n-2-layer][layer] = bl;
        cnt++;
    } while(cnt < numRotations);
}

// best solution
std::string reverseString(std::string s) {
    // traverse only half the string
    // fill in from front and from end at the same time swapping chars
    for (int i = 0; i < s.size() / 2; i++) {
        char t = s[i];
        s[i] = s[s.size() - i-1];
        s[s.size() - i-1] = t;
    }
    return s;
}

// obvious slow solution 
int firstUniqChar(std::string s) {
	std::map<char, int> charMap;
	for (const auto& ch : s) {
		auto it = charMap.find(ch);
		if (it == charMap.end()) {
			charMap[ch] = 1;
		}
		else {
			charMap[ch]++;
		}
	}

	// find first char with only 1 occurence 
	for (int i = 0; i < s.size(); i++) {
		auto it = charMap.find(s[i]);
		if (it->second == 1)
			return i;
	}
	return -1;
}

// different approach but slow
// 127 ms
int firstUniqCharV2(std::string s) {
	std::map<char, int> charMap;
	uint32_t res = INT32_MAX;
	for(int i = 0; i < s.size(); i++) {
        auto it = charMap.find(s[i]);
        if (it == charMap.end())
            charMap[s[i]] = i;
        else
            charMap[s[i]] = INT32_MAX;
    }
    for (const auto& ch : s)
        res = (charMap[ch] < res) ? charMap[ch]:res;

	    return (res != INT32_MAX) ? res : -1;
}

// better solution above average 40ms
int firstUniqCharV3(std::string s) {
    std::vector<int> v(26,0);
    for (char i : s) {
        v[i -'a']++;
    }
    for(int i =0; i<s.size(); i++){
        if(v[s[i]-'a']==1)
            return i;
    }
    return -1;
}

int firstUniqCharV4(std::string s) {
    int charArr[26];
    int cnt = 0;
    std::memset(charArr, 0, sizeof(charArr));
    for (int i = 0; i < s.size(); i++)
        charArr[s[i] - 'a']++;

    for (const auto &ch : s) {
        if (charArr[ch - 'a'] == 1) return cnt;
        cnt++;
    }
    return -1;
}

// simple approach using a vector, can assume all lower case chars
// O(n) solution 11ms 84.92 percentile
bool validAnaGram(std::string& s, std::string& t) {
    if (s.size() != t.size())
        return false;
    std::vector<int> charVect(26, 0);
    for (const auto& ch: s)
        charVect[ch - 'a']++;
    for (const auto& ch: t) {
        if (charVect[ch - 'a'] == 0)
            return false;
        else
            charVect[ch-'a']--;
    }
    return true;
}

// even better solution 4ms
bool validAnaGramV2(std::string& s, std::string t) {
    if(s.size()!=t.size())
        return false;
    int chCount[26]={0};

    // both strings should cancel eachothers counters out if they are anagrams
    // ie all values in the table should have 0
    for(int i=0;i<s.size();i++){
        chCount[s[i]-'a']++;
        chCount[t[i]-'a']--;
    }

    // makeing sure all counters are zero
    for (int i : chCount) {
        if(i !=0)
            return false;
    }
    return true;
}

// mysolution: 95.16 percentile solution 10ms
bool validPalindrome(std::string& s) {
    if (s.empty())
        return true;
    size_t j;
    size_t i=0;

    // lower case all chars
    std::transform(s.begin(), s.end(), s.begin(),
                   [](char ch) -> char { return static_cast<char>(std::tolower(ch)); });

    // remove non letter characters
    s.erase(
            std::remove_if(s.begin(), s.end(), [](char ch)-> bool {
                return ( !((ch >= 'a' && ch <= 'z') ||
                           (ch >= '0' && ch <= '9')) );
            }),
    s.end());
    std::cout << "modified string: --> \n" << s << std::endl;
    j = s.size()-1;
    for(; i < s.size()/2; i++) {
        if(s[i] != s[j]) return false;
        j--;
    }

    return true;
}

int _cleanStrToInt(const std::string& val, int pwr, int sign) {
    unsigned int res = 0;
    std::cout << "input: " << val << std::endl;
    // check for out of range
    if (val.size() > 10) {
        return ((sign == 1) ? INT32_MAX:INT32_MIN);
    }
    for (const auto& ch: val) {
        res += (ch-48)*pwr;
        pwr/=10;
    }
    std::cout <<"val: " << res << std::endl;
    if (res >= 2147483648)
        return ((sign == 1) ? INT32_MAX:INT32_MIN);
    else
        return (sign*res);
}

int myAtoi(const std::string& str) {
    if (str.empty())
        return 0;
    std::string tmp;
    int sign = 1;
    int pwr = 0;
    bool started = false;
    bool signHappened = false;
    const std::map<char, int> charMap = {
            {'0', 0},
            {'1', 1},
            {'2', 2},
            {'3', 3},
            {'4', 4},
            {'5', 5},
            {'6', 6},
            {'7', 7},
            {'8', 8},
            {'9', 9}
    };
    for (auto ch: str) {
        if ((ch==0x20||ch==0x09)) {
            if (started) break;
            continue;
        }
        if ((ch=='-'||ch=='+') && !signHappened) {
            sign = ((ch=='+') ? 1:-1);
            signHappened = true;
            started = true;
            continue;
        }
        auto it = charMap.find(ch);
        if (it!=charMap.end()) {
            started = true;
            tmp += it->first;
            if (!pwr) pwr = 1;
            else pwr *= 10;
        } else {
            break;
        }
    }
    if (tmp.empty())
        return 0;
    else
        return _cleanStrToInt(tmp, pwr, sign);
}

// optimized solution 
int myAtoiV2(const std::string& str) {
    if (str.empty())
        return 0;

    // trim
    auto offset = 0;
    while ((str[offset] == ' ' || str[offset] == '0') && offset < str.length())
        offset++;

    auto sign = 1;
    // sign
    if (str[offset] == '-') {
        sign = -1;
        ++offset;
    }
    else if (str[offset] == '+') {
        sign = 1;
        ++offset;
    }

    auto ret = 0;
    for (auto i = offset; i < str.length(); ++i) {
        auto c = str[i];
        auto val = 0;
        if (c >= '0' && c <= '9')
            val = c - '0';
        else
            break;

        if (ret > INT32_MAX / 10 || (ret == INT32_MAX / 10 && val > 7))
            return sign > 0 ? INT32_MAX : INT32_MIN;

        ret *= 10;
        ret += val;
    }

    return sign * ret;
}

int strStr(std::string haystack, std::string needle) {
	if (needle.empty()) return 0;
	int ind = -1;
	int j = 0;
	size_t found = 0;
	size_t needleLen = needle.size();
	int i = 0;
	for(; i < haystack.size(); i++) {
		// found condition 
		if (found == needleLen)
			break;

		if (haystack[i] == needle[j]) {
			if (ind==-1)
				ind = i;
			j++;
			found++;
		}
		else {  // reset finding substr
			ind = -1;
			j = 0;
			i = (found) ? static_cast<int>(i-(found)):i;
			found = 0;
		}
	}
	if (found != needleLen) return -1;
	return ind;
}

int _getCount(const std::string& str, const int& offset) {
	if (str.size() == 1) {
		return 1;
	}
	
	int cnt = 1;
	char tmp = str[offset];
	for (int i = offset+1; i < str.size(); i++) {
		if (str[i] == tmp)
			cnt++;
		else
			return cnt;
	}
	return cnt;
}

void _genCntNSay(std::string& currTerm, std::string& nextTerm) {
	std::string interTerm = currTerm;
	int offset = 0;
	int cnt;
	
	while (offset < currTerm.size()) {
		char tmp = currTerm[offset];
		cnt = _getCount(currTerm, offset);
		nextTerm += std::to_string(cnt);
		nextTerm += tmp;
		offset += cnt;

	}
}

std::string countAndSay(int n) {
	if (!n) return "";
	std::string currTerm = "1";
	std::string nextTerm;

	// generate the sequence up to the nth term
	for (int i = 1; i < n; i++) {
		// std::cout << "currTerm: " << currTerm << std::endl;
		_genCntNSay(currTerm, nextTerm);
		currTerm = nextTerm;
		nextTerm = "";
	}
	return currTerm;
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


void _dive(TreeNode* node, TreeNode* root, int& deep, int& deepest) {
        if (!node||node->val==INT32_MIN) {
            std::cout << "deep: " << deep << " deepest: " << deepest << std::endl;
            if (deep > deepest)
                deepest = deep;
            return;
        }
        deep++;
        _dive(node->left, root, deep, deepest);
        if (node == root)
            deep = 1;
        _dive(node->right, root, deep, deepest);
        return;
}

int maxDepth(TreeNode* root) {
    if (!root) return 0;
    TreeNode* tmp = root;
    int maxDepth = 0;
    int deep = 0;
    _dive(tmp, root, deep, maxDepth);
    return maxDepth;
}

int maxDepthV2(TreeNode* root) {
    if (!root) return 0;
    else {
        // traverse down left side and then right side first 
        int lheight = maxDepthV2(root->left);
        int rheight = maxDepthV2(root->right);

        // return larger of the sides depth 
        if (lheight>rheight) return (lheight+1);
        else return (rheight+1);
    }
}

int maxDepthV3(TreeNode *root) {
    if(root == nullptr)
        return 0;

    int res = 0;
    std::queue<TreeNode *> q;
    q.push(root);
    while(!q.empty()) {
        ++res;
        for(int i = 0, n = (int)q.size(); i < n; ++i) {
            TreeNode *p = q.front();
            q.pop();
            if(p->left != nullptr)
                q.push(p->left);

            if(p->right != nullptr)
                q.push(p->right);
        }
    }
    return res;
}


bool _bstCheck(TreeNode* root, TreeNode* _min = nullptr, TreeNode* _max = nullptr) {
	if (!root) return true;

	if (_min && root->val <= _min->val) return false;
	if (_max && root->val >= _max->val) return false;
	return _bstCheck(root->left, _min, root) &
		_bstCheck(root->right, root, _max);
}

bool isValidBST(TreeNode* root) {
	if (!root) return true;
	return _bstCheck(root);
}

bool _checkSymmetric(TreeNode* lft, TreeNode* rht) {
    if (!lft && !rht) return true;

    if ((lft&&rht) && (lft->val==rht->val) ) {
        return _checkSymmetric(lft->left, lft->right) &&
                    _checkSymmetric(rht->right, rht->left);
    } else {
        return false;
    }
}


//      1
//    /  \
//   2    2
//  / \  / \
// 3  4 4  3
// [1,2,2,null,3,null,3]
// [2,3,3,4,5,5,4,null,null,8,9,9,8]
bool isSymmetric(TreeNode* root) {
	if (!root) return true;
	return _checkSymmetric(root->left, root->right);
}

// provided level will be index of the vector 
void _collectGivenLevel(TreeNode* root, int level, std::vector<int>& data) {
    if (!root) 
        return;
    if (level == 0) {
        data.push_back(root->val);
    }
    else if (level > 0) {
        _collectGivenLevel(root->left, level-1, data);
        _collectGivenLevel(root->right, level-1, data);
    }
}

// display tree reading it from left to right 
VectOfVect levelOrder(TreeNode* root) {
    if (!root) return {{}};
    TreeNode* tmp = root;
    int height = maxDepthV2(tmp);
    tmp = root; 
    VectOfVect result(height);
    for (int lvl = 0; lvl < height; lvl++) {
        _collectGivenLevel(root, lvl, result[lvl]);
    }
    return result; 
}

void _DFS(VectOfVect &res,TreeNode* root,int level){
    if(root==nullptr)
        return;
    if(res.size()==level)
        res.push_back(std::vector<int>());
    res[level].push_back(root->val);
    _DFS(res,root->left,level+1);
    _DFS(res,root->right,level+1);
}

// faster more efficient version (6ms)
VectOfVect levelOrderV2(TreeNode* root) {
    if(!root)
        return VectOfVect();
    VectOfVect res;
    _DFS(res,root,0);
    return res;
}

// iterative using queue solution, left to right
VectOfVect levelOrderV3(TreeNode* root) {
    std::queue<TreeNode*> nodeQue;
    VectOfVect result;
    if (!root)
        return result;
    nodeQue.push(root);
    while (!nodeQue.empty()) {
        auto lvlSize = (int)nodeQue.size();
        std::vector<int> curLvl;
        for (int i = 0; i < lvlSize; i++) {
            TreeNode* nd = nodeQue.front();
            nodeQue.pop();
            if (nd->left) nodeQue.push(nd->left);
            if (nd->right) nodeQue.push(nd->right);
            curLvl.push_back(nd->val);
        }
        result.push_back(curLvl);
    }
    return result;
}

TreeNode* _insertData(int l, int r, std::vector<int>& data) {
    if ( l>r )
        return nullptr;
    int midpt = (l+r)/2;
    auto root = new TreeNode(data[midpt]);
   root->left = _insertData(l, midpt-1, data);
   root->right = _insertData(midpt+1, r, data);
   return root;
}

TreeNode* sortedArrayToBST(std::vector<int>& data) {
    if (data.empty()) return nullptr;
    return _insertData(0, (int)(data.size()-1), data);
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
    rmap['I'] = 1;
    rmap['V'] = 5;
    rmap['X'] = 10;
    rmap['L'] = 50;
    rmap['C'] = 100;
    rmap['D'] = 500;
    rmap['M'] = 1000;
    int result = 0;
    char prev = '\0';
    for (const auto& ch: rnum) {
        result += rmap[ch];
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

// Write a function that takes an unsigned integer and returns
// the number of '1' bits it has (also known as the Hamming weight).
int hammingWeight(uint32_t n) {
    int cnt = 0;
    uint8_t byte;
    uint8_t mask = 0x1;
    for (int i = 0; i < 4; i++) {
        byte = *((uint8_t*)(&n)+i);
        for (int j = 0; j < 8; j++) {
            if (byte & (mask<<j))
                cnt++;
        }
    }
    return cnt;
}

int hammingWeightV2(uint32_t n) {
    int cnt = 0;
    uint32_t mask = 0x1;
        for (int j = 0; j < 32; j++) {
            if (n&mask)
                cnt++;
            mask <<= 1;
        }
    return cnt;
}

int hammingDistance(int x, int y) {
    int dist = 0;
    int mask = 0x1;
    for (int i = 0; i < 32; i++) {
        if ((int)(x&mask) != (int)(y&mask)) dist++;
        mask <<= 1;
    }
    return dist;
}

// Reverse bits of a given 32 bits unsigned integer
uint32_t reverseBits(uint32_t n) {
    std::vector<int> bits;
    uint32_t result = 0;
    for (int i = 0; i < 32; i++)
        bits.push_back( (n >> i) & 1 );
    for (int i = 0; i < 32; i++)
        result += bits[31-i] * (1<<i);
    return result;
}

/*
Input: 5
Output:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
*/
std::vector<std::vector<int>> generatePascalsTriangle(int numRows)
{
	std::vector<std::vector<int>> triangle(numRows);
	for (int i = 0; i < numRows; i++) {
		std::vector<int>& tmp = triangle[i];
		for (int j = 0; j < (i + 1); j++) {
			if (j == 0 || j == i ) {
				tmp.push_back(1);
				continue;
			}
			tmp.push_back( (triangle[i - 1][j-1] + triangle[i - 1][j]) );
		}
	}
	return triangle;
}

// {[]}
bool isValidParenthesisStr(std::string& str) {
	if (str.empty()) return true;
	if (str.size() % 2) return false;
	std::stack<char> stkOpen, stkClose;
	char tmp;
	
	for (const auto& ch : str) {
		if (ch == '[' || ch == '(' || ch == '{')
			stkOpen.push(ch);
		else {  // closing character 
			if (!stkOpen.empty())
				tmp = stkOpen.top();
			else return false;
			
			if (tmp == '[' && ch == ']')
				stkOpen.pop();
			else if (tmp == '(' && ch == ')')
				stkOpen.pop();
			else if (tmp == '{' && ch == '}')
				stkOpen.pop();
			else {
				stkClose.push(ch);
			}
		}
	}
	if (stkOpen.size() != stkClose.size()) return false;
	for (size_t j = 0; j < stkClose.size(); j++) {
	    if (stkClose.top() != stkOpen.top()) return false;
	}
    return true;
}

bool isValidParethesisStrV2(std::string s) {
    std::stack<char> stkOpen;
    for (const auto& ch : s) {
        if (ch == '{' || ch == '[' || ch == '(') {
            stkOpen.push(ch);
        } else if (!stkOpen.empty()) {
            if (ch == ']' && stkOpen.top() != '[') return false;
            else if (ch == '}' && stkOpen.top() != '{') return false;
            else if (ch == ')' && stkOpen.top() != '(') return false;
            stkOpen.pop();
        } else
            return false;
    }
    if (!stkOpen.empty()) return false;
    return true;
}

// needs to run in linear runtime with 0(1) mem complexity
int missingNumber(std::vector<int>& nums) {
    auto el = std::find_if(nums.begin(), nums.end(), [](auto el){ return el == 0; });
    if (el == nums.end())
        return 0;
    LOG << "el: " << *el << END;
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    LOG << "sum: " << sum << END;
    int targetSum = 0;
    int tmp = 1;
    int val = 1;
    for (int i = 1; i < nums.size()+1; i++) {
        targetSum += val++;
    }
    LOG << "targetSum: " << targetSum << END;
    return targetSum-sum;
}

// using the length returned by your function, it prints the first len elements.
size_t removeDuplicates(std::vector<int> &nums) {
    int count = 0;
    size_t n = nums.size();
    for(int i = 1; i < n; i++){
        if(nums[i] == nums[i-1]) count++;
        else nums[i-count] = nums[i];
    }
    return n-count;
}

// inplace remove duplicates
// [0 0 1 1 1 3 3]
int removeDuplicatesV2(std::vector<int> &nums) {
    if (nums.empty()||nums.size()==1) return (int)nums.size();
    int prev = nums[0];
    int j = 1;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] != prev)
            nums[j++] = nums[i];
        prev = nums[i];
    }
    return j;
}


// inplace 0(1) mem
// [* * *]  * *
void rotateVector(std::vector<int> &nums, int k) {
    int ind;
    auto n = (int)nums.size();
    int offset = k % n;
    for (int i=0; i<n; i++) {
        ind = i + offset;
        if (ind>=n)
            ind-=n;
        nums[i]=nums[ind];
    }
}

/*
Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? 
Find all unique triplets in the array which gives the sum of zero.
Approach:
	Overall: Sort array, then, find indices in different parts of the array, add them up and see if they sum to zero 
				[* * i j-> * * * * * * * * <-k]. Find a negative value index for i, set j on next element and k and last
				after that converge j and k together creating different combinations of i j k the ones that add to zero 
				will be saved as part of the solution. Note that for any duplicates we can skip since the entries need 
				to be unique arrays. Note the movement of the indices only makes sense since the array is sorted before all
				of this. The solution set must NOT contain duplicate triplets.
	Steps:
		0. sort array 
		1. index i: 
			- skip duplicates, 
			- if we hit positve values then stop processing all together as 3 positve values will never add to zero 
		2. index j: 
			- set to 1 position ahead of i
		3. index k: 
			- set to last element in array 
*/
std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
	if (nums.size() < 3)
		return {  };
	// 1. sort 
	std::sort(nums.begin(), nums.end());
	std::vector<std::vector<int>> result;
	int i, sum;
	int j = 0;
	int k = 0;
	for (i = 0; i < nums.size() - 2; i++) {
		if (i > 0 && nums[i] == nums[i - 1]) continue;	// skip duplicates to ensure that each array is unique 
		if (nums[i] > 0) break;							// stop processing at positive values as they will never add to zero
		j = i + 1;										// set second index, 1 ahead of i 
		k = nums.size() - 1;							// third index to last element
		while (j < k) {
			if (j > i+1 && nums[j] == nums[j - 1]) {
				j++;
				continue;
			}
			if (nums[i] + nums[j] > 0) break;  // already above zero, no point in using k as it has no change to sum to zero 
			sum = nums[i] + nums[j] + nums[k];
			if (sum < 0) j++;
			else if (sum > 0) k--;
			else {
				result.emplace_back(
					std::initializer_list<int>{ nums[i], nums[j], nums[k] }
				);
				j++;
				k--;
			}
		}
	}
	return result;
}

/*
	A straight forward solution using O(mn) space is probably a bad idea.
	A simple improvement uses O(m + n) space, but still not the best solution.
	Could you devise a constant space solution?
*/
void setZeroes(IntMatrix& matrix)
{
	bool firstCol = false;
	bool firstRow = false;
	int numRows = (int)matrix.size();
	int numCols = (int)matrix[0].size();

	// flag rows and columns to be 0'd out
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			if (!matrix[i][j]) {
				matrix[i][0] = 0;
				matrix[0][j] = 0;
				if (i == 0) firstRow = true; 
				if (j == 0) firstCol = true; 
			}
		}
	}

    // set marked rows to zero
    for (int i = numRows-1; i > 0; i--) {
	    if (matrix[i][0] == 0)
	        for (auto& el : matrix[i])
	            el = 0;
	}

	// set marked columns
    for (int i = numCols-1; i > 0; i--) {
	    if (matrix[0][i] == 0)
	        for (int j = numRows-1; j > 0; j--)
	            matrix[j][i] = 0;
	}

	// if first element of the first row was marked, zero out that row
    if (firstRow)
        for (auto& el : matrix[0]) el = 0;

	// if the first element of the first column was marked, we zero out that column
    if (firstCol)
	    for (auto& row : matrix) row[0] = 0;
}

// Space Complexity 0(n)
// Runtime Complexity 0(n*m)
// where n = size of strs,
// and m = number of keys in the map
StrMatrix groupAnagrams(std::vector<std::string> &strs) {
    StrMatrix result;
    std::map<std::string, std::vector<std::string>> anaMap;
    std::string key;
    for (auto& str : strs) {
        key = str;
        std::sort(key.begin(), key.end());
        auto entry = anaMap.find(key);
        if (entry == anaMap.end()) {
            anaMap[key] = { str };
        } else {
            anaMap[key].push_back(str);
        }
    }

    // fill result
    for (auto& entry : anaMap) {
        std::vector<std::string> tmpVect;
        for (auto& el : entry.second) {
            tmpVect.push_back(el);
        }
        result.push_back(tmpVect);
    }
    return result;
}

// use map<std::string, int> map to keep the key and the index it came from
StrMatrix groupAnagramsV2(std::vector<std::string> &strs) {
    std::vector<int> prime;
    int c=2;
    for(int i=0;i<26;i++){
        while(!isPrime(c))
            c++;
        prime.push_back(c++);
    }
    std::vector<std::vector<std::string>> ret;
    std::map<int,std::vector<std::string>> mp;
    for(auto &str : strs){
        int tmp = 1;
        for(int i=0;i<str.size();++i)
            tmp *= prime[str[i]-'a'];
        mp[tmp].push_back(str);
    }
    for(auto &m:mp)
        ret.push_back(m.second);
    return ret;
}

// use a map to keep track of character and the index it came from
// when a duplicate is found we can reposition i
int lengthOfLongestSubstring(const std::string& str) {
    if (str.size() == 1) return 1;
    int i = 0;
    int longest = 0;
    auto len = static_cast<int>(str.size());
    std::map<char, int> charMap; // mapping character to its index
    while (i<len) {
        auto it = charMap.find(str[i]);
        if (it == charMap.end()) {
            charMap[str[i]] = i;
        } else {  // char has already been seen
            if (charMap.size() > longest) {
                longest = static_cast<int>(charMap.size());
            }
            i = it->second;
            charMap.clear();
        }
        i++;
    }
    if (charMap.size() > longest) return static_cast<int>(charMap.size());
    else return longest;
}

// optimized verison (not working yet)
// runtime O(n) solution
int lengthOfLongestSubstringV2(const std::string& str) {
	if (str.empty() || str.size() == 1) return str.size();
	auto len = (int)str.size();
	int start = 0, currLen = 0, longest = 0;
	std::map<char, int> charMap; // <char, index>
	for (int i = 0; i < str.size(); i++) {
		char currChar = str[i];
		start = std::max(
			start,
			((charMap.find(currChar) != charMap.end()) ? charMap[currChar] + 1 : 0)
		);
		longest = std::max(i - start + 1, longest);
		charMap[str[i]] = i;
	}
	return longest;
}

// using two pointers start and end
// abcabcbb
// 'a' end = 1 {a, 1}
// 'b'
int lengthOfLongestSubstringV3(const std::string& str) {
    if (str.empty()) return 0;
    auto len = (int)str.size();
    int prevIndex=0, curLen=1, longest=1;

    // 256 different chars
    int charMap[256];
    std::memset(charMap, -1, sizeof(charMap));

    // first char already processed
    charMap[str[0]] = 0;  // a

    /*
     * 0(n) solution one pass through string. Can think of this as a window passing through
     * the string. When a duplicate is found the current substring len is updated this is
     * essentially the distance from current index and one past the char at prev index
     * "a b c d e f a"
     *    j         i  --> str[j:i] inclusive is the new current substring the
     *    length would be i-j --> 6-1+1, add one to compensate for index starting at 0
     */
    for (int i = 1; i < len; i++) {
        prevIndex = charMap[str[i]];
        // check if char has been processed or if i is not part of the current substring (i-curLen)
        if (prevIndex == -1 || i - curLen > prevIndex) {
            curLen++; // 2
        } else {
            if (curLen > longest)
                longest = curLen;
            curLen = i - prevIndex;
        }
        // save index of processed char
        charMap[str[i]] = i;
    }
    if (curLen > longest)
        longest = curLen;
    return longest;
}

// ["b","l","u","e"," ","i","s"," ","s","k","y"," ","t","h","e"]
// simple solution (terrible)
// runtime: O(n^2) where n is num of chars
void reverseWords(std::vector<char>& str) {
    int fromEnd = 0;
    std::string word;
    std::vector<char> revWords;
    for (auto& ch : str) {
        if (ch != ' ') {
            word += ch;
        } else {
            std::reverse(word.begin(), word.end());
            for (auto chtmp : word)
                revWords.insert(revWords.end()-fromEnd++, chtmp);
            revWords.insert(revWords.end()-fromEnd++, ' ');
            word = "";
        }
    }
    std::reverse(word.begin(), word.end());
    for (auto chtmp : word)
        revWords.insert(revWords.end()-fromEnd++, chtmp);
    str = revWords;
}

void reverseWordsV2(std::vector<char>& str) {
    int cnt = 0;
    int offset = 0;
    std::vector<char> revWords;
    for (auto& ch : str) {
        if (ch == ' ') {
            cnt++;
            revWords.insert(revWords.begin(), ch);
            offset = cnt;
            continue;
        }
        revWords.insert(revWords.begin()+cnt-offset, ch);
        cnt++;
    }
    str = revWords;
}

// optimized
// reverse entire string
// move j past the first word
// reverse word between i and j
// reset iterators to be at the beginning of the next word
void reverseWordsV3(std::vector<char> &str) {
    std::reverse(str.begin(), str.end());
    std::vector<char>::iterator i, j;
    i = j = str.begin();
    while (j != str.end()) {
        while (j != str.end() && !isspace(*j)) {
            ++j;
        }
        std::reverse(i, j);

        //
        if (j!=str.end()) {
            i = j = j+1;
        }
    }
}

// Given a non-empty array of integers, return the third maximum number in this array.
// If it does not exist, return the maximum number.
int thirdMax(const std::vector<int> &nums) {
    if (nums.empty()) return 0;
    if (nums.size() < 3) {
        return *std::max_element(nums.begin(), nums.end());
    }
    int64_t mmax=INT64_MIN, secondMax=INT64_MIN, thirdMax=INT64_MIN;
    for (auto& el : nums) {
        if (el > mmax) {
            thirdMax = secondMax;
            secondMax = mmax;
            mmax = el;
        } else if (el>secondMax && el!=mmax) {
            thirdMax = secondMax;
            secondMax = el;
        } else if (el > thirdMax && !(el==secondMax||el==mmax)){
            thirdMax = el;
        }
    }
    return
            static_cast<int>((thirdMax!=INT64_MIN) ?
                             thirdMax : *std::max_element(nums.begin(), nums.end()));
}

// just find common elements between both arrays
std::vector<int> intersection(std::vector<int> &nums1, std::vector<int> &nums2) {
    size_t len1 = nums1.size();
    size_t len2 = nums2.size();

    if (len1 == 0 || len2 == 0) return {};

    std::map<int, bool> elMap;
    std::vector<int> *bigVectRef, *smallVectRef, result;

    // reference the larger of the two vectors
    if (len1 > len2) {
        bigVectRef = &nums1;
        smallVectRef = &nums2;
    } else {
        bigVectRef = &nums2;
        smallVectRef = &nums1;
    }

    // fill map <element, index>
    for (auto& el : *bigVectRef)
        elMap[el] = false;

    for (auto& el : *smallVectRef) {
        auto entry = elMap.find(el);
        if (entry != elMap.end()) {
            if (!entry->second) {
                result.push_back(el);
                entry->second = true;  // ensure unique elements in result
            }
        }
    }
    return result;
}

// another solution
std::vector<int> intersectionsV2(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::unordered_map<int, int> dict;
    std::vector<int> res;
    // fill map containing elements and their frequency from nums2
    for(int i = 0; i < (int)nums1.size(); i++) dict[nums1[i]]++;
    // for each element in nums2
    for(int i = 0; i < (int)nums2.size(); i++)
        if(--dict[nums2[i]] >= 0) res.push_back(nums2[i]);
    return res;
}

static std::vector<char> _combineCharCnt(char ch, int cnt) {
    std::vector<char> result;
    result.push_back(ch);
    if (cnt == 1) return result;
    while (cnt > 0) {
        int tmp = cnt % 10;
        result.insert(result.begin()+1, (char)('0'+tmp));
        cnt /= 10;
    }
    return result;
}

// sample input: ["a","a","b","b","c","c","c"]
// output: ["a","2","b","2","c","3"]
// chars with only 1 do not get compressed
// for say bbbbbbbbbbbb ==> 'b' '1' '2'
// simple solution
int compressString(std::vector<char>& chars) {
    if (chars.empty())
        return 0;
    char tmp = chars[0];
    int cnt = 1, start=0;
    int i = 1;
    while (i < chars.size()) {
        if (tmp == chars[i]) {
            cnt++;
        } else {
            std::vector<char> entry = _combineCharCnt(tmp, cnt);
            chars.erase(chars.begin()+start, chars.begin()+i);
            for (int j = (int)entry.size()-1; j >= 0; j--)
                chars.insert(chars.begin()+start, entry[j]);
            start += (int)entry.size();
            i = start;
            tmp = chars[i];
            cnt = 1;
        }
        i++;
    }
    // last entry
    std::vector<char> entry = _combineCharCnt(tmp, cnt);
    chars.erase(chars.begin()+start, chars.begin()+i);
    for (int j = (int)entry.size()-1; j >= 0; j--)
        chars.insert(chars.begin()+start, entry[j]);
    return (int)chars.size();
}

/*
 * The idea with this algo is to collect all indices that
 * show the height to continue to decrease and push them on to the
 * stack.
 * Once we hit an element where the current height increases we go to
 * the else case.
 * In this case we check the left boundary and right boundary and take the min
 * between those two, to get the depth we take the difference between the
 * min of the two boundaries and the bottom, the get the length
 * you subtract i - index of right boundary - 1 --> i - stk.top() - 1
 * so maxBotWater = depth * width
 * otherwise if stack is empty then zero water is being contained
 * Note i is only increased when pushed to the stack to ensure all
 * indices are processed
 */
int trapRainWater(const std::vector<int>& height) {
    if (height.size()==1 || height.empty()) return 0;
    std::stack<int> stk;
    int i = 0, maxWater = 0, maxBotWater = 0;
    while (i < (int)height.size()) {
        if (stk.empty() || height[i] < height[stk.top()]) {
            stk.push(i++);
        } else {
            int bottom = stk.top();
            stk.pop();
            maxBotWater = stk.empty() ?
                    0 : (std::min(height[stk.top()], height[i]) - height[bottom]) * (i - stk.top()-1);
            maxWater += maxBotWater;
        }
    }
    return maxWater;
}

std::vector<int> spiralOrder(IntMatrix &matrix) {
    if (matrix.size() == 1)
        return matrix[0];
    else if (matrix.empty())
        return {};

    std::vector<int> spiral;
    size_t rowLen = matrix[0].size();
    size_t colLen = matrix.size();
    size_t rowPadding=0, colPadding=0;

    while (true) {
        // face 1 top side left to right
        for (size_t i = colPadding; i < (rowLen - colPadding); i++)
            spiral.push_back(matrix[rowPadding][i]);

        if (spiral.size()>=(rowLen*colLen)) break;

        // face 2 vertical right top to bottom
        for (size_t i = rowPadding+1; i < (colLen-rowPadding); i++)
            spiral.push_back(matrix[i][rowLen - colPadding - 1]);

        if (spiral.size()>=(rowLen*colLen)) break;

        // face 3 horizontal right to left
        for (int i = (int)(rowLen - colPadding - 2); i >= (int)colPadding; i--)
            spiral.push_back(matrix[colLen-rowPadding-1][i]);

        if (spiral.size()>=(rowLen*colLen)) break;

        // face 4 vertical left side up
        for (int i = (int)(colLen - colPadding - 2); i > (int)rowPadding; i--)
            spiral.push_back(matrix[i][colPadding]);

        if (spiral.size()>=(rowLen*colLen)) break;

        // increment padding
        colPadding++;
        rowPadding++;

        //  DEBUG
        LOG << "displaying spiral: colPadding: " << colPadding << " rowPadding: " << rowPadding << END;
        display(spiral);
        std::cout << "\n\n" << END;
    }
    return spiral;
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
            if (entry.second < temp.second || entry.second
                                              == temp.second && temp.first < entry.first)
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

/*
 * Window position              Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
 output: [3, 3, 5, 5, 6, 7]
 */
// brute force !!
// O( k*(n-k+1) )
std::vector<int> maxSlidingWindow(std::vector<int> &nums, int k) {
    std::vector<int> result;
    if (nums.empty() || nums.size() < k) return {};
    if (nums.size() == 1 || k == 1) return nums;

    int i = 0, j = k - 1;
    auto len = static_cast<int>(nums.size());
    while (j < len) {
        result.push_back(
                maxElement<std::vector<int>::iterator, int>(nums.begin()+i, nums.begin()+j)
        );
        i++;
        j++;
    }
    return result;
}

// optimized solution
// O(n)
// TODO :: still some issues
std::vector<int> maxSlidingWindowV2(const std::vector<int> &nums, int k) {
    if (nums.empty() || nums.size() < k) return {};
    if (nums.size() == 1 || k == 1) return nums;

    std::vector<int> result;
    std::pair<int , int> prevMaxVal = {INT32_MIN, INT32_MIN};   // val, index
    std::pair<int , int> maxVal = {INT32_MIN, INT32_MIN};   // val, index

    for (int i = 0; i < (int)nums.size(); i++) {
        int el = nums[i];
        // save max and previous max
        if (el > maxVal.first) {
            prevMaxVal = maxVal;
            maxVal.first = el;
            maxVal.second = i;
        } else if (el > prevMaxVal.first) {
            prevMaxVal.first = el;
            prevMaxVal.second = i;
        }
        if (i>=k-1) {
            result.push_back(maxVal.first);
            // check if prev Max index falls out of window next iteration
            if ( maxVal.second <= i - k + 1 ) {
                maxVal = prevMaxVal;
                prevMaxVal = {INT32_MIN, INT32_MIN};
            } else if (prevMaxVal.second <= i - k + 1) {
                prevMaxVal = {nums[i-1], i-1};
            }
        }
    }
    return result;
}

// solution using a deque
// amortized O(n) solution (from discussion)
std::vector<int> maxSlidingWindowV3(const std::vector<int> &nums, int k) {
    if (nums.empty() || k <= 0) return {};
    int n = (int)nums.size();
    std::vector<int> result(n-k+1, 0);
    int ri = 0;
    std::deque<int> dq;
    for (int i = 0; i < n; i++) {
        // removes numbers out of range k
        while (!dq.empty() && dq.front() < i - k + 1) dq.pop_front();

        // remove smaller numbers in k range as they are useless
        while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();

        // q contains index
        dq.push_back(i);
        if (i >= k -1) result[ri++] = nums[dq.front()];
    }
    return result;
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

VectOfVect zigzagLevelOrder(TreeNode *root) {
    VectOfVect result;
    std::deque<TreeNode*> nodeQue;
    if (!root) return result;
    bool leftToRight = true;  // bool to dictate direction of level traversal
    nodeQue.push_back(root);
    while(!nodeQue.empty()) {
        int lvlSize = (int)nodeQue.size();
        std::vector<int> currLvl;
        for (int i = 0; i < lvlSize; i++) {
            TreeNode* nd;
            if (leftToRight) {
                nd = nodeQue.front();
                nodeQue.pop_front();
            }
            else {
                nd = nodeQue.back();
                nodeQue.pop_back();
            }
            currLvl.push_back(nd->val);
            if (leftToRight) {
                if (nd->left) nodeQue.push_back(nd->left);
                if (nd->right) nodeQue.push_back(nd->right);
            } else {    // we go right to left
                if (nd->right) nodeQue.push_front(nd->right);
                if (nd->left) nodeQue.push_front(nd->left);
            }
        }
        leftToRight = !leftToRight;
        result.push_back(currLvl);
    }
    return result;
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

/*
 *
    3
   / \
  0   4
   \
    2
   /
  1

  L = 1
  R = 3

Output:
      3
     /
   2
  /
 1

 */
TreeNode *trimBST(TreeNode *root, int L, int R) {
    if (!root) return root;

    // check if out of range
    if (root->val < L) return trimBST(root->right, L, R);
    if (root->val > R) return trimBST(root->left, L, R);

    // assign nodes
    root->left = trimBST(root->left, L, R);
    root->right = trimBST(root->right, L, R);
    return root;
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

int removeElement(std::vector<int>& nums, int val) {
    if (nums.empty()) return 0;
    int j = 0;
    for ( int i = 0; i < nums.size(); i++) {
        if (nums[i] != val)
            nums[j++] = nums[i];
    }
    return j;
}

// * * * * * *
static bool _isPalindrome(const std::string& word) {
    int len = (int)word.size();
    int j = (int)word.size()-1;
    for (int i = 0; i < len/2; i++)
            if (word[i] != word[j--])
                return false;
    return true;
}

// brute force
// slow
// O(n^3)
std::string longestPalindrome(std::string& s) {
    if (s.size() == 1 || s.empty()) return s;
    std::string currSS;
    std::string longest;
    auto len = (int)s.size();
    for (int i = 0 ; i < len-1; i++) {
        for (int j = i+1; j <= len; j++) {
            if (j-i > longest.size())
                currSS = s.substr( (long)i, (long)(j-i) );
            else
                continue;
            if (currSS.size() > longest.size() && _isPalindrome(currSS))
                longest = currSS;
        }
    }
    return longest;
}

// lo and hi supplied will be expanded from their starting points
// lo will go <-- and hi will go -->
// longest palindrome is returned
static std::string expandToFindPalindrome(std::string word, int lo, int hi) {
    int len = (int)word.size();
    while (lo >= 0 && hi < len && (word[lo] == word[hi])) {
        lo--;
        hi++;
    }
    return word.substr(lo+1, (hi-lo-1));
}

// optimized
std::string longestPalindromeV2(std::string &s) {
    std::string currWord, longest;
    int len = static_cast<int>(s.size());
    for (int i = 0; i < len; i++) {

        // odd lengthed words have one center point
        currWord = expandToFindPalindrome(s, i, i);
        if (currWord.size() > longest.size()) longest = currWord;

        currWord = expandToFindPalindrome(s, i, i+1);
        if (currWord.size() > longest.size()) longest = currWord;
    }
    return longest;
}

// 2 3 1 1 4
// todo :: finish
static void _jump(const std::vector<int>& nums, int currIndex, int jump, bool& result) {
    // base case
    if ( (currIndex==nums.size()-1) || result ) {
        result = true;
        return;
    }

    // jumping
    while (jump>0 && (currIndex + jump < nums.size())) {
        _jump(nums, currIndex + jump, nums[currIndex + jump--], result);
    }

    // exit if result already set true
    if (result) return;

    // increment current index
    currIndex++;

    // increment index
    if (currIndex < nums.size()-1)
        _jump(nums, currIndex, nums[currIndex], result);
}

// [3,2,1,0,4]
// map <num, vector<int>>
// map is number of steps mapped to index
bool canJump(std::vector<int> &nums) {
    if (nums.empty()) return false;
    if (nums.size()==1)
        return !nums[0];
    bool result = false;
    _jump(nums, 0, nums[0], result);
    return result;
}

static int _calcNum(int n) {
    int tmp;
    int result = 0;
    while (n > 0) {
        tmp = n % 10;
        n/=10;
        result += tmp*tmp;
    }
    return result;
}

bool isHappy(int n) {
    int val = n;
    std::map<int, int> nums;
    while (val!=1) {
        val = _calcNum(val);
        auto entry = nums.find(val);
        if (entry != nums.end()) return false;
        nums[val] = val;
    }
    return true;
}

std::vector<int> iterativeInorderTraversal(TreeNode* root) {
    if (!root) return {{}};
    TreeNode* tmp = root;
    std::vector<int> result;
    std::stack<TreeNode*> stk;
    while (tmp || !stk.empty()) {
        if (tmp->left) {
            stk.push(tmp->left);
            tmp = tmp->left;
        } else {
            TreeNode* node = stk.top();
            result.push_back(node->val);
            if (node->right)
                stk.push(node->right);
        }
    }
    return result;
}
