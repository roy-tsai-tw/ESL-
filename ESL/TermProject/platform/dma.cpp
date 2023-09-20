#include "dma.h"

void dma::dma_process() {
	Interrupt.write(false);
	base_addr = 0x100000;
	cnt = 0;
	status = 0;
	tlm::tlm_command cmd = tlm::TLM_READ_COMMAND;

	while(1) {
		wait();
		if (status == 0) { //IDLE
			if (START_CLEAR) {
				cout << "start/clear = 1, DMA start\n\nmoving data ...\n\n";
				status = 1;
			}
		}
		else if (status == 1) { //moving data
			if (cnt < SIZE) {
				tlm::tlm_generic_payload *trans = new tlm::tlm_generic_payload;
				sc_time delay = sc_time(10, SC_NS);
				if (cmd == tlm::TLM_WRITE_COMMAND) {
					trans->set_command(cmd);
					trans->set_address(TARGET + cnt * 4);
					trans->set_data_ptr(reinterpret_cast<unsigned char*> (&reg));
					trans->set_data_length(4);
					trans->set_streaming_width(4);
					trans->set_byte_enable_ptr(0);
					trans->set_dmi_allowed(false);
					trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
					master->b_transport(*trans, delay);
					if (trans->is_response_error())
						SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
					else {
						cmd = tlm::TLM_READ_COMMAND;
						cnt++;
					}
				}
				else if (cmd == tlm::TLM_READ_COMMAND) {
					trans->set_command(cmd);
					trans->set_address(SOURCE + cnt * 4);
					trans->set_data_ptr(reinterpret_cast<unsigned char*> (&reg));
					trans->set_data_length(4);
					trans->set_streaming_width(4);
					trans->set_byte_enable_ptr(0);
					trans->set_dmi_allowed(false);
					trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
					master->b_transport(*trans, delay);
					if (trans->is_response_error())
						SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
					else
						cmd = tlm::TLM_WRITE_COMMAND;
				}
			}
			else { //complete
				cout << "moving data completed, Interrupt high\n";
				status = 2;
				Interrupt.write(true);
			}
		}
		else { //Interrupt high, waiting for clear by CPU
			if (!START_CLEAR) {
				cout << "start/clear = 0\nInterrupt low\n";
				status = 0;
				cnt = 0;
				Interrupt.write(false);
			}
		}
	}
}

void dma::b_transport(tlm::tlm_generic_payload &trans, sc_time &delay) {
	tlm::tlm_command cmd = trans.get_command();
	sc_dt::uint64 addr = trans.get_address();
	unsigned char *ptr = trans.get_data_ptr();
	unsigned int len = trans.get_data_length();
	unsigned char *byte = trans.get_byte_enable_ptr();
	unsigned int wid = trans.get_streaming_width();

	if (addr > sc_dt::uint64(0xC) || byte != 0 || len > 4 || wid < len)
		SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");
	else if (cmd == tlm::TLM_WRITE_COMMAND) {
		uint tmp = *(reinterpret_cast<uint *>(ptr));
		switch (addr) { //in this platform, base_addr has already been masked
			case 0x0: SOURCE = tmp;
			break;
			case 0x4: TARGET = tmp;
			break;
			case 0x8: SIZE = tmp;
			break;
			case 0xC: {
				if (tmp != 0)
					START_CLEAR = true;
				else
					START_CLEAR = false;
			}
			break;
			default: cout << "wrong address for DMA slave port (write) !\n";
		}
		wait(delay);
		trans.set_response_status(tlm::TLM_OK_RESPONSE);
	}
}