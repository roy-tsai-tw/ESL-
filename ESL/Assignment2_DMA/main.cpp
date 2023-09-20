#include "dma.h"
#include "cpu.h"
#include "memory.h"


int sc_main(int argc, char* argv[]){
	
	//==========================================================================//
	//=----------------------------Port Connection-----------------------------=//
	//==========================================================================//
	
	/*-----------------------Main port-------------------------*/
	//Clock
	sc_time t(10, SC_NS);
    sc_clock clk("clock", t);
	//Monitoring I/O Signals
	sc_signal<bool> rst;
	sc_signal<bool> interrupt;
	sc_signal<bool> act; // Add-on for simulation in main.cpp
	//Registers
	//sc_signal<sc_uint<32> > Base_addr;
	//sc_signal<sc_uint<3> > count;
	
	/*--------------------------CPU----------------------------*/
	cpu cpu1("CPU");
	cpu1.clk(clk);
	cpu1.rst(rst);
	cpu1.interrupt(interrupt);
	cpu1.act(act);
	
	
	
	/*--------------------------DMA----------------------------*/
	dma	dma1("DMA");
	dma1.clk(clk);
	dma1.reset(rst);
	dma1.Interrupt(interrupt);
	
	/*--------------------------MEM----------------------------*/
	memory memory1("RAM");
	
	/*--------------------------bind----------------------------*/
	cpu1.socket_m( dma1.slave_p );
	memory1.slave_p( dma1.master_p );
	
	//==========================================================================//
	//=----------------------------Create VCD file-----------------------------=//
	//==========================================================================//
	
	sc_trace_file *out = sc_create_vcd_trace_file("RESULT");	
	sc_trace(out, clk, "clock");
	sc_trace(out, rst, "reset");
	sc_trace(out, interrupt, "interrupt");
	sc_trace(out, act, "act");
	sc_trace(out, cpu1.Base_addr, "Base_addr");
	//sc_trace(out, cpu1.count, "count");
	//sc_trace(out, cpu1.SOURCE, "cpu1_SOURCE");
	//sc_trace(out, cpu1.TARGET, "cpu1_TARGET");
	//sc_trace(out, cpu1.SIZE, "cpu1_SIZE");
	//sc_trace(out, cpu1.START_CLEAR, "cpu1_START_CLEAR");
	
	sc_trace(out, dma1.dma_state, "dma_state");
	sc_trace(out, dma1.slave_r_w, "dma_slave_r_w");
	sc_trace(out, dma1.SOURCE, "SOURCE");
	sc_trace(out, dma1.TARGET, "TARGET");
	sc_trace(out, dma1.SIZE, "SIZE");
	sc_trace(out, dma1.START_CLEAR, "START_CLEAR");
	//sc_trace(out, dma1.tmp_data, "DMA_TMP_DATA");
	
	sc_trace(out, memory1.memsrc[1], "ram_memsrc(1)");
	sc_trace(out, memory1.memsrc[2], "ram_memsrc(2)");
	//sc_trace(out, memory1.memsrc[4], "ram_memsrc(4)");
	sc_trace(out, memory1.memtgt[3], "ram_memtgt(3)");
	sc_trace(out, memory1.memtgt[4], "ram_memtgt(4)");
	//sc_trace(out, memory1.memtgt[5], "ram_memtgt(5)");
	
	/*--------------------------1st run----------------------------*/
	sc_start(0, SC_NS);
	rst.write(0);
	sc_start(10, SC_NS);
	rst.write(1);
	sc_start(10, SC_NS);
	act.write(0);
	sc_start(150, SC_NS);
	act.write(1);
	/*--------------------------2nd run----------------------------*/
	sc_start(30, SC_NS);
	
	
	/*--------------------------3rd run----------------------------*/
	//sc_start(100, SC_NS);
	
	sc_close_vcd_trace_file(out);
    return(0);
}







