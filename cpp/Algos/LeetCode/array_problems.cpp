#include <algorithm>
#include <stack>
#include <string>
#include <unordered_map>
#include <climits>
#include "array_problems.h"
#include "utility.h"

// ================================================helper functions ====================================================
static  bool _checkDuplicate(const std::vector<char>& rw) {
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

static void _initColMap(std::map<int, SudokuRow>& cols) {
    for (int i = 0; i < 9; i++)
        cols[i] = SudokuRow(9, '.');
}

static void _addColsElement(SudokuColumns& cols, const SudokuRow& row, int colIndex) {
    unsigned int i = 0;
    for(auto el: row)
        cols[i++].push_back(el);
}

static bool _checkCols(std::map<int, SudokuRow>& cols) {
    LOG << "checking columns" << std::endl;
    for(const auto& col: cols) {
        if (_checkDuplicate(col.second))
            return false;
    }
    return true;
}

static bool _checkSquares(SudokuBoard &board) {
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

 // rotates layer of a matrix
// faces --> face1: first row; face2: right vertical; face3: last row; face4: left vertical
static void _rotateLayer(IntMatrix& matrix, uint32_t layer) {
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

// find partner to swap with
static bool _findSwap(std::vector<std::pair<int, int>>& people, int personInd) {
    int cnt = 0;
    int height = people[personInd].first;
    int inFrontCnt = people[personInd].second;
    for (int i = 0; i < people.size(); i++) {
        if (i == personInd) continue;
        if (people[i].first >= height) cnt++;
        if (cnt == inFrontCnt) {
            if (i > personInd) {
                iter_swap(people.begin()+i, people.begin()+personInd);
                return true;
            }
            return false;
        }
    }
    return false;
}

// zero out land squares as we travel through them DFS
// read about traversing graphs, DFS, BFS, and their associated method types (ie. recursive)
static void traverseIslandDFS(CharMatrix& grid, int row, int col) {
    if (grid[row][col]=='1') {
        grid[row][col] = '0';
        std::cout << "\n" << std::endl; displayMatrix(grid);
    }
    else return;
    if (row < grid.size()-1) traverseIslandDFS(grid, row+1, col);
    if (row > 0) traverseIslandDFS(grid, row-1, col);
    if (col < grid[0].size()-1) traverseIslandDFS(grid, row,  col+1);
    if (col > 0) traverseIslandDFS(grid, row, col-1);
}

/*
 *  finds next point to jump
 *  for odd even jump problem
 */
static int findNextJump(int i, const std::vector<int>& nums, bool evenJump) {
	int prevJump = -1;
	for (int j = i+1; j < nums.size(); j++) {
		// even jump
		if (evenJump) {
			if ((prevJump < 0  && nums[i] >= nums[j]) ||
					(nums[i] >= nums[j] && nums[j] > nums[prevJump])) {
				prevJump = j;
				if (j == nums.size()-1) {
					return j;
				}
			}
		} else {  // odd jump
			if ((prevJump < 0 && nums[i] < nums[j]) ||
					(nums[i] < nums[j] && nums[j] < nums[prevJump])) {
				prevJump = j;
				if (j == nums.size()-1) {
					return j;
				}
			}
		}
	}
	return prevJump;
}

// ===============================================END HELPER FUNCTIONS==================================================


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

int removeElement(std::vector<int>& nums, int val) {
    if (nums.empty()) return 0;
    int j = 0;
    for ( int i = 0; i < nums.size(); i++) {
        if (nums[i] != val)
            nums[j++] = nums[i];
    }
    return j;
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

// [3,2,1,0,4]
// map <num, vector<int>>
// map is number of steps mapped to index
bool canJump(std::vector<int> &nums) {
    auto len = (int)nums.size();
    int i = 0;
    for (int reach = 0; i < len && i <= reach; i++)
        reach = std::max(i + nums[i], reach);
    return i == len;

}

/*
 * complexity: nlogn (due to sort)
 * 1. sort by height descending order
 *      - if same height then sort by number of ppl in front in ascending order
 *      - example --> [[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]] --> [7,0] [7,1] [6,1] [5,0] ...
 * 2. iterate through sorted list and insert each person in to solution list by number of ppl in front being the index
 * if we are at [7,0] [7,1] [6,1] and we need to insert [5,0] then that element would go -->
 * [5,0] [7,0] [7,1] [6,1] ...
 */
std::vector<std::pair<int, int>> reconstructQueue(std::vector<std::pair<int, int>>& people) {
    sort(people.begin(), people.end(),[](std::pair<int,int> p1, std::pair<int,int> p2){
        return p1.first > p2.first || (p1.first == p2.first && p1.second < p2.second);
    });
    std::cout << "sorted...." << std::endl;
    display(people);
    std::cout << "\n\n" << std::endl;
    std::vector<std::pair<int,int>> sol;
    for (auto person : people){
        display(sol);
        sol.insert(sol.begin() + person.second, person);
    }
    return sol;
}

// time limit exceeds for larger inputs
std::vector<int> dailyTemperatures(std::vector<int> &T) {
    if (T.empty()) return {};
    std::vector<int> res;
    int cnt = 1;
    bool foundDay = false;
    for (int i = 0; i < T.size()-1; i++) {
        for (int j = i+1; j < T.size(); j++) {
            if (T[j] > T[i]) {
                res.push_back(cnt);
                foundDay = true;
                break;
            } else
                cnt++;
        }
        if (!foundDay) res.push_back(0);
        foundDay = false;
        cnt = 1;
    }
    res.push_back(0);
    return res;
}

/*
 * Explanation:
 * example based on i = 2 and j = 3
 *   ?   ?   ?   2   1   1   0   0
 * [73, 74, 75, 71, 69, 72, 76, 73]
 * 0. allocate memory for result to be temps.size()
 * 1. we start from end of temps
 * 2. we use i and j = i+1;
 * 3. if (temps[i] < temps[j]) then res.push_back(1)
 * 4. if (temps[i] > temps[j]) then
 * 4a. we look at res[j] ==> res[3] and see how many days until a hotter day (2)
 *      - we can jump to that day which is 72 (i=5)
 *      - 72 is still lower than 75, since 72 has a day 1 day ahead that is hotter we jump there
 *      -  we arrive at 76
 *      - we add the total steps taken to be 2 + 1 = 3,
 *      - 3 days was from j=i+1 so we add 1 more so total of 4 days from i
 */
std::vector<int> dailyTemperaturesV2(std::vector<int> &temps) {
    if (temps.size()==1) return temps;
    std::vector<int> res(temps.size(), 0);
    int j;
    for (int i = temps.size()-2; i >= 0; i--) {
        j = i+1;
        if (temps[i] < temps[j]) {
            res[i]=1;
        } else {
            // use res to find next highest day by jumping
            std::cout << "found >= case ==> i=" << i << " j=" << j << " temp: " << temps[i] << "\n";
            res[i]=0;
            while (j<res.size()-1 && temps[i] >= temps[j] && res[j]>0) {
                j += res[j];
                std::cout << "j=" << j << std::endl;
                if (temps[i] < temps[j]) {
                    std::cout << "offset found: " << (j-i) << std::endl;
                    res[i] = (j-i);
                    break;
                }
            }
        }
    }
    return res;
}

// to get logn complexity we find a local max by using binary search
int findPeakElement(std::vector<int> &nums) {
    int l = 0, r = nums.size() - 1;
    while (l < r) {
        int mid = (l + r) / 2;
        if (nums[mid] > nums[mid + 1])
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}

/*
 * Algorithm:
 * Linear scan the 2d grid map, if a node contains a '1',
 * then it is a root node that triggers a Depth First Search.
 * During DFS, every visited node should be set as '0' to mark as visited node.
 * Count the number of root nodes that trigger DFS, this number would be the number of
 * islands since each DFS starting at some root identifies an island.
 * 11000
 * 11000
 * 00100
 * 00011
 *
 * 11000
 * 01100
 */
int numIslands(std::vector<std::vector<char>> &grid) {
    if (grid.empty()) return 0;
    int cnt = 0;
    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[0].size(); col++) {
            if (grid[row][col]=='1') {
                cnt++;
                std::cout << "\n-----------clearing island!!--------------" << std::endl;
                traverseIslandDFS(grid, row, col);
            }
        }
    }
    return cnt;
}


/*
 * Also given an integer k, you need to output in which day there exists two flowers in the status of blooming,
 * and also the number of flowers between them is k and these flowers are not blooming
 *
 [5,4,1,3]
 2
 expected answer is day 3.
 Explanation:
    day 3 corresponds to flower in position 1, previous flower in position 4 bloomed
    what that means is positions 2 and 3 dont have flowers yet, since k = 2 and there are
    also 2 flowers between 4 and 1 that have not bloomed yet that is our answer

 fail cases to check:
    - k > flowers.size()-2   --> for garden size of 3 k at most can only be 1 ==> 3-2 = 1

 approach:
    - 2 based indexing
    - create map, for each index we indicate how many had bloomed at that boomed
    for garden --> [5,4,1,3,2]
    {1: 0, 2: 0, 3: 2, }

    dumb question, worded unclearly skipping
*/
int kEmptySlots(std::vector<int>& flowers, int k) {
	if (k > flowers.size() - 2) return -1;
	for (int i = 1; i < flowers.size(); i++) {
		if (std::abs(flowers[i] - flowers[i-1]) - 1 == k) {
			// k flowers in future days should be in positions between i and i-1
			int cnt = 0;
			int maxpos = std::max(flowers[i], flowers[i-1]);
			int minpos = std::min(flowers[i], flowers[i-1]);
			for (int j = i+1; j < flowers.size(); j++) {
				if (flowers[j] < maxpos && flowers[j] > minpos) cnt++;
				else break;
				if (cnt == k) return i+1;
			}
		}
	}
	return -1;
}

// time: O(n) 
// space: O(n)
// approach: fill even values first then odd 
std::vector<int> sortArrayByParity(std::vector<int>& A) {
    std::vector<int> result;
    for (auto el: A) if ((el&1)==0) result.push_back(el);  // even
    for (auto el: A) if ((el&1)!=0) result.push_back(el);  // odd
    return result;
}

// time: O(n)
// space: O(1)
// approach: inplace swapping method, using two pointers 
std::vector<int> sortArrayByParityV2(std::vector<int>& A) {
    int i = 0;
    for (int j = 0; j < A.size(); j++)
        if ((A[j]&1)==0) swap(A[i++], A[j]);
    return A;
}

/*
    - first jump is considered 1, so its an odd jump
    - odd jump: A[i] < A[j] and A[j] is the smallest possible value from i, smallest such index
    - even jump: A[i] >= A[j] and A[j] is the largest possible value, smallest such index
    A = [10,13,12,14,15]
*/
int oddEvenJumps(std::vector<int>& A) {
	int jmp = 1;
	int prevJumpVal = 0;
	int i = 0;
	int st = 0;
	int cnt = 0;
	int pos = 0;
	while (st < A.size()) {
		prevJumpVal = jmp % 2 != 0 ? INT_MAX : INT_MIN;

		// look for next jump
		pos = findNextJump(i, A, jmp%2==0);
		if (pos == A.size()-1) {  // reached end
			st++;
			i = st;
			jmp = 1;
			cnt++;
		} else if (pos < 0) {  // no jump made

		} else {  // continuing on!
			i = pos;
			jmp++;
		}

		i++;
		if (i == A.size()) {
			st++;
			i = 0;
			jmp = 1;
		}
	}
	return cnt;
}