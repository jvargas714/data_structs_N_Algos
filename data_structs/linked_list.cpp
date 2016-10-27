#include "linked_list.h"
#include <sstream>

linked_list::linked_list(): root( nullptr )
{}

linked_list::linked_list( const int& data )
{
	root = new node( data );
}

/* deallocate memory before list is destroyed */
linked_list::~linked_list()
{
	delete_list();
}

/* deletes entire linked_list leaving root null */
void linked_list::delete_list()
{
	node* current = root;
	node* next;
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
	std::cout << "linked_list::push_back(): " << data << std::endl;
	if( !root )
	{
		std::cout << "linked_list::push_back(): root is null" << std::endl;
		root = new node( data );
		std::cout << "end push back" << std::endl;
		return;
	}
	node* tmp_node = root;
	while( tmp_node->next != nullptr )
	{
		tmp_node = tmp_node->next;
	}
	tmp_node->next = new node( data );
}

/* place new data in front of the linked list */
void linked_list::push_front( const int& data )
{
	std::cout << "linked_list::push_front(): " << data << std::endl;
	node* entry = new node( data );
	node* tmp 	= root;
	root 		= entry;
	root->next 	= tmp;
}

/* returns true on successful insertion, returns false on failure */ 
bool linked_list::insert( const int& data, const size_t& index )
{
	std::cout << "linked_list::insert(): data: " << data << " index: " << index << std::endl;
	if( size() < index+1 )
	{
		return false;
	}
	else if( index == 0 )
	{
		push_front( data );
		return true;	
	}
	node* entry 	= new node( data );
	node* 	tmp 	= root;
	size_t  cnt 	= 0;

	while( cnt != index-1 )
	{
		tmp = tmp->next;
		cnt++;
	}
	node* tmp2 = tmp->next;
	tmp->next = entry;
	tmp->next->next = tmp2;
	return true;
}

/* function to interate through list to find the size of the list */
size_t linked_list::size() const
{	
	std::cout << "linked_list::size(): " << std::endl;
	if( !root )
	{
		return 0;
	}
	size_t cnt 	= 0;
	node* tmp 	= root;
	while( tmp )
	{
		tmp = tmp->next;
		cnt++;
	}
	return cnt;
}

std::string linked_list::to_string() const 
{
	std::cout << "linked_list::to_string(): " << std::endl;
	const node* nd = root;
	std::stringstream ss;
	ss << "Length of list: " << size() << std::endl;
	while( nd != nullptr )
	{
		ss << *nd->data << " ";
		nd = nd->next;
	}
	ss << std::endl;
	return ss.str();
}