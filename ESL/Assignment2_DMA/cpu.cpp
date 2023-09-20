#include "cpu.h"



void cpu::cpu_proc(){
	DMA_Base_addr = 0xf0000000;
	NOP_Base_addr = 0xd0000000;
	Base_addr.write(NOP_Base_addr);
	count.write(0);
	SOURCE = 0xa0000000;
	TARGET = 0xb0000000;
	SIZE = 0;
	START_CLEAR = 0;
	
	while(1){
		wait();
		
		tlm::tlm_generic_payload* cpu_m = new tlm::tlm_generic_payload;
		sc_time delay = sc_time(10,SC_NS);
		tlm::tlm_command cmd_m;
		
		switch(act){
					
			case DMA_Task:
				
				if(count.read() < 5){
					
					switch(count.read()){
						case 0: //IDLE
							cout << "---@count 0 CPU wait for basic settings --- " << endl;
							Base_addr.write(DMA_Base_addr);
							SOURCE = 0xa0000004;
							TARGET = 0xb000000c;
							SIZE = 0x00000008;
							START_CLEAR = 1;
							count.write(count.read() + 1);
							//cout << "DMA_TASK: 0" << endl;
						break;
						case 1: //SEND SOURCE ADDRESS
							cmd_m = tlm::TLM_WRITE_COMMAND;
							cout << "---@count 1 CPU send SOURCE ADDRESS to DMA --- " << endl;
							cpu_m->set_command(cmd_m);
							cpu_m->set_address(Base_addr.read());
							cpu_m->set_data_ptr(reinterpret_cast<unsigned char*>(&SOURCE) );
							cpu_m->set_data_length(4);
							cpu_m->set_streaming_width(4);
							cpu_m->set_byte_enable_ptr(0);
							cpu_m->set_dmi_allowed(false);
							cpu_m->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE );
							socket_m->b_transport( *cpu_m, delay );
							count.write(count.read() + 1);
							//cout << "DMA_TASK: 1" << endl;
						break;
						
						case 2: //SEND TARGET ADDRESS
							cmd_m = tlm::TLM_WRITE_COMMAND;
							cout << "---@count 2 CPU send TARGET ADDRESS to DMA --- " << endl;
							cpu_m->set_command(cmd_m);
							cpu_m->set_address(Base_addr.read() + 4);
							cpu_m->set_data_ptr(reinterpret_cast<unsigned char*>(&TARGET) );
							cpu_m->set_data_length(4);
							cpu_m->set_streaming_width(4);
							cpu_m->set_byte_enable_ptr(0);
							cpu_m->set_dmi_allowed(false);
							cpu_m->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE );
							socket_m->b_transport( *cpu_m, delay );
							count.write(count.read() + 1);
							//cout << "DMA_TASK: 2" << endl;
						break;
						
						case 3: //SEND SIZE
							cmd_m = tlm::TLM_WRITE_COMMAND;
							cout << "---@count 3 CPU send SIZE to DMA --- " << endl;
							cpu_m->set_command(cmd_m);
							cpu_m->set_address(Base_addr.read() + 8);
							cpu_m->set_data_ptr(reinterpret_cast<unsigned char*>(&SIZE) );
							cpu_m->set_data_length(4);
							cpu_m->set_streaming_width(4);
							cpu_m->set_byte_enable_ptr(0);
							cpu_m->set_dmi_allowed(false);
							cpu_m->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE );
							socket_m->b_transport( *cpu_m, delay );
							count.write(count.read() + 1);
							//cout << "DMA_TASK: 3" << endl;
						break;
						case 4: //SEND START_CLEAR
							cmd_m = tlm::TLM_WRITE_COMMAND;
							cout << "---@count 4 CPU send START_CLEAR to DMA --- " << endl;
							cpu_m->set_command(cmd_m);
							cpu_m->set_address(Base_addr.read() + 12);
							cpu_m->set_data_ptr(reinterpret_cast<unsigned char*>(&START_CLEAR) );
							cpu_m->set_data_length(4);
							cpu_m->set_streaming_width(4);
							cpu_m->set_byte_enable_ptr(0);
							cpu_m->set_dmi_allowed(false);
							cpu_m->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE );
							socket_m->b_transport( *cpu_m, delay );
							count.write(count.read() + 1);
							//cout << "DMA_TASK: 4" << endl;
							
						break;
						default:
							//count.write(0);
							cout << "DMA_TASK: default" << endl;
						break;
					}
					
				}else{
					
					if(count.read() == 5){
						cmd_m = tlm::TLM_READ_COMMAND;
						cpu_m->set_command(cmd_m);
						cpu_m->set_address(Base_addr.read());
						cpu_m->set_data_ptr(reinterpret_cast<unsigned char*>(&START_CLEAR) );
						cpu_m->set_data_length(4);
						cpu_m->set_streaming_width(4);
						cpu_m->set_byte_enable_ptr(0);
						cpu_m->set_dmi_allowed(false);
						cpu_m->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE );
						socket_m->b_transport( *cpu_m, delay );
						//cout << "---@count 5 cmd_m change into READ mode --- " << endl;
						
					}
					
					if(interrupt.read() == 1){
						START_CLEAR = 0;
						cmd_m = tlm::TLM_WRITE_COMMAND;
						cpu_m->set_command(cmd_m);
						cpu_m->set_address(Base_addr.read());
						cpu_m->set_data_ptr(reinterpret_cast<unsigned char*>(&START_CLEAR) );
						cpu_m->set_data_length(4);
						cpu_m->set_streaming_width(4);
						cpu_m->set_byte_enable_ptr(0);
						cpu_m->set_dmi_allowed(false);
						cpu_m->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE );
						socket_m->b_transport( *cpu_m, delay );
						//cout << "---@count " << count.read() << " interrupt =1, START_CLEAR = 0 " << endl;
						
					}

					if((START_CLEAR == 0) && (count.read() == 5 + (SIZE/4) + 1)){
						cmd_m = tlm::TLM_READ_COMMAND;
						cpu_m->set_command(cmd_m);
						cpu_m->set_address(Base_addr.read());
						cpu_m->set_data_ptr(reinterpret_cast<unsigned char*>(&START_CLEAR) );
						cpu_m->set_data_length(4);
						cpu_m->set_streaming_width(4);
						cpu_m->set_byte_enable_ptr(0);
						cpu_m->set_dmi_allowed(false);
						cpu_m->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE );
						socket_m->b_transport( *cpu_m, delay );
						//cout << "---@count " << count.read() << " cmd_m change into READ mode ---"  << endl;
					}
					count.write(count.read() + 1);
					//cout << "---@count " << count.read() << " --- "<< endl;
				}

			break;
			case OTHER_TASK:
				cout << "CPU is doing other tasks. Please wait." << endl;
			break;
			default:
				cout << "CPU is in default mode. Nothing happened." << endl;
			break;
		}
	}
}




















