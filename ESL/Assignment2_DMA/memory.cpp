#include "memory.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

void memory::b_transport( tlm::tlm_generic_payload& trans, sc_time& delay ){
    	tlm::tlm_command cmd = trans.get_command();
    	sc_dt::uint64    adr = trans.get_address();
    	unsigned char*   ptr = trans.get_data_ptr();
    	unsigned int     len = trans.get_data_length();
    	unsigned char*   byt = trans.get_byte_enable_ptr();
    	unsigned int     wid = trans.get_streaming_width();

    	if((adr & 0xff000000) == 0xa0000000 ){
    		if ( cmd == tlm::TLM_READ_COMMAND )
      			memcpy(ptr, &memsrc[(adr - 0xa0000000)/4], len);
    		else if ( cmd == tlm::TLM_WRITE_COMMAND )
      			memcpy(&memsrc[(adr - 0xa0000000)/4], ptr, len);
		}
		else if((adr & 0xff000000) == 0xb0000000 ){
    		if ( cmd == tlm::TLM_READ_COMMAND )
      			memcpy(ptr, &memtgt[(adr - 0xb0000000)/4], len);
    		else if ( cmd == tlm::TLM_WRITE_COMMAND )
      			memcpy(&memtgt[(adr - 0xb0000000)/4], ptr, len);
		}
    	//Check response
   		trans.set_response_status( tlm::TLM_OK_RESPONSE );
  	}
