#include "string_problems.h"
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include "utility.h"
#include "facebook.h"


static const std::unordered_map<char, std::string> DIAL_PAD = {
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}
};
static const std::vector<std::string> DIAL_MAP =
        {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

//============================================helper functions=================================================
static int _cleanStrToInt(const std::string& val, int pwr, int sign) {
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

static int _getCount(const std::string& str, const int& offset) {
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

static void _genCntNSay(std::string& currTerm, std::string& nextTerm) {
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

static bool _isPalindrome(const std::string& word) {
	int len = (int)word.size();
	int j = (int)word.size()-1;
	for (int i = 0; i < len/2; i++)
		if (word[i] != word[j--])
			return false;
	return true;
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

// is target a substring of base
static bool isSubString(const std::string& base, const std::string& target) {
	if (base.size() < target.size()) return false;
	size_t i = 0;
	size_t tarLen = target.size();
	size_t baseLen = base.size();
	std::string tmpSub;
	while (i < baseLen) {
		if (base[i]==target[0])
			if (base.substr(i, tarLen) == target) return true;
		i++;
	}
	return false;
}

// generate generate combos (recursive method)
// say 27 is pressed
// 2:"abc" 3:"def" 4:"ghi" 5:"jkl", 6:"mno" 7:"pqrs" 8:"tuv" 9:"wxyz"
static void generateT9Combos(const std::string& digits, std::vector<std::string>& result, int i) {
    if (i >= digits.size()) {
        return;
    }
}

std::vector<std::string> splitStringBy(std::string str, const std::string& delim) {
    std::vector<std::string> result;
    auto pos = str.find(delim);
    if (pos==0) {
        str.erase(0, 1);
        pos = str.find(delim);
    }
    std::string ss;
    while (pos != std::string::npos) {
        ss = str.substr(0, pos);
        result.push_back(ss);
        str.erase(0, pos+1);
        pos = str.find(delim);
    }
    if (!str.empty()) result.push_back(str);
    return result;
}

void reeformatEmailUsername(std::string& username) {
    if (username.find('.') != std::string::npos)
        username.erase(std::remove(username.begin(), username.end(), '.'));
    size_t pos = username.find('+');
    if (pos != std::string::npos)
        username = username.substr(0, pos);
}

bool isValidTime(std::string tm) {
    tm.erase(tm.begin() + tm.find(':'));
    int hr = std::strtol(&tm[0], 0, 10)*10 + std::strtol(&tm[1], 0, 10);
    int min = std::strtol(&tm[2], 0, 10)*10 + std::strtol(&tm[3], 0, 10);
    if (hr > 24 || min > 60) return false;
    else return true;
}
// ============================================end helper functions============================================

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

/*
Given two strings A and B, find the minimum number of times A has to be
repeated such that B is a substring of it.
    "aa"
    "a"
 1 + b*3/a
 numrepeats :: numRpts < (1 + (b.size()*3)/a.size())
 */
int repeatedStringMatch(std::string a, std::string b) {
	int numRpts = 1;
	std::string origA(a);
	if (a.empty()) return -1;
	size_t maxRpts = (2 + (b.size()*2)/a.size());
	int charMap[256];
	std::memset(charMap, 0, sizeof(charMap));

	// ensure every char in b is in a as well
	for (const auto& ch : a)
		charMap[(int)ch]++;

	for (const auto& ch : b)
		if (!charMap[(int)ch]) return -1;

	// size a so that at least it is at least as long as B if its shorter
	while(a.size() < b.size()) {
		a+=origA;
		numRpts++;
	}

	while (numRpts <= maxRpts) {
		if ( isSubString(a, b) ) return numRpts;
		else {
			a += origA;
			numRpts++;
		}
	}
	return -1;
}


/*
 * Optimized version using KMP algo
 * runtime: O(alen + blen)
 * space: O(blen) for prefix table
 */
int repeatedStringMatchV2(std::string a, std::string b) {
	using namespace std;
	int i = 1, j = 0, len = 0;
	int blen = (int) b.size();
	int alen = (int) a.size();
	vector<int> lps(blen, 0);

// build prefix/suffix table to avoid extra comparisons in the next part
	while (i < blen) {
		if (b[i] == b[len]) {
			lps[i++] = ++len;
		} else {
			if (len != 0)
				len = lps[len - 1];
			else
				lps[i++] = 0;
		}
	}
	i = 0;
	// find b as a substring within a (repeated)
	while (i < alen) {
		while (j < blen && a[(i + j) % alen] == b[j]) ++j;
		if (j == blen) {
			return (
				(i + j) / alen + ((i + j) % alen != 0 ? 1 : 0)
			);
		}
		// increment stuff
		if (j > 0) {
		i += max(1, j - lps[j-1]);
		j = lps[j-1];
		} else {
			i++;
		}
	}
	return -1;
}

int lengthLongestPath(const std::string& dirTree) {
	std::map<int, std::string> tabRootMap;
	int index=-1, tabCnt=0, maxLen=0, currLevel=0;
	bool istabs = false;
	bool isfile = false;
	std::map<int, int> parentDirMap;  // <numTabs, dirlen>

	for (int i = index+1; i < (int)dirTree.size(); i++) {
		char ch = dirTree[i];
		if (istabs) {
			if (ch == '\t') {
				tabCnt++;
				continue;
			} else {
				parentDirMap[tabCnt] = 0;
				currLevel = tabCnt;
				tabCnt = 0;
				istabs = false;
			}
		}

		// check if current segment is a file or not
		if (ch == '\n' && isfile) {
			isfile = false;
			int lenDir=0;
			// find length of current directory
			for (int j = 0; j <= currLevel; j++) lenDir+=parentDirMap[j];
			if (lenDir > maxLen) maxLen = lenDir;
			parentDirMap[currLevel] = 0;
		}

		// count chars including / which is counted as the new line char
		if (ch != '\n') {
			parentDirMap[currLevel]++;
			if (ch == '.' && !isfile) isfile = true;
		}
		else {  // new line
			parentDirMap[currLevel]++;
			istabs = true;
		}
	}
	if (isfile) {
		int lenDir=0;
		for (int j = 0; j <= currLevel; j++) lenDir+=parentDirMap[j];
		if (lenDir > maxLen) maxLen = lenDir;
	}
	return maxLen;
}

/*
Input: S = "5F3Z-2e-9-w", K = 4
Output: "5F3Z-2E9W"
*/
std::string licenseKeyFormatting(std::string S, int K) {
	std::string result;

	// remove all dashes and upper case all chars
	std::transform(S.begin(), S.end(), S.begin(),
		[](auto& ch) {return std::toupper(ch);});
	S.erase(
		std::remove_if(S.begin(), S.end(), [](auto& ch){ return ch == '-'; }),
		S.end());

	if (S.size() == 1) return S;
	int len_first_chunk = static_cast<int>(S.size() % K);
	result += S.substr(0, (unsigned long)len_first_chunk);
	if (len_first_chunk > 0) result+= '-';
	int cnt = 0, i= (len_first_chunk == 0) ? 0:len_first_chunk;

	while (i < S.size()) {
		if (cnt == K) {
			result += '-';
			cnt = 0;
		} else {
			result += S[i++];
			cnt++;
		}
	}
	return result;
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
	int start = 0, longest = 0;
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
    charMap[ static_cast<int>(str[0]) ] = 0;  // a

    /*
     * 0(n) solution one pass through string. Can think of this as a window passing through
     * the string. When a duplicate is found the current substring len is updated this is
     * essentially the distance from current index and one past the char at prev index
     * "a b c d e f a"
     *    j         i  --> str[j:i] inclusive is the new current substring the
     *    length would be i-j --> 6-1+1, add one to compensate for index starting at 0
     */
    for (int i = 1; i < len; i++) {
        prevIndex = charMap[ static_cast<int>(str[i]) ];
        // check if char has been processed or if i is not part of the current substring (i-curLen)
        if (prevIndex == -1 || i - curLen > prevIndex) {
            curLen++; // 2
        } else {
            if (curLen > longest)
                longest = curLen;
            curLen = i - prevIndex;
        }
        // save index of processed char
        charMap[static_cast<int>(str[i])] = i;
    }
    if (curLen > longest)
        longest = curLen;
    return longest;
}

// 2:"abc" 3:"def" 4:"ghi" 5:"jkl", 6:"mno" 7:"pqrs" 8:"tuv" 9:"wxyz"
// Input: "23"
//Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"]
// static const std::unordered_map<char, std::string> DIAL_PAD
std::vector<std::string> letterCombinations(const std::string& digits) {
    std::vector<std::string> result;


    // say 2, 7 is pressed
    for (int i = 0; i < (int)digits.size(); i++) {
        int cnt = (int)DIAL_PAD.find(digits[i])->second.size();
        for (int j = 0; j < cnt; j++) {
            result.push_back(
                    std::to_string(DIAL_PAD.find(digits[i])->second[j]));  // a, b, c
        }
    }
    return result;
}
// 2:"abc" 3:"def" 4:"ghi" 5:"jkl", 6:"mno" 7:"pqrs" 8:"tuv" 9:"wxyz"
// say 27 is pressed
std::vector<std::string> letterCombinationsV3(const std::string& digits) {
    if (digits.empty()) return {};
    std::vector<std::string> result;

    // initialize result
    for (auto ch : DIAL_MAP[digits[0]-'0'])
        result.push_back({ch});

    for (int i = 1; i <digits.size(); i++) {
        char dig = digits[i];
        std::string letterGroup = DIAL_MAP[dig-'0'];
        std::vector<std::string> prevResCpy = result;  // ap bp cp .. .. ..
        std::vector<std::string> tmp;
        for (auto letter : letterGroup) // dig = 7, group = pqrs
            for (auto& entry : prevResCpy) // letter='p'
                tmp.push_back(entry + letter);
        result.swap(tmp);  // [ap bp .. .. .. ]
    }
    return result;
}

// a b c
std::vector<std::string> letterCombinationsV2(const std::string& digits) {
    std::vector<std::string> ans;
    if(digits.empty()) return ans;
    while(ans[0].size()!=digits.length()) {
        std::string remove = *ans.erase(ans.begin());
        std::string mmap = DIAL_PAD.find(
                digits[(remove.empty()) ?
                '0':remove.size()-1])->second;
        for(char c: mmap) {
            ans.push_back(remove+c);
        }
    }
    return ans;
}

// 2:"abc" 3:"def" 4:"ghi" 5:"jkl", 6:"mno" 7:"pqrs" 8:"tuv" 9:"wxyz"
std::vector<std::string> letterCombinationsV4(const std::string& digits) {
    if (digits.empty()) return {};
    std::vector<std::string> result;

    // initialize result
    for (auto ch : DIAL_MAP[digits[0]-'0'])
        result.push_back({ch});

    for (int i = 1; i <digits.size(); i++) {
        std::string letterGroup = DIAL_MAP[digits[i]-'0'];
        std::vector<std::string> tmp;
        for (auto letter : letterGroup) // dig = 7, group = pqrs
            for (auto& entry : result) // letter='p'
                tmp.push_back(entry + letter);
        result.swap(tmp);  // [ap bp .. .. .. ]
    }
    return result;
}

// slow 40 ms
// Input: ["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
// Output: 2
//Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com" actually receive mails
int numUniqueEmails(std::vector<std::string> &emails) {
    int cnt = 0;
    if (emails.empty()) return cnt;
    // <domainName, std::set<userName>> (converted of course)
    std::map<std::string, std::set<std::string>> domainMap;

    // populate map first
    for (const auto& email : emails) {
        auto splt = splitStringBy(email, "@");
	    reeformatEmailUsername(splt[0]);
        domainMap[splt[1]].insert(splt[0]);
    }
    // iterate through map add all sizes of vectors and return result
    for (const auto& entry : domainMap)
        cnt += static_cast<int>(entry.second.size());
    return cnt;
}

// optimized ( split method is faster) 24ms
int numUniqueEmailsV3(const std::vector<std::string>& emails) {
    int cnt = 0;
    if (emails.empty()) return cnt;
    // <domainName, std::set<userName>> (converted of course)
    std::map<std::string, std::set<std::string>> domainMap;

    // populate map first
    for (const auto& email : emails) {
        std::vector<std::string> splt;
        split(email, '@', splt);
	    reeformatEmailUsername(splt[0]);
        domainMap[splt[1]].insert(splt[0]);
    }
    // iterate through map add all sizes of vectors and return result
    for (const auto& entry : domainMap)
        cnt += static_cast<int>(entry.second.size());
    return cnt;
}

// optimized further
// build a full string just having the domain and what makes a username unique store in an unordered set
int numUniqueEmailsV4(std::vector<std::string> &emails) {
    if (emails.empty()) return 0;
    std::unordered_set<std::string> acctSet;
    for (auto acct : emails) {
        std::vector<std::string> splt;
        split(acct, '@', splt);
	    reeformatEmailUsername(splt[0]);
        acctSet.insert(splt[0]+splt[1]);
    }
    return acctSet.size();
}

/*
Given a time represented in the format "HH:MM", form the next closest time by reusing the current digits. There is no
 limit on how many times a digit can be reused.
You may assume the given input string is always valid. For example, "01:34", "12:09" are all valid.
 "1:34", "12:9" are all invalid.

Example 1:

Input: "19:34"
Output: "19:39"
Explanation: The next closest time choosing from digits 1, 9, 3, 4, is 19:39,
 which occurs 5 minutes later.  It is not 19:33, because this occurs 23 hours and 59 minutes later.
 * problem: Next Closest Time #681
 * result:
 */
std::string nextClosestTime(std::string &tm) {
    std::string result;
    std::string tmCpy = tm;
    std::sort(tmCpy.begin(), tmCpy.end());
    int j = 4;
    bool tmMod = false;
    while (j >= 0) {
        if (tm[j] == ':') j--;
        for (int i = 0; i < tm.size()-1; i++) {
            if ((tmCpy[i] - '0') > (tm[j] - '0')) {
                if ( (j == 3 && tmCpy[i] - '0' > 5)
                || (j == 0 && tmCpy[i] - '0' > 2) ||
                (j == 1 && tm[0]=='2' && tmCpy[i] - '0' > 3)) {
                    continue;
                }
                tm[j] = tmCpy[i];
                tmMod = true;
                break;
            }
        }
        if (tmMod) break;
        j--;
    }

    j++;
    while (j < tm.size()) {
        if (tm[j]==':') j++;
        tm[j++] = tmCpy[0];
    }
    return tm;
}

/*
	Approach:
		1. use a map to store all non alpha chars by {index : char}
		2. iterate through chars of S check to see if current index is a non alpha
			- if so loop through starting from that i and add to result 
		3. add alpha char to result increment i 
	
	issue: 
		this can be optimized as we pass through non alpha chars more than once one using the iterator and one 
		in the inner loop, this slows down our runtime
	
	runtime: O(n)
	space time: O(n)
*/
std::string reverseOnlyLetters(std::string S) {
	if (S.empty()) return "";
	std::map<int, char> charMap;
	std::string result;
	int i = 0;
	for (auto ch: S) {
		if ( !isalpha(ch) ) {
			charMap[i] = ch;
		}
		i++;
	}
	i = 0;
	for (auto it = S.rbegin(); it != S.rend(); it++) {
		while (charMap.find(i) != charMap.end()) {
			result += charMap[i++];
		}
		if (isalpha(*it)) {
			result += *it;
			i++;
		}
	}
	while (charMap.find(i) != charMap.end())
			result += charMap[i++];
	return result;
}


/*
	Optimized Solution:
	Approach:
		1. use a direct access array to keep track of non alpha character frequencies, by index
		2. keep two pointers 
			i: current character to build result (starts at end of string)
			j: current index of result 
		3. we can use j to detect when we reach an index that is supposed to have a non alpha character
			- if it a spot for a non-alpha character we append to result and decrement the cnt down 
				(wont matter since the map is by index)
			- increment j as result is built, keeps track of current index of result
		4. after main loop ends we check for non-alpha chars at the end of the string using j
		5. deallocate charFreq 
	runtime: O(n) << inner loop condition is the same as the outer
	space time: O(n)
*/
std::string reverseOnlyLettersV2(const std::string& S) {
        if (S.empty()) return "";
        int* charFreq = new int[S.length()];
        memset(charFreq, 0, sizeof(int)*S.length());
        std::string result;
        
        for (int i = 0; i < S.length(); i++)
            if (!isalpha(S[i]))
                charFreq[i]++;
        
        int i = S.length()-1;
        int j = 0;
        
        while (i>=0 && j<S.length()) {
            char ch = S[i];
            while (j<S.length() && charFreq[j]-- > 0) {
                result += S[j++];
            }
            if (isalpha(ch)) {
                result += ch;
                j++;
            }
            i--;
        }
        while (j < S.length())
            result += S[j++];
        delete[] charFreq;
        return result;
    }