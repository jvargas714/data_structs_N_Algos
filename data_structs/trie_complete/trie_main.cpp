#include <iostream>
#include <cstring>
#include "../trie.h"

using namespace std;
trie_base* handle_args( int argc, char** argv )
{
    trie_base* trie;
    if( !strcmp( argv[1], "manual" ) )
    {
        trie = new trie_predictor;
    }
    else if( !strcmp( argv[1], "file" ) )
    {
        cout << "Filling trie with words from " << argv[2] << endl;
        trie = new trie_predictor( string( argv[2] ) );
    }
    else
    {
        cout <<  "Error with input, exiting...." << endl;
        exit(1);
    }
    return trie;
}

int main( int argc, char** argv )
{
    trie_base* trie = handle_args( argc, argv );
    string input;
    string mode( argv[1] );
    if( mode == "manual" )
    {
        cout << "indefinately enter words to add to trie. To end session type 'end' " << endl;
        while( true )
        {
            cin >> input;

            if( !input.compare( "end" ) )
                break;
            cout << trie->insert( input ) << " nodes created" << endl;
            cout << "Total Nodes: " << trie->get_cnt() << endl;
            cout << "\n\n" << endl;
        }
    }
    while( true )
    {
        cout << "Enter a word to get predictions back based on whats in the trie." << endl;
        cin >> input;
        if( !input.compare( "end" ) )
            break;
        trie->find_matches( input );
        trie->display_matches();
    }
    delete trie;
    return 0;
}