#include "linked_list.h"
#include <sstream>
#include <stdexcept>  // out_of_range


linked_list::linked_list(): root( nullptr )
{}

linked_list::linked_list( const int& data )
{
	root = new llnode( data );
}

// TODO :: define iterators to clean the loop up
linked_list::linked_list( const linked_list& ll )
{
	using namespace std;
	size_t llsize = ll.size();
	if ( !llsize )
	{
		root = nullptr;
		return;
	}
	llnode* tmp = ll.root;
	while ( tmp != nullptr )
	{
		push_back(tmp->data);
		tmp = tmp->next;
	}
}

/* deallocate memory before list is destroyed */
linked_list::~linked_list()
{
	delete_list();
}

/* deletes entire linked_list leaving root null */
void linked_list::delete_list()
{
	llnode* current = root;
	llnode* next;
	while( current )
	{
		next = current->next;
		delete current;
		current = next;
	}
	root = nullptr;
}

/* places element at end of linked list */
void linked_list::push_back( const int& data )
{
	// if no root the we simply add to front of llist as root
	if( !root )
	{
		root = new llnode( data );
		return;
	}
	llnode* tmp_node = root;
	while( tmp_node->next != nullptr )
	{
		tmp_node = tmp_node->next;
	}
	// once the finally hit a null ptr we can then assign the llnode
	tmp_node->next = new llnode( data );
}

/* place new data in front of the linked list */
void linked_list::push_front( const int& data )
{
	llnode* entry = new llnode( data );
	llnode* tmp 	= root;
	root 		= entry;   // root points to a new mem location 
	root->next 	= tmp;     // the next llnode now becomes the old root (which is still pointing to the rest of the data)
}

/* returns true on successful insertion, returns false on failure */ 
bool linked_list::insert( const int& data, const size_t& index )
{
	// if desired location is out of bounds, put data at end 
	if( size() < index+1 )
	{
		push_back( data );
	}
	else if( index == 0 )
	{
		push_front( data );
		return true;
	}
	llnode* entry 	= new llnode( data );
	llnode* 	tmp 	= root;
	size_t  cnt 	= 0;

	while( cnt != index-1 )
	{
		tmp = tmp->next;
		cnt++;
	}
	llnode* tmp2 = tmp->next;
	tmp->next = entry;
	tmp->next->next = tmp2;
	return true;
}

// remove element at index 
bool linked_list::remove( const size_t& index )
{
	if ( size() < index )
		return false;
	llnode* tmp = root;
	size_t cnt = 0;
	while( cnt != (index-1) ) 
	{
		tmp = tmp->next;
		cnt++;
	}	
	// deallocate data to be removed
	llnode* toBeDeleted = tmp->next;
	tmp->next = tmp->next->next;
	delete toBeDeleted;
	return true;
}

/* function to interate through list to find the size of the list */
size_t linked_list::size() const
{	
	if( !root )
	{
		return 0;
	}
	size_t cnt 	= 0;
	llnode* tmp 	= root;
	while( tmp )
	{
		tmp = tmp->next;
		cnt++;
	}
	return cnt;
}

std::string linked_list::to_string() const 
{
	const llnode* nd = root;
	std::stringstream ss;
	ss << "Linked List--->\nLength of list: " << size() << std::endl;
	while( nd != nullptr )
	{
		ss << nd->data << " ";
		nd = nd->next;
	}
	ss << std::endl;
	return ss.str();
}

int &linked_list::operator[](int i) 
{
	if( i > size() )
		throw std::out_of_range("Index out of range");
	llnode* tmp = root;
	for(size_t j = 0; j < i; ++j)
		tmp = tmp->next;
	return tmp->data;
}






