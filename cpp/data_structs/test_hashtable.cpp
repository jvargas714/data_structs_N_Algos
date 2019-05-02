#include <cstdint>
#include <iostream>
#include "hash_table.h"

#define FUNCT_HEADER std::cout << "================================" << __FUNCTION__ << "==============================" << END
#define NEWLINE std::cout <<"\n" << END

using std::cout;
using std::endl;
using std::string;

typedef struct _test_data {
	int a;
	int b;
	_test_data(int a, int b):
	a(a), b(b) {}
} S_TEST_DATA;

void test_hashNode() {
    FUNCT_HEADER;
    std::pair<string, S_TEST_DATA> keyval("lVal", S_TEST_DATA(500, 1000));
    string key("bears");
    cout << "testing r-val ctor" << endl;
    HashTableNode<int, int> nd({5, 1});
    cout << "\ntesting l-val ctor" << endl;
    HashTableNode<string, S_TEST_DATA> nd2(keyval);

    cout << "\ntesting r-val ctor" << endl;
    HashTableNode<string, int> nd3("helo");
    HashTableNode<string, int> nd5(std::pair<string, int>{"tobemved", 6969});

    cout << "\ntesting l-val ctor" << endl;
    HashTableNode<string, int> nd4(key);

    std::cout << "\ntesting cpy operator" << END;
    nd4 = nd3;

    cout << "\ntesting move assignment operator" << END;
    nd3 = std::move(nd5);

    cout << "\ntesting cpy ctor" << END;
    HashTableNode<string, int> nd6(nd3);
    cout << "val should be 6969 val=" << nd6.data << END;

    cout << "\ntesting mv ctor" << END;
    HashTableNode<string, int> nd7(std::move(nd6));
    cout << "val shall be 6969, val=" << nd7.data << "\n\n" << END;

    cout << "\ntest linking ...linking 6969 to "
}

void test_basicInitAndFill() {
	FUNCT_HEADER;
	HashTable<string, S_TEST_DATA> table;
	cout << "***calling put r-val overload 5 times***" << endl;
	table.put({"hello", S_TEST_DATA(5, 10)});
	NEWLINE;
	table.put({"hello", S_TEST_DATA(10, 15)});   // updating
	NEWLINE;
	table.put({"tiger", S_TEST_DATA(5, 10)});
	NEWLINE;
	table.put({"lions", S_TEST_DATA(5, 10)});
	NEWLINE;

	S_TEST_DATA data(100, 150);
    string key("bears");
    table.put({key, data});
    std::cout << "size should be 4 at this point, current size: " << table.size() << "\n\n" << endl;

	std::pair<string, S_TEST_DATA> keyval("lVal", S_TEST_DATA(500, 1000));
	cout << "calling l-val overload of put(), size should be 5 after put." << endl;
	table.put(keyval);
	cout << "current size of table: " << table.size() << endl;
}

void test_ctorsAndOps() {

}

int main() {
    test_hashNode();
    test_basicInitAndFill();
	return 0;
}