#include <vector>
#include <deque>
#include "test_framework/generic_test.h"
using std::vector;
using std::deque;
using std::floor;
/*
 * problem 5.10
 * Given n, return all primes up to and including n
 * Approach:
 *  - similar approach as below instead we ignore even numbers
 *  - storage is reduced
 *  - from book
*/
vector<int> _GeneratePrimes(int n) {
    if (n < 2) return {};
    const int size = static_cast<int>(floor(.5 * (n-3))) + 1;
    vector<int> primes;
    primes.emplace_back(2);
    /*
     * is_prime[i] represents whether (2i+3) is prime or not. For example is_prime[0] represents whether
     * 2(0)+3 = 3 is prime or not --> is_prime[1] = 5, is_prime[2] = 7 ....
     * we intially set all to true then we use sieving to eliminate nonprimes.
     *
     */
    deque<bool> is_prime(size, true);
    for (int i = 0; i < size; i++) {
        if (is_prime[i]) {
            // every index i gives us the next prime when using 2i+3 ie if i = 7 --> 7*2 + 3 = 17 which is prime
            // from here we can eliminate p^2 multiples which is p = (2i+3)^2 = (4i^2 + 12i + 9)
            int p = (i*2) + 3;
            primes.emplace_back(p);
            /*
             * sieving from p^2 whose value is (4i^2 + 12i + 9). The index in is_prime us (2i^2 + 6i + 3) because
             * is_prime[i] represents 2i+3
             *
             * note that we need to use long long for j because p^2 might overflow\
             */
            for (long long j = 2LL * i * i + 6 * i + 3; j < size; j += p) {
                is_prime[j] = false;
            }
        }
    }
    return primes;
}

/*
 * Approach:
 *  in this method we go from 2 to sqrt(n) and save only the ones that are not factors of elements below
 *  we start with setting all values in is_prime to true
 *  for each number p each we save if set to true, the eliminate all multiples of p up to and including n. This is a
 *  slow approach using trial division
 *  Time:
 *      Average running time:   50 ms
 *      Median running time:     4 us
 *  Complexity:
 *      runtime: proportional to O(n/2 + n/3 + n/5 + n/7 + n/11 ...) ==> O(n * log(log(n))
 *      space: O(n)
 *
 */
vector<int> GeneratePrimes_bruteForce(int n) {
    vector<int> primes;
    deque<bool> is_prime(n+1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p <= n; ++p) {
        if (is_prime[p]) primes.emplace_back(p);
        // eliminate multiples start at a multiple of 2
        for (int i = p * 2; i <=n; i += p) {
            is_prime[i] = false;
        }
    }
    return primes;
}

vector<int> GeneratePrimes(int n) {
    if (n < 2)
        return {};
    vector<int> primes;
    deque<bool> is_prime(n, true);
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.emplace_back(i);
            for (long long j = i*i; j <= n; j+=i) {
                is_prime[j] = false;
            }
        }
    }
    return primes;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
