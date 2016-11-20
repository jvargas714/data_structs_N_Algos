#include "heap.h"
#include <sstream>

/*
	new element is placed at the bottom of the heap (last index)
	After that the heap properties must be upheld so the bubble up 
	algorithm is called to place the new element in the correct location
	above within the heap
*/
void min_heap::insert( int el )
{
	if ( data.size() == 0 )
	{
		data.push_back( el );
		return;
	}
	data.push_back( el );
	bubble_up();
}

/*
	this function displays the elements of the heap. Each line will hold 
	LINE_LIMIT. Once we reach LINE_LIMIT elements a new line is started, cnt is reset
*/
void min_heap::display() const
{
	int cnt=0;
	for( auto& el : data )
	{
		if( cnt > LINE_LIMIT )
		{
			std::cout << el << " " << std::endl;
			cnt = 0;
		}
		std::cout << el << " ";
		cnt++;
	}std::cout << std::endl;
}


/*
	This function extract the minimum value in the heap and takes the last element 
	and sets it to the root (min). The heap properties are restored using the 
	bubble_down algo.
*/
int min_heap::extract_min()
{
	if( data.size() == 0 )
	{
		std::stringstream ss; 
		ss << "min_heap::extract_min(): Error heap size is zero\n";
		throw std::string( ss.str() ); 
	}
	if( data.size() == 1 )
	{
		int root = data[0];
		data.pop_back();
		return root;
	}
	int root 	= data[ 0 ];
	data[ 0 ]	= data[ data.size()-1 ];
	data.pop_back();
	bubble_down();
	return root;
}

/*
	Element is bubbled down from root to correct spot in the heap
	1. root swaps with the smaller of the children
	2. index of swapped element is collected and its left and right children are compared 
		and swapped if need be
*/
void min_heap::bubble_down( )
{
	int parent = 0;
	int tmp;
	int max_ind = data.size()-1;
	// std::cout <<"max_ind: " << max_ind << std::endl; 

	// check for edge cases with 0 1 or 2 elements in heap
	switch( max_ind + 1 )
	{
		case 0:
			return;
		case 1:
			return;
		case 2:
			if( data[0] > data[1] )
			{
				tmp = data[0];
				data[0] = data[1];
				data[1] = tmp;
				return;
			}return;
	}

	do
	{
		int left_child 	= left( parent ); 	// left index  
		int right_child = right( parent );	// right index
		int to_be_swapped;
		// std::cout << "left_child: " << left_child << ", right_child: " << right_child << std::endl;

		// need to ensure that we do not go out of bounds here 
		if( left_child == max_ind ) // left is at max index then right child is def out of bounds 
		{
			// std::cout << "left child is max index.." << std::endl; 
			// we check to see left is larger than parent
			if( data[ left_child ] <= data[ parent ] )
			{
				// std::cout << "then swap" << std::endl;
				// swap them if so
				tmp = data[ left_child ];
				data[ left_child ] = data[ parent ];
				data[ parent ] = tmp;
			}
			break;
		}
		else if( left_child > max_ind )	// case where left is out of bounds
		{
			// just get out 
			break;
		}
		else
		{
			// select smallest child element, set to be swapped 
			( data[ left_child ] <= data[ right_child ] ) ?
			to_be_swapped = left_child : 
			to_be_swapped = right_child;

			if( data[ parent ] <= data[ to_be_swapped ] )
			{
				// great we are done
				break;
			}
			// the switcharoo
			// std::cout << "switching !! P: " << data[parent] << " with to_be_swapped: " << data[to_be_swapped] << std::endl;
			tmp = data[ to_be_swapped ];
			data[ to_be_swapped ] = data[ parent ];
			data[ parent ] = tmp;
			parent = to_be_swapped;
		}
	} while( true );

}

/*
	Restores heap properties by bubbling element at end of heap to its proper position 
	above in the heap.
*/
void min_heap::bubble_up()
{
	int new_el_ind 			= data.size()-1;
	int parent_ind 			= parent( new_el_ind );
	int new_el 				= data[ data.size()-1 ]; 
	// bubble up algorithm
	while ( new_el_ind != 0 && data[ parent_ind ] > new_el )
	{
		// swap with parent
		int tmp 			= data[ parent_ind ];
		data[ parent_ind ] 	= data[ new_el_ind ];
		data[ new_el_ind ] 	= tmp;
		new_el_ind 			= parent_ind;
		parent_ind 			= parent( new_el_ind );
	}
}

// Worst Case: O(n)
int min_heap::get_index( int el ) const
{
	int ind = 0;
	for( auto& tmp : data )
	{
		if ( tmp == el )
		{
			return ind;
		}ind++;
	}
	std::stringstream ss;
	ss << "min_heap::get_index(int): Error element: " << el << " not found.\n"; 
	throw std::string( ss.str() );
}

// sorts underlying data and returns a sorted vector, heap gets emptied out
std::vector<int> min_heap::sort( bool cpy )
{
	std::vector<int> sorted_data, tmp;
	if( cpy )
	{
		//tmp.swap( data );
		tmp = data;
	}
	size_t sz = data.size();
	for(size_t i = 0; i < sz; i++)
	{	
		int min = extract_min();
		sorted_data.push_back( min );
	}
	if( cpy )
	{
		data.swap( tmp );
	}
	return sorted_data;
}

// return min element, does not delete element
int min_heap::get_min() const 
{
	if( data.size() > 0 )
		return data[0];
	else
		throw std::string("Error: get_min(): size of heap <= 0, exiting...");
}