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
	auto pt = [square_matrix](size_t row, size_t col) {
		return square_matrix[row][col];
	};

	size_t n = square_matrix.size();
	size_t numEls = n * n;
	size_t lvl=0;
	vector<int> res;
	int numlvls = n % 2 == 0 ? n/2 : n/2 + 1;
	// lock row with lvl

	while (res.size() != numEls) {
        // face 1
        if (lvl == numlvls-1) {
            res.push_back( pt(lvl, lvl) );
            return res;
        }
        for (int col = lvl; col < n - lvl; col++)
            res.push_back( pt(lvl, col) );

        // face 2
        for (int row = lvl; row < n-lvl; row++)
            res.push_back( pt(row, n-lvl-1) );

        // face 3
        for (int col = n - lvl - 1; col > lvl; col --)
            res.push_back( pt() );
	}

}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering_segments.cc",
                         "spiral_ordering_segments.tsv", &MatrixInSpiralOrder,
                         DefaultComparator{}, param_names);
}
