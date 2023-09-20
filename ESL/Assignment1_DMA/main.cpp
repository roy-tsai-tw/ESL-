#include "dma.h"

#define slave_pause 300

int sc_main(int argc, char* argv[]){
	//signals
    
	//master_signal
	sc_signal<sc_uint<32> > master_data_in; //input
	sc_signal<sc_uint<32> > master_addr;    //output
	sc_signal<sc_uint<32> > master_data;    //output
	sc_signal<bool> master_r_w; //1:read, 0:write //output
	
	//slave_signal
    sc_signal<sc_uint<32> > slave_data_out; //output
	sc_signal<sc_uint<32> > slave_addr;    //input
	sc_signal<sc_uint<32> > slave_data;    //input
	sc_signal<bool> slave_r_w; //1:read, 0:write //output
	
	sc_signal<bool> interrupt;
	sc_signal<bool> reset;
    sc_signal<bool> start_clear;
    
    sc_time t(10, SC_NS);
    sc_clock clock("clock", t);
	
	//Initial Src_Mem addr & Tgt_Mem addr
	sc_uint<32> src_addr;
	sc_uint<32> tgt_addr;
	sc_uint<3> size;
	sc_uint<1> start;
	
	//Src. Mem. & Tgt. Mem.
	sc_uint<32> Src_Mem[12];
	sc_uint<32> Tgt_Mem[12];
	
	for(int i = 0;i<12;i++){
		Src_Mem[i] = i + 1;
		Tgt_Mem[i] = 3 * i + 5;
	}
	
	for(int i = 0;i<12;i++){
		cout << "Src_Mem[" << i << "] = " << Src_Mem[i] << endl;
		cout << "Tgt_Mem[" << i << "] = " << Tgt_Mem[i] << endl;
	}
	
	
    //Instance
    dma dma1("DMA");
    dma1.master_port.data_in(master_data_in);
	dma1.master_port.addr(master_addr);
	dma1.master_port.data(master_data);
	dma1.master_port.r_w(master_r_w);
	
	dma1.slave_port.data_out(slave_data_out);
	dma1.slave_port.addr(slave_addr);
	dma1.slave_port.data(slave_data);
	dma1.slave_port.r_w(slave_r_w);
	
    dma1.interrupt(interrupt);
    dma1.reset(reset);
	dma1.clk(clock);
	
	
	//Create wave file
    sc_trace_file *out = sc_create_vcd_trace_file("DMA");
	//clock
    sc_trace(out, clock, "clock");
	//reset
	sc_trace(out, reset, "reset");
	//4 control registers
	sc_trace(out, dma1.Control_Reg[0x0], "Control_Reg_0x0");
	sc_trace(out, dma1.Control_Reg[0x4], "Control_Reg_0x4");
	sc_trace(out, dma1.Control_Reg[0x8], "Control_Reg_0x8");
	sc_trace(out, dma1.Control_Reg[0xc], "Control_Reg_0xc");
	//master 
    sc_trace(out, master_data_in, "master_port_data_in");
	sc_trace(out, master_addr, "master_port_addr");
	sc_trace(out, master_data, "master_port_data");
	sc_trace(out, master_r_w, "master_port_r_w");
	//slave
	sc_trace(out, slave_data_out, "slave_port_data_out");
	sc_trace(out, slave_addr, "slave_port_addr");
	sc_trace(out, slave_data, "slave_port_data");
	sc_trace(out, slave_r_w, "slave_port_r_w");
	//interrupt
	sc_trace(out, interrupt, "interrupt");
	//state
	sc_trace(out, dma1.dma_state, "dma_state");
	//Data_Reg
	sc_trace(out, dma1.Data_Reg, "Data_Reg");
	//DMA_base_addr
	sc_trace(out, dma1.DMA_base_addr, "DMA_base_addr");
	
	
    
	
	
	/*
	//Source Memory
    sc_trace(out, Src_Mem[0], "Src_Mem_0");
    sc_trace(out, Src_Mem[1], "Src_Mem_1");
    sc_trace(out, Src_Mem[2], "Src_Mem_2");
    sc_trace(out, Src_Mem[3], "Src_Mem_3");
    sc_trace(out, Src_Mem[4], "Src_Mem_4");
    sc_trace(out, Src_Mem[5], "Src_Mem_5");
    sc_trace(out, Src_Mem[6], "Src_Mem_6");
    sc_trace(out, Src_Mem[7], "Src_Mem_7");
	sc_trace(out, Src_Mem[8], "Src_Mem_8");
	sc_trace(out, Src_Mem[9], "Src_Mem_9");
	sc_trace(out, Src_Mem[10], "Src_Mem_10");
	sc_trace(out, Src_Mem[11], "Src_Mem_11");
	
	//Target Memory
    sc_trace(out, Tgt_Mem[0], "Tgt_Mem_0");
    sc_trace(out, Tgt_Mem[1], "Tgt_Mem_1");
    sc_trace(out, Tgt_Mem[2], "Tgt_Mem_2");
    sc_trace(out, Tgt_Mem[3], "Tgt_Mem_3");
    sc_trace(out, Tgt_Mem[4], "Tgt_Mem_4");
    sc_trace(out, Tgt_Mem[5], "Tgt_Memv5");
    sc_trace(out, Tgt_Mem[6], "Tgt_Mem_6");
    sc_trace(out, Tgt_Mem[7], "Tgt_Mem_7");
	sc_trace(out, Tgt_Mem[8], "Tgt_Mem_8");
	sc_trace(out, Tgt_Mem[9], "Tgt_Mem_9");
	sc_trace(out, Tgt_Mem[10], "Tgt_Mem_10");
	sc_trace(out, Tgt_Mem[11], "Tgt_Mem_11");
	*/
    
	//Simulation starts here.
	
	//Initial Value
	src_addr = 0xa0000000;
	tgt_addr = 0xb0000000;
	size = 4;
	start = 0;
	reset = 0;
	
	//Reset first.
	sc_start(0, SC_NS);
	reset.write(0);
	sc_start(10, SC_NS);
	reset.write(1);
	sc_start(10, SC_NS);
	
	//===============================First Move======================================//
	//DMA receive data from the CPU.
	slave_r_w.write(1);
	slave_data.write(src_addr);         //slave receive "SOURCE" from CPU
	slave_addr.write(0xf0000000);
    sc_start(10, SC_NS);
	slave_data.write(tgt_addr);         //slave receive "TARGET" from CPU
	slave_addr.write(0xf0000004);
    sc_start(10, SC_NS);
	slave_data.write(size);             //slave receive "SIZE" from CPU
	slave_addr.write(0xf0000008);       
    sc_start(10, SC_NS);
	slave_data.write(start);            //slave receive "START_CLEAR" from CPU
	slave_addr.write(0xf000000c);
	sc_start(10, SC_NS);
	slave_data.write(1);
	sc_start(10, SC_NS);
	slave_r_w.write(0);
	
	
	//Memory read and write data
	while(interrupt.read() == 0){
		//cout << "master_addr: " << master_addr.read() << " r_w: " << master_r_w.read()<< endl;
		if(((master_addr.read()&0xa0000000) == 0xa0000000)&&(master_r_w.read() == 0)){
			int Src_idx = (master_addr.read()&0x0FFFFFFF) >> 2;
			master_data_in.write(Src_Mem[Src_idx]);
			cout << "MEM1-1" << endl;
			sc_start(10, SC_NS);
		}else{
			cout << "MEM1-2" << endl;
			//sc_start(10, SC_NS);
		}
		
		cout << "master_addr: " << master_addr.read() << " r_w: " << master_r_w.read()<< endl;
		if(((master_addr.read()&0xb0000000) == 0xb0000000)&&(master_r_w.read() == 1)){
			int Tgt_idx = (master_addr.read()&0x0FFFFFFF) >> 2;
			Tgt_Mem[Tgt_idx] = master_data.read();
			cout << "MEM2-1" << endl;
			sc_start(10, SC_NS);
		}else{
			cout << "MEM2-2" << endl;
			//sc_start(10, SC_NS);
		}
	}
	
	
	//Check if memory read and write correctly.
	cout << "State: Memory Read & Write" << endl;
	for(int i = 0;i<12;i++){
		cout << "Src_Mem[" << i << "] = " << Src_Mem[i] << endl;
	}
	for(int i = 0;i<12;i++){
		cout << "Tgt_Mem[" << i << "] = " << Tgt_Mem[i] << endl;
	}
	
	//check the moveend_st
	sc_start(10,SC_NS);
	slave_r_w.write(1);
	slave_addr.write(0xf000000c);
	slave_data.write(0);
	sc_start(10,SC_NS);
	slave_r_w.write(0);
	sc_start(10,SC_NS);
	
	
	//===============================Second Move=====================================//
	//DMA receive data from the CPU.
	slave_r_w.write(1);
	slave_data.write(0xa0000018);         //slave receive "SOURCE" from CPU
	slave_addr.write(0xf0000000);
    sc_start(10, SC_NS);
	slave_data.write(0xb0000018);         //slave receive "TARGET" from CPU
	slave_addr.write(0xf0000004);
    sc_start(10, SC_NS);
	slave_data.write(2);             //slave receive "SIZE" from CPU
	slave_addr.write(0xf0000008);       
    sc_start(10, SC_NS);
	slave_data.write(start);            //slave receive "START_CLEAR" from CPU
	slave_addr.write(0xf000000c);
	sc_start(10, SC_NS);
	slave_data.write(1);
	sc_start(10, SC_NS);
	slave_r_w.write(0);
	
	
	//Memory read and write data
	while(interrupt.read() == 0){
		//cout << "master_addr: " << master_addr.read() << " r_w: " << master_r_w.read()<< endl;
		if(((master_addr.read()&0xa0000000) == 0xa0000000)&&(master_r_w.read() == 0)){
			int Src_idx = (master_addr.read()&0x0FFFFFFF) >> 2;
			master_data_in.write(Src_Mem[Src_idx]);
			cout << "MEM1-1" << endl;
			sc_start(10, SC_NS);
		}else{
			cout << "MEM1-2" << endl;
			//sc_start(10, SC_NS);
		}
		
		cout << "master_addr: " << master_addr.read() << " r_w: " << master_r_w.read()<< endl;
		if(((master_addr.read()&0xb0000000) == 0xb0000000)&&(master_r_w.read() == 1)){
			int Tgt_idx = (master_addr.read()&0x0FFFFFFF) >> 2;
			Tgt_Mem[Tgt_idx] = master_data.read();
			cout << "MEM2-1" << endl;
			sc_start(10, SC_NS);
		}else{
			cout << "MEM2-2" << endl;
			//sc_start(10, SC_NS);
		}
	}
	
	//Check if memory read and write correctly.
	cout << "State: Memory Read & Write" << endl;
	for(int i = 0;i<12;i++){
		cout << "Src_Mem[" << i << "] = " << Src_Mem[i] << endl;
	}
	for(int i = 0;i<12;i++){
		cout << "Tgt_Mem[" << i << "] = " << Tgt_Mem[i] << endl;
	}
	

	//check the moveend_st
	sc_start(10,SC_NS);
	slave_r_w.write(1);
	slave_addr.write(0xf000000c);
	slave_data.write(0);
	sc_start(10,SC_NS);
	slave_r_w.write(0);
	sc_start(10,SC_NS);
	//===============================End======================================//
	sc_start(50, SC_NS);
   
    sc_close_vcd_trace_file(out);
    return(0);
}
