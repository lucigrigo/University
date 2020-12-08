function TEST_SBI;
	input integer io_addr;
	input integer bit_val;
	begin
		case (uut.pipeline_stage)
			`STAGE_IF:
				TEST_SBI = 1'b1;
			`STAGE_ID:
				if (!(uut.control.opcode_type === `TYPE_SBI)) begin
					TEST_SBI = 1'bx;
					$display("SBI  %d,R%2d - ID: FAILED, check opcode_type: %d vs %d",
																						
																						io_addr,
																						bit_val,
																						`TYPE_SBI,
																						uut.control.opcode_type);
				end else if (!(uut.control.opcode_bit === bit_val)) begin
					TEST_SBI = 1'bx;
					$display("SBI  %d,R%2d - ID: FAILED, check opcode_bit: %d vs %d",
																						
																						io_addr,
																						bit_val,
																						bit_val,
																						uut.control.opcode_bit);
				end else if (!(uut.control.opcode_imd === io_addr)) begin
					TEST_SBI = 1'bx;
					$display("SBI  %d,R%2d - ID: FAILED, check opcode_imd: %d vs %d",
																						
																						io_addr,
																						bit_val,
																						io_addr,
																						uut.control.opcode_imd);
				end else if(!(uut.control.opcode_group[`GROUP_IO_READ])) begin
					TEST_SBI = 1'bx;
					$display("SBI  %d,R%2d,  - ID: FAILED - SBI instruction should be in GROUP_IO_READ",
																						
																						io_addr,
																						bit_val);
				end else if(!(uut.control.opcode_group[`GROUP_IO_READ])) begin
					TEST_SBI = 1'bx;
					$display("SBI  %d,R%2d,  - ID: FAILED - SBI instruction should be in GROUP_IO_READ",
																						
																						io_addr,
																						bit_val);
																						
				end else if(!(uut.control.opcode_group[`GROUP_ALU_AUX])) begin
					TEST_SBI = 1'bx;
					$display("SBI  %d,R%2d,  - ID: FAILED - SBI instruction should be in GROUP_ALU_AUX",
																						io_addr,
																						bit_val);
				end else if (!(uut.control.bus_int.bus_addr === io_addr)) begin
					TEST_SBI = 1'bx;
					$display("SBI %d,R%2d, - ID: FAILED, check bus_addr in bus_interface_unit.v: %d vs %d",
																						
																						io_addr,
																						bit_val,
																						io_addr, 
																						uut.control.bus_int.bus_addr);
				end else if (!(uut.control.alu_rr == uut.control.bus_data)) begin
					TEST_SBI = 1'bx;
					$display("SBI R%2d, %d - ID: FAILED, signal alu_rr should have other value for SBI instruction",
																						
																						io_addr,
																						bit_val);
				end else begin 
					TEST_SBI = 1'b1;
					$display("SBI R%2d, %d - ID: OK", io_addr, bit_val);
				end
			`STAGE_EX: 
				if (!uut.control.signals[`CONTROL_IO_WRITE]) begin
					TEST_SBI = 1'bx;
					$display("SBI R%2d, %d - ID: FAILED, signal CONTROL_IO_WRITE should be active for SBI instruction",
																						
																						io_addr,
																						bit_val);
				end else if (!uut.control.alu_enable) begin
					TEST_SBI = 1'bx;
					$display("SBI R%2d, %d - ID: FAILED, signal alu_enable should be active for SBI instruction",
																						
																						io_addr,
																						bit_val);
				end else if (!(uut.control.alu_rd == (1 << bit_val))) begin
					TEST_SBI = 1'bx;
					$display("SBI R%2d, %d - ID: FAILED, signal alu_rd should have other value for SBI instruction",
																						
																						io_addr,
																						bit_val);
				end else begin
					TEST_SBI = 1'b1;
					$display("SBI R%2d, %d - EX: OK", io_addr, bit_val);
				end
			`STAGE_MEM: TEST_SBI = 1'b1;
			`STAGE_WB: TEST_SBI = 1'b1;
				
		endcase
	end
endfunction
