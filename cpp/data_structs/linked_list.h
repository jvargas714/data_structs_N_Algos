#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iostream>	 			// std::cout, std::endl
#include "node.h" 				// node<int> dl_node<int>
#include <initializer_list> 	// std::initializer_list
#include <sstream>

// common interface for both types of linked lists
template<class DataType>
class linked_list_base 
{
public:
	virtual void push_back(DataType&&=0);
	virtual void push_back(const DataType&)=0;

	virtual void push_front(const DataType& data)=0;
	virtual void push_front(DataType&&)=0;

	virtual bool insert(const DataType&, size_t)=0;
	virtual bool insert(DataType&&, size_t)=0;

	virtual bool remove(const DataType&)=0;
	virtual bool remove(DataType&&)=0;

	virtual size_t size() const=0;

	virtual void delete_list()=0;

	virtual std::string to_string() const noexcept { return "Must Implement"; };
};

template<class DataType>
class linked_list : public linked_list_base<DataType>
{
	using llnode = node<DataType>;
	llnode* root;
	llnode* tail;
	size_t len;

public:
	linked_list()
	: root(nullptr),
	tail(nullptr),
	len(0) {}

	explicit linked_list(const DataType& data)
	: root(new node<DataType>(data)),
	tail(root),
	len(1) {}

	linked_list(const std::initializer_list<DataType>& data)
	: root(nullptr),
	tail(nullptr),
	len(0) {
		if (data.size() == 0) {
			root = nullptr;
			return;
		}
		root = new llnode(data[0]);
		++len;
		llnode* nd = root;
		tail = root;
		for (const auto& el : data.begin()+1) {
			nd->next = new llnode(el);
			tail = nd->next;
			nd = nd->next;
			++len;
		}
	}

	linked_list(std::initializer_list<DataType>&& data)
	: root(nullptr),
	tail(nullptr),
		len(0) {
		if (data.size() == 0) {
			root = nullptr;
			return;
		}
		root = new llnode(std::move(data[0]));
		tail = root;
		llnode* nd = root;
		for (auto&& el : data) {
			nd->next = new llnode(std::move(el));
			tail = nd->next;
			nd = nd->next;
			++len;
		}
	}

	// cpy ctor
	linked_list( const linked_list& ll)
	: root(nullptr),
	tail(nullptr),
	len(0) {
		*this == ll;
	}

	// cpy assignment op
	linked_list& operator = (const linked_list& ll) {
		clear();
		if (!ll.root) return *this;
		root = new llnode(ll.root);
		tail = root;
		llnode* tmp = root;
		llnode* tmp_in = ll.root;
		while (tmp_in) {
			tmp->next = new llnode(tmp_in->data);
			tmp = tmp->next;
			tail = tmp;
			tmp_in = tmp_in->next;
		}
	}

	// mv ctor
	linked_list(linked_list&& ll) noexcept
	:root(nullptr),
	tail(nullptr),
	len(0) {
		*this = std::move(ll);
	}

	linked_list& operator = (linked_list&& ll) {
		clear();
		if (!ll.root) return *this;
		root = std::move(ll.root);
		llnode* tmp = root;
		while (tmp->next) {
			tmp = tmp->next;
		}
		tail = tmp;
	}

	~linked_list() {
		llnode* nd = root;
		llnode* tmp = root;
		while (tmp) {
			tmp = nd->next;
			delete nd;
			nd = tmp;
		}
	}

	void clear() {
		if (!root) return;
		llnode* nxt = root->next;
		while (nxt) {
			delete root;
			root = nxt;
			nxt = nxt->next;
		}
		len = 0;
	}

	std::string to_string() const noexcept override {
		llnode* tmp = root;
		constexpr int LINE_LEN = 20;
		std::stringstream ss;
		int cnt = 0;
		ss << "size: " << len << "\n";
		while (tmp) {
			if (cnt > 0 && (cnt % LINE_LEN) == 0) {
				ss << "[" << tmp->data << "]\n";
			} else {
				ss << "[" << tmp->data << "]->";
			}
			++cnt;
			tmp = tmp->next;
		}
		ss << std::endl;
		return ss.str();
	}

	// appends node to the end of the list
	void push_back(DataType&& data) override {
		tail->next = new llnode(std::move(data));
		tail = tail->next;
		len++;
	}

	// appends node to the end of the list
	void push_back(const DataType& data) override {
		tail->next = new llnode(data);
		tail = tail->next;
		len++;
	}

	// places a new element at the front of the list
	void push_front(const DataType& data) noexcept override  {
		llnode* tmp = root;
		root = new llnode(data);
		root->next = tmp;
		len++;
	}

    void push_front(DataType&& data) noexcept override {
	    llnode* tmp = root;
	    root = new llnode(std::move(data));
	    root->next = tmp;
	    ++len;
	}

    bool insert(const DataType& data, const size_t pos) override {

	}

	bool insert (DataType&& data, const size_t pos) override {

	}

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
