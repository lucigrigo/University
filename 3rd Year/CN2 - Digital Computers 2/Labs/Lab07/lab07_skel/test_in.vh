function TEST_IN;
	input integer io_addr;
	input integer rd_addr;
	begin
		case (uut.pipeline_stage)
			`STAGE_IF:
				TEST_IN = 1'b1;
			`STAGE_ID:
				if (!(uut.control.opcode_type === `TYPE_IN)) begin
					TEST_IN = 1'bx;
					$display("IN R%2d, %d - ID: FAILED, check opcode_type: %d vs %d",
																						rd_addr,
																						io_addr,
																						`TYPE_IN,
																						uut.control.opcode_type);
				end else if (!(uut.control.opcode_rd === rd_addr)) begin
					TEST_IN = 1'bx;
					$display("IN R%2d, %d - ID: FAILED, check opcode_rd: %d vs %d",
																						rd_addr,
																						io_addr,
																						rd_addr,
																						uut.control.opcode_rd);
				end else if (!(uut.control.opcode_imd === io_addr)) begin
					TEST_IN = 1'bx;
					$display("IN R%2d, %d - ID: FAILED, check opcode_imd: %d vs %d",
																						rd_addr,
																						io_addr,
																						io_addr,
																						uut.control.opcode_imd);
				end else if(!(uut.control.opcode_group[`GROUP_IO_READ])) begin
					TEST_IN = 1'bx;
					$display("IN R%2d, %d - ID: FAILED - IN instruction should be in GROUP_IO_READ",
																						rd_addr,
																						io_addr);
				end else if (!(uut.control.signals[`CONTROL_IO_READ])) begin
					TEST_IN = 1'bx;
					$display("IN R%2d, %d - ID: FAILED, signal CONTROL_IO_READ should be active for IN instruction",
																						rd_addr,
																						io_addr);
				end else if (!(uut.control.bus_int.bus_addr === io_addr)) begin
					TEST_IN = 1'bx;
					$display("IN R%2d, %d - ID: FAILED, check bus_addr in bus_interface_unit.v: %d vs %d",
																						rd_addr,
																						io_addr,
																						io_addr, 
																						uut.control.bus_int.bus_addr);
				end else begin 
					TEST_IN = 1'b1;
					$display("IN R%2d, %d - ID: OK", rd_addr, io_addr);
				end
			`STAGE_EX: 
				TEST_IN = 1'b1;
			`STAGE_MEM:
				TEST_IN = 1'b1;
			`STAGE_WB: 
				if (!(uut.control.signals[`CONTROL_REG_RD_WRITE])) begin
					TEST_IN = 1'bx;
					$display("IN R%2d, %d - WB: FAILED, signal CONTROL_REG_RD_WRITE should be active for IN instruction",
																						rd_addr,
																						io_addr);
				end else	if (!(uut.control.writeback_value === uut.control.bus_data)) begin 
					TEST_IN = 1'bx;
					$display("IN R%2d, %d - WB: FAILED, check writeback_value : %d vs %d",
																						rd_addr,
																						io_addr, 
																						uut.control.bus_data,
																						uut.control.writeback_value);
				end else begin
					TEST_IN = 1'b1;
					$display("IN R%2d, %d - WB: OK", rd_addr, io_addr);
				end
		endcase
	end
endfunction
