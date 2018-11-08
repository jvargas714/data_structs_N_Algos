#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include "sort_search_problems.h"
#include "utility.h"


// ---------------------------------------------------Helper-----------------------------------------------------------
static bool doTimesConflict(const Interval& iv1, const Interval& iv2) {
    if (iv1.start >= iv2.start && iv1.start < iv2.end) return true;
    else return iv1.start < iv2.start && iv1.end > iv2.start;
}

/*
 *
[0,1,2,8,0,0]
4
[0,2]
2
 */
// merge nums2 in to nums1 it can be assumed that nums1 has m+n elements already
void mergeVectors(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
    if (nums2.empty()) return;
    int i1=0, i2=0;
    while (i1 < (m+i2) && i2 < n) {
        std::cout << "i1: " << i1 << ", i2: " << i2 << std::endl;
        if (nums2[i2] <= nums1[i1]) {
            nums1.erase(nums1.end()-1);
            nums1.insert(nums1.begin()+i1, nums2[i2++]);
            display(nums1);
        } else {
            i1++;
        }
    }
    std::cout << "Outside of loop: \n\ti1: " << i1 << ", i2: " << i2 << std::endl;

    // fill in the rest at the end
    for (; i1 < (m+n) && i2 < n; i1++, i2++)
        nums1[i1] = nums2[i2];
}

void mergeVectorsV2(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
    if (nums2.empty()) return;
    int cnt = 0;
    int mergeLen = m + n, i = 0, j = 0;
    bool inserted = false;
    while (j < n && i < mergeLen - 1) {
        int tmp = nums2[j];  // 2
        if (tmp > nums1[i] && tmp <= nums1[i + 1]) {
            nums1.insert(nums1.begin() + (i + 1), tmp);
            j++;
            cnt++;
            inserted = true;
        } else if (tmp < nums1[i]) {
            nums1.insert(nums1.begin()+i, tmp);
            inserted = true;
            j++;
        } else if (tmp == nums1[i]) { // equal
            nums1.insert(nums1.begin() + i, tmp);
            inserted = true;
            j++;
            cnt++;
        }
        i++;
        if (inserted) {
            nums1.erase(nums1.end() - 1);
            inserted = false;
        }
    }

    // fill in rest of elements from nums2 that didnt make it
    std::cout << "i: " << i << " j: " << j << std::endl;
    if (j == n - 1) {
        nums1[mergeLen - 1] = nums2[j];
    } else {
        for (int z = j; z < n; z++) {
            nums1[mergeLen - cnt -1] = nums2[z];
            cnt--;
        }
    }
}

// merge from behind version
void mergeVectorsV3(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
    if (nums2.empty()) return;
    while (m > 0 && n > 0) {
        if (nums1[m-1] > nums2[n-1]) {
            nums1[m + n - 1] = nums1[m-1];
            m--;
        } else {
            nums1[m + n - 1] = nums2[n-1];
            n--;
        }
    }

    // fill in rest
    while (n > 0) {
        nums1[n-1] = nums2[n - 1];
        n--;
    }
}

// globals
std::vector<bool> g_versions;
int g_nVersions;
int g_badVersion;
static int cnt = 0;


int firstBadVerison(int n) {
    int mid;
    int left = 1;
    int right = n;

    // binary search
    while (left < right) {
        mid = left + (right-left)/2;
        if (isBadVersion(mid)) right = mid;
        else left = mid+1;
    }
    return left;
}

bool isBadVersion(int v) {
    static size_t cnt = 0;
    cnt++;
    std::cout << "API call: " << cnt << std::endl;
    if (v >= g_badVersion) return true;
    else return false;
}

// number version is based on first index being one
void initVersionVect(int badVersion, int numVersions) {
    g_badVersion = badVersion;
    g_nVersions = numVersions;
}

// my original solution :: not good
std::vector<std::string> topKFrequent(std::vector<std::string> &words, int k) {
    if (words.size() == 1) return {words[0]};
    std::vector<std::string> result;
    std::map<std::string, int> freqMap;
    int cnt = 0;

    std::sort(words.begin(), words.end());

    for (const auto& word : words) {
        auto entry = freqMap.find(word);
        if (entry == freqMap.end())
            freqMap[word] = 1;
        else
            entry->second++;
    }

    std::string nextWord;
    while (cnt < k) {
        int maxCnt = 0;
        for (const auto& word : words) {
            auto entry  = freqMap.find(word);
            if (entry != freqMap.end() && entry->second > maxCnt) {
                maxCnt = entry->second;
                nextWord = entry->first;
            }
        }
        result.push_back(nextWord);
        freqMap.erase(nextWord);
        maxCnt = 0;
        cnt++;
    }
    return result;
}

