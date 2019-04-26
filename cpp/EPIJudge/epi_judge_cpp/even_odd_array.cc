#include <set>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

using std::vector;

/*
 * Arrange array so that even numbers appear in the first half of the
 * array. This must be done without allocating any extra space, space
 * complexity must be O(1)
 *
 * [5 2 4 7 10 11]
 * 
 * [5 3 6 8 7 10 11]
 * Approach:
 * 
 */
void EvenOdd(vector<int> *A_Ptr) {
	std::vector<int>& nums = *A_Ptr;
	if (nums.size() == 1)
		return;
	uint64_t i = 0, j = 1;
	while (i < nums.size() && j < nums.size()) {
		// find first odd in the array
		if (nums[i] % 2 == 0) {
			i++;
			j = (i == j) ? j + 1 : j;
			continue;
		}
		if (nums[j] % 2 == 0)
			std::swap(nums[i++], nums[j]);
		j++;
	}
}

void EvenOddWrapper(TimedExecutor &executor, vector<int> A) {
	std::multiset<int> before(begin(A), end(A));
	executor.Run([&] { EvenOdd(&A); });

	bool in_odd = false;
	for (int a : A) {
		if (a % 2 == 0) {
			if (in_odd) {
				throw TestFailure("Even elements appear in odd part");
			}
		} else {
			in_odd = true;
		}
	}

	std::multiset<int> after(begin(A), end(A));
	if (before != after) {
		throw TestFailure("Elements mismatch");
	}
}

int main(int argc, char *argv[]) {
	std::vector<std::string> args{argv + 1, argv + argc};
	std::vector<std::string> param_names{"executor", "A"};
	return GenericTestMain(args, "even_odd_array.cc", "even_odd_array.tsv",
	                       &EvenOddWrapper, DefaultComparator{}, param_names);
}
