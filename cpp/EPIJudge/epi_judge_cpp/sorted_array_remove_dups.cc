#include <vector>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::vector;

/* Returns the number of valid entries after deletion.
 * remove duplicates from the array. Go for a O(n) O(1) solution
 *
 * runtime complexity: O(n)
 * space complexity: O(1)
 *
 * Average running time:    3 us
 * Median running time:     2 us
 */
int DeleteDuplicates_mine(vector<int>* A_ptr) {
    vector<int>& nums = *A_ptr;
    if (nums.empty()) return 0;
    size_t i = 0, j = 1, len = nums.size();
    while (i < len && j < len) {
        if (nums[i] == nums[j]) {
            j++;
        } else if (j - i > 1) {
            nums[++i] = nums[j];
        } else {
            ++i; ++j;
        }
    }
    return i+1;
}

/*
 * solution from book
 * Average running time:    2 us
 * Median running time:     2 us
 */
int DeleteDuplicates(vector<int>* A_ptr) {
    vector<int>& A = *A_ptr;
    if (A.empty()) {
        return 0;
    }

    int write_index = 1;
    for (int i = 1; i < A.size(); ++i) {
        if (A[write_index - 1] != A[i]) {
            A[write_index++] = A[i];
        }
    }
    return write_index;
}

vector<int> DeleteDuplicatesWrapper(TimedExecutor& executor, vector<int> A) {
  int end = executor.Run([&] { return DeleteDuplicates(&A); });
  A.resize(end);
  return A;
}



int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A"};
  return GenericTestMain(
      args, "sorted_array_remove_dups.cc", "sorted_array_remove_dups.tsv",
      &DeleteDuplicatesWrapper, DefaultComparator{}, param_names);
}
