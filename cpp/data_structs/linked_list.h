#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iostream>	 			// std::cout, std::endl
#include "node.h" 				// node<int> dl_node<int>
#include <initializer_list> 	// std::initializer_list

// common interface for both types of linked lists
template<class DataType>
class linked_list_base 
{
public:
	virtual std::string to_string() const{ return "Must Implement"; };
	virtual void push_back( int )=0;
	virtual void push_front( const int& data )=0;
	virtual bool insert( const int&, const size_t& )=0;
	virtual bool remove( const size_t& )=0;
	virtual size_t size() const=0;
	virtual void delete_list()=0;
};

template<class DataType>
class linked_list : public linked_list_base<DataType>
{
	using llnode = node<DataType>;
	llnode* root;
	size_t len;

public:
	linked_list(): root(nullptr) {}

	explicit linked_list(const DataType& data) : root(new node<DataType>(data)) {}

	linked_list(const std::initializer_list<DataType>& data) {
		if (data.size() == 0) {
			root = nullptr;
			return;
		}
		root = new llnode(data[0]);
		llnode* nd = root;
		for_each(data.begin()+1, data.end(), [nd](const auto& el){
			nd->next = new llnode(el);
			nd = nd->next->next;
		});
	}

	linked_list(std::initializer_list<DataType>&& data) {
		if (data.size() == 0) {
			root = nullptr;
			return;
		}
		root = new llnode(std::move(data[0]));
		llnode* nd = root;
		for_each(data.begin()+1, data.end(), [nd](const auto&& el){
			nd->next = new llnode(std::move(el));
			nd = nd->next->next;
		});
	}

	// cpy ctor
	linked_list( const linked_list& ll) {
		*this == ll;
	}

	// cpy assignment op
	linked_list& operator = (const linked_list& ll) {
		clear();
		root = ll.root;
		llnode* tmp = ll.root;
		if (tmp) return *this;

		while (tmp->next) {

		}

	}

	// mv ctor
	linked_list(linked_list&& ll) noexcept {
		*this = std::move(ll);
	}

	linked_list& operator = (linked_list&& ll) {
		clear();
	}

	~linked_list();

	void clear() {
		if (!root) return;
		llnode* nxt = root->next;
		while (tmp) {
			delete root;
			root = nxt;
			nxt = nxt->next;
		}
		len = 0;
	}

	std::string to_string() const;

	void push_back( int );

	void push_front( const int& data );

	bool insert( const int&, const size_t& );

	bool remove( const size_t& );

	int &operator[](const size_t& i);

	llnode* getElement(const size_t&);

	size_t size() const;

	void delete_list();

	llnode* data(){ return root; }
};

// class dlinked_list : public linked_list_base
// { 
// 	dlnode* root;

// public:
// 	dlinked_list();
// 	dlinked_list(const int&);
// 	~dlinked_list();
// 	std::string to_string() const;
// 	void push_back( const int& );
// 	void push_front( const int& data );
// 	bool insert( const int&, const size_t& );
// 	bool remove( const size_t& );
// 	size_t size() const;
// 	void delete_list();
// };

#endif 	// end LINKED_LIST_H
