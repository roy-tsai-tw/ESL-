//===========================================================================//
// SystemC Assignment3 - Inheritance                                         //
// file: Node.cpp                                                            //
// description: Implementation of the base class Node                        //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 10/30/2021                                                          //
//===========================================================================//


#include "Node.h"

using namespace std;

Node::Node(){
    _Node = NULL;
}

Node::Node(unsigned int _length){
    if(_length == 0)
        _Node = NULL;
    else{
        _Node = new long [_length];
        assert(_Node != NULL);
    }
}

Node::~Node(){
    _Node = NULL;
}

long* Node::reCreate(unsigned int _length){
    if(_length == 0)
        _Node = NULL;
    else{
        _Node = new long [_length];
        assert(_Node != NULL);
    }
    
    return _Node;
}

void Node::set_Node(long* Node){
    _Node = Node;
};

long* Node::get_Node() const{
    return _Node;
};