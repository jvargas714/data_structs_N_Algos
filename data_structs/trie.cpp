#include "trie.h"
#include <algorithm>   // std::find

/* 
	 name and creates new branch for each unique character
	returns # of new nodes created
	@---t---r-------------y---*
	         \            \___i___n___g___*
	         \_i__p__*
*/
uint32_t trie_base::insert( const std::string& input );
{
	// should handle case where input string is only 1 character in length 
	if( input.size() == 1 )
	{
		if( find( root.children.begin(), root.children.end(), input[0] ) ) == root.end() )
		{
			root.children.push_back( input[0] );
			num_nodes++;
			return 1;
		}
	}
	else
	{
		if( root.children.find( TERMINATOR ) == root.children.end() )
		{
			root.children.push_back( TERMINATOR );
			num_nodes++;
			return 1;
		}
		return 0;
	}

	trie_node* 	tmp = root;
	uint32_t 	cnt = 0; 
	for( std::string::iterator it = input.begin(); it != input.end(); it++ )
	{
		if( tmp->children.find( TERMINATOR ) == tmp->children.end() )  // no terminator found
		{
			// if no terminator and last letter of word
			if( it == input.end()-1 )
			{
				tmp->children.push_back( *it );
				tmp->children.push_back( TERMINATOR );
				cnt+=2;
				num_nodes+=2;
				return cnt;
			}
		}

		if( tmp>children.find( *it ) == tmp>children.end() )
		{
			// case where the child does not exists
			tmp.children.push_back( new trie_node( *it ) );
			cnt++;
			num_nodes++;

		}
		else
		{
			// Child does exists 
			tmp = *tmp.children[*it]; // wrong access we are using a vector here
			if( tmp.children.size() == 0 )
			{
				// enter rest of word in to trie structure
				for( std::string::iterator _it = it; _it != input.end(); _it++ )
				{
					tmp.children.push_back( new trie_node(*_it) );
					tmp = tmp.children[ tmp ];
					cnt++;
					num_nodes++;
				}
				break;
			}
		}
	}
	return cnt;
}

/*
	Returns vector of possible matches based on input string. Note that the input string does
	not have to be a full word.
*/
bool trie_predictor::possible_matches( const std::string& input )
{
	/*
		Algo:: 
		1. check if input string is only 1 char, if so return empty vector
		2. 
	*/
}
