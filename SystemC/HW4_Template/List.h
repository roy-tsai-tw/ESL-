//===========================================================================//
// SystemC Assignment4 - Template                                            //
// file: List.h                                                              //
// description: Define the derived class List from Node                      //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 11/10/2021                                                          //
//===========================================================================//

#ifndef LIST_H
#define LIST_H
#define debug 1
#if !debug
#define NDEBUG
#endif
#include <assert.h>
#include <cstdlib>
#include <iostream>
#include <string>


template<class T>
class List;
template<class T>
std::istream& operator>> (std::istream &in, List<T> &);
template<class T>
std::ostream& operator<< (std::ostream &out, List<T>);

template<class T>
class List : public Node<T>{
    private:
        unsigned int length;
    public:
        List();
        List(unsigned int _length);
        List(const List<T>& other);  
        ~List();
        List& operator=(const List<T> &);
        int setLength(unsigned int);
        unsigned int getLength() const;
        int setElement(unsigned int pos, T val);
        T getElement(unsigned int pos);
        
        
        friend std::ostream& operator<< <>(std::ostream &, List<T>); 
        friend std::istream& operator>> <>(std::istream &, List<T> &);  
        inline bool operator==(const List<T> &);     
};

template<class T>
List<T>::List():Node<T>(){
    length = 0;
}

template<class T>
List<T>::List(unsigned int _length):Node<T>(_length){
    length = _length;
    if (length == 0)
        this->set_Node(NULL);
    else {
        assert(this->get_Node() != NULL);
    }
}

template<class T>
List<T>::List(const List& other){
    length = other.getLength();
    if(length > 0){
        this->set_Node(new T [length]);
        assert(this->get_Node() != NULL);
        for(int i = 0; i < length; i++){
            (this->get_Node())[i] = (other.get_Node())[i];
        }
    }
    else
        this->set_Node(NULL);
}

template<class T>
List<T>::~List(){
    length = 0;
}

template<class T>
List<T>& List<T>::operator=(const List& other){
    if(this != & other){
        
        length = other.getLength();
        
        if(length> 0){
            this->reCreate(length);
            assert(this->get_Node() != 0);
            for(int i =0; i < (int)length; i++){
                (this->get_Node())[i] = (other.get_Node())[i];
            }
        }
        else
            this->set_Node(NULL); 
    }
    return * this;
}

template<class T>
int List<T>::setLength(unsigned int _length){
    if(length == 0){
        length = _length;
        this->reCreate(length);          
        return 1;
    }
    else{
        std::cout << "Error: Length is not 0." << std::endl;
        return 0;
    }
    if(this->get_Node() == NULL){
        std::cout << "Node is NULL" << std::endl;
    }
}

template<class T>
unsigned int List<T>::getLength() const{
    return length;
}

template<class T>
int List<T>::setElement(unsigned int pos, T val){
    //std::cout << "setElement" << std::endl;
    if((pos < this->getLength()) && pos >= 0){
        //std::cout << "1" << std::endl;
        (this->get_Node())[pos] = val;
        //std::cout << "2" << std::endl;
        return 1;
    }
    else{
        std::cout << "setElement Error: pos " << pos 
             << " is out of bound." << std::endl;
        std::cout << "You will see core dumped." << std::endl;
        return 0;
    }
}

template<class T>
T List<T>::getElement(unsigned int pos){
    T tmp = (this->get_Node())[0];
    if((pos < this->getLength()) && pos >= 0){
        T val_ = (this->get_Node())[pos];
        return val_;
    }
    else{
        std::cout << "getElement Error: pos " << pos 
             << " is out of bound." << std::endl;
        std::cout << "You will see core dumped." << std::endl;
        assert((pos < this->getLength()) && pos >= 0);
        //return();
    }
}

template<class T>
std::ostream& operator<<(std::ostream &out, List<T> list){
    for(int i =0; i < (int)list.getLength(); i++){
        out << (list.get_Node())[i] << " ";  
    }
    return out;
}

template<class T>
std::istream& operator>>(std::istream &in, List<T> &list){  
    T val;
    //std::cout << "length = " << list.getLength() << std::endl;
    for(int i = 0;i < (int)list.getLength(); i++){
        in >> val;
        //std::cout << "val = " << val << std::endl;
        list.setElement(i, val);
        //in >> (list.get_Node())[i];       
    }
    return in;
}

template<class T>
bool List<T>::operator==(const List<T> &other){
    int count = 0;
    if(this->getLength() != other.getLength()){
        return false;
    }
    else{
        for(int i = 0;i < (int)length; i++){
            if((this->get_Node())[i] != (other.get_Node())[i]){
                return false;
            }
            else{
                count++;
                if(count == this->getLength()){
                return true;
                }
            }
        }
        
    }
    return false;
}



#endif


