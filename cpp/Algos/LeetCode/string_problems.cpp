#include "string_problems.h"
#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "utility.h"

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
 *  TODO :: did not work
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
