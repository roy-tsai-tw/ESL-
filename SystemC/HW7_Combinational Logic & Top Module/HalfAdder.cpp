//===========================================================================//
// SystemC Assignment7 - Combinational Logic & Top Module                    //
// file: HaldAdder.cpp                                                       //
// description: Implementation of the halfadder module                       //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 12/29/2021                                                          //
//===========================================================================//


#include "HalfAdder.h"

void HalfAdder::runHalfAdder(){
    Sum = A ^ B;
    Carry = A & B;
}