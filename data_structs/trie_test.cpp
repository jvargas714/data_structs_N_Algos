#include "trie.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    int n;
    string type;
    contact_trie trie;
    std::string op;
    std::string contact;
    cout << "Input type: (file/stdout)?" << endl;
    cin >> type;

    if( type == "file" )
    {
    	ifstream fstrm("trie_test4.input");
    	fstrm >> n;

	    for( int a0 = 0; a0 < n; a0++ )
	    {
	        fstrm >> op >> contact;
	        if( op == "add" )
	        {
	            trie.insert_contact( contact );   
	        }
	        else if( op == "find")
	        {
	            std::cout << trie.find_partial( contact ) << std::endl;
	            // trie.display_trie( );
	        }
	    }
	    fstrm.close();
    }
    else
    {
	    std::cin >> n;
	        
	    for( int a0 = 0; a0 < n; a0++ )
	    {
	        std::cin >> op >> contact;
	        if( op == "add" )
	        {
	            trie.insert_contact( contact );   
	        }
	        else if( op == "find")
	        {
	            //std::cout << trie.find_partial( contact ) << std::endl;
	            trie.display_trie( );
	        }
	    }    	
    }

	return 0;
}