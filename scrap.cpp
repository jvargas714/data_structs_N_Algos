#include <iostream>
#include <cstdio>
#include <utility>
#include <memory>
#include <stack>
#include <ios> 

// globals
template<typename T>
class node;
using namespace std;
typedef shared_ptr<node<int> > sptr_node;

// class def 
template<typename T>
class node
{
    typedef std::shared_ptr<node<T> > node_ptr;
    public:
        node_ptr                left;
        node_ptr                right;
        shared_ptr<T>           data;   // must implement < > and ==
        node();
        node( T&& );
        node( T& );
        ~node();
};


int main()
{   
    // test using smart pointers 
    int data = 11;
    int data2 = 55;
    node<int> root( 234 );
    stack<sptr_node&> stk;
    cout << std::hex << endl; 

    // check ref counts
    sptr_node sptr = std::make_shared<node<int> >( root );
    cout << "root: ref count: "     << sptr.use_count()         << "\n";
    cout << "root.left ref cout: "  << sptr->left.use_count()   << "\n";
    cout << "root.right ref cout: " << sptr->right.use_count()  << "\n";
    cout << "root.left.get(): "     << root.left.get()          << "\n";
    cout << "root.right.get(): "    << root.right.get()         << "\n"; 
    cout << "sptr.get(): "          << sptr.get()               << "\n";
    cout << "root.data address: "   << sptr->data << "\n\n"     << endl;

    // now trying to use the stack container
    stk.push( sptr->right );
    stk.push( sptr->left );

    // check addresses of data inside of stack
    cout << "addy before assignment in stack stk.top().get(): " << stk.top().get() << endl;
    stk.top() = make_shared<node<int> >( node<int>( data ) );      // insert node to left
    cout << "in stack stk.top()->data.get(): " << stk.top()->data.get() << endl;
    cout << "in stack addy stk.top().get(): " << stk.top().get() << endl;           // we end up with copies of these pointers inside of stack
    cout << "out of stack addy root.get() " << root.left.get() << "\n\n" << endl;
    stk.pop();


    cout << std::hex << &stk.top() << endl;
    stk.top() = make_shared<node<int> >( node<int>( 6969 ) );      // insert node to right 
    stk.pop();

    cout << "ref_count root->left : "   << root.left.get()  << endl;
    cout << "ref_count root->right : "  << root.right.get() << endl; 


    // test with non pointers (works) 
    /*
    stack<int*> istk;
    int i = 11;
    int j = 22;
    int k = 33;
    int* ptri = &i;

    istk.push( ptri );
    istk.push( &j );
    istk.push( &k );

    *istk.top() = 111;

    cout << k << endl;
    cout << *istk.top() << endl;
    */

// raw pointer test (no working either)
    /*
    int data = 11;
    int data2 = 55;
    sptr_node root = new node<int>(234);
    cout << "root->data : " << *root->data << endl; 
    stack<sptr_node> stk;

    // now trying to use the stack container
    stk.push( root->right );
    stk.push( root->left );

    stk.top() = new node<int>( data );      // insert node to left
    cout << std::hex << stk.top() << endl;
    stk.pop();

    stk.top() = new node<int>( 6969 );      // insert node to right 
    cout << std::hex << stk.top() << endl;
    stk.pop();

    cout << "ref_count root->left : "   << *root->left->data  << endl;
    cout << "ref_count root->right : "  << *root->right->data << endl; 

    delete root;
    delete root->left; 
    delete root->right;
    */


    cout << "Exiting program... " << endl;
    return 0;
}

// node implementations 
template<typename T>
node<T>::node()
{ 
    left    = nullptr;
    right   = nullptr;
    data    = nullptr;
}

template<typename T>
node<T>::node( T& t )
{
    left    = nullptr;
    right   = nullptr;
    data    = make_shared<T>( t );
}

template<typename T>
node<T>::node( T&& t )
{
    left    = nullptr;
    right   = nullptr;
    data    = make_shared<T>( std::move( t ) );
}

template<typename T>
node<T>::~node( )
{
    cout << "node(): Dtor called... " << "<" << this << "> " << "data address: " << data << endl;
}