/*
 optimized using a heap
 fill map <word, number of occurances>
 fill priority queue (max) each element being a
 std::pair with the word paired with its numOccurences from the vector
 the comparator for the queue MyPairCompGreater, the comparator ensures
 the order is from smallest to largest

 Elements are compares each word by number of occurences if they are equal the tie
 is broken by when word comes first in the alphabet
 this comparator determines the position in the pri queue
      if (p1.second != p2.second)
          return p1.second > p2.second;
      return p1.first < p2.first;

 an additional optimization is once the pri queue reaches size of k
 we pop the top (word with least occurences)

 After queue is filled we can fill k elements in to the array ending with
 element 0 to be the word with the most frequent appearances
 O( nlog(k) )
 */
std::vector<std::string> topKFrequentV2(const std::vector<std::string> &words, int k) {
    std::unordered_map<std::string, int> freqMap;

    // O(n)
    for (const auto& word : words)
        freqMap[word]++;

    // priority queue looks up O(1) with the element being the greatest
    std::priority_queue<std::pair<std::string, int>,
            std::vector<std::pair<std::string, int>>,
            MyPairCompGreater> heap;
    for (const auto& entry: freqMap) {
        if (heap.size() < k) {
            heap.push(std::make_pair(entry.first, entry.second));
        } else {
            auto temp = heap.top();
            if ( ((entry.second < temp.second) || entry.second)
                 == (temp.second && (temp.first < entry.first)) )
                continue;
            heap.pop();   // keeps pri queue from exceeded k in size
            heap.push(std::make_pair(entry.first, entry.second));
        }
    }

    std::vector<std::string> result;
    while (!heap.empty()) {
        result.insert(result.begin(), heap.top().first);
        heap.pop();
    }
    return result;
}

struct TopFreqCompare {
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second < b.second;
    }
};

std::vector<int> topFrequentKIntegers(std::vector<int>& nums, int k) {
    std::vector<int> result;
    std::map<int, int> freqMap;
    std::priority_queue<std::pair<int, int>,
            std::vector<std::pair<int, int>>,
            TopFreqCompare> priQ;  // top element is most frequent

    // map word : numAppearences
    for (auto& el : nums)
        freqMap[el]++;

    // fill queue up with freq pairs, will order entries for us, most freq will be at the top
    for (auto& el : nums) {
        auto entry = freqMap.find(el);
        if (entry == freqMap.end()) continue;
        priQ.push({entry->first, entry->second});
        freqMap.erase(el);
        if (freqMap.empty()) break;
    }

    // fill result from pri-queue
    while (result.size() < k) {
        result.insert(result.begin(), priQ.top().first);
        priQ.pop();
    }
    return result;
}

template<typename T>
struct TopFreqCompareGreater {
    bool operator()(T& a, T& b) {
        return a.second<b.second;
    }
};

std::string frequencySort(std::string s) {
    std::string result;
    std::map<char, int> freqMap;
    std::priority_queue<std::pair<char, int>,
            std::vector<std::pair<char, int>>,
            TopFreqCompareGreater<std::pair<char, int>>> priQ;

    // fill map <char, numAppearences>
    // O(n)
    for (auto& ch : s)
        freqMap[ch]++;

    // fill queue keeps elements sorted by appearences (most appearences on top)
    for (auto& entry: freqMap) {
        priQ.push( {entry.first, entry.second} );
    }

    // fill result O(priQSize * n)
    while (!priQ.empty()) {
        char ch = priQ.top().first;
        for (int i = 0 ; i < priQ.top().second; i++)
            result+=ch;
        priQ.pop();
    }
    return result;
}

/*
 use binary search accounting for rotation
 [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]
 first find the number of rotations put on the array
 this is done by:
 1. find the mid index
 2a. if that value is larger than the hi index then we move the low index up 1 past the mid index
 2b. if that value is equal to or less then we set hi to the mid index
 3. when lo == hi we have found the lowest value and how many rotations occurred
 */
