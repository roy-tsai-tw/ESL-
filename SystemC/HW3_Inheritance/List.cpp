//===========================================================================//
// SystemC Assignment3 - Inheritance                                         //
// file: List.cpp                                                            //
// description: Implementation of the derived class Node                     //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 10/30/2021                                                          //
//===========================================================================//

#include "Node.h"
#include "List.h"

using namespace std;

List::List():Node(){
    length = 0;
}

List::List(unsigned int _length):Node(_length){
    length = _length;
}

List::List(const List& other){
    length = other.length;
    if(length > 0){
        this->set_Node(new long [length]);
        assert(this->get_Node() != NULL);
        for(int i = 0; i < (int)length; i++){
            (this->get_Node())[i] = (other.get_Node())[i];
        }
    }
    else
        this->set_Node(NULL);
}

List::~List(){
    length = 0;
}

List& List::operator=(const List& other){
    if(this != & other){
        length = other.getLength();
        if(length> 0){
            //long* NodePtr = new long [length];
            this->set_Node(new long [length]);
            assert(this->get_Node() != 0);
            for(int i =0; i< (int)length; i++){
                (this->get_Node())[i] = (other.get_Node())[i];
            }
        }
        else
            this->set_Node(NULL);
    }
    return * this;
}

int List::setLength(unsigned int _length){
    if(this->length == 0){
        length = _length;
        this->reCreate(length);
        return 1;
    }
    else{
        cout << "Error: Length is not 0." << endl;
        return 0;
    }
}

unsigned int List::getLength() const{
    return length;
}

int List::setElement(unsigned int pos, long val){
    if(pos < this->getLength()){
        (this->get_Node())[pos] = val;
        return 1;
    }
    else{
        cout << "Error: pos is out of bound." << endl;
        return 0;
    }
}

long List::getElement(unsigned int pos) const{
    if(pos < length){
        long val_ = (this->get_Node())[pos];
        return val_;
    }
    else{
        cout << "Error: pos is out of bound." << endl;
        return -99999;
    }
}

List List::operator+(const List &other){
    unsigned int loop = (length < other.getLength())? 
        length : other.getLength(); 
    List lt(loop);
    for(int i =0; i < (int)loop; i++){
        (lt.get_Node())[i] = (get_Node())[i] + (other.get_Node())[i];
    }
    return lt;
}
List& List::operator+=(const List &other){
    unsigned int loop = (length < other.getLength())? 
        length : other.getLength(); 
    for(int i =0; i < (int)loop; i++){
        (this->get_Node())[i] += (other.get_Node())[i];
    }
    return *this;
}
List List::operator++(){
    List tmp(*this);
    for(int i =0; i < (int)tmp.getLength(); i++){
        (tmp.get_Node())[i] = ++(this->get_Node())[i];
    }
    return tmp;
}
List List::operator++(int){
    List tmp(*this);
    for(int i =0; i < (int)tmp.getLength(); i++){
        (tmp.get_Node())[i] = (this->get_Node())[i]++;
    }
    return tmp;
}
List List::operator--(){
    List tmp(*this);
    for(int i =0; i < (int)length; i++){
        (tmp.get_Node())[i] = --(this->get_Node())[i];
    }
    return tmp;
}
List List::operator--(int){
    List tmp(*this);
    for(int i =0; i < (int)length; i++){
        (tmp.get_Node())[i] = (this->get_Node())[i]--;
    }
    return tmp;
}
ostream& operator<<(ostream &out, List list){
    for(int i =0; i < (int)list.getLength(); i++){
        out << (list.get_Node())[i] << " ";  
    }
    return out;
}

istream& operator>>(istream &in, List &list){
    long val = 0;
    for(int i = 0; i < (int)list.getLength(); i++){
        in >> val;
        list.setElement(i, val);
        cout << val << endl;
    }
    return in;
}