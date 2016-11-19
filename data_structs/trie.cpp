#include "trie.h"

// insert contact and add respective branches for trie DS
uint contact_trie::insert_contact( const std::string& name )
{
	uint new_nodes;
	trie_node* tmp_node = root;

	// add to contact list
	//names.push_back( name );

	// if have no children then no need to traverse children
	if( !root->children.size() )
	{
		for( auto it = name.begin(); it != name.end(); ++it )
		{
			// when input single char words
			if( name.size() == 1 )
			{
				trie_node nd( *it );
				nd.children.push_back( trie_node() );
				tmp_node->children.push_back( nd );
				num_nodes+=2;
				return 2;
			}

			trie_node nd( *it );
			tmp_node->children.push_back( nd );
			
			if( (it+1) == name.end() )
			{
				tmp_node->children.push_back( trie_node() );
			}
			tmp_node = &tmp_node->children[ tmp_node->children.size()-1 ];
		}
		new_nodes = name.size()+1;
		num_nodes += new_nodes;
		return new_nodes;
	}
	int cnt = 0;
	bool found_node = false;

	// here we only add children to nodes that exist 
	for( auto it = name.begin(); it != name.end(); ++it )
	{
		found_node = false;
		for( uint i = 0; i < tmp_node->children.size(); ++i )
		{
			// check for match at one of the child nodes of tmp
			if( tmp_node->children[i].ch == *it )
			{
				// if match then move down the line to next node and break to next letter of name
				tmp_node = &tmp_node->children[i];
				found_node = true;
				break;
			}
		}

		// if not found then we can add rest of name to trie DS
		if( !found_node )
		{
			while( it != name.end() )
			{
				trie_node nd( *it );
				tmp_node->children.push_back( nd );
				tmp_node = &tmp_node->children[tmp_node->children.size()-1];
				it++;
				cnt++;
			}
			break;
		}
	}
	tmp_node->children.push_back( trie_node() ); 	// add * terminator to signify entry
	num_nodes += cnt + 1;
	return cnt; //	return # of new nodes to DS
}

/* 
	based on partial input of a possible contact 
	Matches must contain all letters of frag
		-- if not then no matches then 
		-- returns number of possible matches based on frag provided

*/
uint contact_trie::find_partial( const std::string& frag ) const
{
	trie_node* tmp_node = root;
	bool char_found = false;
	uint num_matches = 0;

	for( auto& c : frag )
	{
		char_found = false;
		for( auto& child : tmp_node->children )
		{
			if( child.ch == c )
			{
				//std::cout << child.ch << std::endl;
				tmp_node = &child;
				char_found = true;
				break;
			}
		}
		// if a character is not found then we have no matches
		if( !char_found )
		{
			return num_matches;
		}
	}

	/* 
		if we make it this far then we have some matches
		all that needs to be done is to count the TERMINATOR chars '*'
	*/
	count_terminators( *tmp_node, num_matches );
	return num_matches;
}


bool contact_trie::has_term( const trie_node& nd ) const
{
	for( auto& child : nd.children )
	{
		if( child.ch == TERMINATOR )
			return true;
	}
	return false;
}

void contact_trie::count_terminators( const trie_node& node, uint& count ) const
{
	for( auto& child : node.children )
	{
		if ( child.ch == TERMINATOR )
		{
			count++;
			return;
		}
		count_terminators( child, count );
	}
}

void contact_trie::display_trie( ) const
{
	_display_trie( *root );
}

void contact_trie::_display_trie( const trie_node& node ) const
{
	std::cout << "node: " << node.ch << std::endl;
	uint num_children = node.children.size(); 
	std::cout << "children: ";

	for( auto child : node.children )
	{
		std::cout << child.ch << " ";
	}
	std::cout << "\n" << std::endl;

	// recursively show subsequent node children as well 
	for( uint i = 0; i < num_children; i++ )
	{
		_display_trie( node.children[i] );
	}
}