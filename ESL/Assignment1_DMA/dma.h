#ifndef DMA_H
#define DMA_H

#include <systemc.h>

#define slave_st 0
#define readaddr_st 1
#define getdata_st 2
#define writedata_st 3
#define moveend_st 4

struct master{
	sc_in<sc_uint<32> > data_in; //input
	sc_out<sc_uint<32> > addr;    //output
	sc_out<sc_uint<32> > data;    //output
	sc_out<bool> r_w; //1:read, 0:write //output

};

struct slave{
	sc_out<sc_uint<32> > data_out; //output
	sc_in<sc_uint<32> > addr;    //input
	sc_in<sc_uint<32> > data;    //input
	sc_in<bool> r_w; //0:read, 1:write //input

};

SC_MODULE(dma){
	//input & output
	struct master master_port;
	struct slave slave_port;
	sc_out<bool> interrupt; //output
	sc_in<bool> reset; //input
	sc_in<bool> clk; //clock
	
	//base address register
	sc_signal<sc_uint<32> > DMA_base_addr; 
	
	//4 control registers
	sc_uint<32> Control_Reg[16];
	//sc_uint<32> SOURCE; //Control_Reg[0x0]:SOURCE
	//sc_uint<32> TARGET; //Control_Reg[0x4]:TARGET
	//sc_uint<32> SIZE;   //Control_Reg[0x8]:SIZE
	//bool START_CLEAR;   //Control_Reg[0xc]:START_CLEAR;
	
	//Data Register
	sc_signal<sc_uint<32> > Data_Reg;
	
	//state signal
	sc_uint<3> dma_state;
	
	//Src. Mem. & Tgt. Mem.
	sc_uint<32> Src_Mem[12];
	sc_uint<32> Tgt_Mem[12];
	
	void dma_proc();
	//void getnextst();
	//void setstate();
	
	SC_CTOR(dma){
        SC_CTHREAD(dma_proc, clk.pos());
        reset_signal_is(reset, false);
		
		/*
		SC_METHOD(getnextst);
		sensitive << current_state;
		SC_METHOD(setstate);
		sensitive_pos (clk);
		reset_signal_is(reset, false);
		*/
    }
};

#endif