#include <cstdint>
#include <iostream>
#include <chrono>
#include "hash_table.h"

#define FUNCT_HEADER std::cout << "\n\n================================" << __FUNCTION__ << "==============================" << END
#define NEWLINE std::cout <<"\n" << END

using std::cout;
using std::endl;
using std::string;
using namespace std::chrono;

typedef high_resolution_clock hrc;
typedef hrc::time_point t_point;
t_point t1_bub, t2_bub;

static void showExeTime(const string& label) {
	std::cout << "\n+-+-+-+-+-+-+-+-+-+-+" << END;
	auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
	auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
	std::cout << label << " time of execution -->\n" << milli_sec << "msec\n" << micro_sec << "usec" << END;
	std::cout << "+-+-+-+-+-+-+-+-+-+-+" << END;
}


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

    cout << "\ntest linking ...linking 6969 to " << END;
    nd7.next = std::make_shared<HashTableNode<string, int>>(std::pair<string, int>("secondLink", 5588));
    nd7.next->next = std::make_shared<HashTableNode<string, int>>(std::pair<string, int>("thirdLink", 6699));
    HashTableNode<string, int> nd8;
    nd8 = nd7;
    cout << "RESULT ==> nd8.data: " << nd8.data << " nd8.next->data: " << nd8.next->data <<
    " nd8.next->next->data:" << nd8.next->next->data << "\n\n" <<END;

    HashTableNode<string, int> nd9;
    cout << "\n\ntesting move operator on linked nodes" << END;
    nd9 = std::move(nd8);
	cout << "RESULT ==> nd9.data: " << nd9.data << " nd9.next->data: " << nd9.next->data <<
	     " nd9.next->next->data:" << nd9.next->next->data << "\n\n" <<END;
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
	FUNCT_HEADER;
	using HTable = HashTable<string, double>;
	HTable table;
	HTable table2;
	cout << "testing [] rval operator" << END;
	table2["first"] = 1.234;
	cout << "table2[\"first\"] = " << table2["first"] << "\n\n" << END;

	cout << "testing [] lval operator" << END;
	string second = "second";
	table2[second] = 2.234;
	cout << "table2[\"second\"] = " << table2["second"] << "\n\n" << END;

	cout << "[] operator updating 2.234 to 2.345" << END;
	table2[second] = 2.345;
	cout << "table2[second] = " << table2[second] << "\n\n" << END;

	cout << "testing [] by adding third element without assignment" << END;
	table2["third"];

	cout << "\n\ntesting cpy ctor " << END;
	HTable table3(table2);

	cout << "\n\ntesting cpy operator" << END;
	table = table2;
	cout << "first: " << table["first"] << END;
	cout << "second: " << table["second"] << END;
	cout << "third: " << table["third"] << END;

	cout << "\n\ntesting mv ctor" << END;
	HTable table4(std::move(table3));

	cout << "\n\ntesting mv assignment operator" << END;
	HTable table5;
	table5 = std::move(table4);
	cout << "first: " << table4["first"] << END;
	cout << "second: " << table4["second"] << END;
	cout << "third: " << table4["third"] << END;
	cout << "\n\n" << END;
}

void test_timing() {
	FUNCT_HEADER;
	cout << "BATTLE AGAINST std::unordered_map\n\n" << END;

}

int main() {
    test_hashNode();
    test_basicInitAndFill();
    test_ctorsAndOps();
    test_timing();
	return 0;
}