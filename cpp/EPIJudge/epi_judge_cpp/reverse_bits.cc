#include "test_framework/generic_test.h"
/*
 * write a program that takes a 64 bit unsigned int and returns its bits reversed
 * 0b10011101010101100010011000100010110100000 output should be
 * 0b10110100010001100100011010101011100100000000000000000000000
 * res: 1 --> 10
 * res:
 */
// runtime:
unsigned long long ReverseBits(unsigned long long x) {
    unsigned long long res = 0;
    for (int i = 1; i < sizeof(unsigned long long)*8; i++) {
        res |= (x&1);
        res <<= 1;
        x >>=1;
    }
    return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
