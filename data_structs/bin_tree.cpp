#include "binary_tree.h"

using namespace std;

int main()
{	
	logger* log = logger::instance( "binary_tree.log" );

	int a, b, c, d, e, f;
	a = 111;
	b = 123;
	c = 665;
	d = 666;
	e = 150;
	f = 4;

	bst<int> tree( 11 );
	tree.insert( 6 );
	tree.insert( 7 );
	tree.insert( 77 );
	tree.insert( 66 );
	tree.insert(a);
	tree.insert(b);
	tree.insert(c);
	tree.insert(d);
	tree.insert(e);
	tree.insert(f);

	cout << "Size of tree: " << tree.size() << endl; 
	
	*log << "---------PREORDER TRAVERSAL---------->" << "\n";
	tree.display_nodes( PREORDER );
	log->log( "\n---------END PREORDER TRAVERSAL----------\n\n\n", false );

	*log << "----------INORDER TRAVERSAL-------------->" << "\n";
	tree.display_nodes( INORDER );
	log->log( "\n---------END INORDER TRAVERSAL----------\n\n\n", false );

	*log << "----------POSTORDER TRAVERSAL-------------->" << "\n";
	tree.display_nodes( POSTORDER );
	log->log( "\n---------END POSTORDER TRAVERSAL----------\n\n\n", false );


	return 0;
}