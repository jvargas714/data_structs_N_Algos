#ifndef DATASTRUCTS_N_ALGOS_HASH_TABLE_H
#define DATASTRUCTS_N_ALGOS_HASH_TABLE_H
#include <array>
#include <iostream>
#include <memory>
#include <utility>
#include <sstream>
#include <vector>

#define LOG std::cout << __FUNCTION__ << "(): "
#define END std::endl

constexpr uint64_t DEFAULT_BUCKET_CNT = 100;
constexpr double MAX_LOAD_FACTOR = 0.75;
/*
 * Example:
 * Example of using custom classes for using std::hash, not part of implementation of the hash_table
 * can create a specialization using this type of Key
 *
 */
struct Key
{
	std::string first;
	std::string second;
	int         third;

	bool operator==(const Key &other) const
	{ return (first == other.first
	          && second == other.second
	          && third == other.third);
	}
};

// can define a Functor to be used as a hashing function in the unordered map or any unordered type
struct KeyHasher
{
	std::size_t operator()(const Key& k) const
	{
		using std::size_t;
		using std::hash;
		using std::string;

		return ((hash<string>()(k.first)
		         ^ (hash<string>()(k.second) << 1)) >> 1)
		       ^ (hash<int>()(k.third) << 1);
	}
};

/*
 * making use of our KeyHasher class
 * std::unordered_map<Key, MyData, KeyHasher> myMap;
 *
 */
// ====================================== End example ====================================




/*
 * Important for custom KeyTypes not supported by std::hash it would advisable to inject
 * a custom std::hash specialization in the std namespace i.e:
 * namespace std {
 *      template<> struct hash<S> {
 *          typedef S argument_type;  // where S has two string data members
	        typedef std::size_t result_type;
	        result_type operator()(argument_type const& s) const noexcept {
	            result_type const h1 ( std::hash<std::string>{}(s.first_name) );
	            result_type const h2 ( std::hash<std::string>{}(s.last_name) );
	            return h1 ^ (h2 << 1); // or use boost::hash_combine (see Discussion)
            }
 *      };
 * }
 *
 */

// KeyType must have a defined == and be hashable using std::hash
// may need to create a specialization for std::hash for this
// todo :: workout perfect forwarding ctor as well as move semantics
template<class KeyType, class DataType>
struct HashTableNode {
	KeyType key;
	DataType data;
	std::shared_ptr<DataType> next;

	HashTableNode(): next(nullptr) {
#ifdef TESTING_HASHTABLE
		LOG << "def ctor called" << END;
#endif
	}

	explicit HashTableNode(KeyType&& key)
	: data(),
	key(std::move(key))
	{}

	explicit HashTableNode(const KeyType& key)
	: data(),
	key(key)
	{}

	explicit HashTableNode(std::pair<KeyType, DataType>&& keyval)
		: key(std::move(keyval.first)),
		data(std::move(keyval.second)),
		next(nullptr) {
#ifdef TESTING_HASHTABLE
		LOG << "&& pair ctor called" << END;
#endif
	}

	explicit HashTableNode(const std::pair<KeyType, DataType>& keyval)
			: key(keyval.first),
			  data(keyval.second),
			  next(nullptr) {
#ifdef TESTING_HASHTABLE
		LOG << "&& pair ctor called" << END;
#endif
	}

	// cpy ctor
	HashTableNode(const HashTableNode& nd): {
#ifdef TESTING_HASHTABLE
		LOG << "cpy ctor called, val: " << nd.data << END;
#endif
		if (this != &nd)
			*this = nd;
	}

	// mv ctor
	HashTableNode(HashTableNode&& nd) noexcept {
#ifdef TESTING_HASHTABLE
		LOG << "mv ctor called val: " << nd.data << END;
#endif
		// invoke move assignment operator
		if (this != &nd)
			*this = std::move(nd);
	}

	// cpy operator
	HashTableNode& operator = (const HashTableNode& nd) {
#ifdef TESTING_HASHTABLE
	LOG << "cpy operator called val: " << nd.val << END;
#endif
		this->key = nd.key;
		this->data = nd.data;
		// jdebug :: can this be recursive, will it recurse forever
		if (nd.next)
			this->next = nd.next;
		else
			this->next = nullptr;
	}

	// mv assignment operator
	HashTableNode& operator = (HashTableNode&& nd) {
#ifdef TESTING_HASHTABLE
		LOG << "mv assignment operator called, val " << nd.data << END;
#endif
		this->key = std::move(nd.key);
		this->data = std::move(nd.data);
		if (nd.next)
			this->next = std::move(nd.next);
		else
			this->next = nullptr;
	}
};

/*
 * todo:
 *  - define iterator support *iter ==, ++, --, operators, begin(), end(), etc etc
 *  - implement to_string method
 *  - implement resize method
 *  - implement find method using iterators (like the std lib)
 */
template<typename KeyType, typename DataType>
class HashTable {
	using NodePtr = std::shared_ptr<HashTableNode<KeyType, DataType>>;
//	std::array<NodePtr, DEFAULT_BUCKET_CNT>* buckets;
	std::vector<NodePtr> buckets;
	size_t n, k, bktSize;
	double maxLoadFactor;

public:
	HashTable():
	k(DEFAULT_BUCKET_CNT),
	maxLoadFactor(MAX_LOAD_FACTOR),
	bktSize(DEFAULT_BUCKET_CNT) {
		buckets = std::vector<NodePtr>(bktSize);
	}

	explicit HashTable(size_t bktCnt)
	: k(bktCnt),
	  bktSize(DEFAULT_BUCKET_CNT),
	  maxLoadFactor(MAX_LOAD_FACTOR) { }

