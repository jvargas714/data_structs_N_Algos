#include "test_framework/generic_test.h"
/*
 * 4.1
 * - be comfortable with XOR
 * - know to clear and set the lowermost set bit
 *
 * The Parity of a binary word is 1 if the number of 1s in the word is odd, 0 if even
 * x & (x-1) --> clears the lowermost bit
 * x & ~(x-1) isolates the lowest bit that is 1 in x ~ is the bitwise complement
 * 0b101 & ~(0b100) --> 0b101 & 0b011 --> 0b001
 * 0b010 & ~(0b001) --> 0b010 & 0b110 --> 0b010
 *
 * compute the parity of a very large binary word
 */

// input: 100100 --> ~(x-1) = 011100 >> 100100 & 011100 --> 000100
// runtime: O(k)  --> where k is the number of bits set to 1 , worst case when number is all ones
// space: O(1)
short Parity(unsigned long long x) {
    int cnt = 0;
  while (x) {
      cnt++;
      x ^= (x & ~(x-1));
  }
  return (cnt&1)? 1:0;
}

// best solution
// O(k) where k is the number of bits set to 1
short Parity_solution(unsigned long long x) {
    short result = 0;
    while (x) {
        result ^= 1;
        x &= (x-1);  // drop lowest set 1 bit so --> 1100010001000 -->  110001000000  --> 1100000000000 ... 000
    }
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
