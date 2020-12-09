function TEST_OUT;
	input integer io_addr;
	input integer rr_addr;
	input integer rr; 		// the value of the register rr
	begin
		case (uut.pipeline_stage)
			`STAGE_IF:  TEST_OUT = 1'b1;
			`STAGE_ID:
				if (!(uut.control.opcode_type === `TYPE_OUT)) begin
					TEST_OUT = 1'bx;
					$display("OUT %d, R%2d - ID: FAILED, check opcode_type: %d vs %d",
																						io_addr,
																						rr_addr,
																						`TYPE_OUT,
																						uut.control.opcode_type);
				end else if (!(uut.control.opcode_rr === rr_addr)) begin
					TEST_OUT = 1'bx;
					$display("OUT %d, R%2d - ID: FAILED, check opcode_rr: %d vs %d",
																						io_addr,
																						rr_addr,
																						rr_addr,
																						uut.control.opcode_rr);
				end else if (!(uut.control.opcode_imd === io_addr)) begin
					TEST_OUT = 1'bx;
					$display("OUT %d, R%2d - ID: FAILED, check opcode_imd: %d vs %d",
																						io_addr,
																						rr_addr,
																						io_addr,
																						uut.control.opcode_imd);
				end else if(!(uut.control.opcode_group[`GROUP_IO_WRITE])) begin
					TEST_OUT = 1'bx;
					$display("OUT %d, R%2d - ID: FAILED - OUT instruction should be in GROUP_IO_WRITE",
																															io_addr,
																															uut.rr_addr);
				end else if (!(uut.control.signals[`CONTROL_REG_RR_READ])) begin
					TEST_OUT = 1'bx;
					$display("OUT %d, R%2d - ID: FAILED, signal CONTROL_REG_RR_READ should be active for OUT instruction",
																						io_addr,
																						rr_addr);
				end else if (!(uut.control.bus_int.bus_addr === io_addr)) begin
					TEST_OUT = 1'bx;
					$display("OUT %d, R%2d - ID: FAILED, check bus_addr in bus_interface_unit.v: %d vs %d",
																						io_addr,
																						rr_addr,
																						io_addr, 
																						uut.control.bus_int.bus_addr);
				end else begin 
					TEST_OUT = 1'b1;
					$display("OUT %d, R%2d - ID: OK", io_addr, rr_addr,);
				end
			`STAGE_EX: TEST_OUT = 1'b1;
			`STAGE_MEM: TEST_OUT = 1'b1;
			`STAGE_WB: 
				if (!(uut.control.signals[`CONTROL_IO_WRITE])) begin
					TEST_OUT = 1'bx;
					$display("OUT %d, R%2d - WB: FAILED, signal CONTROL_IO_WRITE should be active for OUT instruction",
																						io_addr,rr_addr);
				end else begin 
					TEST_OUT = 1'b1;
					$display("OUT %d, R%2d - WB: OK", io_addr, rr_addr);
				end
																	
		endcase
	end
endfunction
