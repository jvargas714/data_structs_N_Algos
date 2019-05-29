#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
/*
 * Given n, return all primes up to and including n
*/
vector<int> _GeneratePrimes(int n) {
  return {};
}

/*
 * Approach:
 *  in this method we go from 2 to sqrt(n) and save only the ones that are not factors of elements below that number
 */
vector<int> GeneratePrimes(int n) {
    vector<int> result;
    vector<bool> primes(n+1, true);
    for (int i = 2; i <= n; i++) {
        if (primes[i]) result.push_back(i);
        if (i*i < n) {
            for (int j = 2; i*j <= n; j++) {
                primes[i*j] = false;
            }
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
