#include <iostream>
#include <cstring>
#include "../trie.h"

trie_base* handle_args( int argc, char** argv )
{
    trie_base* trie;
    if( !strcmp( argv[1], "man" ) )
    {
        trie = new trie_predictor;
    }
    else if( !strcmp( argv[1], "file" ) )
    {
        std::cout << "Filling trie with words from " << argv[2] << std::endl;
        trie = new trie_predictor( std::string( argv[2] ) );
        std::cout << trie->get_word_cnt() << " words inserted into trie." << std::endl;
    }
    else
    {
        std::cout <<  "Error with input, exiting...." << std::endl;
        exit(1);
    }
    return trie;
}

int main( int argc, char** argv )
{
    trie_base* trie = handle_args( argc, argv );
    std::string input;
    std::string mode( argv[1] );
    if( mode == "man" )
    {
        std::cout << "Enter words to add to predictor trie. To end session type 'end'" << std::endl;
        while( true )
        {
            std::cin >> input;
            if( !input.compare( "end" ) )
                break;
            std::cout << trie->insert( input ) << " nodes created" << std::endl;
            std::cout << "Total Nodes: " << trie->get_cnt() << std::endl;
            std::cout << "\n\n" << std::endl;
        }
    }
    while( true )
    {
        std::cout << "Enter a word to get predictions back based on whats in the trie." << std::endl;
        std::cin >> input;
        if( !input.compare( "end" ) )
            break;
        trie->find_matches( input );
        trie->display_matches( std::cout );
    }
    delete trie;
    return 0;
}