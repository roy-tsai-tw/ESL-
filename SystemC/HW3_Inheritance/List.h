//===========================================================================//
// SystemC Assignment3 - Inheritance                                         //
// file: List.h                                                              //
// description: Define the derived class List from Node                      //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 10/30/2021                                                          //
//===========================================================================//

#ifndef LIST_H
#define LIST_H
#define debug 1
#if !debug
#define NDEBUG
#endif
#include <cassert>
#include <cstdlib>
#include <iostream>


class List : public Node{
    private:
        unsigned int length;
    public:
        List();
        List(unsigned int _length);
        List(const List& other);
        ~List();
        List& operator=(const List& other);
        int setLength(unsigned int _length);
        unsigned int getLength() const;
        int setElement(unsigned int pos, long val);
        long getElement(unsigned int pos) const;
        List operator+(const List &);
        List& operator+=(const List &);
        List operator++();
        List operator++(int);
        List operator--();
        List operator--(int);
        friend ostream& operator<<(ostream &, List);
        friend istream& operator>>(istream &, List &);
};


#endif







