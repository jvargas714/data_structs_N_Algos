#include "test_framework/generic_test.h"

/*
 * Further optimized we find the highest factor of the power to reduce time even more
 * solution from book
 * Approach:
 *      - we can think of the power represented in binary i.e: x^11 = x^(1011)
 *      - we also know that x^(1011) = x * x^(10) * x^(10) * x^(10) * x^(10) * x^(10)
 *      - when y is a power of 2 this approach uses the fewest multiplications by squaring forming
 *          x, x^2, (x^2)^2 = x^4, (x^4)^2 = x^8 .....
 *      - generalizing we can think of x^y as = (x^(y/2))^2 if LSBit is 0, or x(x^(y/2))^2
 * Result:
 *      - assume a positive exponent power, invert x if its negative
 *      - we know that if the least significant bit is 0 that the power is a power of 2 so it may be broken as such
 *          powers in the example are in base 2
 *          x^(n) = x^(10) * x^(10) * ... * ... * x <<
 *      - we can take the
 *  runtime complexity: O(n) worst case where the number of multiplications is at most 2 times the index of y's MSB
 *  Average running time:    1 us
 *  Median running time:     1 us
 */
double Power(double x, int y) {
    double result = 1.0;
    long long power = y;
    if (y < 0) {
    }
    while (power) {
        if (power & 1) {
            result *= x;
        }
        x *= x, power >>= 1;
    }
    return result;
}

/*
 * Write a program that takes a double x and integer y and returns x^y
 * Exploit mathematical properties of exponentiation
 * exponent properties:
 * (x^y)(x^z) = x^(y+z)
 * (x^y)^z = x^(yz)
 * (xy)^a = x^a(y^a)
 * Approach:
 *
 *
 *
 *  Optimized:
 *      - instead of multiplying that many times we can use exp properties to cut time in half x^8 = (x^2)^4
 *
 *  Result:
 *      Average running time:   12 us
 *      Median running time:     9 us
 *      runtime complexity: O(y/2) where y
 */
double Power_halfTime(double x, int y) {
    if (y == 0) return 1;
    if (abs(y) == 1) return y > 0 ? x:1/x;

    x = y < 0 ? 1/x:x;
    double res = x;
    bool odd = false;
    y = abs(y);

    if (y % 2 == 0) {
        y /= 2;
    } else {
        y--;
        y /= 2;
        odd = true;
    }
    res = x*x;
    while (y > 1) {
        res *= (x*x);
        y-=1;
    }
    res *= (odd?x:1);
    return res;
}

/*
 * brute force:
 *      - obviously we can just return x * x * x .... y times and return the answer
 *  Average running time:   23 us
 *  Median running time:    17 us
 *  runtime: O(y)
 */
double Power_brutish(double x, int y) {
    if (y==0) return 1;
    x = (y < 0 ? 1/x : x);
    double res = x;
    y = abs(y);

    while (y > 1) {
        res *= x;
        y--;
    }
    return res;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "y"};
  return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
                         DefaultComparator{}, param_names);
}
