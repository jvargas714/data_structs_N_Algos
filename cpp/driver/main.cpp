#include <iostream>
#include <random>
#include <chrono>
#include "theNextPalindrome.h"
#include "problems.h"
#include "leet_algos.h"
#include "utility.h"

using namespace std::chrono;
typedef high_resolution_clock hrc;
typedef hrc::time_point t_point;


void display_input(int cnt, char** args);
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

// TestSets!! 
void crackingTestSet();
void leetTestSet();

int main() {
	char exit;
    t_point t1_bub, t2_bub;
    t1_bub = hrc::now();
    leetTestSet();
    t2_bub = hrc::now();
    auto milli_sec = duration_cast<milliseconds>( t2_bub - t1_bub ).count();
    auto micro_sec = duration_cast<microseconds>( t2_bub - t1_bub ).count();
    std::cout << "time of execution -->\n" << milli_sec << "msec\n" << micro_sec << "usec\n" << std::endl;
    std::cin >> exit;
	return 0;
}





void display_input(int cnt, char** args) {
	std::cout << "input: ";
	for (int i = 1; i < cnt; ++i) {
		std::cout << args[i] << " ";
	}
	std::cout << std::endl;
}

/*2.1*/
void test_remove_dups() {
	std::cout << "==================================== TESTING 2.1: Remove Dups ===================================" << std::endl;
	linked_list ll, ll2;
	linked_list_CH2::populateLL(ll, 20, 10);
	linked_list_CH2::populateLL(ll2, 20, 10);

	std::cout << ll.to_string() << std::endl;
	std::cout << "removing duplicates using buffer..." << std::endl;
	linked_list_CH2::removeDupsWbuff(ll.data());
	std::cout << "after removing dups" << std::endl;
	std::cout << ll.to_string() << "\n\n\n" << std::endl;

	std::cout << "second linkedList: " << ll2.to_string() << std::endl;
	std::cout << "removing duplicates not using buffer..." << std::endl;
	linked_list_CH2::removeDups(ll2.data());
	std::cout << "after removing duplicates" << std::endl;
	std::cout << ll2.to_string() << "\n" << std::endl;
	std::cout << "=================================================================================================" << std::endl;
}

/*2.2: iterative*/
void test_findKthElement() {
	std::cout << "==================================== TESTING 2.2: Return Kth to Last ============================" << std::endl;
	linked_list ll, ll2;
	linked_list_CH2::populateLL(ll, 10, 100000);
	std::cout << ll.to_string() << std::endl;
	std::cout << "element found: " << linked_list_CH2::findKthFromEnd(ll.data(), 3, ll.size()) << std::endl;
	std::cout << "=================================================================================================" << std::endl;
}

/*2.2: Recursive*/
void test_findKthElementRecursive(size_t kth) {
	std::cout << "==================================== TESTING 2.2: find Kth element recursive variation ==========" << std::endl;
	linked_list ll;
	linked_list_CH2::populateLL(ll, 50, 1000);
	std::cout << ll.to_string() << "\n\n" << std::endl;
	std::cout << "the " << kth << "th " << "element from the element is " << linked_list_CH2::findKthFromEndNoLen(ll.data(), 3) << std::endl;
	std::cout << "=================================================================================================" << std::endl;
}

/*2.3*/
void test_deleteMiddleNode(size_t ind) {
	std::cout << "==================================== TESTING 2.3: Delete middle Node ============================" << std::endl;
	linked_list ll;
	linked_list_CH2::populateLL(ll, 10, 100);

	std::cout << ll.to_string() << std::endl;
	std::cout << "removing element: " << ll[ind] << std::endl;
	linked_list_CH2::deleteNodeInMiddle(ll.getElement(ind));
	std::cout << "list after removal: \n" << ll.to_string() << std::endl;
	std::cout << "=================================================================================================" << std::endl;
}

/*2.4: iterative*/
void test_partitionLL(int partPt) {
	std::cout << "==================================== TESTING 2.4: Delete middle Node ============================" << std::endl;
	linked_list ll;
	linked_list_CH2::populateLL(ll, 100, 100);

	std::cout << ll.to_string() << std::endl;
	std::cout << "partitioning around " << partPt << std::endl;
	llnode* head = linked_list_CH2::partition(ll.data(), partPt);
	std::cout << "After partitioning-->" << std::endl;
	linked_list_CH2::display_ll(head, true);
	std::cout << "=================================================================================================" << std::endl;
}

void test_llIsPalindrome() {
	std::cout << "==================================== TESTING 2.6: Is LinkedList Palindrome ======================" << std::endl;
	linked_list ll = { 1, 2, 3, 4, 5, 4, 3, 2, 1 };
	linked_list ll2 = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::string output = "yes";
	bool res = linked_list_CH2::ll_is_palindrome(ll.data());
	if (!res)
		output = "no";
	std::cout << ll.to_string() << "\nis a palindrome?? --> " << output << "\n\n" << std::endl;

	res = linked_list_CH2::ll_is_palindrome(ll2.data());
	if (!res)
		output = "no";
	std::cout << ll2.to_string() << "\nis a palindrome?? --> " << output << std::endl;
	std::cout << "=================================================================================================" << std::endl;
}

