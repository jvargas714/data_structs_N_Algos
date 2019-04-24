#ifndef DATASTRUCTS_N_ALGOS_HASH_TABLE_H
#define DATASTRUCTS_N_ALGOS_HASH_TABLE_H
#include <memory>
#include <vector>

constexpr uint64_t DEFAULT_BUCKET_CNT = 100;
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
class HashTableNode {
	DataType data;
	KeyType key;
	std::unique_ptr<DataType> next;
	HashTableNode() = default;
	HashTableNode(KeyType key, const DataType& data)
	: data(data), key(key) {

	}
};

template<typename KeyType, typename DataType>
class hash_table {
	using NodePtr = std::unique_ptr<HashTableNode<KeyType, DataType>>;
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

	void put(KeyType key, DataType data) {
		uint64_t bktInd = std::hash<KeyType>(key) % k;
		NodePtr& entry = buckets[bktInd];

		if (!entry) {  // new entry

		} else if (key == entry->key) { // update existing entry

		} else {  // deal with collision

		}
	}
};

/*
 * Add custom specializations here
 */
#endif //DATASTRUCTS_N_ALGOS_HASH_TABLE_H
