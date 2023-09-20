//===========================================================================//
// SystemC Assignment3 - Inheritance                                         //
// file: Node.h                                                              //
// description: Define the base class Node                                   //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 10/30/2021                                                          //
//===========================================================================//

#ifndef NODE_H
#define NODE_H
#define debug 1
#if !debug
#define NDEBUG
#endif
#include <cassert>
#include <cstdlib>
#include <iostream>

using namespace std;

class Node{
    private:
        long *_Node;
    public:
        Node();
        Node(unsigned int _length);
        ~Node();
        long* reCreate(unsigned int _length);
        void set_Node(long* Node);
        long* get_Node() const;
};

#endif