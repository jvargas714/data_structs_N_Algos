#include <iostream>
#include <unordered_map>
#include <vector>

/*
	TODO: need to fix issue with input files tr_test4.input
	TODO: for a couple of files execution is too slow, see input file trie_test5.input
*/


// typedefs & defines 
typedef std::vector<std::string> Names;
typedef unsigned int uint;
#define TERMINATOR '*'

// fwd dec 
class contact_trie;

// basic node for trie DS 
class trie_node 
{
	friend class contact_trie;
	char ch;
	std::vector<trie_node> children;

public:
	trie_node(): ch( TERMINATOR ){}
	trie_node( const trie_node& nd ): ch( nd.ch ), children( nd.children ){}
	trie_node( char c ): ch( c ){}
};


/* 
	trie DS for contact list application
	IDEAS:
		- could have a container in class to hold full contact names
			** map, vector, set
*/
class contact_trie 
{
	
private:
	trie_node* root;
	//Names names;
	uint num_nodes;

public:
	contact_trie(): root( new trie_node ), num_nodes(0){ };
	~contact_trie(){ delete root; };
	
	/* 
		inserts contact name and creates new branch for each unique character
		returns # of new nodes created
	*/
	uint insert_contact( const std::string& );

	// traverses trie in search of contact based on partial word input
	// returns number of possible contacts u tree
	uint find_partial( const std::string& ) const;
	
	// for debug purposes show contacts in trie
	inline void print_contacts( const Names& names ) const
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
	void count_terminators( const trie_node&, uint& ) const;
};