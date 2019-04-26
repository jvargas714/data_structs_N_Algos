#include "test_framework/generic_test.h"

/*
 * solution from book, more concise
 * Result:
 *      Average running time:    1 us
 *      Median running time:     1 us
 * Runtime Complexity: O(k) where k is the number of digits in x
 */
long long Reverse(int x) {
    long long res = 0;
    while (x) {
        res = res * 10 + x % 10;
        x/=10;
    }
    return res;
}

/*
 * Write a program which takes an integer and returns the integer corresponding to the digits of the
 * input in reverse order. For example 24 --> 42, or -314 --> -413
 * Approach:
 *      1. determine power of 10 of our number (how many digits needed)
 *      2. mod 10 to get LSD
 *      3. divide by 10 to get next LSD next iteration
 *      4. add in to the result, shrink power
 * Result:
 *      Average running time:    1 us
 *      Median running time:     1 us
 * Runtime Complexity: O( floor(log10(x) ) or O(k) where k is the number of digits in x
 */
long long Reverse_mine(int x) {
    long long res = 0;
    long long dig;
    bool neg = x < 0;
    x = std::abs(x);

    // get how many places our number will be
    int pwr = std::pow(10, static_cast<int>(std::log10(x)));
    while (pwr) {
        dig = x % 10;
        x /= 10;
        res += pwr * dig;
        pwr /= 10;
    }
    return res * (neg ? -1:1);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_digits.cc", "reverse_digits.tsv",
                         &Reverse, DefaultComparator{}, param_names);
}
