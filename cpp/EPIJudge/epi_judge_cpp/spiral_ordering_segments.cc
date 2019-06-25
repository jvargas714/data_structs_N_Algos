#include <vector>
#include <array>
#include "test_framework/generic_test.h"
using std::vector;
using std::array;

// solution from book
vector<int> fromBook_MatrixInSpiralOrder(vector<vector<int>> square_matrix) {
	const array<array<int, 2>, 4> kShift = {{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};
	int dir = 0, x = 0, y = 0;
	vector<int> spiral_ordering;

	for (int i = 0; i < square_matrix.size() * square_matrix.size(); ++i) {
		spiral_ordering.emplace_back(square_matrix[x][y]);
		square_matrix[x][y] = 0;
		int next_x = x + kShift[dir][0], next_y = y + kShift[dir][1];
		if (next_x < 0 || next_x >= square_matrix.size() || next_y < 0 ||
		    next_y >= square_matrix.size() || square_matrix[next_x][next_y] == 0) {
			dir = (dir + 1) % 4;
			next_x = x + kShift[dir][0], next_y = y + kShift[dir][1];
		}
		x = next_x, y = next_y;
	}
	return spiral_ordering;
}



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
 *  ave time: 123us
 *  median time: 78us
 *
 * Complexity:
 *  runtime:
 *  space:
 */
vector<int> MatrixInSpiralOrder(vector<vector<int>> square_matrix) {
	if (square_matrix.empty()) return {};
	if (square_matrix.size() == 1) return square_matrix[0];
	auto pt = [square_matrix](size_t row, size_t col) {
		return square_matrix[row][col];
	};

	size_t n = square_matrix.size();
	size_t lvl=0;
	vector<int> res;
	int numlvls = n % 2 == 0 ? n/2 : n/2 + 1;
	// lock row with lvl

	while (lvl != numlvls) {
		// face 1
		for (int col = lvl; col < n - lvl; col++)
			res.push_back( pt(lvl, col) );

		// face 2
		for (int row = lvl+1; row < n-lvl; row++)
			res.push_back( pt(row, n-lvl-1) );

		// face 3
		for (int col = n - lvl - 2; col > lvl; col--)
			res.push_back( pt(n-lvl-1, col) );

		// face 4 up left vertical path
		for (int row = n - lvl - 1; row > lvl; row--)
			res.push_back( pt(row, lvl) );

		lvl++;
	}
	return res;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering_segments.cc",
                         "spiral_ordering_segments.tsv", &MatrixInSpiralOrder,
                         DefaultComparator{}, param_names);
}
