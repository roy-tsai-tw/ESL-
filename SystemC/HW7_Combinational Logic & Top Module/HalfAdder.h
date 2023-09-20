//===========================================================================//
// SystemC Assignment7 - Combinational Logic & Top Module                    //
// file: HaldAdder.h                                                         //
// description: Definition of the halfadder module                           //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 12/29/2021                                                          //
//===========================================================================//

#include "systemc.h"
#ifndef HALFADDER_H
#define HALFADDER_H

SC_MODULE(HalfAdder){
    sc_in<bool> A, B;
    sc_out<bool> Sum, Carry;
    
    void runHalfAdder();
    
    SC_CTOR(HalfAdder){
        SC_METHOD(runHalfAdder);
        sensitive << A << B;
    }
};

#endif