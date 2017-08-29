#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <string>
#include <cstdlib>
#include <iostream>
#include "node.h"

using llnode = node<int>;
using dlnode = dl_node<int>;

// common interface for both types of linked lists
class linked_list_base 
{
public:
	virtual std::string to_string() const{ return "Must Implement"; };
	virtual void push_back( const int& )=0;
	virtual void push_front( const int& data )=0;
	virtual bool insert( const int&, const size_t& )=0;
	virtual bool remove( const size_t& )=0;
	virtual size_t size() const=0;
	virtual void delete_list()=0;
};

class linked_list : public linked_list_base
{
	llnode* root;

public:
	linked_list();
	linked_list( const int& );
	linked_list( const linked_list& );
	~linked_list();
	std::string to_string() const;
	void push_back( const int& );
	void push_front( const int& data );
	bool insert( const int&, const size_t& );
	bool remove( const size_t& );
	int &operator[](int i);
	size_t size() const;
	void delete_list();
	llnode* data(){ return root; }
};

class dlinked_list : public linked_list_base
{ 
	dlnode* root;

public:
	dlinked_list();
	dlinked_list(const int&);
	~dlinked_list();
	std::string to_string() const;
	void push_back( const int& );
	void push_front( const int& data );
	bool insert( const int&, const size_t& );
	bool remove( const size_t& );
	size_t size() const;
	void delete_list();
};

#endif 	// end LINKED_LIST_H
