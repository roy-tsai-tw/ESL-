
#include "dma.h"


void dma::dma_proc(){
	//sc_uint<3> state;
	//sc_uint<3> n_state;
	sc_uint<32> src_mem_addr;
	sc_uint<32> tgt_mem_addr;
	sc_uint<32> src_mem_data;
	sc_uint<32> tgt_mem_data;
	
	
	DMA_base_addr = 0xf0000000;
	Data_Reg = 0;
	Control_Reg[0x0] = 0;   //Control_Reg[0x0]:SOURCE
	Control_Reg[0x4] = 0;   //Control_Reg[0x4]:TARGET
	Control_Reg[0x8] = 0;   //Control_Reg[0x8]:SIZE
	Control_Reg[0xc] = 0;   //Control_Reg[0xc]:START_CLEAR;
	
	interrupt.write(0);
	dma_state = slave_st;
	
	while(true){
		wait();

		switch(dma_state){
		
			case slave_st: //State 0:Read from slave port

				if(slave_port.r_w.read() == 1){
					switch(slave_port.addr.read() - DMA_base_addr.read()){
						case 0x0: 
							Control_Reg[0x0] = slave_port.data.read();
							dma_state = slave_st;
						break;
						case 0x4: 
							Control_Reg[0x4] = slave_port.data.read();
							dma_state = slave_st;
						break;
						case 0x8: 
							Control_Reg[0x8] = slave_port.data.read();
							//size = slave_port.data.read();
							dma_state = slave_st;
						break;
						case 0xc: 
							Control_Reg[0xc] = slave_port.data.read();
							if(slave_port.data.read() == 1 && Control_Reg[0x8] > 0){
								dma_state = readaddr_st;
								master_port.r_w.write(0);
								master_port.addr = Control_Reg[0x0];
							}else{
								dma_state = slave_st;
							}	
						break;
						default:
							dma_state = slave_st;
							cout << "0-1" << endl;
						break;
					}			
				}
			break;
			case readaddr_st: //State 1:Get source addr. from SOURCE register
				//slave_port.r_w.write(0);
				if((Control_Reg[0xc] == 1)&& (Control_Reg[0x8] > 0)){
					Data_Reg = master_port.data_in.read();
					dma_state = getdata_st;
					cout << "1-1"<<endl;
				}else{
					dma_state = slave_st;
					cout << "1-2" << endl;
				}
			break;
			case getdata_st: //State 2:Get data from Src.mem
				if((Control_Reg[0xc] == 1)&&(Control_Reg[0x8] > 0)){
					master_port.r_w.write(1);
					//master_port.addr = Control_Reg[0x0];
					//src_mem_addr = master_port.data_in.read();
					//src_mem_data = Tgt_Mem[src_mem_addr];
					master_port.addr = Control_Reg[0x4];
					master_port.data = Data_Reg.read();
					Control_Reg[0x0] = Control_Reg[0x0] + 0x4;
					dma_state = writedata_st;
					cout << "2-1" << endl;
				}
				else{
					dma_state = slave_st;
					cout << "2-2" << endl;
				}
			break;
			case writedata_st: //State 3:Write data into Tgt.mem
				if((Control_Reg[0xc] == 1)&&(Control_Reg[0x8] > 0)){
					//size = size - 1;
					Control_Reg[0x8] = Control_Reg[0x8] - 0x1;
					Control_Reg[0x4] = Control_Reg[0x4] + 0x4;
					master_port.r_w.write(0);
					master_port.addr = Control_Reg[0x0];
					
					dma_state = (Control_Reg[0x8] == 0)? moveend_st:readaddr_st;
					cout << "3-1" << endl;
				}else{
					dma_state = slave_st;
				}
			break;
			case moveend_st: //State 4:State after the data movement is completed
				interrupt.write(1);
				master_port.r_w.write(0);
				if((slave_port.addr.read() - DMA_base_addr.read() == 0xc)&&(slave_port.data.read() == 0)&&(slave_port.r_w.read() == 1)){
					interrupt.write(0);
					Data_Reg = 0;
					//slave_port.r_w.write(1);
					Control_Reg[0x0] = 0;
					Control_Reg[0x4] = 0;
					Control_Reg[0x8] = 0;
					Control_Reg[0xc] = 0;
					//slave_port.r_w.write(0);
					dma_state = slave_st;
					cout << "4-1" << endl;
				}
				else{
					dma_state = moveend_st;
					cout << "4-2" << endl;
				}
			break;
			default:
				dma_state = slave_st;
				cout << "5-1" << endl;
			break;
			}	
		}	
}
