#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <string>
#include <cstdlib>
#include <iostream>

class linked_list 
{
	class node
	{
	public:
		node* next;
		node* prev;
		int*  data;
	
		node(): next( nullptr ), prev( nullptr ), data( nullptr )
		{
		}

		node( const int& input ): next( nullptr ), prev( nullptr )
		{
			data = new int( input );
		}

		~node()
		{
			std::cout << "node dtor called, data: " << *data << std::endl;
		}
	};

private:
	node* root;

public:
	linked_list();
	linked_list( const int& );
	~linked_list();
	std::string to_string() const;
	void push_back( const int& );
	void push_front( const int& data );
	bool insert( const int&, const size_t& );
	void remove( const int& );
	size_t size() const;
	void delete_list();
};
#endif 	// end LINKED_LIST_H