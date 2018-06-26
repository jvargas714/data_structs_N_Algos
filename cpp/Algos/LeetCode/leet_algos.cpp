#include <algorithm>
#include <map>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <iomanip>
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
    for(int i=0;i<s.size();i++){
        chCount[s[i]-'a']++;
        chCount[t[i]-'a']--;
    }
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

std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
    std::vector<std::vector<int>> result;

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

// inplace 0(1) mem
void rotateVector(std::vector<int> &nums, int k) {
    unsigned int ind;
    size_t n = nums.size();
    unsigned int offset = k % n;
    for (unsigned int i=0; i<n; i++) {
        ind = i + offset;
        if (ind>=n) {
            ind-=n;
        }
        nums[i]=nums[ind];
    }
}

