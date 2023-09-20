#ifndef MEMORY_H
#define MEMORY_H

#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/simple_initiator_socket.h"
using namespace sc_core;
using namespace sc_dt;
using namespace std;

SC_MODULE(memory){
	tlm_utils::simple_target_socket<memory> slave_p;
	enum { SIZE = 256 };
	int memsrc[SIZE];
	int memtgt[SIZE];
	
	void b_transport( tlm::tlm_generic_payload&, sc_time& );
	
	SC_CTOR(memory) : slave_p("slave_p") {
		slave_p.register_b_transport(this, &memory::b_transport);
   		// Initialize memory with random data
   	 	for (int i = 0; i < SIZE; i++)
      		memsrc[i] = 0xa0000000 | ((i*150+21) % 256);
      	for (int i = 0; i < SIZE; i++)
      		memtgt[i] = 0xb0000000 | ((i*200+21) % 256);
    }
};

#endif