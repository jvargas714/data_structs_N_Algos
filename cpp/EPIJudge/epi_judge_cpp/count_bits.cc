#include "test_framework/generic_test.h"
/*
 * 4.1
 */
short CountBits(unsigned int x) {
    int cnt = 0;
    int mask = 0x1;
    int i = 0;
    while (i < sizeof(int)*8) {
        if ((mask & x) > 0)
            cnt++;
        mask <<= 1;
        i++;
    }
    return cnt;
}

// this solution is better as if x is set to 0n then we do no iterations
// my solution forces 32 iterations even if we do not need to
short CountBits_solution(unsigned int x) {
    short num_bits = 0;
    while (x) {
        num_bits += x & 1;
        x >>= 1;
    }
    return num_bits;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "count_bits.cc", "count_bits.tsv", &CountBits,
                         DefaultComparator{}, param_names);
}
