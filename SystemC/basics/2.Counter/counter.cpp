/********************************

Title: Counter Design
Originated from (http://www.asic-world.com/systemc/first1.html)
Author: Roy Tsai
Date: Mar. 21, 2021

********************************/

#include "counter.h"

void first_counter::incr_count(){
	if(reset.read() == 1){
		count = 0;
		counter_out.write(count);
	}
	else if(enable.read() == 1){
		count = count + 1;
		counter_out.write(count);
		cout << "Incremented Counter is " << counter_out.read() << "@" << sc_time_stamp() <<endl;
	}
}
