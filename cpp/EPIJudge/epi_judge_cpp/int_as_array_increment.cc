#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

/*
 * Description:
 *      write a program which takes as input an array of digits encoding a non-negative decimal integer D and updates
 *      the array of digits to represent the digit D + 1 --> (1, 2, 9) --> (1, 3, 0)
 */

/*
 * Average running time:    2 us
 * Median running time:     2 us
 *
 * runtime complexity: O(n)
 * space: O(1)
 */
vector<int> PlusOne_(vector<int> A) {
    if (A.empty()) return {};
    size_t pos = A.size()-1;
    A[pos]++;
    if (pos == 0 && A[pos] > 9) {
        A[pos] = 0;
        A.insert(A.begin(), 1);
        return A;
    }
    while (pos > 0 && A[pos] > 9) {
        A[pos] = 0;
        A[--pos]++;
    }
    if (pos == 0 && A[pos] > 9) {
        A[pos] = 0;
        A.insert(A.begin(), 1);
    }
    return A;
}

/*
 * provided by book
 * Average running time:    1 us
 * Median running time:     2 us
 */
vector<int> PlusOne(vector<int> A) {
    ++A.back();
    for (int i = A.size() - 1; i > 0 && A[i] == 10; --i) {
        A[i] = 0, ++A[i - 1];
    }
    if (A[0] == 10) {
        // There is a carry-out, so we need one more digit to store the result.
        // A slick way to do this is to append a 0 at the end of the array,
        // and update the first entry to 1.
        A[0] = 1;
        A.emplace_back(0);
    }
    return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}
