//===========================================================================//
// SystemC Assignment5 - Timer                                               //
// file: timer.cpp                                                           //
// description: Implementation of the timer module                           //
// authors: Tsung-Ying(Roy) Tsai                                             //
// date: 12/6/2021                                                           //
//===========================================================================//

#include "timer.h"

void timer::runtimer(){
    while(1){
        if(start.read()){
            cout << "Timer: timer start detected " << endl;
            count.write(5);
            timeout.write(0);
        }
        else{
            if(count.read() == 0){
                timeout.write(1);
            }
            else{
                count.write(count.read() - 1);
                timeout.write(0);
            }
        }
        wait();
    }
}