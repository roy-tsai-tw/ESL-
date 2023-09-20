#ifndef DMA_H
#define DMA_H

#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/simple_initiator_socket.h"
using namespace sc_core;
using namespace sc_dt;
using namespace std;

#define slave_st 0
#define dataR_st 1
#define dataW_st 2
#define MVend_st 3

SC_MODULE(dma){
	//input & output
	sc_in<bool> clk; 
	sc_in<bool> reset; 
	sc_out<bool> Interrupt;
	tlm_utils::simple_target_socket<dma> slave_p;
	tlm_utils::simple_initiator_socket<dma> master_p;
	
	//base address register
	sc_signal<sc_uint<32> > DMA_base_addr; 
	
	//4 control registers
	sc_signal<sc_uint<32> > SOURCE; //Control_Reg[0x0]:SOURCE
	sc_signal<sc_uint<32> > TARGET; //Control_Reg[0x4]:TARGET
	sc_signal<sc_uint<32> > SIZE;   //Control_Reg[0x8]:SIZE
	sc_signal<bool> START_CLEAR;   //Control_Reg[0xc]:START_CLEAR;
	
	//State signal
	sc_uint<3> dma_state;
	
	//Local variables
	bool slave_r_w;
	int tmp_addr_mask; 
	int tmp_data;
	
	void dma_proc();
	void b_transport(tlm::tlm_generic_payload&, sc_time&);
	
	
	SC_CTOR(dma): slave_p("slave_p"), master_p("master_p"){
		slave_p.register_b_transport(this, &dma::b_transport);
        SC_CTHREAD(dma_proc, clk.pos());
        reset_signal_is(reset, false);
		
		DMA_base_addr = 0xf0000000;

    }
};

#endif
