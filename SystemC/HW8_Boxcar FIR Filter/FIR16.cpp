//===========================================================================//
// SystemC Assignment8 - Boxcar FIR Filter                                   //
// file: FIR16.cpp                                                           //
// description: Implementation of the FIR16 module                           //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 1/3/2022                                                            //
//===========================================================================//

#include "FIR16.h"

void FIR16::fir_proc(){
    // reset
    for(int i = 0; i <16; i++){
        mid[i] = 0;
    }
    for(int i =0; i < 17; i++){
        b[i] = 3855;
    }
    // computation
    while(1){
        wait();
        // wires
        w1 = x.read();
        w2 = w1 * b[0];
        for(int i = 0; i < 16; i++){
            w2 = w2 + mid[i].read() * b[i + 1]; 
        }
        
        // registers
        for(int i = 15; i > 0; i--){
            mid[i].write(mid[i - 1].read());
            if(i == 1){
                mid[0].write(w1);
            }
        }
        // output
        y.write(w2);
    }
}