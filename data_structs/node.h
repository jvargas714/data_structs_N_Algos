

/* 
    ---- standard node class used in linked list, binary trees etc etc ----
    TODO: Template this bitch up
*/ 

class node 
{
    int data;
    node* left;
    node* right;

public:
    bool operator < ( node nd ) { return this->data < nd.data;  }
    bool operator > ( node nd ) { return this->data > nd.data; }
    bool operator == ( node nd ) { return this->data == nd.data; }    
    node() : data( 0 ), left( nullptr ), right( nullptr ){}
    node( int input ) : data( input ), left( nullptr ), right( nullptr ){}
};