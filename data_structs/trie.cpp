#include "trie.h"
#include <algorithm>    // std::find
#include <fstream>      // std::ifstream
#include "string_util.h"

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

	         TODO:: issue lies with terminator placement not at end, need to take another look at this
*/
uint32_t trie_base::insert( const std::string& input )
{
	std::cout << "inserting " << input << std::endl;
	if( input.size() == 1 )
	{
		auto tmp_it = std::find_if( root->children.begin(), root->children.end(),
		[input]( trie_node nd )
		{
			return nd.ch == input[0];
		} );
		if( tmp_it == root->children.end() )
		{
			root->children.emplace_back( input[0] );
			num_nodes++;
			return 1;
		}
		else
		{
			if( !has_term( *tmp_it ) )
			{
				tmp_it->children.push_back( *(new trie_node( TERMINATOR ) ) );
				num_nodes++;
				return 1;
			}
			return 0;
		}
	}
    // multi-letter word entry
	trie_node* 	tmp = root;
	uint32_t 	cnt = 0;
	for( auto it = input.begin(); it != input.end(); it++ )
	{
		// when we are processing the last letter of the word 
		if( it == input.end()-1 )
		{
			std::cout << "we have hit the last letter " << *it << std::endl;

			// Move tmp to last letter child if exists else just add both
			auto possible_last_letter_nd = std::find_if( tmp->children.begin(), tmp->children.end(), 
				[ it ]( const trie_node& nd ) 
				{
					return (nd.ch == *it);
				});
			if( possible_last_letter_nd == tmp->children.end() )
			{
				tmp->children.emplace_back( *it );
				tmp = &tmp->children.back();
				tmp->children.emplace_back( TERMINATOR );
				cnt+=2;
				return cnt;
			}
			else   // otherwise add a terminator if it isnt already there 
			{
				tmp = &*possible_last_letter_nd;
				if( !has_term( *tmp ) )
				{
					tmp->children.emplace_back( TERMINATOR );
					cnt++;
					return cnt;
				}
				else
				{
					return cnt;
				}
			}
		}
		std::cout << "Current letter: " << *it << std::endl;
		auto child_it = std::find_if( tmp->children.begin(), tmp->children.end(), // check if current node has a terminator or not
	    
	    // case where last letter and has a terminator
	    []( const trie_node& nd )
		{
			return (nd.ch == TERMINATOR);
		} );
		if( child_it != tmp->children.end() && (it == input.end()-1) )  // there is a term 
		{
				return cnt;
		}

		// Case where we are not at the last letter in the word 
		child_it = std::find_if( tmp->children.begin(), tmp->children.end(),
		  [it]( const trie_node& nd )
		  {
			  return *it == nd.ch;
		  });
		if( child_it == tmp->children.end() )
		{
			std::cout << "current node " << tmp->ch << " does not have " << *it << " as a child..." << std::endl;

			// child does not exists place rest of word down a new branch
			for( auto _it = it; _it != input.end(); _it++ )
			{
				std::cout << "Finishing rest of word down branch, adding " << *_it << std::endl;
				tmp->children.emplace_back( *_it ); // [w, o, r, d]
				tmp = &tmp->children.back();
				std::cout << "new current node: " << tmp->ch << std::endl;
				cnt++;
				num_nodes++;
			}
			std::cout << "Adding a terminator to node: " << tmp->ch << std::endl;
			tmp->children.push_back( *(new trie_node(TERMINATOR)) );  // add terminator to signify end of word d->[*]
			cnt++;
			break;
		}
		else  // means current node had the next lette of the word as a child so
		{
			std::cout << "Current node " << tmp->ch << " has child " << *it << std::endl;
			tmp = &*child_it;
			std::cout << "New current node " << tmp->ch << std::endl;
		}
	}
	return cnt;
}


bool trie_base::has_term( const trie_node& nd ) const
{
	for( auto el : nd.children )
	{
		if( el.ch == TERMINATOR )
			return true;
	}
	return false;
}

/***************************************trie_predictor*********************************************/
trie_predictor::trie_predictor( std::string file_name )
{
    std::ifstream fstrm( file_name );
    std::string word;
    while( fstrm.good() )
    {
        std::getline( fstrm, word );
        word = elim_whitespace( word );
        insert( word );
    }
}

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

void trie_predictor::_display_trie( const trie_node& node ) const
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
        _display_trie( nd );
    cout << endl;
}

void trie_predictor::display_trie() const
{
	_display_trie( *root );
}








