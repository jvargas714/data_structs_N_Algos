#include <string>
#include "test_framework/generic_test.h"
using std::string;
using std::map;

static string createNextEntry(const string& str) {
	if (str.empty()) return "1";
	map<char, int> cntMap;
	char prev = str[0];
	int cnt = 1;
	string res;
	char buff[256] = {0};
	for (auto it = str.begin()+1; it != str.end(); it++) {
		if (prev != *it) { // new char add to result str
			sprintf(buff, "%i%c", cnt, prev);
			res.append(buff);
			memset(buff, '\0', sizeof(buff));
			prev = *it;
			cnt = 1;
			continue;
		}
		cnt++;
	}
	if (cnt > 0) {
		sprintf(buff, "%i%c", cnt, prev);
		res.append(buff);
	}
	return res;
}

/*
 * Description:
 *      return the nth integer of the look and say seq
 *      i.e. 1 11 21 1211 111221 312211
 *
 * Time:
 *      Average running time:    3 ms
		Median running time:   143 us
   Complexity:
        runtime: O(n2^n)  << each successive number can have at most twice as many digits as the previous one,
                            this happens when all digits are different. This means that max length of the
                            number can be no more than 2^n. Since we have n iterations and the work in each
                            iteration is proportional to the length of the number computed in the iteration,
                            a simple bound on the time complexity can be O(n2^n)
        space:
 */
string LookAndSay(int n) {
  string res;
  int cnt = 1;
  while (cnt <= n) {
	res = createNextEntry(res);
  	cnt++;
  }
  return res;
}

// ============================ BOOK SOLUTION =================================
string NextNumber(const string& s);

/*
 * this result came out to be essentially the same algo that i came up with, similar results in running time
 */
string _LookAndSay(int n) {
	string s = "1";
	for (int i = 1; i < n; ++i) {
		s = NextNumber(s);
	}
	return s;
}

string NextNumber(const string& s) {
	string result;
	for (int i = 0; i < s.size(); ++i) {
		int count = 1;
		while (i + 1 < s.size() && s[i] == s[i + 1]) {
			++i, ++count;
		}
		result += std::to_string(count) + s[i];
	}
	return result;
}
int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "look_and_say.cc", "look_and_say.tsv",
                         &LookAndSay, DefaultComparator{}, param_names);
}
