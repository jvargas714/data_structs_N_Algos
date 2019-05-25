#include "linked_list.h"
#include <random>
#include <iostream>
#include "utility.h"
constexpr size_t N = 20;
using std::random_device;
using std::cout;
using std::endl;
using std::string;
using list = linked_list<int>;

void fill_data(list& ll) {
	FUNCT_HEADER;
    random_device rd;
    LOG << "filling " << N << " random elements (using push_back(rval))" << END;
    for (int i = 0; i < N; i++)
        ll.push_back(rd());
    cout << ll.to_string() << endl;
    FUNCT_END;
}

void test_indexing(list& ll) {
	FUNCT_HEADER;
	cout << "size: " << ll.size() << endl;
    for (size_t i = 0; i < ll.size(); i++)
        cout << "i: " << i << " val: " << ll[i] << END;
    FUNCT_END;
}

void test_removal(list& ll) {
	FUNCT_HEADER;
	int i = 4;
	cout << "removing index " << i << " val: " << ll[i] << endl;
	ll.remove(i);
	cout << ll.to_string() << endl;
	i = 0;

	cout << "removing index " << i << " val: " << ll[i] << endl;
	ll.remove(i);
	cout << ll.to_string() << endl;

	cout << "removing index " << ll.size() - 1 << " val: " << ll[ll.size()-1] << endl;
	ll.remove(ll.size() - 1);
	cout << ll.to_string() << endl;

	FUNCT_END;
}

void test_insert(list& ll) {
	FUNCT_HEADER;
	cout << "inserting 999 in to index " << 99 << endl;
	ll.insert(999, 2);
	cout << ll.to_string() << endl;

	FUNCT_END;
}

int main() {
    linked_list<int> ll;
    fill_data(ll);
    test_indexing(ll);
    test_removal(ll);
    test_insert(ll);
    return 0;
}