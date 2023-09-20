//===========================================================================//
// SystemC Assignment8 - Boxcar FIR Filter                                   //
// file: FIR16.h                                                             //
// description: Define the FIR16 module                                      //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 1/3/2022                                                            //
//===========================================================================//



#ifndef FIR16_H
#define FIR16_H

#include "systemc.h"

SC_MODULE(FIR16){
    sc_in<sc_uint<32> > x;
    sc_out<sc_uint<32> > y;
    sc_in<bool> clk;
    sc_in<bool> rst;
    
    // model registers
    sc_signal<sc_uint<32> > mid0, mid1, mid2, mid3, mid4, mid5, mid6, mid7,
                            mid8, mid9, mid10, mid11, mid12, mid13, mid14,
                            mid15; 
    // coefficients
    sc_uint<32> b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13,
                b14, b15, b16;  
    // wire
    sc_uint<32> w1, w2;
    
    void fir_proc();
    
    SC_CTOR(FIR16){
        SC_CTHREAD(fir_proc, clk.pos());
        reset_signal_is(rst, false);
        
    }
};

#endif