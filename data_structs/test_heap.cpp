#include "heap.h"

using namespace std;

int main(int arc, char* argv[] )
{
	// vector<int> data = { 41, 14, 23, 32, 90, 23, 5, 87, 23, 23, 53, 23, 64, 50 };
	//vector<int> data = {8, 19, 6, 10, 3, 8, 6, 13, 12, 12, 16, 5, 7, 19, 7, 7, 1, 3, 5, 1};
	vector<int> data = { 3, 5, 5, 6, 10, 6, 7, 7, 13, 12, 16, 8, 7, 19, 8, 19, 12 };
	min_heap hp;

	for( int& el : data )
		hp.insert( el );
	
	cout << "After being filled..." << endl;
	hp.display();
	
	cout << "size: " << hp.size() << endl;

	// unsigned int heap_size = hp.size();
	// for( unsigned int i=0; i<heap_size; i++ )
	// {
	// 	cout << "\nAfter removing min ... " << endl;
	// 	hp.extract_min();
	// 	hp.display();
	// }

	vector<int> sorted_vect = hp.sort();
	for(auto& el: sorted_vect)
		cout << el << " ";
	cout << endl;
	return 0;
}