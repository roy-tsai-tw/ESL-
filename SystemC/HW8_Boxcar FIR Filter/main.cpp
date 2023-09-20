//===========================================================================//
// SystemC Assignment8 - Boxcar FIR Filter                                   //
// file: main.cpp                                                            //
// description: Test file for the FIR16 module                               //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 1/3/2022                                                            //
//===========================================================================//

#include "FIR16.h"
#include <fstream>

int sc_main(int argc, char* argv[]){
    
    // open file for readinf
    ifstream iFile;
    int val_in[64];
    int count = 0;
    iFile.open("firData", ios::in);
    if(!iFile.fail()){
        while(!iFile.eof()){
                iFile >> val_in[count];
                count++;
        }
    }
    else{
        cout << "Error: The file is not opened." << endl;
    }
    iFile.close();
    
    // Clock
    sc_time t(10, SC_NS);
    sc_clock clk("clk", t);
    
    // I/O ports
    sc_signal<bool> rst;
    sc_signal<sc_uint<32> > x;
    sc_signal<sc_uint<32> > y;
    
    // Instantiate a FIR16 module
    FIR16 my_fir("FIR16");
    my_fir.clk(clk);
    my_fir.rst(rst);
    my_fir.x(x);
    my_fir.y(y);
    
    // Trace File 
    sc_trace_file *out = sc_create_vcd_trace_file("RESULT");
    // clock
    sc_trace(out, clk, "clk");
    // rst
    sc_trace(out, rst, "rst");
    // input x
    sc_trace(out, x, "x");
    // output y
    sc_trace(out, y, "y");
    // registers
    sc_trace(out, my_fir.mid[0], "mid0");
    sc_trace(out, my_fir.mid[1], "mid1");
    sc_trace(out, my_fir.mid[2], "mid2");
    sc_trace(out, my_fir.mid[3], "mid3");
    sc_trace(out, my_fir.mid[4], "mid4");
    sc_trace(out, my_fir.mid[5], "mid5");
    sc_trace(out, my_fir.mid[6], "mid6");
    sc_trace(out, my_fir.mid[7], "mid7");
    sc_trace(out, my_fir.mid[8], "mid8");
    sc_trace(out, my_fir.mid[9], "mid9");
    sc_trace(out, my_fir.mid[10], "mid10");
    sc_trace(out, my_fir.mid[11], "mid11");
    sc_trace(out, my_fir.mid[12], "mid12");
    sc_trace(out, my_fir.mid[13], "mid13");
    sc_trace(out, my_fir.mid[14], "mid14");
    sc_trace(out, my_fir.mid[15], "mid15");
    // wire
    sc_trace(out, my_fir.w2, "w2");

    
    //==========================Simulation starts============================//
    // Reset
    sc_start(0, SC_NS);
    rst.write(0);
    sc_start(10, SC_NS);
    rst.write(1);
    
    // Input 64 times
    for(int i = 0;i < 64; i++){
        sc_start(10, SC_NS);
        x.write(val_in[i]);
    }
    
    // Finish until 300ns(30 cycles)
    sc_start(200, SC_NS);
    //==========================Simulation ends==============================//
    
    sc_close_vcd_trace_file(out);
    return(0);
}