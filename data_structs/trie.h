#ifndef __TRIE_H__
#define __TRIE_H__
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <unordered_map>

// typedefs & defines 
#define TERMINATOR '*'
#define ROOT_CHAR  '@'
#define MAX_PER_LINE 10

/*
	TODO :: Create a dictionary class like a hash map data structure would be something like  
	A : {sorted vector to bin search through}
*/
class trie_node;
typedef std::vector<trie_node> Nodes;
typedef std::vector<std::string> Predictions;

// basic node for trie DS 
class trie_node 
{
public:
	char ch;
	// for O(1) searches
	Nodes children;
	trie_node(): ch( TERMINATOR ){}
	trie_node( const trie_node& nd ): ch( nd.ch ), children( nd.children ){}
	trie_node( char c ): ch( c ){}
	std::iostream& operator << ( std::iostream& os );
};

class trie_base
{
protected:
	trie_node* root;
	uint32_t num_nodes;

public:
	trie_base(): root( new trie_node( ROOT_CHAR ) ), num_nodes(0){ };
	~trie_base(){ /*TODO:: run through all chidren and delete them */ }

	uint32_t insert( const std::string& input );
    inline size_t get_cnt() { return num_nodes; }

private:
	// returns true if node has a TERMINATOR char '*'
	bool has_term( const trie_node& ) const;

	// helper function to get recursive display started 
	void display_trie( const trie_node& node) const;

	// recursively goes through nodes to find terminators keeps count
	void count_terminators( const trie_node&, uint32_t& ) const;
};



/* Contains a vector with the current potential matches,
	-- will need some sort of output interface reference as well 
 */
class trie_predictor : public trie_base
{
	Predictions possible_matches;
public:
	// kicker off predictor thread
	trie_predictor(){}

	// ctor with file name containing words to insert into the trie, kicks off predictor thread
	trie_predictor( std::string );

	// traverse tree to return number of matches found if a match exists, updates vector with matches
	size_t find_matches( const std::string& );

	// displays all possible matches
	void display_matches() const;

private:
	// helper function to fill match vector
	void words_from_node( trie_node*, const std::string& );
};

#endif  // __TRIE_H__