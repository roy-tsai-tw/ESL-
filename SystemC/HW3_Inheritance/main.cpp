//===========================================================================//
// SystemC Assignment3 - Inheritance                                         //
// file: main.cpp                                                            //
// description: Implementation of the derived class Node                     //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 10/30/2021                                                          //
//===========================================================================//

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Node.h"
#include "List.h"
#include <string>

using namespace std;

int main(int argc, char *argv[]){
    fstream iFile;
    ofstream oFile;
    List inList;
    long val_in = 0;
    int count = 0;
    //const List* inList_ptr = &inList;
    
    if(argc == 2){
        cout << "The number of input arguments is right." << endl;  
    }
    else{
        cout << "The number of input arguments is wrong." << endl;  
    }
    iFile.open(argv[1], ios::in);
    if(!iFile.fail()){
        while(!iFile.eof()){
            iFile >> val_in;
            if(count == 0){
                inList.setLength(val_in);
                
            }
            else{
                inList.setElement(count - 1, val_in);
            }
            count++;
        }
        
        cout << "Input Element number = " << inList.getLength() << endl;
        for(int i =0; i < (int)inList.getLength(); i++){
            cout << "Element[" << i << "] = " << inList.getElement(i) << endl;
        }
    }
    else{
        cout << "Error: The file is not opened." << endl;
    }
    iFile.close();
    
    // Print out and write into RESULT the user-defined list type 
    oFile.open("RESULT", ios::app);
    if(!oFile.is_open()){
        cout << "Outputfile RESULT is not opened." << endl;
    }
    else{
        cout << "inList: " << inList << endl;
        oFile << "The original List object inList" << endl;
        oFile << inList << endl;
        oFile << endl;
    }
    
    List list2, list3;
    
    // Copy inList - Method 1: Using copy constructor 
    List list1(inList);
    // Copy inList - Method 2: Using assignment operator
    list2 = inList;
    // Copy inList - Method 3: Copy every member function directly
    list3.setLength(inList.getLength());
    list3.set_Node(inList.Node::get_Node());
    
    
    // Copy inList - Method 1: Using copy constructor 
    if(!oFile.is_open()){
        cout << "Outputfile RESULT is not opened." << endl;
    }
    else{
        cout << "list1: " << list1 << endl;
        oFile << "Copy the List using method 1 - copy constructor" << endl;
        oFile << list1 << endl;
        oFile << endl;
    }
    // Copy inList - Method 2: Using assignment operator
    if(!oFile.is_open()){
        cout << "Outputfile RESULT is not opened." << endl;
    }
    else{
        cout << "list2: " << list2 << endl;
        oFile << "Copy the List using method 2 - assignment operator" << endl;
        oFile << list2 << endl;
        oFile << endl;
    }
    // Copy inList - Method 3: Copy every member function directly
    if(!oFile.is_open()){
        cout << "Outputfile RESULT is not opened." << endl;
    }
    else{
        cout << "list3: " << list3 << endl;
        oFile << "Copy the List using method 3 - copy every member function \
            directly" << endl;
        oFile << list3 << endl;
        oFile << endl;
    }
    
    // Overloading operator +
    list3 = list1 + list2;
    if(!oFile.is_open()){
        cout << "Outputfile RESULT is not opened." << endl;
    }
    else{
        cout << "list1 + list2: " << list3 << endl;
        oFile << "list1 + list 2" << endl;
        oFile << list3 << endl;
        oFile << endl;
    }
    
    // Overloading operator ++(int)
    list3 = list1++;
    if(!oFile.is_open()){
        cout << "Outputfile RESULT is not opened." << endl;
    }
    else{
        cout << "list1++: " << list3 << endl;
        oFile << "list1++" << endl;
        oFile << list3 << endl;
        oFile << endl;
    }
    
    // Overloading operator +
    list3 = ++list2;
    if(!oFile.is_open()){
        cout << "Outputfile RESULT is not opened." << endl;
    }
    else{
        cout << "++list2: " << list3 << endl;
        oFile << "++list2" << endl;
        oFile << list3 << endl;
        oFile << endl;
    }
    
    // Overloading operator +=
    list1 += list2;
    if(!oFile.is_open()){
        cout << "Outputfile RESULT is not opened." << endl;
    }
    else{
        cout << "list1+=list2: " << list1 << endl;
        oFile << "list1+=list2" << endl;
        oFile << list1 << endl;
        oFile << endl;
    }
    
    // Overloading operator --(int)
    list3 = list1--;
    if(!oFile.is_open()){
        cout << "Outputfile RESULT is not opened." << endl;
    }
    else{
        cout << "list1--: " << list3 << endl;
        oFile << "list1--" << endl;
        oFile << list3 << endl;
        oFile << endl;
    }
    
    // Overloading operator --
    list3 = --list1;
    if(!oFile.is_open()){
        cout << "Outputfile RESULT is not opened." << endl;
    }
    else{
        cout << "--list1: " << list3 << endl;
        oFile << "--list1" << endl;
        oFile << list3 << endl;
        oFile << endl;
    }
    oFile.close();
}