void test_insertInto() {
	std::cout << "==================================== TESTING 5.1: InsertInto=====================================" << std::endl;
	uint32_t N = 0xffffffff;
	// uint32_t N = 103217;
	uint32_t M = 0x00030;
	// uint32_t M = 0x51;
	uint32_t i = 10;
	uint32_t j = 20;
	std::string tmp = bit_banger_CH5::bin2str(&N);
	std::cout << "N: " << tmp << std::endl;
	std::cout << "M: " << bit_banger_CH5::bin2str(&M) << std::endl;
	std::cout << "i: " << i << "\tj: " << j << std::endl;
	bit_banger_CH5::insertInto(N, M, i, j);
	std::cout << "N modified: " << bit_banger_CH5::bin2str(&N) << std::endl;
	std::cout << "=================================================================================================" << std::endl;
}

void test_helpers() {
	std::cout << "==================================== TESTING HELPER FUNCTIONS====================================" << std::endl;
	uint32_t N = 0xfedcba98;
	std::cout << std::hex << N << std::endl;
	std::string binstring = bit_banger_CH5::bin2str(&N, true);
	std::cout << binstring << std::endl;

	unsigned char buff[4] = { 0x55, 0xFF, 0x23, 0xaa };
	std::cout << "\n0x55, 0xFF, 0x23, 0xaa" << std::endl;
	std::string tmp = bit_banger_CH5::bin2str(buff, 4, true);
	std::cout << tmp << std::endl;
	std::cout << "=================================================================================================" << std::endl;
}

void test_stackOfPlates() {
	std::random_device rd;
	using namespace stacks_n_queues;
	std::cout << "==================================== TESTING Stack of Plates=====================================" << std::endl;
	SetOfPlates stkPlates;
	for (int i = 0; i < 50; i++)
		stkPlates.push(rd() % 1000);
	std::cout << "\nPopping 25 elements...." << std::endl;
	for (int i = 0; i < 25; i++)
		stkPlates.pop();
	stkPlates.display();
	std::cout << "Popping stack at index 2...\n\n";
	stkPlates.popAt(2);
	stkPlates.display();
	std::cout << "\nPopping stack at index 1...\n\n";
	stkPlates.popAt(1);
	stkPlates.display();
	std::cout << "=================================================================================================" << std::endl;
}

void test_twoStackQueue() {
	using namespace stacks_n_queues;
	std::random_device rd;
	std::cout << "==================================== TESTING Queue via Two Stacks================================" << std::endl;
	TwoStackQueue queue;
	int tmp;
	std::cout << "inserting 10 random integer values into the queue..." << std::endl;
	for (int i = 0; i < 10; ++i) {
		tmp = rd() % 1000;
		std::cout << "pushing " << tmp << " to queue" << std::endl;
		queue.push(tmp);
	}
	std::cout << "front of queue " << queue.front() << std::endl;
	std::cout << "front of queue " << queue.front() << std::endl;

	queue.display();
	queue.display();
	std::cout << "=================================================================================================" << std::endl;
}

void test_binaryToString() {
	std::cout << "==================================== TESTING Binary to String====================================" << std::endl;
	double x = .7223435765687;
	float xx = .7223435765687;
	std::cout << "converting double " << x << " to a string" << std::endl;
	std::cout << "RESULT: " << bit_banger_CH5::bin2str(x) << std::endl;
	std::cout << "\nconverting float " << xx << " to a string" << std::endl;
	std::cout << "RESULT: " << bit_banger_CH5::bin2str(xx) << std::endl;
	std::cout << "=================================================================================================" << std::endl;
}

void crackingTestSet() {
	uint32_t n;
	std::string val, result;
	std::cin >> n;
	for (uint32_t i = 0; i < n; ++i) {
		std::cin >> val;
		find_next_palindrome(val);
		std::cout << val << std::endl;
		std::cout << "\n\n\n\nCRACKING\n\n\n\n" << std::endl;
		test_remove_dups();
		std::cout << std::endl;
		test_findKthElement();
		std::cout << std::endl;
		test_findKthElementRecursive(3);
		std::cout << std::endl;
		test_deleteMiddleNode(3);
		std::cout << std::endl;
		test_partitionLL(75);
		std::cout << std::endl;
		test_llIsPalindrome();
		std::cout << std::endl;
		test_insertInto();
		std::cout << std::endl;
		test_helpers();
		std::cout << std::endl;
		test_stackOfPlates();
		std::cout << std::endl;
		test_twoStackQueue();
		std::cout << std::endl;
		test_binaryToString();
		std::cout << "exiting..." << std::endl;
	}
}

void leetTestSet()
{
	std::vector<int> arr = fill_vector(20000);
//	moveZeroes(arr);
	display(twoSums(arr, 78));
//	display(arr);
}
