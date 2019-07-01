#include <string>
#include <stack>
#include <unordered_map>
#include "test_framework/generic_test.h"
using std::string;
using std::stack;
using std::unordered_map;
/*
 * Description:
 * for a string comprised of characters []{}() check to see if
 * string is well formed. Well formed strings are strings that properly open
 * and terminate these characters.
 *
 * Time:
 *  Average running time:    5 us
	Median running time:     1 us
 *
 * Complexity:
 *  runtime: O(n)
 *  space: O(n)
 */
bool _IsWellFormed(const string& s) {
	stack<char> stk;
	for (const auto& ch : s) {
		switch(ch) {
			case '[':
				stk.push(ch);
				break;
			case '(':
				stk.push(ch);
				break;
			case '{':
				stk.push(ch);
				break;
			default:
				if (stk.empty()) return false;
				if (ch == ')' && stk.top() != '(')
					return false;
				else if (ch == '}' && stk.top() != '{')
					return false;
				else if (ch == ']' && stk.top() != '[')
					return false;
				else {
					stk.pop();
				}
		}
	}
    return stk.empty();
}

/*
 * ------ BOOK SOLUTION ------
 *  Average running time:   18 us
	Median running time:     4 us
 */
bool IsWellFormed(const string& s) {
	stack<char> left_chars;
	const unordered_map<char, char> kLookup = {
		{'(', ')'}, {'{', '}'}, {'[', ']'}};
	for (int i = 0; i < s.size(); ++i) {
		if (kLookup.count(s[i])) {

			left_chars.emplace(s[i]);
		} else {
			if (left_chars.empty() || kLookup.at(left_chars.top()) != s[i]) {
				// Unmatched right char or mismatched chars.
				return false;
			}
			left_chars.pop();
		}
	}
	return left_chars.empty();
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_valid_parenthesization.cc",
                         "is_valid_parenthesization.tsv", &IsWellFormed,
                         DefaultComparator{}, param_names);
}
