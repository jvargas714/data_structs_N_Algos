#include "linked_list.h"
#include <random>
#include <iostream>
#include "utility.h"
constexpr size_t N = 50;
using std::random_device;
using std::cout;
using std::endl;
using list = linked_list<int>;

void fill_data(list& ll) {
    random_device rd;
    LOG << "filling " << N << " random elements" << END;
    for (int i = 0; i < N; i++)
        ll.push_back(rd());
    LOG << "current size: " << ll.size() << END;
}

void test_indexing(list& ll) {
    for (size_t i = 0; i < ll.size(); i++) {
        cout << "i: " << i << " val: " << ll[i] << END;
    }
}

int main() {
    linked_list<int> ll;
    fill_data(ll);
    return 0;
}