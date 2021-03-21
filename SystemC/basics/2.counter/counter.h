/********************************

Title: Counter Design
Originated from (http://www.asic-world.com/systemc/first1.html)
Author: Roy Tsai
Date: Mar. 21, 2021

********************************/

//This is my second SystemC program.

#ifndef COUNTER_H
#define COUNTER_H

#include "systemc.h"

SC_MODULE(first_counter){
	sc_in_clk clock;
	sc_in<bool> reset;
	sc_in<bool> enable;
	sc_out<sc_uint<4> > counter_out; //Reminder: There is a space between "4>" and ">".
	
	//local variable
	sc_uint<4> count;
	
	SC_CTOR(first_counter)
		:clock("clock")
		,reset("reset")
		,enable("enable")
		,counter_out("counter_out")
		{
			cout << "Executing now" << endl;
			
			SC_METHOD(incr_count);
			sensitive << reset;
			sensitive << clock.pos();
		}
	
	void incr_count();
};

#endif