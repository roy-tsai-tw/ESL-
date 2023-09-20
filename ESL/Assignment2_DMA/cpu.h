#ifndef CPU_H
#define CPU_H

#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/simple_initiator_socket.h"


#define DMA_Task 0
#define OTHER_TASK 1

SC_MODULE(cpu){
	//Inputs & Outputs
	sc_in<bool> clk;
	sc_in<bool> rst;
	sc_in<bool> interrupt;
	sc_in<bool> act; // Add-on for simulation in main.cpp
	//sc_out<bool> start_clear;
	
	//Registers
	sc_signal<sc_uint<32> > Base_addr;
	sc_signal<sc_uint<4> > count;
	sc_uint<32> DMA_Base_addr;
	sc_uint<32> NOP_Base_addr;
	unsigned int SOURCE;
	unsigned int TARGET;
	unsigned int SIZE;
	bool START_CLEAR;
	sc_uint<3> number;
	
	//TLM 2.0 Sockets
	tlm_utils::simple_initiator_socket<cpu> socket_m;
	
	void cpu_proc();
	
	SC_CTOR(cpu) : socket_m("socket_m"){
		SC_CTHREAD(cpu_proc, clk.pos());
        reset_signal_is(rst, false);
	}
	
};

#endif