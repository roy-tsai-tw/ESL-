/********************************

Title: Counter Design
Originated from (http://www.asic-world.com/systemc/first1.html)
Author: Roy Tsai
Date: Mar. 21, 2021

********************************/

#include "counter.h"

int sc_main(int argc, char* argv[]){
	sc_signal<bool> clock;
	sc_signal<bool> reset;
	sc_signal<bool> enable;
	sc_signal<sc_uint<4> > counter_out;
	int i = 0;
	
	first_counter counter1("COUNTER");
		counter1.clock(clock);
		counter1.reset(reset);
		counter1.enable(enable);
		counter1.counter_out(counter_out);
	
	sc_start(1,SC_NS);
	
	//Create a wave file in the format of vcd.
	sc_trace_file *wf = sc_create_vcd_trace_file("counter");
	//Dump the desired signals
	sc_trace(wf, clock, "clock");
	sc_trace(wf, reset, "reset");
	sc_trace(wf, enable, "enable");
	sc_trace(wf, counter_out, "counter_out");
	
	//Initialize all variables
	reset = 0;
	enable = 0;
	
	
	for(int i=0;i<5;i++){  //create clock
		clock = 0;
		sc_start(1,SC_NS);
		clock = 1;
		sc_start(1,SC_NS);
	}
	
	reset = 1; //Assert the reset
	cout <<"Assert rest @ " << sc_time_stamp()<<endl;
	for(int i=0;i<20;i++){
		clock = 0;
		sc_start(1,SC_NS);
		clock = 1;
		sc_start(1,SC_NS);
	}
	reset = 0; //De-assert the reset
	cout <<"De-assert rest @ " << sc_time_stamp()<<endl;
	for(int i=0;i<10;i++){
		clock = 0;
		sc_start(1,SC_NS);
		clock = 1;
		sc_start(1,SC_NS);
	}
	enable = 1; //Assert enable
	cout <<"Assert enable @ " << sc_time_stamp()<<endl;
	for(int i=0;i<20;i++){
		clock = 0;
		sc_start(1,SC_NS);
		clock = 1;
		sc_start(1,SC_NS);
	}
	enable = 0; //De-assert enable
	cout <<"De-assert enable @ " << sc_time_stamp()<<endl;
	
	cout << "Terminating simulation @ " << sc_time_stamp() << endl;
	sc_close_vcd_trace_file(wf);
	
	return (0);
}
