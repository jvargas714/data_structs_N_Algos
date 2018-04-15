#include <iostream>
#include <chrono>
#include <types.h>
#include "utility.h"
#include "leet_algos.h"

using namespace std::chrono;
typedef high_resolution_clock hrc;
typedef hrc::time_point t_point;
int main()
{
    // valid sudoku board
     SudokuBoard sud1 = {
            {'5','3','.','.','7','.','.','.','.'},
            {'6','.','.','1','9','5','.','.','.'},
            {'.','9','8','.','.','.','.','6','.'},
            {'8','.','.','.','6','.','.','.','3'},
            {'4','.','.','8','.','3','.','.','1'},
            {'7','.','.','.','2','.','.','.','6'},
            {'.','6','.','.','.','.','2','8','.'},
            {'.','.','.','4','1','9','.','.','5'},
            {'.','.','.','.','8','.','.','7','9'}
    };

    // invalid sudoku board


    t_point t1_bub, t2_bub;
    std::vector<int> vect = {3, 2, 4};// fill_vector(100000);
    t1_bub = hrc::now();
    std::cout << "sudoku is valid?: " << ((isValidSudoku(sud1)) ? "yes":"no") << std::endl;
    t2_bub = hrc::now();
    auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    std::cout << "time of execution -->\n" << milli_sec << "msec\n" << micro_sec << "usec\n" << std::endl;
    return 0;
}
