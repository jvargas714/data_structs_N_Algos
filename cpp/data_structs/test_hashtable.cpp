#include <cstdint>
#include <iostream>
#include "hash_table.h"
using std::string;

typedef struct _test_data {
	int a;
	int b;
	string str;
	_test_data(int a, int b, string str):
	a(a), b(b), str(str) {}
} S_TEST_DATA;

void test_basicInitAndFill() {
	LOG << END;
	HashTable<string, S_TEST_DATA> table;
	table.put({"hello", S_TEST_DATA(5, 10, "dahh")});
	table.put({"hello", S_TEST_DATA(10, 15, "h")});   // updating
	table.put({"tiger", S_TEST_DATA(5, 10, "equadsf")});
	table.put({"lions", S_TEST_DATA(5, 10, "dsdfasdf")});
	S_TEST_DATA data(100, 150, "this is an l val");
	string key("bears");
	table.put({key, data});

	std::pair<string, S_TEST_DATA> keyval("lVal", S_TEST_DATA(500, 1000, "this is a keyval"));
	table.put(keyval);
	LOG << "current size of table: " << table.size() << END;

	HashTableNode<int, int> nd({5, 1});
	HashTableNode<string, S_TEST_DATA> nd2(keyval);
	HashTableNode<string, int> nd3("helo");
	HashTableNode<string, int> nd4(key);
}

int main() {

	return 0;
}