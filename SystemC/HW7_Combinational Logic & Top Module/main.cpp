//===========================================================================//
// SystemC Assignment7 - Combinational Logic & Top Module                    //
// file: main.cpp                                                            //
// description: Test file for the halfadder & fulladder module               //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 12/29/2021                                                          //
//===========================================================================//

#include "HalfAdder.h"
#include "FullAdder.h"

int sc_main(int argc, char* argv[]){
    
    // Clock
    sc_time t(10, SC_NS);
    sc_clock clock("clock", t);
    
    // I/O ports
    //==Half Adder==//
    sc_signal<bool> A, B;
    sc_signal<bool> Sum, Carry;
    //==Full Adder==//
    sc_signal<bool> A_, B_;
    sc_signal<bool> Cin;
    sc_signal<bool> S, Cout;
    
    
    // Instantiate a HalfAdder module
    HalfAdder adder1("HALFADDER");
    adder1.A(A);
    adder1.B(B);
    adder1.Sum(Sum);
    adder1.Carry(Carry);
    
    // Instantiate a FullAdder module
    FullAdder adder2("FuULLADDER");
    adder2.A(A_);
    adder2.B(B_);
    adder2.Cin(Cin);
    adder2.S(S);
    adder2.Cout(Cout);
    
    // Trace File 
    sc_trace_file *out = sc_create_vcd_trace_file("RESULT");
    // clock
    sc_trace(out, clock, "clock");
    
    //==Half Adder==//
    // Input A
    sc_trace(out, adder1.A, "A");
    // Input B
    sc_trace(out, adder1.B, "B");
    // Output Sum
    sc_trace(out, adder1.Sum, "Sum");
    // Output Carry
    sc_trace(out, adder1.Carry, "Carry");
    
    //==Full Adder==//
    // Input A
    sc_trace(out, adder2.A, "A");
    // Input B
    sc_trace(out, adder2.B, "B");
    // Input Cin
    sc_trace(out, adder2.Cin, "Cin");
    // Output S
    sc_trace(out, adder2.S, "S");
    // Output Cout
    sc_trace(out, adder2.Cout, "Cout");
    
    //==========================Simulation starts============================//
    // Start
    sc_start(0, SC_NS);
    A.write(0);
    B.write(0);
    A_.write(0);
    B_.write(0);
    Cin.write(0);
    
    
    // All 4 situations for HalfAdder
    // A = 0, B = 0
    sc_start(10, SC_NS);
    A.write(0);
    B.write(0);
    A_.write(0);
    B_.write(0);
    
    // A = 0, B = 1
    sc_start(10, SC_NS);
    B.write(1);
    B_.write(1);
    
    // A = 1, B = 0
    sc_start(10, SC_NS);
    A.write(1);
    B.write(0);
    A_.write(1);
    B_.write(0);
    
    // A = 1, B = 1
    sc_start(10, SC_NS);
    B.write(1);
    B_.write(1);
    
    // Alnother 4 situations for FullAdder
    // A = 0, B = 0
    sc_start(10, SC_NS);
    A.write(0);
    B.write(0);
    A_.write(0);
    B_.write(0);
    Cin.write(1);
    
    // A = 0, B = 1
    sc_start(10, SC_NS);
    B_.write(1);
    
    // A = 1, B = 0
    sc_start(10, SC_NS);
    A_.write(1);
    B_.write(0);
    
    // A = 1, B = 1
    sc_start(10, SC_NS);
    B_.write(1);
    
    // Finish until 
    sc_start(20, SC_NS);
    //==========================Simulation ends==============================//
    
    sc_close_vcd_trace_file(out);
    return(0);
}