	~HashTable()= default;

	inline uint64_t hashKey(KeyType&& key) const { return std::hash<KeyType>(std::move(key)) % k; }

	inline uint64_t hashKey(const KeyType& key) const { return std::hash<KeyType>(key) % k; }

	// [{()->()->()}, {()->()}, {()}, {()->()}]  << each {} is an entry , each entry contains a linked list of elements
	// l-value data overload
	void put(const std::pair<KeyType, DataType>& keyval) {
#ifdef TESTING_HASHTABLE
		LOG << "l-value overload called" << END;
#endif
		const auto& key = keyval.first;
		const auto& data = keyval.second;

		uint64_t bktInd = hashKey(key);
		NodePtr& entry = buckets[bktInd];
		if (!entry) {  // new entry
			entry = std::make_shared<HashTableNode<KeyType, DataType>>(key, data);
			n++;
		} else
			handleCollision(bktInd, key, data);
		resize();
	}

	// r-value overload
	void put(std::pair<KeyType, DataType>&& keyval) {
#ifdef TESTING_HASHTABLE
		LOG << "r-value overload called" << END;
#endif
		uint64_t bktInd = hashKey(keyval.first);
		NodePtr& entry = buckets[bktInd];
		if (!entry) {  // new entry
			entry = std::make_shared<HashTableNode<KeyType, DataType>>(
					keyval.first,
					std::move(keyval.second)
					);
			n++;
		} else
			handleCollision(bktInd, key, std::move(keyval.second));
		resize();
	}

	DataType& operator [] (KeyType&& key) {
		uint64_t bktInd = hashKey(key);
		NodePtr& tmp = buckets[bktInd];
		if (!tmp) {
			tmp = std::make_shared<HashTableNode<KeyType, DataType>>(key);
			n++;
			return tmp->data;
		} else if (tmp->key == key)
			return tmp->data;

		while (tmp->next) {
			if (key == tmp->next->key) return tmp->next->data;
			tmp = entry->next->next;
		}
		// not found so create one
		tmp->next = std::make_shared<HashTableNode<KeyType, DataType>>(std::move(key));
		return tmp->next->data;
	}

	DataType& operator [] (const KeyType& key) {
		uint64_t bktInd = hashKey(key);
		NodePtr& tmp = buckets[bktInd];
		if (!tmp) {
			tmp = std::make_shared<HashTableNode<KeyType, DataType>>(key);
			n++;
			return tmp->data;
		} else if (tmp->key == key)
			return tmp->data;

		while (tmp->next) {
			if (key == tmp->next->key) return tmp->next->data;
			tmp = entry->next->next;
		}
		// not found so create one
		tmp->next = std::make_shared<HashTableNode<KeyType, DataType>>(key);
		return tmp->next->data;
	}

	inline size_t size() const noexcept { return n; }

	inline void setMaxLoadFactor(double val) noexcept { maxLoadFactor = val; }

	std::string toString() const noexcept {
		std::stringstream ss;
		ss << "size: " << size() << "\n";
		ss << "TODO :: IMPLEMENT ME PLEASE" << END;
		return ss.str();
	}

	friend std::ostream& operator << (std::ostream& os, HashTable<KeyType, DataType>& table);

//	iterator begin() {  }
//  iterator end() { }
private:
	// L-val
	void handleCollision(std::pair<KeyType, DataType>&& keyval) {
		LOG << __FUNCTION__ << "(): calling l-value form" << END;
		uint64_t bktInd = hashKey(keyval.first);
		NodePtr& entry = buckets[bktInd];
		NodePtr& tmp = entry;
		while (tmp->next) {
			if (keyval.first == tmp->key) { // update existing entry
				tmp->data = std::move(keyval.second);  // if data is r-value then this move is constant time O(1)
				return;
			}
			tmp->next = tmp->next->next;
		}
		// append to end of linkedlist
		// tmp->next = std::make_shared<HashTableNode<KeyType, DataType>>(key, std::forward<DataType>(data));
		tmp->next = std::make_shared<HashTableNode<KeyType, DataType>>(std::move(keyval));
		n++;
	}

	// R-val
	void handleCollision(uint64_t bktInd, KeyType&& key, const DataType&& data) {
		LOG << __FUNCTION__ << "(): calling r-value form" << END;
		NodePtr& entry = buckets[bktInd];
		NodePtr& tmp = entry;
		while (tmp->next) {
			if (key == tmp->key) { // update existing entry
				tmp->data = std::move(data);  // if data is r-value then this move is constant time O(1)
				return;
			}
			tmp->next = tmp->next->next;
		}
		// append to end of linkedlist
		tmp->next = std::make_shared<HashTableNode<KeyType, DataType>>(key, std::move(data));
		n++;
	}

	inline float getLoadFactor() const {
#ifdef TESTING_HASHTABLE
		LOG << "current load factor: " << n/k << END;
#endif
		return n/k;
	}

	// resizes map when load factor exceeds max allowed value
	void resize() {
#ifdef TESTING_HASHTABLE
		LOG << "current load factor: " << getLoadFactor()
		    << " maxLoadfactor: " << maxLoadFactor << END;
#endif
		if (getLoadFactor() > maxLoadFactor) {
#ifdef TESTING_HASHTABLE
			LOG << "resizing hash table!!!" << END;
#endif
		}
	}
};

// misc overloads
template<class KeyType, class DataType>
std::ostream& operator << (std::ostream& os, HashTable<KeyType, DataType>& table) {
	os << table.toString();
	return os;
}


/*
 * Add custom specializations here
 */
#endif //DATASTRUCTS_N_ALGOS_HASH_TABLE_H
