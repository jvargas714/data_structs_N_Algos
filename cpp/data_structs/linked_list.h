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
	virtual void push_back(DataType&&)=0;
	virtual void push_back(const DataType&)=0;

	virtual void push_front(const DataType& data)=0;
	virtual void push_front(DataType&&)=0;

	virtual bool insert(const DataType&, size_t)=0;
	virtual bool insert(DataType&&, size_t)=0;

	virtual bool remove(size_t)=0;

	virtual size_t size() const=0;

	virtual void clear()=0;

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

	// O(len)
	~linked_list() {
		llnode* nd = root;
		llnode* tmp = root;
		while (tmp) {
			tmp = nd->next;
			delete nd;
			nd = tmp;
		}
	}

	// O(len)
	void clear() override {
		if (!root) return;
		llnode* nxt = root->next;
		while (nxt) {
			delete root;
			root = nxt;
			nxt = nxt->next;
		}
		len = 0;
	}

	// O(len)
	std::string to_string() const noexcept override {
		llnode* tmp = root;
		constexpr int LINE_LEN = 10;
		std::stringstream ss;
		size_t cnt = 0;
		ss << "size: " << len << "\n";
		while (tmp) {
			if (tmp == tail) {
				ss << "[" << tmp->data << "]\n";
				break;
			}
			ss << "[" << tmp->data << "]->";
			if (++cnt % LINE_LEN == 0) ss << "\n";
			tmp = tmp->next;
		}
		ss << std::endl;
		return ss.str();
	}

	// appends node to the end of the list O(1)
	void push_back(DataType&& data) override {
		if (!tail) {
			root = new llnode(std::move(data));
			tail = root;
			len++;
			return;
		}
		tail->next = new llnode(std::move(data));
		tail = tail->next;
		len++;
	}

	// appends node to the end of the list O(1)
	void push_back(const DataType& data) override {
		if (!tail) {
			root = new llnode(data);
			tail = root;
			return;
		}
		tail->next = new llnode(data);
		tail = tail->next;
		len++;
	}

	// places a new element at the front of the list O(1)
	void push_front(const DataType& data) noexcept override  {
		if (!root) {
			root = new llnode(data);
			tail = root;
			len++;
			return;
		}
		llnode* tmp = root;
		root = new llnode(data);
		root->next = tmp;
		len++;
	}

	// O(1)
    void push_front(DataType&& data) noexcept override {
		if (!root) {
			root = new llnode(std::move(data));
			tail = root;
			len++;
			return;
		}
	    llnode* tmp = root;
	    root = new llnode(std::move(data));
	    root->next = tmp;
	    ++len;
	}

	// O(len)
    bool insert(const DataType& data, const size_t pos) override {
        if (pos >= len) return false;
        else if (pos == 0) {
            push_front(data);
            return true;
        }
        else if (pos == len-1) {
            push_back(data);
            return true;
        }
        if (!root)
        	return false;

	    llnode* prev = root;
        llnode* curr = prev->next;
	    size_t i = 0;

        while (curr && i != pos) {
            prev = curr;
            curr = curr->next;
            i++;
        }
        // [] -> [prev] -> [curr] -> [] -> []
        auto* tmp = new llnode(data);
        // [] -> [prev] ->
        // [tmp] -> [curr] -> [] -> []
        tmp->next = curr;
        // [] -> [prev] -> [tmp] -> [curr] -> [] -> []
        prev->next = tmp;
        len++;
        return true;
	}

    // O(len)
	bool insert(DataType&& data, const size_t pos) override {
        if (pos >= len) return false;
        else if (pos == 0) {
            push_front(std::move(data));
            return true;
        }
        else if (pos == len-1) {
            push_back(std::move(data));
            return true;
        }
        if (!root)
        	return false;

        llnode* prev = root;
        llnode* curr = prev->next;
        size_t i = 0;

        while (curr && i != pos) {
            prev = curr;
            curr = curr->next;
            i++;
        }
        // [] -> [prev] -> [curr] -> [] -> []
        auto* tmp = new llnode(std::move(data));

        // [] -> [prev] ->
        // [tmp] -> [curr] -> [] -> []
        tmp->next = curr;

        // [] -> [prev] -> [tmp] -> [curr] -> [] -> []
        prev->next = tmp;
        len++;
        return true;
	}

	// remove element at index pos O(n)
	bool remove(size_t pos) override {
        if (len == 0 || pos >= len) return false;
	    if (pos == 0) {
            llnode* newroot = root->next;
            delete root;
            root = newroot;
            len--;
            return true;
        }
        size_t i = 0;

	    if (!root)
	    	return false;

        llnode* curr = root;
        while (curr->next && i != (pos-1)) {
            curr = curr->next;
            i++;
        }
		if (pos == len - 1) {
			// delete tail and replace
			delete curr->next;
			curr->next = nullptr;
			tail = curr;
		} else if (curr->next) {
            llnode *tmp = curr->next->next;
            delete curr->next;
            curr->next = tmp;
        } else {
            return false;
        }
        len--;
        return true;
	}

    DataType& operator[](const size_t& pos) {
	    return getElement(pos);
	}

	DataType& getElement(size_t pos) {
        if (pos>= len || !root)
            throw std::out_of_range("index " + std::to_string(pos) + " is out of range!!");
        size_t i = 0;
        llnode* tmp = root;
        while(tmp && i++ != pos) {
            tmp = tmp->next;
        }
        if (!tmp) throw std::runtime_error("node is corrupt :(");
        return tmp->data;
	}

	inline size_t size() const override { return len; }

	llnode* getRoot() { return root; }
};

#endif 	// end LINKED_LIST_H