int searchSortedRotatedArray(std::vector<int>& nums, int target) {
    auto len = static_cast<int>(nums.size());
    int lo=0, hi=len-1;

    // finds the real lo and hi index accounting for the rotation
    while(lo<hi) {
        int mid = (lo+hi) / 2;
        if (nums[mid] > nums[hi]) lo = mid + 1;  // shrink the gap between lo and hi
        else hi = mid;
    }

    // lo == hi is the index of smallest value and the number of places rotated
    int numRot = lo;
    lo = 0;
    hi = len -1;

    // normal binary search accounting for rotation
    while (lo <= hi) {
        int mid = (lo+hi) / 2;
        int realMid = (mid+numRot) % len;
        if (nums[realMid]==target) return realMid;
        if (nums[realMid]<target) lo = mid+1;
        else hi = mid - 1;
    }
    return -1;  // not found
}

/*
 * finding number of rotations in this problem does not work
 * we must take this approach
 * steps:
 * 1.
 */
bool searchSortedRotatedArrayII(std::vector<int> &nums, int target) {
    int left = 0, right = static_cast<int>(nums.size()-1);
    int mid;

    while (left <= right) {
        LOG << "left: " << left << " right: " << right << "\n" << END;
        mid = (left + right) / 2;
        if (nums[mid] == target) return true;

        // for duplicate case we converge both left and right towards the center by one
        if (nums[left] == nums[mid] && nums[mid] == nums[right] ) {
            left++;
            right--;
        } else if (nums[left] <= nums[mid]) {  // left side of array is in order
            if ((nums[left] <= target) && (nums[mid] > target)) // left is < mid and less than target and mid > target
                right = mid - 1;  // since mid val is larger we bring in the right side
            else
                left = mid + 1; // move left up to mid our left side is larger
        } else {
            if ( (nums[mid] < target) && (nums[right] >= target) )
                left = mid + 1;  // normal case where we bring up the left side since mid < target
            else
                right = mid - 1;
        }
    }
    return false;
}

// not as fast as V1
bool searchSortedRotatedArrayIIV2(std::vector<int> &nums, int target) {
    int start=0,end=static_cast<int>(nums.size()-1);
    while(start<=end){
        int mid=start+(end-start)/2;
        if(nums[mid]==target) return true;
        if(nums[mid]==nums[start]) {
            start++;
        }
        else if(nums[start]<=nums[mid]) {
            if (nums[start] <= target && target <= nums[mid]) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }
        else {
            if (nums[mid] <= target && target <= nums[end]) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }
    }
    return false;
}

/*
 * [[5,8],[6,8]]
   Output: 2
 */
int minMeetingRooms(std::vector<Interval> &intervals) {
    if (intervals.empty()) return 0;
    std::sort(intervals.begin(), intervals.end(),
              [](const auto& i1, const auto& i2){ return i1.start < i2.start; });
    if (intervals.size()==2) {
        const Interval& iv1 = intervals[0];
        const Interval& iv2 = intervals[1];
        if ((iv1.start == iv2.start) || (iv2.start < iv1.end)) return 2;
        else return 1;
    }
    int rooms = 0;
    std::vector<bool> needsRoom(intervals.size(), true);
//    needsRoom[0] = false;
    for (int i  = 0; i < intervals.size(); i++) {
        for (int j = 0; j < intervals.size(); j++) {
            if (i==j) continue;
            const Interval& iv1 = intervals[i];
            const Interval& iv2 = intervals[j];

            if (needsRoom[i] && (iv1.start >= iv2.start) && (iv1.start < iv2.end)) {
                rooms++;
                needsRoom[i] = false;
            } else if (needsRoom[i] && (iv1.start < iv2.end) && (iv1.end > iv2.start)) {
                rooms++;
                needsRoom[i] = false;
            } else if (iv1.start >= iv2.end) {
//                if (!needsRoom[j]) {
//                    rooms += (needsRoom[i]) ? -1 : 0;
                    break;
//                }
            }
        }
    }
    return rooms;
}

int minMeetingRoomsV2(const std::vector<Interval> &intervals) {
    int rooms = 0;
    for (int i  = 0; i < intervals.size(); i++) {
        for (int j = 0; j < intervals.size(); j++) {
            const Interval iv1 = intervals[i];
            const Interval iv2 = intervals[j];
            if (doTimesConflict(iv1, iv2)) {
                // do something !!
            }
        }
    }
    return rooms;
}


