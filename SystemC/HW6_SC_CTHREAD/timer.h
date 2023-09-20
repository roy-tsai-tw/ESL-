//===========================================================================//
// SystemC Assignment5 - Timer                                               //
// file: timer.h                                                             //
// description: Define the timer module                                      //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 12/6/2021                                                           //
//===========================================================================//

#include "systemc.h"

SC_MODULE(timer){
    sc_in<bool> start;
    sc_out<bool> timeout;
    sc_in<bool> clock;
    
    int count;
    void runtimer();
    
    SC_CTOR(timer){
        SC_CTHREAD(runtimer, clock.pos());
        reset_signal_is(start, true);
        
    }
};