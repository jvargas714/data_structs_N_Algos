#include <iostream>
#include "problems.h"
using namespace std;

void display_input( int cnt, char** args );
void test_remove_dups();
void test_removeKthElement();



int main( int argc, char* argv[] ) {
	test_removeKthElement();
    return 0;
}



void display_input( int cnt, char** args ) {
    cout << "input: ";
    for( int i = 1; i < cnt; ++i ) {
        cout << args[i] << " ";
    }
    cout << endl;
}

void test_remove_dups() {
	linked_list ll, ll2;
	linked_list_CH2::populateLL(ll, 20, 10);
	linked_list_CH2::populateLL(ll2, 20, 10);

	cout << ll.to_string() << endl;
	cout << "removing duplicates using buffer..." << endl;
	linked_list_CH2::removeDupsWbuff(ll.data());
	cout << "after removing dups" << endl; 
	cout << ll.to_string() <<  "\n\n\n" << endl;

	cout << "second linkedList: " << ll2.to_string() << endl;
	cout << "removing duplicates not using buffer..." << endl; 
	linked_list_CH2::removeDups(ll2.data());
	cout << "after removing duplicates" << endl;
	cout << ll2.to_string() << "\n" << endl;
}

void test_removeKthElement() {
	linked_list ll, ll2;
	linked_list_CH2::populateLL(ll, 10, 100000);
	linked_list_CH2::populateLL(ll2, 10, 100000);
	cout << ll.to_string() << endl;
	cout << "element found: " << linked_list_CH2::findKthFromEnd(ll.data(), 3, ll.size()) << endl;
}




