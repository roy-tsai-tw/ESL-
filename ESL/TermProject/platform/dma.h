#ifndef DMA_H
#define DMA_H

#include "systemc"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

SC_MODULE(dma) {
	tlm_utils::simple_initiator_socket<dma> master;
	tlm_utils::simple_target_socket<dma> slave;
	
	sc_in<bool> clk, reset;
	tlm::tlm_analysis_port<unsigned int> Interrupt;
	uint SOURCE; // 0x0
	uint TARGET; // 0x4
	uint SIZE; // 0x8
	bool START_CLEAR; // 0xC
	uint base_addr; // base address for DMA
	uint reg;
	uint cnt;
	uint status;
	
	void dma_process();
	void b_transport(tlm::tlm_generic_payload &, sc_time &);

	SC_CTOR(dma): master("master"), slave("slave") {
		SC_CTHREAD(dma_process, clk.pos());
		reset_signal_is(reset, false);
		slave.register_b_transport(this, &dma::b_transport);
	}
};

#endif