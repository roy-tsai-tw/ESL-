//===========================================================================//
// SystemC Assignment5 - Timer                                               //
// file: main.cpp                                                            //
// description: Test file for the timer module                               //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 12/6/2021                                                           //
//===========================================================================//

#include "timer.h"

int sc_main(int argc, char* argv[]){
    
    // Clock
    sc_time t(10, SC_NS);
    sc_clock clock("clock", t);
    
    // I/O ports
    sc_signal<bool> start;
    sc_signal<bool> timeout;
    
    // Instantiate a timer module
    timer timer1("TIMER");
    timer1.clock(clock);
    timer1.start(start);
    timer1.timeout(timeout);
    
    // Trace File 
    sc_trace_file *out = sc_create_vcd_trace_file("RESULT");
    // clock
    sc_trace(out, clock, "clock");
    // start
    sc_trace(out, start, "start");
    // timeout
    sc_trace(out, timeout, "timeout");
    // count (register)
    sc_trace(out, timer1.count, "count");
    
    //==========================Simulation starts============================//
    // Reset
    sc_start(0, SC_NS);
    start.write(1);
    sc_start(30, SC_NS);
    start.write(0);
    
    // Count & Reset before count = 0
    sc_start(30, SC_NS);
    start.write(1);
    sc_start(10, SC_NS);
    start.write(0);
    
    // Count & Reset after count = 0
    sc_start(120, SC_NS);
    start.write(1);
    sc_start(10, SC_NS);
    start.write(0);
    
    // Finish until 300ns(30 cycles)
    sc_start(100, SC_NS);
    //==========================Simulation ends==============================//
    
    sc_close_vcd_trace_file(out);
    return(0);
}