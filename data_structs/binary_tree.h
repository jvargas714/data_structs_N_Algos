#ifndef BINARY_TREE_H
#define BINARY_TREE_H 1
#include <cstdlib>          // rand(), size_t 
#include <iostream>         // cout, endl
#include <vector>           // vector, size_t
#include <stack>            // std::stack
#include <memory>           // unique_ptr<T>
#include "logger.h"         // logger
#include <sstream>          // std::stringstream

/*
    NOTES:
        -- bst insert function seems to work
        -- investigate whether these elements are going in as references or not
        -- implement display function 
        -- see if we can modify tree from references or not
    TODOs:
        1. finish traversals display
            ** need to finish breadth first display see https://www.cs.cmu.edu/~adamchik/15-121/lectures/Trees/trees.html
        2. redo _size(node& nd) function
        3. Have ctor to take init lists 
        4. have ctor to take array
*/

// global 
typedef unsigned int uint;
enum Traversals
{
    PREORDER,
    INORDER,
    POSTORDER,
    LEVELORDER
};

template<typename T>
class binary_tree;

// generic data node
template<typename T>
class node
{
    typedef std::shared_ptr<node<T> > node_ptr;
    friend class binary_tree<T>;
    public:
        node_ptr            left;
        node_ptr            right;
        std::shared_ptr<T>  data;   // must implement < > and ==

        // ctors 
        node();
        node( T& );
        node( T&& );
};


// standard binary tree abstract class
template<typename T>
class binary_tree
{
    typedef std::shared_ptr<node<T> > node_ptr;
    typedef std::stack<node_ptr> node_stack;    
    
    public:
        //ctors & dtor
        binary_tree();
        binary_tree( T& );
        binary_tree( T&& );
        virtual ~binary_tree( );
        
        // find node in tree, can specify traversal algo
        virtual T& find( T&, Traversals )=0;
        virtual T& find( T& )=0;
        
        // insert element in to tree left to right, maintains balanced branches an rvalue
        virtual void insert( T&& )=0;    // rvalue ref 
        virtual void insert( T& )=0;     // lvalue ref


        // returns number of nodes in tree
        size_t size() const;
        
        // displays data to log file or stdout
        void display_nodes( Traversals )    const;

        // depth first
        void        preorder_trav()         const;
        void        inorder_trav()          const;
        void        postorder_trav()        const;

        // breadth first
        void        levelorder_trav()       const;


    protected:
        virtual void log_element( const T&) const;
        node_ptr    root;
        size_t      __size;
        logger*     log;
        void        _size( node_ptr& );
        void        _preorder_trav( const node_ptr& ) const;
        void        _inorder_trav( const node_ptr& ) const;
        void        _postorder_trav( const node_ptr& ) const;
        void        _levelorder_trav( const node_ptr& ) const;
};

/*
    Binary Search Tree data must be comparable
        1. left child is always < parent node
*/
template <typename T>
class bst : public binary_tree<T>
{
    using binary_tree<T>::log;  // need to specify scope with templated derived classes 
    using binary_tree<T>::root;
    using binary_tree<T>::__size;
    typedef std::shared_ptr<node<T> > node_ptr;

    public:
        bst();
        bst( T& );
        bst( T&& );
        virtual ~bst();
        virtual T& find( T&, Traversals );
        virtual T& find( T& );
        virtual void insert( T& );
        virtual void insert( T&& );

    private:
        void _insert( node_ptr&, T& );
        void _insert( node_ptr&, T&& );
};



///////////////////////////////////////////Implementation///////////////////////////////////////////

//------------------------------------node implementations------------------------------------------
template<typename T>
node<T>::node() : 
    left(  node_ptr() ), 
    right( node_ptr() ),
    data(  std::shared_ptr<T>() )
{}

template<typename T>
node<T>::node( T& t ) :
    left(  node_ptr() ), 
    right( node_ptr() ),
    data(  std::shared_ptr<T>( new T( t ) ) )
{}

template<typename T>
node<T>::node( T&& t ) :
    left(  node_ptr() ), 
    right( node_ptr() ),
    data(  std::shared_ptr<T>( new T( std::move( t ) ) ) )
{}

//-----------------------------------binary_tree implementations------------------------------------
template<typename T>
binary_tree<T>::binary_tree()
:  root( node_ptr( new node<T> ) ),
    __size(0),
    log( logger::instance("binary_tree.log") )
{
    #ifdef LOGGING_ON
        log->set_mode( D );
        *log << FN << "Log mode set to DEBUG, size of tree: " << __size << "\n";
    #else
        log->set_mode( "OFF" );
    #endif
    
}

template<typename T>
binary_tree<T>::binary_tree( T& t )
: root( node_ptr( new node<T> ) ),
    __size(0),
    log( logger::instance("binary_tree.log") )
{
    root->data = std::make_shared<T>( t );
    __size++;

    #ifdef LOGGING_ON
        log->set_mode(D);
        *log << FN << "Log mode set to DEBUG, size of tree: " << __size << "\n";
    #else
        log->set_mode("OFF");
    #endif
}

template<typename T>
binary_tree<T>::binary_tree( T&& t )
: root( node_ptr( new node<T> ) ),
    __size(0),
    log( logger::instance("binary_tree.log") )
{
    root->data = std::make_shared<T>( t );
    __size++;

    #ifdef LOGGING_ON
        log->set_mode( D );
        *log << FN << "Log mode set to DEBUG, size of tree: " << __size << "\n";
    #else
        log->set_mode("OFF");
    #endif

}

