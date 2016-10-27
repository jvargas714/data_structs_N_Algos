#ifndef STACK_H
#define STACK_H 1
#include <utility>      // std::move
#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <initializer_list>
#include <cstddef>
#include <cstring>

#define RESIZE_FACTOR 2

template<typename T>
class stack 
{
    private:
        size_t  _size;
        size_t  _buff_size;
        T*      _buff;

    public:
        stack( );
        stack( T& );
        stack( T&& );
        stack( std::initializer_list<T> );
        ~stack();
        void push( T& );
        void push( T&& );
        T& top() const;
        void pop();
        size_t size();

    private:
        void resize_buff( );

};


// implementations 
template<typename T>
stack<T>::stack() : _size( 0 ), _buff_size( 10 )
{
    _buff = new T[ _buff_size ];
}

template<typename T>
stack<T>::stack( T& t ) : _size( 1 ), _buff_size( 10 )
{
    _buff = new T[ _buff_size ];
    _buff[0] = t;
}

template<typename T>
stack<T>::stack( T&& t ) : _size( 1 ), _buff_size( 10 )
{
    _buff = new T[ _buff_size ];
    _buff[0] = t;
}

template<typename T>
stack<T>::stack( std::initializer_list<T> lst )
{
    _buff_size  = lst.size() + 10;
    _size       = lst.size();
    _buff       = new T[ _buff_size ];

    size_t cnt = -1;
    for ( auto& el : lst )
        _buff[ ++cnt ] = el;
}

template<typename T>
stack<T>::~stack( )
{
    delete[] _buff;
}

template<typename T>
void stack<T>::push( T& t )
{
    if( _size < _buff_size )
    {
        _buff[ _size-1 ] = t;
        _size++;
    }
    else // reallocate for more elements then push
    {   
        resize_buff( );
        _buff[ _size-1 ] = t;
        _size++;
    }
}

template<typename T>
void stack<T>::push( T&& t )
{
    if( _size < _buff_size )
    {
        _buff[ _size-1 ] = std::move( t );
        _size++;
    }
    else // reallocate for more elements then push
    {
        resize_buff( );
        _buff[ _size-1 ] = std::move( t );
        _size++;
    }
}

template<typename T>
T& stack<T>::top() const
{
    if (_size > 0 )
        return _buff[ _size-1 ];
    else
        throw std::length_error("stack::top(): ERROR, invalid index, exiting...");
}

template<typename T>
void stack<T>::pop()
{
    if ( _size == 0 )
        return;
    _size--;
}

template<typename T>
void stack<T>::resize_buff( )
{
    _buff_size *= RESIZE_FACTOR;
    T* resized_buff = new T[ _buff_size ];
    std::memcpy( resized_buff, _buff, _size * sizeof(T) );
    delete[] _buff;
    _buff = resized_buff;
}

template<typename T>
size_t stack<T>::size()
{
    return _size;
}
#endif
