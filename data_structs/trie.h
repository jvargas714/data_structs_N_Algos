#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <unordered_map>

// typedefs & defines 
#define TERMINATOR '*'
#define ROOT_CHAR  '@'

/*
	TODO :: Create a dictionary class like a hash map data structure would be something like  
	A : {sorted vector to bin search through}
*/

// basic node for trie DS 
class trie_node 
{
public:
	char ch;
	// for O(1) searches
	std::vector<trie_nodes> children;
	trie_node(): ch( TERMINATOR ){}
	trie_node( const trie_node nd ): ch( nd.ch ), children( nd.children ){}
	trie_node( char c ): ch( c ){}
};

class trie_base
{
private:
	trie_node* root;
	uint32_t num_nodes;

public:
	trie_base(): root( new trie_node( ROOT_CHAR ) ), num_nodes(0){ };
	~trie_base(){ delete root; };  // TODO :: will need to traverse and delete every node
	
	/* 
		 name and creates new branch for each unique character
		returns # of new nodes created
	*/
	uint32_t insert( const std::string& input );


	
	// for debug purposes show contacts in trie
	inline void print_elements( const Names& names ) const
	{ 
		for( auto& name : names ) 
			std::cout << name << std::endl;
	}

	// public facing display for function for troubleshooting
	void display_trie() const;

private:
	// returns true if node has a TERMINATOR char '*'
	bool has_term( const trie_node& ) const;

	// helper function to get recursive display started 
	void _display_trie( const trie_node& node) const;

	// recursively goes through nodes to find terminators keeps count
	void count_terminators( const trie_node&, uint32_t& ) const;
};



/* Contains a vector with the current potential matches,
	-- will need some sort of output interface reference as well 
 */
class trie_predictor : public trie_base
{
	std::vector<std::string> possible_matches;
public:
	// kicker off predictor thread
	trie_predictor();

	// ctor with file name containing words to insert into the trie, kicks off predictor thread
	trie_predictor( std::string );

	// traverse tree to return true if a match exists, update the vector with all possible matches 
	bool possible_matches( const std::string& );

	// displays all possible matches
	void display_matches() const;

};


// TODO :: maybe some gui to test predictions as the user types.