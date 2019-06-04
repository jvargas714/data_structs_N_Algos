#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
#include <random>
#include "test_framework/generic_test.h"
#include "test_framework/random_sequence_checker.h"
#include "test_framework/timed_executor.h"
using std::bind;
using std::vector;

/*
 * implement an algorithm that takes as input an array of distinct elements and a size, and returns a subset
 * of the given size elements. All subsets should be equally likely. Return the subset in input array itself.
 *  Approach:
 *  if we have an array of say [1, 2, 3, 4, 5] and k = 3 then we 
 *      swap(nums[0], rand(nums[0, len]))
 *      swap(nums[1], rand(nums[1, len])) 
 *      swap(nums[2], rand(nums[2, len]))
 *      
 *  Time:
 *      Average running time:  400 ms
 *      Median running time:   403 ms
 *  
 *  complexity:
 *      runtime: O(k)
 *      space: O(1)
 */
void RandomSampling(int k, vector<int>* A_ptr) {
  vector<int>& nums = *A_ptr;
  if (nums.empty()) return;
  std::default_random_engine seed( (std::random_device())() );
  size_t len = nums.size();
  for (int i = 0; i < k; i++) {
      std::swap(nums[i], nums[std::uniform_int_distribution<int>{i, static_cast<int>(len - 1)}(seed)]);
  }
  return;
}
bool RandomSamplingRunner(TimedExecutor& executor, int k, vector<int> A) {
  vector<vector<int>> results;

  executor.Run([&] {
    for (int i = 0; i < 100000; ++i) {
      RandomSampling(k, &A);
      results.emplace_back(begin(A), begin(A) + k);
    }
  });

  int total_possible_outcomes = BinomialCoefficient(A.size(), k);
  sort(begin(A), end(A));
  vector<vector<int>> combinations;
  for (int i = 0; i < BinomialCoefficient(A.size(), k); ++i) {
    combinations.emplace_back(ComputeCombinationIdx(A, A.size(), k, i));
  }
  vector<int> sequence;
  for (vector<int> result : results) {
    sort(begin(result), end(result));
    sequence.emplace_back(
        distance(begin(combinations),
                 find(begin(combinations), end(combinations), result)));
  }
  return CheckSequenceIsUniformlyRandom(sequence, total_possible_outcomes,
                                        0.01);
}

void RandomSamplingWrapper(TimedExecutor& executor, int k,
                           const vector<int>& A) {
  RunFuncWithRetries(
      bind(RandomSamplingRunner, std::ref(executor), k, std::cref(A)));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "k", "A"};
  return GenericTestMain(args, "offline_sampling.cc", "offline_sampling.tsv",
                         &RandomSamplingWrapper, DefaultComparator{},
                         param_names);
}
