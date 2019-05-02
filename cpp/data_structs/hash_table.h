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
struct Key {
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
struct KeyHasher {
	std::size_t operator()(const Key& k) const {
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
template<class KeyType, class DataType>
struct HashTableNode {
    using NodePtr = HashTableNode<KeyType, DataType>;
	KeyType key;
	DataType data;
	std::shared_ptr<NodePtr> next;

	HashTableNode()
	: next(nullptr) {
#ifdef TESTING_HASHTABLE
		LOG << "def ctor called" << END;
#endif
	}

	explicit HashTableNode(KeyType&& key)
    : key(std::move(key)),
    data() {
	    #ifdef TESTING_HASHTABLE
            LOG << "r-val key ctor called" << END;
        #endif
    }

	explicit HashTableNode(const KeyType& key)
	: key(key),
	data() {
        #ifdef TESTING_HASHTABLE
                LOG << "l-val key ctor called" << END;
        #endif
	}

	HashTableNode(std::pair<KeyType, DataType>&& keyval)
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
		LOG << "& pair ctor called" << END;
#endif
	}

	// cpy ctor
	HashTableNode(const HashTableNode& nd) noexcept {
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
	LOG << "cpy operator called, key=" << nd.key << END;
#endif
		this->key = nd.key;
		this->data = nd.data;
		// jdebug :: can this be recursive, will it recurse forever
		if (nd.next)
			this->next = nd.next;  // jdebug :: ensure that copying smart pointer just increments the ref counter
		else
			this->next = nullptr;
		return *this;
	}

	// mv assignment operator
	HashTableNode& operator = (HashTableNode&& nd) {
#ifdef TESTING_HASHTABLE
		LOG << "mv assignment operator called, val " << nd.data << END;
#endif
		this->key = std::move(nd.key);
		this->data = std::move(nd.data);
		if (nd.next) // jdebug :: ensure that copying smart pointer just increments the ref counter
			this->next = std::make_shared<HashTableNode<KeyType, DataType>>(std::move(*nd.next));
		else
			this->next = nullptr;
		return *this;
	}
};

/*
 * jdebug:
 *  - define iterator support *iter ==, ++, --, operators, begin(), end(), etc etc
 *  - implement to_string method
 *  - implement resize method
 *  - implement find method using iterators (like the std lib)
 *  - implement copy constructor
 *  - implement mv constructor
 *  - implement cpy assignment operator
 *  - implement mv assignment operator
 */
template<typename KeyType, typename DataType>
class HashTable {
	using NodePtr = std::shared_ptr<HashTableNode<KeyType, DataType>>;
    size_t n, k, bktSize;
	double maxLoadFactor;
    std::vector<NodePtr> buckets;

public:
	HashTable():
		n(0),
	    k(DEFAULT_BUCKET_CNT),
	    bktSize(DEFAULT_BUCKET_CNT),
	    maxLoadFactor(MAX_LOAD_FACTOR),
	    buckets(std::vector<NodePtr>(bktSize))
	    { }

	explicit HashTable(size_t bktCnt):
		n(0),
		k(bktCnt),
		bktSize(DEFAULT_BUCKET_CNT),
		maxLoadFactor(MAX_LOAD_FACTOR)
		{ }

	// cpy ctor
	HashTable(const HashTable& tbl):
		n(tbl.n),
		k(tbl.k),
		bktSize(tbl.bktSize),
		maxLoadFactor(tbl.maxLoadFactor),
		buckets(tbl.buckets) {
			#ifdef TESTING_HASHTABLE
				LOG << "cpy ctor called" << END;
			#endif
	}

	// mv ctor
	HashTable(HashTable&& tbl):
		n(tbl.n),
	    k(tbl.k),
	    bktSize(tbl.bktSize),
	    maxLoadFactor(tbl.maxLoadFactor),
	    buckets(std::move(tbl.buckets)) {
		#ifdef TESTING_HASHTABLE
				LOG << "mv ctor called" << END;
		#endif
	}

	// cpy assignment operator
	HashTable& operator = (const HashTable& tbl) {
		#ifdef TESTING_HASHTABLE
				LOG << "cpy assignment operator called" << END;
		#endif
		if (&tbl == this) return *this;
		n = tbl.n;
		k = tbl.k;
		bktSize = tbl.bktSize;
		maxLoadFactor = tbl.maxLoadFactor;
		buckets = tbl.buckets;
		return *this;
	}

	// mv assignment operator
	HashTable& operator = (HashTable&& tbl) {
		#ifdef TESTING_HASHTABLE
				LOG << "mv assignment operator called" << END;
		#endif
		if (&tbl == this) return *this;
		n = tbl.n;
		k = tbl.k;
		bktSize = tbl.bktSize;
		maxLoadFactor = tbl.maxLoadFactor;
		buckets = tbl.buckets; // std::move(tbl.buckets);
		return *this;
	}

