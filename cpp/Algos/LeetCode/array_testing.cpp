#include "utility.h"
#include "array_problems.h"
using namespace std;

void testDailyTemperatures() {
    cout << "Problem #739 Daily Temperatures" << endl;
    vector<int> temps = {73,74,75,71,69,72,76,73};
    cout << "expected: 1,1,4,2,1,1,0,0" << endl;
    display(dailyTemperatures(temps));
}

int main() {
    testDailyTemperatures();
    return 0;
}

