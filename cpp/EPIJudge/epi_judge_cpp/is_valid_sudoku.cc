#include <vector>
#include "test_framework/generic_test.h"
using std::vector;
/*
 * determine if sudoku board is valid or not
 * mxn rows x col
 */
bool IsValidSudoku(const vector<vector<int>>& board) {
	auto hasDups = [](const vector<int>& nums) -> bool {
		vector<bool> dups(nums.size()+1, false);
		for (const auto& el : nums) {
			if (el == 0) continue;
			if (dups[el]) return true;
			else dups[el] = true;
		}
		return false;
	};

	auto hasDupsInRegion = [board](int rowStart, int colStart) -> bool {
		vector<bool> dups(10, false);
		for (int row = rowStart; row < rowStart + 3; row++) {
			for (int col = colStart; col < colStart + 3; col++) {
				int val = board[row][col];
				if (val == 0) continue;
				if (dups[val]) return true;
				else dups[val] = true;
			}
		}
		return false;
	};

	// check for duplicates across all rows
	for (int row = 0; row < board.size(); row++) {
		if (hasDups(board[row])) return false;
	}

	vector<bool> dups(board.size(), false);

	// check for dups across all columns
	for (int col = 0; col < board[0].size(); col++) {
		for (int row = 0; row < board.size(); row++) {
			int val = board[row][col];  // i->row n -> col
			if (val == 0) continue;
			if (dups[val]) return false;
			else
				dups[val] = true;
		}
		std::fill(dups.begin(), dups.end(), false);
	}

	// check 3x3 regions for duplicates
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (hasDupsInRegion(3*i, 3*j)) return false;
		}
	}
	return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"partial_assignment"};
  return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                         &IsValidSudoku, DefaultComparator{}, param_names);
}
