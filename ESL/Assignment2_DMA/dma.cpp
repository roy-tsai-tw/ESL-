#include "dma.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

/*-----------------------slave mode------------------------*/
void dma::b_transport(tlm::tlm_generic_payload& trans, sc_time& delay){
	tlm::tlm_command cmd_s = trans.get_command();
	sc_dt::uint64 addr_s = trans.get_address();
	unsigned char* data_s = trans.get_data_ptr();
	unsigned int len = trans.get_data_length();
	
	cout << "---------------- Bus Transaction (CPU & DMA) -------------"<<endl;
    cout << sc_time_stamp();
    cout << "Command : "<< (cmd_s ? "write" : "read") <<endl;
    cout <<  "Address : 0x" << hex << addr_s <<endl;
	
	if(cmd_s == tlm::TLM_WRITE_COMMAND){
		//addressed write operations
		tmp_addr_mask = addr_s - DMA_base_addr.read();
		tmp_data = *(reinterpret_cast<int*>(data_s));
		slave_r_w = 1;
		cout << "addr = 0x" << tmp_addr_mask << endl;
        cout << "data = " << hex << *(reinterpret_cast<int*>(data_s)) << endl;
	}else{
		//addressed read operations
		slave_r_w = 0;
		
	}
	
	wait(delay);  //use the external delay
	trans.set_response_status(tlm::TLM_OK_RESPONSE);
}

/*-----------------------state proc------------------------*/
void dma::dma_proc(){
	//reset behavior
	SOURCE = 0;
	TARGET = 0;
	SIZE = 0;
	START_CLEAR = 0;
	Interrupt.write(0);
	slave_r_w = 0;
	
	while(1){
		wait();
		tlm::tlm_generic_payload* trans_m = new tlm::tlm_generic_payload;
		tlm::tlm_command cmd_m;
		sc_time delay = sc_time(10,SC_NS);
		sc_uint<32> addr_s, addr_t;
		unsigned int data_get;
		
		switch(dma_state){
			case slave_st: //State 0:Read from slave port

				if((slave_r_w == 1) && (START_CLEAR.read() == 0)){
					cout << "tmp_addr_mask: " << tmp_addr_mask << endl;
					switch(tmp_addr_mask){
						case 0x0: 
							SOURCE.write(tmp_data);
							dma_state = slave_st;
							cout << "SOURCE = " << hex << tmp_data << endl;
							cout << "DMA_slave_st: 0x0" << endl;
						break;
						case 0x4: 
							TARGET.write(tmp_data);
							dma_state = slave_st;
							cout << "TARGET = " << hex << tmp_data << endl;
							cout << "DMA_slave_st: 0x4" << endl;
						break;
						case 0x8: 
							SIZE.write(tmp_data);
							dma_state = slave_st;
							cout << "SIZE = " << hex << tmp_data << endl;
							cout << "DMA_slave_st: 0x8" << endl;
						break;
						case 0xc: 
							START_CLEAR.write(tmp_data);
							if(tmp_data == 1 && SIZE.read() > 0){
								dma_state = dataR_st;
								cout << "START = " << hex << tmp_data << endl;
								cout << "DMA_slave_st: 0xc_1" << endl;
								//master_port.r_w.write(0);
								//master_port.addr = Control_Reg[0x0];
							}else{
								dma_state = slave_st;
								//slave_r_w = 0;
								cout << "DMA_slave_st: 0xc_2" << endl;
							}	
						break;
						default:
							dma_state = slave_st;
							cout << "DMA_slave_st: default" << endl;
						break;
					}			
				}
			break;
			case dataR_st: //State 1:Get source addr. from SOURCE register
				//slave_port.r_w.write(0);
				if((START_CLEAR.read() == 1)&& (SIZE.read() > 0)){
					//Data_Reg = master_port.data_in.read();
					addr_s = SOURCE.read();
					//addr_t = TARGET.read();
					
					
					//addr_s = SOURCE.read();
					cmd_m = tlm::TLM_READ_COMMAND;
					trans_m->set_command(cmd_m);
					trans_m->set_address(addr_s);
					trans_m->set_data_ptr(reinterpret_cast<unsigned char*>(&data_get));
					//cout << "data from src. mem.: " << hex << data_get << endl;
					trans_m->set_data_length(4);
					trans_m->set_streaming_width(4);
					trans_m->set_byte_enable_ptr(0);
					trans_m->set_dmi_allowed(false);
					trans_m->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
					master_p->b_transport(*trans_m, delay);
					
					cout << "DMA1: dataR" << endl;
					SOURCE.write(SOURCE.read() + 4);
					addr_s = addr_s + 4;
					dma_state = dataW_st;
					
				}else{
					dma_state = slave_st;
					//cout << "1-2" << endl;
				}
			break;
			case dataW_st:
				if((START_CLEAR.read() == 1)&& (SIZE.read() > 0)){
					addr_t = TARGET.read();
		
					cmd_m = tlm::TLM_WRITE_COMMAND;
					trans_m->set_command(cmd_m);
					trans_m->set_address(addr_t);
					trans_m->set_data_ptr(reinterpret_cast<unsigned char*>(&data_get));
					cout << "data to tgt. mem.: " << hex << data_get << endl;
					trans_m->set_data_length(4);
					trans_m->set_streaming_width(4);
					trans_m->set_byte_enable_ptr(0);
					trans_m->set_dmi_allowed(false);
					trans_m->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
					master_p->b_transport(*trans_m, delay);
					
					TARGET.write(TARGET.read() + 4);
					SIZE.write(SIZE.read() - 4);
					addr_t = addr_t + 4;
					dma_state = ((SIZE.read() - 4) == 0)?MVend_st:dataR_st;
					
				}else{
					dma_state = slave_st;
					//cout << "1-2" << endl;
				}
			break;
			case MVend_st: //State 2: Data move end, set Interrupt and other signals.
				Interrupt.write(1);
				if((slave_r_w == 1) && (SIZE.read() == 0)){
					START_CLEAR.write(0);
					Interrupt.write(0);
					SOURCE.write(0);
					TARGET.write(0);
					SIZE.write(0);
					START_CLEAR.write(0);
					dma_state = slave_st;
				}
			break;
			default:
					dma_state = slave_st;
					//cout << "2-1" << endl;
			break;
		}

	}
}