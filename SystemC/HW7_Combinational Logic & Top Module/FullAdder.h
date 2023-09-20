//===========================================================================//
// SystemC Assignment7 - Combinational Logic & Top Module                    //
// file: FullAdder.h                                                         //
// description: Definition of the fulladder module                           //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 12/29/2021                                                          //
//===========================================================================//

#include "HalfAdder.h"
#ifndef FULLADDER_H
#define FULLADDER_H

SC_MODULE(FullAdder){
    sc_in<bool> A, B, Cin;
    sc_out<bool> S, Cout;
    sc_signal<bool> wire1, wire2,wire3; 
    void runFullAdder();
    HalfAdder *ha1, *ha2;
    
    SC_CTOR(FullAdder){
        ha1 = new HalfAdder("ha1");
        ha1->A(A);
        ha1->B(B);
        ha1->Sum(wire1);
        ha1->Carry(wire2);
        
        ha2 = new HalfAdder("ha2");
        ha2->A(wire1);
        ha2->B(Cin);
        ha2->Sum(S);
        ha2->Carry(wire3);
        
        SC_METHOD(runFullAdder);
        sensitive << wire2 << wire3 << Cin;
    }
};

#endif