	~HashTable()=default;

	inline uint64_t hashKey(KeyType&& key) const { return std::hash<KeyType>{}(std::move(key)) % k; }

	inline uint64_t hashKey(const KeyType& key) const { return std::hash<KeyType>{}(key) % k; }

	// l-value data overload
	void put(const std::pair<KeyType, DataType>& keyval) {
        #ifdef TESTING_HASHTABLE
                LOG << "l-value overload called, putting key=" << keyval.first << END;
        #endif
		uint64_t bktInd = hashKey(keyval.first);
		NodePtr& entry = buckets[bktInd];
		if (!entry) {  // new entry
			entry = std::make_shared<HashTableNode<KeyType, DataType>>(keyval);
			n++;
		} else
			handleCollision(bktInd, keyval);
		resize();
	}

	// r-value overload
	void put(std::pair<KeyType, DataType>&& keyval) {
        #ifdef TESTING_HASHTABLE
                LOG << "r-value overload called, putting key=" << keyval.first << END;
        #endif
		uint64_t bktInd = hashKey(keyval.first);
		NodePtr& entry = buckets[bktInd];
		if (!entry) {  // new entry
			entry = std::make_shared<HashTableNode<KeyType, DataType>>(std::move(keyval));
			n++;
		} else
			handleCollision(bktInd, std::move(keyval));
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
			tmp = tmp->next->next;
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
			tmp = tmp->next->next;
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

	friend std::ostream& operator << (std::ostream& os, const HashTable<KeyType, DataType>& table);

private:
	// L-val
	void handleCollision(uint64_t bktInd, std::pair<KeyType, DataType>&& keyval) {
		LOG << __FUNCTION__ << "(): calling r-value ref form" << END;
		NodePtr& entry = buckets[bktInd];
		NodePtr& tmp = entry;
		while (tmp && tmp->next) {
			if (keyval.first == tmp->key) { // update existing entry
                #ifdef TESTING_HASHTABLE
                    LOG << "updating existing entry with new data, key=" << keyval.first << END;
                #endif
				tmp->data = std::move(keyval.second);  // if data is r-value then this move is constant time O(1)
				return;
			}
			tmp->next = tmp->next->next;
		}
        if (tmp && tmp->key == keyval.first) {
            #ifdef TESTING_HASHTABLE
                LOG << "updating existing entry with new data, key=" << keyval.first << END;
            #endif
            // update existing entry with new data
            tmp->data = std::move(keyval.second);
        } else {
            #ifdef TESTING_HASHTABLE
                LOG << "appending entry to end of list, key=" << keyval.first << END;
            #endif
            // append to end of linkedlist
            tmp->next = std::make_shared<HashTableNode<KeyType, DataType>>(std::move(keyval));
            n++;
        }
	}

	// R-val
	void handleCollision(uint64_t bktInd, const std::pair<KeyType, DataType>& keyval) {
        #ifdef TESTING_HASHTABLE
                LOG << __FUNCTION__ << "(): calling l-value ref form" << END;
        #endif
		NodePtr& entry = buckets[bktInd];
		NodePtr& tmp = entry;
		while (tmp->next) {
			if (keyval.first == tmp->key) { // update existing entry
                #ifdef TESTING_HASHTABLE
                    LOG << "updating existing entry with new data, key=" << keyval.first << END;
                #endif
				tmp->data = keyval.second;  // if data is r-value then this move is constant time O(1)
				return;
			}
			tmp->next = tmp->next->next;
		}
        if (tmp && tmp->key == keyval.first) {
            #ifdef TESTING_HASHTABLE
                        LOG << "updating existing entry with new data, key=" << keyval.first << END;
            #endif
            // update existing entry with new data
            tmp->data = keyval.second;
        } else {
            #ifdef TESTING_HASHTABLE
                LOG << "appending entry to end of list, key=" << keyval.first << END;
            #endif
            // append to end of linkedlist
            tmp->next = std::make_shared<HashTableNode<KeyType, DataType>>(std::move(keyval));
            n++;
        }
	}

	inline double getLoadFactor() const {
        #ifdef TESTING_HASHTABLE
                LOG << "current load factor: " << n/static_cast<double>(k) << END;
        #endif
		return n/static_cast<double>(k);
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
std::ostream& operator << (std::ostream& os, const HashTable<KeyType, DataType>& table) {
	os << table.toString();
	return os;
}
#endif //DATASTRUCTS_N_ALGOS_HASH_TABLE_H
