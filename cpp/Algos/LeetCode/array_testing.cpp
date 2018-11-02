#include <chrono>
#include "utility.h"
#include "array_problems.h"
using namespace std;
using namespace std::chrono;
typedef high_resolution_clock hrc;
typedef hrc::time_point t_point;
t_point t1_bub, t2_bub, t3_bub, t4_bub;

static void showExeTime() {
    std::cout << "\n+-+-+-+-+-+-+-+-+-+-+" << END;
    auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    std::cout << "time of execution -->\n" << milli_sec << "msec\n" << micro_sec << "usec" << END;
    std::cout << "+-+-+-+-+-+-+-+-+-+-+" << END;
}
// problem: 739
void test_dailyTemperatures() {
    SEPARATOR;
    cout << "Problem #739 Daily Temperatures" << endl;
    vector<int> temps = {34,80,80,34,34,80,80,80,80,34};
    cout << "input: " << endl;
    display(temps);
    t1_bub = hrc::now();
    auto result = dailyTemperaturesV2(temps);
    t2_bub = hrc::now();
//    cout << "expected: 1 1 4 2 1 1 0 0" << endl;
    cout << "result:   ";
    display(result);
    showExeTime();
    END_PROBLEM;
}

// problem: 406
void test_reconstructTheQueue() {
    SEPARATOR;
    cout << "Problem #739 Reconstruct the Queue" << endl;
    vector<pair<int, int>> input = {
            {8,2},{4,2},{4,5},{2,0},{7,2},{1,4},{9,1},{3,1},{9,0},{1,0}
    };
    vector<pair<int, int>> expected = {
            {1,0},{2,0},{9,0},{3,1},{1,4},{9,1},{4,2},{7,2},{8,2},{4,5}
    };
    t1_bub = hrc::now();
    auto result = reconstructQueue(input);
    t2_bub = hrc::now();

    cout << "\n\n\n";
    cout << "input: " << endl;
    display(input);
    cout << "output: " << endl;
    display(result);
    cout << "expected output: " << endl;
    display(expected);
    showExeTime();
    END_PROBLEM;
}

// problem: 200
// todo :: implement this algo and test
void test_numOfIslands() {
    SEPARATOR;
    cout << "Problem #200 Number of Islands" << endl;
    CharMatrix grid = {
            {'1','1','1','1','0'},
            {'1','1','0','1','0'},
            {'1','1','0','0','0'},
            {'0','0','0','0','1'}
    };
    CharMatrix grid2 = {
            {'0'},
            {'1'},
            {'1'},
            {'0'},
            {'1'}
    };
    CharMatrix grid3 = {
            {'1','0','1','1','1'},
            {'1','0','1','0','1'},
            {'1','1','1','0','1'}
    };
    CharMatrix grid4 = {
            {'1','1','1','1','0'},
            {'1','1','0','1','0'},
            {'1','1','0','0','0'},
            {'0','0','0','0','0'}
    };
    CharMatrix grid5 = {
            {'1','1','1','0','1','0'},
            {'1','1','0','0','0','0'},
            {'0','1','0','0','0','0'},
            {'0','1','0','0','0','0'},
            {'0','0','0','1','0','1'}
    };
    displayMatrix(grid5);
//    int expected = 2;
    t1_bub = hrc::now();
    int res = numIslands(grid5);
    t2_bub = hrc::now();
    cout << "result: " << res << endl;
//    cout << "expected: " << expected << endl;
    showExeTime();
    END_PROBLEM;
}

int main() {
    test_dailyTemperatures();
    test_reconstructTheQueue();
    test_numOfIslands();
    return 0;
}

