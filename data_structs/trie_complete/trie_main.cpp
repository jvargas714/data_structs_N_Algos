#include <iostream>
#include "../trie.h"

using namespace std;
int main()
{
    trie_predictor trie ;
    string input;
    cout << "indefinately enter words to add to trie. To end session type 'end' " << endl;
    while( true )
    {
        cin >> input;

        if( !input.compare( "end" ) )
            break;

        cout << trie.insert( input ) << " nodes created" << endl;
        cout << "Total Nodes: " << trie.get_cnt() << endl;
        cout << "\n\n" << endl;
    }
    while( true )
    {
        cout << "Enter a word to get predictions back based on whats in the trie." << endl;
        cin >> input;
        if( !input.compare( "end" ) )
            break;
        trie.find_matches( input );
        trie.display_matches();

    }
    return 0;
}