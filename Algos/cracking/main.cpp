#include <iostream>
#include <random>
#include "problems.h"
using namespace std;
std::random_device rd;

void display_input( int cnt, char** args );
void test_remove_dups();
void test_findKthElement();
void test_findKthElementRecursive(size_t);
void test_deleteMiddleNode(size_t);
void test_partitionLL(int);
void test_llIsPalindrome();
void test_insertInto();
void test_helpers();
void test_stackOfPlates();
void test_twoStackQueue();
void test_binaryToString();


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
	cout << endl;
	test_llIsPalindrome();
	cout << endl;
	test_insertInto();
	cout << endl;
	test_helpers();
	cout << endl;
	test_stackOfPlates();
	cout << endl;
	test_twoStackQueue();
	cout << endl;
	test_binaryToString();
	cout << "exiting..." << endl;
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
	cout << "==================================== TESTING 2.1: Remove Dups ===================================" << endl; 
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
	cout << "=================================================================================================" << endl; 
}

/*2.2: iterative*/
void test_findKthElement() {
	cout << "==================================== TESTING 2.2: Return Kth to Last ============================" << endl;
	linked_list ll, ll2;
	linked_list_CH2::populateLL(ll, 10, 100000);
	cout << ll.to_string() << endl;
	cout << "element found: " << linked_list_CH2::findKthFromEnd(ll.data(), 3, ll.size()) << endl;
	cout << "=================================================================================================" << endl; 	
}

/*2.2: Recursive*/
void test_findKthElementRecursive(size_t kth) {
	cout << "==================================== TESTING 2.2: find Kth element recursive variation ==========" << endl; 
	linked_list ll; 
	linked_list_CH2::populateLL(ll, 50, 1000);
	cout << ll.to_string() << "\n\n" << endl;
	cout << "the " << kth << "th " << "element from the element is " << linked_list_CH2::findKthFromEndNoLen(ll.data(), 3) << endl;
	cout << "=================================================================================================" << endl; 	
}

/*2.3*/
void test_deleteMiddleNode(size_t ind) {
	cout << "==================================== TESTING 2.3: Delete middle Node ============================" << endl; 
	linked_list ll;
	linked_list_CH2::populateLL(ll, 10, 100);

	cout << ll.to_string() << endl;
	cout << "removing element: " <<  ll[ind] << endl;
	linked_list_CH2::deleteNodeInMiddle( ll.getElement(ind) );
	cout << "list after removal: \n" << ll.to_string() << endl; 
	cout << "=================================================================================================" << endl; 	
}

/*2.4: iterative*/
void test_partitionLL(int partPt) {
	cout << "==================================== TESTING 2.4: Delete middle Node ============================" << endl; 
	linked_list ll;
	linked_list_CH2::populateLL(ll, 100, 100);

	cout << ll.to_string() << endl;
	cout << "partitioning around " << partPt << endl;
	llnode* head = linked_list_CH2::partition(ll.data(), partPt);
	cout << "After partitioning-->" << endl;
	linked_list_CH2::display_ll(head, true);
	cout << "=================================================================================================" << endl; 	
}

void test_llIsPalindrome() {
	cout << "==================================== TESTING 2.6: Is LinkedList Palindrome ======================" << endl;
	linked_list ll = {1, 2, 3, 4, 5, 4, 3, 2, 1};
	linked_list ll2 = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::string output = "yes";
	bool res = linked_list_CH2::ll_is_palindrome( ll.data() );
	if (!res)
		output = "no";
	cout << ll.to_string() << "\nis a palindrome?? --> " << output << "\n\n" << endl;

	res = linked_list_CH2::ll_is_palindrome( ll2.data() );
	if (!res)
		output = "no";
	cout << ll2.to_string() << "\nis a palindrome?? --> " << output << endl;
	cout << "=================================================================================================" << endl; 	
}

void test_insertInto() { 
	cout << "==================================== TESTING 5.1: InsertInto=====================================" << endl;
	uint32_t N = 0xffffffff;
	// uint32_t N = 103217;
	uint32_t M = 0x00030;
	// uint32_t M = 0x51;
	uint32_t i = 10;
	uint32_t j = 20;
	std::string tmp = bit_banger_CH5::bin2str(&N);
	cout << "N: " << tmp << endl;
	cout << "M: " << bit_banger_CH5::bin2str(&M) << endl;
	cout << "i: " << i << "\tj: " << j << endl;
	bit_banger_CH5::insertInto(N, M, i, j);
	cout << "N modified: " << bit_banger_CH5::bin2str(&N) << endl;
	cout << "=================================================================================================" << endl;
}

void test_helpers() {
	cout << "==================================== TESTING HELPER FUNCTIONS====================================" << endl;
	uint32_t N = 0xfedcba98;
	cout << std::hex << N << endl;
	std::string binstring = bit_banger_CH5::bin2str(&N, true);
	cout << binstring << endl;

	unsigned char buff[4] = {0x55, 0xFF, 0x23, 0xaa};
	cout << "\n0x55, 0xFF, 0x23, 0xaa" << endl; 
	string tmp = bit_banger_CH5::bin2str(buff, 4, true);
	cout << tmp << endl;
	cout << "=================================================================================================" << endl;
}

void test_stackOfPlates() {
	using namespace stacks_n_queues;
	cout << "==================================== TESTING Stack of Plates=====================================" << endl;
	SetOfPlates stkPlates;
	for (int i = 0; i < 50; i++)
		stkPlates.push(rd()%1000);
	cout << "\nPopping 25 elements...." << endl;
	for (int i = 0; i < 25; i++)
		stkPlates.pop();
	stkPlates.display();
	cout << "Popping stack at index 2...\n\n";
	stkPlates.popAt(2);
	stkPlates.display();
	cout << "\nPopping stack at index 1...\n\n";
	stkPlates.popAt(1);
	stkPlates.display();
	cout << "=================================================================================================" << endl;
}

void test_twoStackQueue() {
	using namespace stacks_n_queues;
	cout << "==================================== TESTING Queue via Two Stacks================================" << endl;
	TwoStackQueue queue;
	int tmp;
	cout << "inserting 10 random integer values into the queue..." << endl; 
	for (int i = 0; i < 10; ++i) {
		tmp = rd()%1000;
		cout << "pushing " << tmp << " to queue" << endl; 
		queue.push(tmp);
	}
	cout << "front of queue " << queue.front() << endl;
	cout << "front of queue " << queue.front() << endl;

	queue.display();
	queue.display();
	cout << "=================================================================================================" << endl;
}

void test_binaryToString() {
	cout << "==================================== TESTING Binary to String====================================" << endl;
	double x = .7223435765687;
	float xx = .7223435765687;
	cout << "converting double " << x << " to a string" << endl; 
	cout << "RESULT: " << bit_banger_CH5::bin2str(x) << endl; 
	cout << "\nconverting float " <<  xx << " to a string" << endl;
	cout << "RESULT: " << bit_banger_CH5::bin2str(xx) << endl;
	cout << "=================================================================================================" << endl;
}

