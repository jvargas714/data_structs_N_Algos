-//
// Created by jay on 12/7/16.
//

#ifndef DATA_STRUCTS_QUEUE_H
#define DATA_STRUCTS_QUEUE_H
#include "node.h"
#include <cstdlib>
#include <stdexcept>
#define LINE_LEN 30

/* simple queue implemented using doubly linked list */
template<typename T>
class queue
{
private:
    node<T>* _front;
    node<T>* _rear;
    size_t  _size;

public:
    /* ctors & dtor */
    queue(): _front(nullptr), _rear(nullptr), _size(0){};
    queue(T t): _front(t), _rear(nullptr), _size(1){ _front->next = _rear; };
    ~queue();

    /* place element in the rear */
    void enqueue( const T& t );

    /* pop the front element */
    T dequeue();

    /* get size of queue */
    inline size_t size() const noexcept { return _size; };

    /* peek front element */
    inline T& front() const { return _front->data; };

    /* peek rear element */
    T& rear() const { return _rear->data; };

    /* check if queue is empty */
    inline bool empty() const noexcept { return (bool)_size; };

    /* Debug function to display elements */
    void display();
};



/*------------------------------------------------------------------------------------------------*/
/* front<---()<---()<---rear */
template<typename T>
void queue<T>::enqueue(const T& t)
{
    node<T>* temp;
    if( !_front )
    {
        temp        = new node<T>( t );
        _front      = temp;
        /* in-case of no elements at the last line of this function
         * both the rear and front point to the new element*/
    }
    else
    {
        // place new element in rear of queue
        temp = new node<T>( t );
        _rear->next = temp;         // f-->()-->()-->(rear ptr)-->(tmp)
    }
    _rear = temp;                   // f-->()-->()-->(prev rear)-->(rear ptr)
    _size++;
}

/* front<---()<---()<---rear */
template<typename T>
T queue<T>::dequeue()
{
    if( !_front )
        throw std::string("ERROR:: Queue is empty!!");

    // remove front and bring one behind it up
    node<T>* tmp = _front;
    T data  = _front->data;
    _front  = _front->next;
    _size--;
    delete tmp;
    return data;
}

// places numbers in an aligned square
template<typename T>
void queue<T>::display()
{
    size_t tmp_sz = _size;
    std::string delim;
    std::cout << "Size of queue: " << _size << std::endl;
    for( size_t i = 1; i <= tmp_sz; ++i )
    {
        T t = dequeue();

        if ( t < 10 ) delim = "     ";
        else if( t >= 10 && t < 100 ) delim = "    ";
        else if ( t >= 100 ) delim = "   ";

        std::cout << t << delim;

        if( i % LINE_LEN == 0 )
            std::cout << std::endl;
    }
}

template<typename T>
queue<T>::~queue()
{
    for( int i = 0; i < _size; i++ )
        dequeue();
}

#endif //DATA_STRUCTS_QUEUE_H
