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
*/
uint32_t trie_base::insert( const std::string& input )
{
#ifdef DEBUG
	std::cout << "inserting " << input << std::endl;
#endif
    word_bank[input] = input;
	if( input.size() == 1 )
	{
        auto tmp_it = has_child( *root, input[0] );
		if( tmp_it == root->children.end() )
		{
			root->children.emplace_back( input[0] );
			num_nodes++;
			return 1;
		}
		else
		{
			if( has_term( *tmp_it ) == tmp_it->children.end() )
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
            auto possible_last_letter_nd = has_child( *tmp, *it);
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
				if( has_term( *tmp ) == tmp->children.end() )
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
		if( has_term( *tmp ) != tmp->children.end() && (it == input.end()-1) )
		{
				return cnt;
		}

		// Case where we are not at the last letter in the word
        auto child_it = has_child( *tmp, *it );
		if( child_it == tmp->children.end() )
		{
			// child does not exists place rest of word down a new branch
			for( auto _it = it; _it != input.end(); _it++ )
			{
				tmp->children.emplace_back( *_it ); // [w, o, r, d]
				tmp = &tmp->children.back();
				cnt++;
				num_nodes++;
			}
			tmp->children.push_back( *(new trie_node(TERMINATOR)) );
			cnt++;
			break;
		}
		else  // means current node had the next lette of the word as a child so
		{
			tmp = &*child_it;
		}
	}
	return cnt;
}

Trie_node_it trie_base::has_term( trie_node& node ) const
{
    return std::find_if( node.children.begin(), node.children.end(),
      []( const trie_node& nd )
      {
          return (nd.ch == TERMINATOR);
      } );
}

Trie_node_it trie_base::has_child( trie_node& src_node, const char& target ) const
{
    return std::find_if( src_node.children.begin(), src_node.children.end(),
     [ target ]( const trie_node& nd )
     {
         return ( nd.ch == target );
     });
}

void trie_base::display_children( const trie_node& node, std::ostream& os ) const
{
    os << "Node: (" << node.ch << ")" << " Children: ";
    for( auto& nd : node.children )
        os << nd.ch << " ";
    os << std::endl;
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

/* Take a provided query string and match potential matches against what is the trie */
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
    std::cout << "Prediction root: (" << prediction_root->ch << ")" << std::endl;
    display_children( *prediction_root, std::cout );

	// build matches from prediction node
	words_from_node( prediction_root, query );
	return possible_matches.size();
}

void trie_predictor::display_matches( std::ostream& os ) const
{
	size_t cnt = 0;
	os << "Displaying matches: " << std::endl;
	for( auto& el : possible_matches )
	{
		cnt++;
		os << el << "\t" << std::endl;
		if( cnt == MAX_PER_LINE )
		{
			os << std::endl;
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

void trie_predictor::_display_trie( const trie_node& node, std::ostream& os ) const
{
    using std::endl;
    os << node.ch << " --> ";
    os << "children: ";
    for( size_t i = 0; i < node.children.size(); i++ )
    {
        os << node.children[i].ch << " ";
    }
    os << endl;
    // recurse to next child at this level
    for( auto nd : node.children )
        _display_trie( nd, os );
    os << endl;
}

void trie_predictor::display_trie( std::ostream& os) const
{
	_display_trie( *root, os );
}








