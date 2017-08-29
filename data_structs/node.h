#ifndef __NODE_H__
#define __NODE_H__

/* 
    ---- standard node class used in linked list, binary trees etc etc ----
*/

class bin_node
{
    int data;
    bin_node* left;
    bin_node* right;

public:
    bool operator < ( bin_node nd ) { return this->data < nd.data;  }
    bool operator > ( bin_node nd ) { return this->data > nd.data; }
    bool operator == ( bin_node nd ) { return this->data == nd.data; }
    bin_node() : data( 0 ), left( nullptr ), right( nullptr ){}
    bin_node( int input ) : data( input ), left( nullptr ), right( nullptr ){}
    int getLData() { return left->data; }
    int getRData() { return right->data; }
};

template<typename T>
struct node
{
    T data;
    node* next;
    node(): next(nullptr){};
    node(T t): data(t), next(nullptr){};
    bool operator < ( const node& nd ) { return this->data < nd.data; }
    bool operator > ( const node& nd ) { return this->data > nd.data; }
    bool operator == ( const node& nd ) { return this->data == nd.data; }
};

template<typename T>
struct dl_node
{
    T data;
    dl_node* next;
    dl_node* prev;
    bool operator <  ( dl_node nd )  { return this->data < nd.data;  }
    bool operator >  ( dl_node nd )  { return this->data > nd.data;  }
    bool operator == ( dl_node nd )  { return this->data == nd.data; }
    dl_node() : data( 0 ), next( nullptr ), prev( nullptr ){ }
    dl_node( T input ) : data( input ), next( nullptr ), prev( nullptr ){ }
};
#endif  // __NODE_H__