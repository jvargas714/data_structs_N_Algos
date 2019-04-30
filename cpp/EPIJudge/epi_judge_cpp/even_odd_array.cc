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
 *  Average running time:    3 us
	Median running time:     1 us
    Runtime: O(n)
    Space: O(1)  << inplace swapping done
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

/*
 * Approach:
 *      we go with a 2 ptr approach. The idea to minimize the amount of iterations is we target an odd number
 *      in the target even region by incrementing i if nums[i] is already an even number.
 *      After that the goal is to find the next even number in the target odd region which is controlled by
 *      pointer j. Once that even value is found we simply perform the swap and decrement j.
 *      i and j converge as iterations pass.
 *  Average running time:    2 us
	Median running time:     1 us
    Runtime: O(n) for an array where have all od numbers
    Space: O(1), we swap inplace, no space needed
 */
void EvenOdd_mysolv2(vector<int>* A_Ptr) {
	std::vector<int>& nums = *A_Ptr;
	if (nums.size() == 1) return;
	size_t i = 0, j = nums.size()-1;
	while (i < j) {
		if ((nums[i] & 1) == 0) {  // if i even incr to next even
			i++;
		}
		else if ((nums[j] & 1) == 0) {  // if j is even we swap
			std::swap(nums[i++], nums[j--]);
		} else
			j--;
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
