#include "trie.h"
#include <algorithm>   // std::find


std::iostream& trie_node::operator << ( std::iostream& os )
{
	os << "element: " << ch << "\n\t" << std::endl;
	os << "children: ";
	for( auto& el : children )
		os << el.ch << "\t";
	os << std::endl;
	return os;
}

/* 
	 name and creates new branch for each unique character
	returns # of new nodes created
	@---t---r-------------y---*
	         \            \___i___n___g___*
	         \_i__p__*
*/
uint32_t trie_base::insert( const std::string& input )
{
	std::cout << "inserting " << input << " into the trie." << std::endl;
	// should handle case where input string is only 1 character in length 
	if( input.size() == 1 )
	{
		auto tmp_it = std::find_if( root->children.begin(), root->children.end(),
		[input]( trie_node nd )
		{
			return nd.ch == input[0];
		} );
		if( tmp_it == root->children.end() )
		{
			root->children.emplace_back(  *(new trie_node( input[0]) ) );
			num_nodes++;
            display_trie( *root );
			return 1;
		}
		else   // if found then just add a terminator if its not already there
		{
			if( !has_term( *tmp_it ) )
			{
				tmp_it->children.push_back( TERMINATOR );
				num_nodes++;
                display_trie( *root );
				return 1;
			}
            display_trie( *root );
			return 0; // this one letter word has already been entered in to the trie
		}
	}

	trie_node* 	tmp = root;
	uint32_t 	cnt = 0; 
	for( auto it = input.begin(); it != input.end(); it++ )
	{
		auto child_it = std::find_if( tmp->children.begin(), tmp->children.end(),
	   []( const trie_node& nd )
		{
			return (nd.ch == TERMINATOR);
		} );
		if( child_it == tmp->children.end() )
		{
			// if no terminator and last letter of word
			if( it == input.end()-1 )
			{
				tmp->children.emplace_back( *it );
				tmp->children.push_back( TERMINATOR );
				cnt+=2;
				num_nodes+=2;
                display_trie( *root );
				return cnt;
			}
		}
		child_it = std::find_if( tmp->children.begin(), tmp->children.end(),
		  [it]( const trie_node& nd )
		  {
			  return *it == nd.ch;
		  });
		if( child_it == tmp->children.end() )
		{
			// case where the child does not exists
			for( auto _it = it; _it != input.end(); _it++ )
			{
				tmp->children.emplace_back( *(new trie_node(*_it)) );
				tmp = &tmp->children.back();
				cnt++;
				num_nodes++;
			}
			tmp->children.push_back( TERMINATOR );
			break;
		}
		else
		{
			// Child does exists 
			tmp = &*child_it;
		}
	}
	display_trie( *root );
	return cnt;
}


bool trie_base::has_term( const trie_node & nd ) const
{
	for( auto el : nd.children )
	{
		if( el.ch == TERMINATOR )
			return true;
	}
	return false;
}


void trie_base::display_trie( const trie_node& node ) const
{
	using std::cout;
	using std::endl;
	cout << node.ch << " --> ";
	cout << "children: ";
	for( size_t i = 0; i < node.children.size(); i++ )
	{
		cout << node.children[i].ch << " ";
	}
	cout << endl;
	// recurse to next child at this level
	for( auto nd : node.children )
		display_trie( nd );
}

/************************trie_predictor**************************/
size_t trie_predictor::find_matches( const std::string& query )
{
	possible_matches.clear();
	if( query.size() == 1 )
		return 0;
	trie_node* prediction_root = root;
	auto child_it = prediction_root->children.begin();
	for( auto chit = query.begin(); chit != query.end(); chit++ )
	{
		child_it = std::find_if( prediction_root->children.begin(), prediction_root->children.end(),
		[chit]( const trie_node& nd )
		{
			return *chit == nd.ch;
		});

		// match not found, no predictions
		if( child_it == prediction_root->children.end() )
			return 0;

		prediction_root = &*child_it;
	}
	// build matches from prediction node
	words_from_node( prediction_root, query );
	return possible_matches.size();
}

void trie_predictor::display_matches() const
{
	size_t cnt = 0;
	std::cout << "Displaying matches: " << std::endl;
	for( auto& el : possible_matches )
	{
		cnt++;
		std::cout << el << "\t" << std::endl;
		if( cnt == MAX_PER_LINE )
		{
			std::cout << std::endl;
			cnt = 0;
		}
	}
}

// maybe can be recursive to find words
void trie_predictor::words_from_node( trie_node* nd, const std::string& prefix )
{
	std::string predicted_word = prefix;
	for( auto it = nd->children.begin(); it != nd->children.end(); it++ )
	{
		if( it->ch == TERMINATOR )
		{
			possible_matches.push_back( predicted_word );
			return;
		}
		else // keep building word
		{
			std::cout << "adding letter: " << it->ch << std::endl;
			predicted_word+=it->ch;
		}
		if( it->children.size() )
			words_from_node( &*it, prefix );
	}
}