template<typename T>
binary_tree<T>::~binary_tree()
{
    // unique pointers go out of scope and are destroyed
    // reset smart pointer ref count
    // std::cerr << "calling bin tree dtor..." << std::endl;
    #ifdef LOGGING_ON
        log->flush_log( true );
    #endif

    root.reset();
}

// Recursively counts the elements in the tree
template<typename T>
void binary_tree<T>::_size( node_ptr& nd )
{
    // TODO: implement a recursive function to count nodes
}

template<typename T>
size_t binary_tree<T>::size() const
{
    return __size;
}

// display function shows data left to right then down 
template<typename T>
void binary_tree<T>::display_nodes( Traversals trav ) const
{
    // TODO:: implement function based on traversal methods here use a switch statement
	switch( trav )
	{
		case PREORDER:
            preorder_trav();
            break;
        case INORDER:
            inorder_trav();
            break;
        case POSTORDER:
            postorder_trav();
            break;
        case LEVELORDER:
            levelorder_trav();
            break;
        default:
            *log << FN << "Traversal method not found\n";
	}
}


// parent, exhaust left, then go right
template<typename T>
void binary_tree<T>::preorder_trav( ) const
{
    // first go down left side of tree
    _preorder_trav( root );
}


// preorder traversal :: this checks successfully
template<typename T>
void binary_tree<T>::_preorder_trav( const node_ptr& nd ) const
{
    if( !nd )
    {
        log->flush_log();
        return;
    }
    // display and go down left side first then right
    log_element( *nd->data );
    _preorder_trav( nd->left );
    _preorder_trav( nd->right );
    log->flush_log(  );
}

 
// left subtree, parent, right subtree 
// displays elements in increasing order
template<typename T>
void binary_tree<T>::_inorder_trav( const node_ptr& nd ) const 
{
    if( !nd )   // check if null first
    {
        return;
    }

    // travel down left side to smallest element before printing anything
    _inorder_trav( nd->left );
    log_element( *nd->data );
    _inorder_trav( nd->right );
    log->flush_log(  );
}


template<typename T>
void binary_tree<T>::inorder_trav() const 
{
    _inorder_trav( root );
}

// this a breadth first level based traversal top to bottom of tree
// must be non-recursive
template<typename T>
void binary_tree<T>::_levelorder_trav( const node_ptr& nd ) const
{
    if( nd )
    {
        log_element( *nd->data );
    }

    //for()
}


template<typename T>
void binary_tree<T>::levelorder_trav() const 
{
    _levelorder_trav( root );
}

// start at most extreme left, then prioritize as such Left, Right, then Parent
template<typename T>
void binary_tree<T>::_postorder_trav( const node_ptr& nd ) const 
{
    if( !nd )
    {
        return;
    }

    _postorder_trav( nd->left );
    _postorder_trav( nd->right );
    log_element( *nd->data );
    log->flush_log();

}


template<typename T>
void binary_tree<T>::postorder_trav() const 
{
    _postorder_trav( root );
}

template<typename T>
void binary_tree<T>::log_element( const T& t ) const
{
    // simple function to log element
    std::stringstream ss;
    ss << t << " ";
    log->log( ss.str(), false );
}
//-----------------------------------bst implementations--------------------------------------------
template<typename T>
bst<T>::bst() : binary_tree<T>() {}


template<typename T>
bst<T>::bst( T& t ) : binary_tree<T>( t ) {}


template<typename T>
bst<T>::bst( T&& t ) : binary_tree<T>( std::move(t) ) {}


template<typename T>
bst<T>::~bst() {}


template<typename T>
void bst<T>::insert( T&& t )  // rvalue data input 
{
    _insert( this->root, std::move( t ) ); // need specify scope to access protected members from base
}

template<typename T>
void bst<T>::insert( T& t )   // lvalue reference data input 
{   
    _insert( this->root, t ); // need specify scope to access protected members from base
}


template<typename T>
void bst<T>::_insert( node_ptr& rt, T& t )
{  
    // *log << FN << "lval^data: " << t << "\n";
    log->flush_log();

    if( !rt )
    {
        *log << FN << "Inserting data: " << t << "\n";
         log->flush_log();
        rt = std::make_shared<node<T> >(
                node<T>( t )
            );
        __size++;
        return;
    }
    else if( t < *rt->data )
    {

        // *log << FN << "calling left side " << t << "\n";
        _insert( rt->left, t );
    }
    else
    {
        // *log << FN << "calling right side " << t << "\n";
        _insert( rt->right, t );
    }
}


template<typename T>
void bst<T>::_insert( node_ptr& rt, T&& t )
{  
    // *log << FN << "rval^data: " << t << "\n";
    log->flush_log();

    if( !rt )
    {
        *log << FN << "Inserting data: " << t << "\n";
         log->flush_log();
        rt = std::make_shared<node<T> >(
                node<T>( t )
            );
        __size++;
        return;
    }
    else if( t < *rt->data )
    {
        // *log << FN << "calling left side " << t << "\n";
        _insert( rt->left, std::move(t) );
    }
    else
    {
        // *log << FN << "calling right side " << t << "\n";
        _insert( rt->right, std::move(t) );
    }
}



template<typename T>
T& bst<T>::find( T& t, Traversals trav )
{
    return t;
}


template<typename T>
T& bst<T>::find( T& t )
{
    return t;
}



// external functions 
template<typename T>
std::ostream& operator<<( std::ostream& os, const std::shared_ptr<node<T> >& nd )
{
    os << *nd->data;
    return os;
}
#endif 
