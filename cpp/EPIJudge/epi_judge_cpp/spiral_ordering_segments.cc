#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

/*
 * Descr:
 *      write a program which takes a nxn 2D array and returns its spiral order in a vector
 * Approach:
 *      * * * * *
 *      * * * * *
 *      * * * * *
 *      * * * * *
 *      * * * * *
 *
 * Time:
 *  ave time:
 *  median time:
 *
 * Complexity:
 *  runtime:
 *  space:
 */
vector<int> MatrixInSpiralOrder(vector<vector<int>> square_matrix) {
	auto coord = [square_matrix](size_t x, size_t y){
		return
	};
	size_t n = square_matrix.size();
	size_t numEls = n * n;
	size_t x = 0, y = 0;
	vector<int> res;

	while (res.size() != numEls) {

	}

}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering_segments.cc",
                         "spiral_ordering_segments.tsv", &MatrixInSpiralOrder,
                         DefaultComparator{}, param_names);
}
