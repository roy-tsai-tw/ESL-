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
    mid0 = 0; mid1 = 0; mid2 = 0; mid3 = 0; mid4 = 0; mid5 = 0; mid6 = 0;
    mid7 = 0; mid8 = 0; mid9 = 0; mid10 = 0; mid11 = 0; mid12 = 0; mid13 = 0;
    mid14 = 0; mid15 = 0;
    b0 = 3855; b1 = 3855; b2 = 3855; b3 = 3855;
    b4 = 3855; b5 = 3855; b6 = 3855; b7 = 3855;
    b8 = 3855; b9 = 3855; b10 = 3855; b11 = 3855;
    b12 = 3855; b13 = 3855; b14 = 3855; b15 = 3855; b16 = 3855;
    // computation
    while(1){
        wait();
        // wires
        w1 = x.read();
        w2 = (w1 * b0
             + mid0.read() * b1
             + mid1.read() * b2
             + mid2.read() * b3
             + mid3.read() * b4
             + mid4.read() * b5
             + mid5.read() * b6
             + mid6.read() * b7
             + mid7.read() * b8
             + mid8.read() * b9
             + mid9.read() * b10
             + mid10.read() * b11
             + mid11.read() * b12
             + mid12.read() * b13
             + mid13.read() * b14
             + mid14.read() * b15
             + mid15.read() * b16) / (65536);
        // registers
        mid15.write(mid14.read());
        mid14.write(mid13.read());
        mid13.write(mid12.read());
        mid12.write(mid11.read());
        mid11.write(mid10.read());
        mid10.write(mid9.read());
        mid9.write(mid8.read());
        mid8.write(mid7.read());
        mid7.write(mid6.read());
        mid6.write(mid5.read());
        mid5.write(mid4.read());
        mid4.write(mid3.read());
        mid3.write(mid2.read());
        mid2.write(mid1.read());
        mid1.write(mid0.read());
        mid0.write(w1);
        // output
        y.write(w2);
    }
}