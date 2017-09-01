#include <iostream>
#include "problems.h"
using namespace std;

void display_input( int cnt, char** args );
void test_remove_dups();
void test_findKthElement();
void test_findKthElementRecursive(size_t);
void test_deleteMiddleNode(size_t);
void test_partitionLL(int);




/*Driver program for test functions*/
int main( int argc, char* argv[] ) {
	test_remove_dups();
	cout << endl;
	test_findKthElement();
	cout << endl;
	test_findKthElementRecursive(3);
	cout << endl;
	test_deleteMiddleNode(3);
	cout << endl;
	test_partitionLL(75);
    return 0;
}
/***********************************/




void display_input( int cnt, char** args ) {
    cout << "input: ";
    for( int i = 1; i < cnt; ++i ) {
        cout << args[i] << " ";
    }
    cout << endl;
}

/*2.1*/
void test_remove_dups() {
	cout << "=========================TESTING 2.1: Remove Dups =======================" << endl; 
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
	cout << "=========================================================================" << endl; 
}

/*2.2: iterative*/
void test_findKthElement() {
	cout << "======================TESTING 2.2: Return Kth to Last ===================" << endl;
	linked_list ll, ll2;
	linked_list_CH2::populateLL(ll, 10, 100000);
	cout << ll.to_string() << endl;
	cout << "element found: " << linked_list_CH2::findKthFromEnd(ll.data(), 3, ll.size()) << endl;
	cout << "=========================================================================" << endl; 	
}

/*2.2: Recursive*/
void test_findKthElementRecursive(size_t kth) {
	cout << "===============TESTING 2.2: find Kth element recursive variation ========" << endl; 
	linked_list ll; 
	linked_list_CH2::populateLL(ll, 50, 1000);
	cout << ll.to_string() << "\n\n" << endl;
	cout << "the " << kth << "th " << "element from the element is " << linked_list_CH2::findKthFromEndNoLen(ll.data(), 3) << endl;
	cout << "=========================================================================" << endl; 	
}

/*2.3*/
void test_deleteMiddleNode(size_t ind) {
	cout << "=======================TESTING 2.3: Delete middle Node ==================" << endl; 
	linked_list ll;
	linked_list_CH2::populateLL(ll, 10, 100);

	cout << ll.to_string() << endl;
	cout << "removing element: " <<  ll[ind] << endl;
	linked_list_CH2::deleteNodeInMiddle( ll.getElement(ind) );
	cout << "list after removal: \n" << ll.to_string() << endl; 
	cout << "=========================================================================" << endl; 	
}

/*2.4: iterative*/
void test_partitionLL(int partPt) {
	cout << "=======================TESTING 2.4: Delete middle Node ==================" << endl; 
	linked_list ll;
	linked_list_CH2::populateLL(ll, 100, 100);

	cout << ll.to_string() << endl;
	cout << "partitioning around " << partPt << endl;
	llnode* head = linked_list_CH2::partition(ll.data(), partPt);
	cout << "After partitioning-->" << endl;
	linked_list_CH2::display_ll(head);
	cout << "=========================================================================" << endl; 	
}
