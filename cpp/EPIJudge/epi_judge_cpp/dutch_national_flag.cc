#include <array>
#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

using std::vector;
using std::swap;

typedef enum {
	kRed, kWhite, kBlue
} Color;

/*
 * Approach:
 *      1. first loop finds all elements less than the pivot and swaps them to put them toward the front of the array
 *      2. second loop finds all elements greater than the pivot and swaps those so that they are towards the
 *          back of the array
 *             * this was done traversing the array from the back towards thne front, so the swaps place elements at
 *                  the back
 * Runtime:
 *      O(2n^2) --> O(n^2) :: each loop goes visits each element twice
 * Space:
 *      O(1) --> all done using inplace swaps
 * Time:
 *      Average running time:   30 ms
 *      Median running time:     7 us
 */
void DutchFlagPartition_slow(int pivot_index, vector<Color> *A_ptr) {
    auto& nums = *A_ptr;
    int last_swap = 0;
    int pivot = nums[pivot_index];
    for (int i = 0; i < nums.size(); i++) {
        for (int j = i + 1; j < nums.size(); j++) {
            if (nums[j] < pivot) {
                swap(nums[i], nums[j]);
                last_swap = i;
                break;
            }
        }
    }
    for (int i = nums.size()-1; i > 0; i--) {
        for (int j = i-1; j >= 0; j--) {
            if (nums[j] > pivot) {
                swap(nums[i], nums[j]);
                break;
            }
        }
    }
}

/*
 * Space heavy approach
 * In this approach we are able to get O(n) runtime complexity at the expense of O(n) space.
 *
 * Complexity:
 *      runtime complexity: O(n)
 *      space complexity: O(n)
 *
 * Time:
 *      Average running time:   17 us
 *      Median running time:     6 us
 */
void DutchFlagPartition_space(int pivot_index, vector<Color> *A_ptr) {
    auto& nums = *A_ptr;
    vector<Color> ll, leq, lg;
    Color pivot = nums[pivot_index];
    for (auto& el: nums) {
        if (el < pivot)
            ll.push_back(el);
        else if (el > pivot)
            lg.push_back(el);
        else
            leq.push_back(el);
    }
    int i = 0;
    for (auto el: ll) nums[i++] = el;
    for (auto el: leq) nums[i++] = el;
    for (auto el: lg) nums[i++] = el;
}

/*
 * Optimized approach:
 *      in this approach we are able to create each group using only one pass
 *      We keep track of last_swap pointer to fill in the array from the front.
 *      The same approach is used when filling the array with the group of
 *      larger than pivot elements. This solution is still done in two passes.
 * Complexity:
 *      runtime: O(2n) --> O(n)
 *      space: O(1)
 * Time:
 *      Average running time:   11 us (over 2700 times faster than the O(n^2) solution!)
 *      Median running time:     2 us
 */
void DutchFlagPartition_2pass(int pivot_index, vector<Color> *A_ptr) {
    auto& nums = *A_ptr;
    int pivot = nums[pivot_index];
    int last_swap = 0;
    for (int i = 0; i < nums.size(); i++)
        if (nums[i] < pivot) swap(nums[i], nums[last_swap++]);
    last_swap = nums.size()-1;
    for (int i = nums.size()-1; i >= 0; i--)
        if (nums[i] > pivot) swap(nums[i], nums[last_swap--]);
}

/*
 * Approach Super Optimized !
 *      in this approach we attempt to classify the array in to three groups less than, equal to, and greater than
 *      This is done in a single pass by keeping track of last larger element as well as the last smaller element.
 *      The unclassified starts off as every element in the array and is decreased bu one each iteration.
 *      Keep the following invariants during the partition:
 *      bottom group: A[0, smaller-1]
 *      middle group: A[smaller, equal - 1]
 *      unclassified group: A[equal, larger-1]
 *      top group: A[larger, size(A)-1]
 * Complexity:
 *      Runtime: O(n) done in one pass
 *      Space:  O(1) no extra space allocated
 * Time:
 *      Average running time:    7 us
 *      Median running time:     2 us
 */
void DutchFlagPartition(int pivot_index, vector<Color> *A_ptr) {
    auto& nums = *A_ptr;
    Color pivot = nums[pivot_index];
    int smaller=0, equal=0, larger=nums.size();
    while (equal < larger) {
        if (nums[equal] < pivot) {
            swap(nums[equal++], nums[smaller++]);
        } else if (nums[equal] == pivot) {
            equal++;
        } else {
            swap(nums[equal], nums[--larger]);
        }
    }
}

void DutchFlagPartitionWrapper(TimedExecutor &executor, const vector<int> &A,
                               int pivot_idx) {
	vector<Color> colors;
	colors.resize(A.size());
	std::array<int, 3> count = {0, 0, 0};
	for (size_t i = 0; i < A.size(); i++) {
		count[A[i]]++;
		colors[i] = static_cast<Color>(A[i]);
	}
	Color pivot = colors[pivot_idx];

	executor.Run([&] { DutchFlagPartition(pivot_idx, &colors); });

	int i = 0;
	while (i < colors.size() && colors[i] < pivot) {
		count[colors[i]]--;
		++i;
	}

	while (i < colors.size() && colors[i] == pivot) {
		count[colors[i]]--;
		++i;
	}

	while (i < colors.size() && colors[i] > pivot) {
		count[colors[i]]--;
		++i;
	}

	if (i != colors.size()) {
		throw TestFailure("Not partitioned after " + std::to_string(i) +
		                  "th element");
	} else if (count != std::array<int, 3>{0, 0, 0}) {
		throw TestFailure("Some elements are missing from original array");
	}
}

int main(int argc, char *argv[]) {
	std::vector<std::string> args{argv + 1, argv + argc};
	std::vector<std::string> param_names{"executor", "A", "pivot_idx"};
	return GenericTestMain(args, "dutch_national_flag.cc",
	                       "dutch_national_flag.tsv", &DutchFlagPartitionWrapper,
	                       DefaultComparator{}, param_names);
}
