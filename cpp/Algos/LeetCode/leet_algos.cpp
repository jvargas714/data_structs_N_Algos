#include <algorithm>
#include <map>
#include "leet_algos.h"
#include "utility.h"

#define LOG std::cout << __FUNCTION__ << "(): "

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
    int start = 0, end = matrix.size()-1;
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

int firstUniqCharV2(std::string s) {
	char tmp = s[0];
	for (int i = 1; i < s.size()-1; i++) {
		if (tmp != s[i])
			return i - 1;
		else
			tmp = s[i + 1];
	}
	return -1;
}
