#include <chrono>
#include "sort_search_problems.h"
#include "utility.h"
using namespace std;
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

//[[13,15],[1,13],[6,9]]
void test_minMeetingRooms() {
    SEPARATOR;
    cout << "Problem #253. Meeting Rooms II" << endl;
    vector<Interval> intervals = {
            Interval(13,15),
            Interval(1,13),
            Interval(6,9)
    };
//    cout << "input: " << endl;
//    display(intervals);
    t1_bub = hrc::now();
    int result = minMeetingRoomsV2(intervals);
    t2_bub = hrc::now();
    LOG << "expected: 2" << END;
    LOG << "result:   " << result << END;
    showExeTime();
    END_PROBLEM;
}

int main() {
    test_minMeetingRooms();
    return 0;
}
