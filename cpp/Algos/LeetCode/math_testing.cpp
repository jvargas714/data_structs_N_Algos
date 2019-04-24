#include <algorithm>
#include "math_problems.h"
#include "utility.h"
using namespace std;
typedef std::vector<std::vector<int>> IntMatrix;

void test_subsets() {
    FUNCT_HEADER;
    vector<int> nums = {1, 2, 3};
    IntMatrix expected = {{}, {1}, {2}, {3}, {1, 2}, {1, 3}, {2, 3}, {1, 2, 3}};
    IntMatrix res = subsetsV3(nums);
    LOG << "expected: ";
    displayMatrix(expected);
    LOG << "\nresult: ";
    displayMatrix(res);
    sort(res.begin(), res.end());
    sort(expected.begin(), expected.end());
    LOG << "\nyour result is " << (res == expected ? "CORRECT":"WRONG") << END;
    FUNCT_END;
}

int main() {
    test_subsets();
    return 0;
}
