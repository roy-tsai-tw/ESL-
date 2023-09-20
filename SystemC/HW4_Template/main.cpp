//===========================================================================//
// SystemC Assignment4 - Template                                            //
// file: main.cpp                                                            //
// description: Main Function                                                //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 11/10/2021                                                          //
//===========================================================================//


#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Node.h"
#include "List.h"
#include <string>

using namespace std;


int main(int argc, char *argv[]){
    fstream iFile1, iFile2;
    List<double> inList1;
    List<string> inList2;
    //long val_in = 0;
    unsigned int number = 0;
    //const List* inList_ptr = &inList;
    
    if(argc == 3){
        cout << "The number of input arguments is right." << endl;  
    }
    else{
        cout << "The number of input arguments is wrong." << endl;  
    }
    
    
    iFile1.open(argv[1], ios::in);
    if(!iFile1.fail() && (argc == 3)){
        while(!iFile1.eof()){
            iFile1 >> number;
            inList1.setLength(number);
            iFile1 >> inList1;
        }
        cout << "Double Input Element number = " 
             << inList1.getLength() << endl;
        for(int i = 0; i < (int)inList1.getLength(); i++){
            cout << "Element[" << i << "] = " << inList1.getElement(i) << endl;
        }
        cout << "==================================" << endl;
    }
    else{
        cout << "Error: The double file is not opened." << endl;
    }
    iFile1.close();
    
    iFile2.open(argv[2], ios::in);
    
    if(!iFile2.fail() && (argc == 3)){
        while(!iFile2.eof()){
            iFile2 >> number;
            inList2.setLength(number);
            //cout << inList2.get_Node() << endl;
            //cout << "String number = " << inList2.getLength() << endl;
            iFile2 >> inList2;
        }
        cout << "String Input Element number = " 
             << inList2.getLength() << endl;
        for(int i = 0; i < (int)inList2.getLength(); i++){
            cout << "Element[" << i << "] = " << inList2.getElement(i) << endl;
        }
        cout << "==================================" << endl;
    }
    else{
        cout << "Error: The string file is not opened." << endl;
    }
    iFile2.close();
    
    List<double> list2;
    List<string> list3, list4;
    
    // Copy <double> inList1 using copy constructor 
    List<double> list1(inList1);
    
    // Copy <string> inList2 using assignment operator
    list3 = inList2;
    
    /* Use operator== to check if the two double List and the string List 
    are indeed the same */
    cout << "Check if the two double lists are the same:" << endl;
    string str1 = "true", str2 = "true";
    if((inList1 == list2)){
        str1 = "true";
    }else{
        str1 = "false";
    }
    cout << "Is inList1 == list2 ? " << str1 << endl;
    cout << "Check if the two string lists are the same:" << endl;
    if((inList2 == list3)){
        str2 = "true";
    }else{
        str2 = "false";
    }
    cout << "Is inList2 == list3 ? " << str2 << endl;
    cout << "==================================" << endl;
    
    // Use setElement() to assign values to all List objects & check
    unsigned int boundary1 = inList1.getLength();
    cout << "Check the functionality setElement is right:" << endl;
    cout << "Double List inList1:" << endl;
    inList1.setElement(0, 7.77);
    cout << "position " << 0 << " = " << inList1.getElement(0) << endl;
    inList1.setElement(boundary1 - 1, 6.77);
    cout << "position " << (boundary1 - 1) << " = "
         << inList1.getElement(boundary1 - 1) << endl;
    //inList1.setElement(boundary1, 7.777);
    //cout << "position " << boundary1 << " = " 
    //     << inList1.getElement(boundary1) << endl;
    cout << "==================================" << endl;
    
    unsigned int boundary2 = inList2.getLength();
    cout << "Check the functionality setElement is right:" << endl;
    cout << "String List inList2:" << endl;
    inList2.setElement(0, "I ate");
    cout << "position " << 0 << " = " << inList2.getElement(0) << endl;
    inList2.setElement(boundary2 - 1, "apple");
    cout << "position " << (boundary2 - 1) << " = " 
         << inList2.getElement(boundary2 - 1) << endl;
    inList2.setElement(boundary2, "pie");
    cout << "position" << boundary2 << " = " 
         << inList2.getElement(boundary2) << endl;
    cout << "==================================" << endl;
    
    return 0;
}