#ifndef __TRIE_H__
#define __TRIE_H__
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <string>
#include <map>

// typedefs & defines 
#define TERMINATOR '*'
#define ROOT_CHAR  '@'
#define MAX_PER_LINE 10
#define MAX_WORD_LENGTH 45

class   trie_node;
typedef std::vector<trie_node> Nodes;
typedef Nodes::iterator Trie_node_it;
typedef std::vector<std::string> Predictions;
typedef std::map<std::string, std::string> Word_bank;

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

/*
 * Abstract Base class for a trie data structure containing words
 */
class trie_base
{
protected:
	trie_node* root;
	Word_bank word_bank;
    uint32_t num_nodes;

public:
	trie_base(): root( new trie_node( ROOT_CHAR ) ), num_nodes(0){ };
	virtual ~trie_base(){ /*TODO:: run through all chidren and delete them */ }

	uint32_t insert( const std::string& input );
    inline size_t get_cnt() { return num_nodes; }
    virtual size_t find_matches( std::string )=0;
    virtual void display_matches( std::ostream& )const=0;
    virtual void display_trie( std::ostream& ) const=0;
    inline size_t get_word_cnt() const { return word_bank.size(); }

protected:
	// recursively goes through nodes to find terminators keeps count
	void count_terminators( const trie_node&, uint32_t& ) const;
	virtual void _display_trie( const trie_node& node, std::ostream& ) const=0;
    Trie_node_it has_child( trie_node& src_node, const char& target ) const;
    void display_children( const trie_node&, std::ostream& ) const;

private:
    // returns true if node has a TERMINATOR char '*'
    Trie_node_it has_term( trie_node& ) const;
};



/*
    Class that performs predictions based on prefix input from user
 */
class trie_predictor : public trie_base
{
	Predictions possible_matches;
public:
	// kicker off predictor thread
    // default ctor
	trie_predictor(){}

	// ctor with file name containing words to insert into the trie, kicks off predictor thread
	trie_predictor( std::string );

	// traverse tree to return number of matches found if a match exists, updates vector with matches
	size_t find_matches( std::string );

	// displays all possible matches
	void display_matches( std::ostream& ) const;

	// displays trie starting at the root 
	void display_trie( std::ostream& ) const;

protected:
    // display trie structure
    void _display_trie( const trie_node& node, std::ostream& ) const;

private:
	// helper function to fill match vector
	void words_from_node( trie_node&, std::string& );
};
#endif  // __TRIE_H__
