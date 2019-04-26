#ifndef DATASTRUCTS_N_ALGOS_HASH_TABLE_H
#define DATASTRUCTS_N_ALGOS_HASH_TABLE_H
#include <memory>
#include <vector>
#include <utility>
#include <iostream>

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
template<class KeyType, class DataType>
struct HashTableNode {
	DataType data;
	KeyType key;
	std::shared_ptr<DataType> next;

	HashTableNode(): next(nullptr){}

	HashTableNode(KeyType key, const DataType& data)
	: data(data), key(key), next(nullptr) { }

	// cpy ctor
	HashTableNode(const HashTableNode& nd): {
		*this = nd;
	}

	// mv ctor
	HashTableNode(HashTableNode&& nd) noexcept {
		// invoke move assignment operator
		*this = std::move(nd);
	}

	// cpy operator
	HashTableNode& operator = (const HashTableNode& nd) {
		this->key = nd.key;
		this->data = nd.data;
		// jdebug :: can this be recursive
		if (nd.next)
			this->next = nd.next;
		else
			this->next = nullptr;
	}

	// mv assignment operator
	HashTableNode& operator = (HashTableNode&& nd) {
		this->key = std::move(nd.key);
		this->data = std::move(nd.data);
		if (nd.next)
			this->next = std::move(nd.next);
		else
			this->next = nullptr;
	}
};

template<typename KeyType, typename DataType>
class hash_table {
	using NodePtr = std::shared_ptr<HashTableNode<KeyType, DataType>>;
	std::vector<NodePtr> buckets;
	size_t n, k;

public:
	hash_table(): k(DEFAULT_BUCKET_CNT) {
		buckets.resize(k);
	}

	explicit hash_table(size_t bktCnt)
	: k(bktCnt) {
		buckets.resize(k);
	}

	~hash_table()= default;

	// [{()->()->()}, {()->()}, {()}, {()->()}]  << each {} is an entry , each entry contains a linked list of elements
	// R-Value data overload
	void put(const KeyType&& key, DataType&& data) {
		uint64_t bktInd = std::hash<KeyType>(key) % k;
		NodePtr& entry = buckets[bktInd];

		if (!entry) {  // new entry
			entry = std::make_shared<HashTableNode<KeyType, DataType>>(key, std::forward<DataType>(data));
			n++;
			return;
		}
		handleCollision(key, std::forward<DataType>(data));
	}

	inline size_t size() const { return n; }

private:
	// L-val
	void handleCollision(uint64_t bktInd, KeyType&& key, const DataType& data) {
		LOG << __FUNCTION__ << "(): calling l-value form" << END;
		NodePtr& entry = buckets[bktInd];
		NodePtr& tmp = entry;
		while (tmp->next) {
			if (key == tmp->key) { // update existing entry
				tmp->data = std::forward<DataType>(data);  // if data is r-value then this move is constant time O(1)
				return;
			}
			tmp->next = tmp->next->next;
		}
		// append to end of linkedlist
		tmp->next = std::make_shared<HashTableNode<KeyType, DataType>>(key, std::forward<DataType>(data));
		n++;
	}

	// R-val
	void handleCollision(KeyType&& key, const DataType&& data) {
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

	inline float getLoadFactor() const { return n/k; }
};


/*
 * Add custom specializations here
 */
#endif //DATASTRUCTS_N_ALGOS_HASH_TABLE_H
