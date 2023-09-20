//===========================================================================//
// SystemC Assignment4 - Template                                            //
// file: Node.h                                                              //
// description: Define the base class Node                                   //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 11/10/2021                                                          //
//===========================================================================//

#ifndef NODE_H
#define NODE_H
#define debug 1
#if !debug
#define NDEBUG
#endif
#include <assert.h>
#include <cstdlib>
#include <iostream>


template<class T>
class Node{
    private:
        T *_Node;
    public:
        Node();
        Node(unsigned int _length);
        ~Node();
        T* reCreate(unsigned int _length);
        void set_Node(T* Node);
        T* get_Node() const;
};

template<class T>
Node<T>::Node(){
    _Node = NULL;
}

template<class T>
Node<T>::Node(unsigned int _length){
    if(_length == 0)
        _Node = NULL;
    else{
        _Node = new T [_length];
        assert(_Node != NULL);
    }
}

template<class T>
Node<T>::~Node(){
    delete [] _Node; 
    _Node = NULL;
}

template<class T>
T* Node<T>::reCreate(unsigned int _length){
    if(_Node != NULL){
        delete [] _Node;
        _Node = NULL;
    }
    else{
        //std::cout << " I found it!" << std::endl;
        if(_length == 0){
        _Node = NULL;
        std::cout << "_Node == NULL!" << std::endl;
        }
        else{
            //std::cout << "**reCreate**" << std::endl;
            _Node = new T [_length];
            assert(_Node != NULL);
        }
    }
    
    
    return _Node;
}

template<class T>
void Node<T>::set_Node(T* Node){   
    _Node = Node;
};

template<class T>
T* Node<T>::get_Node() const{
    return _Node;
};


#endif





