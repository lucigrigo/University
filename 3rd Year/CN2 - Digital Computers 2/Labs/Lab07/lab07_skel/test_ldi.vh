function TEST_LDI;
	input integer rd_addr;
	input integer value;
	begin
		case (uut.pipeline_stage)
			`STAGE_IF:  TEST_LDI = 1'b1;
			`STAGE_ID:
				if(uut.control.opcode_group[`GROUP_REGISTER]
				&& uut.control.opcode_type == `TYPE_LDI
				&& uut.control.opcode_imd == value)
					begin
						TEST_LDI = 1'b1;
						$display("LDI R%2d, %3d - ID: OK", uut.control.opcode_rd, uut.control.opcode_imd);
					end
				else
					begin
						TEST_LDI = 1'bx;
						$display("LDI R%2d, %3d - ID: FAILED", uut.control.opcode_rd, uut.control.opcode_imd);
					end
			`STAGE_EX:  TEST_LDI = 1'b1;
			`STAGE_MEM: TEST_LDI = 1'b1;
			`STAGE_WB:
				if((uut.control.writeback_value == value)
				&& (uut.control.signals[`CONTROL_REG_RD_WRITE])
				&& (uut.rd_addr == rd_addr))
					begin
							TEST_LDI = 1'b1;
							$display("LDI R%2d, %3d - WB: OK (R%2d = %3d)",
																					uut.rd_addr,
																					uut.control.opcode_imd,
																					uut.rd_addr,
																					value);
					end
				else
					begin
						TEST_LDI = 1'bx;
						$display("LDI R%2d, %3d - WB: FAILED => (%3d) vs (%3d)", 
																							rd_addr,
																							value,
																							uut.control.writeback_value,
																							value);
					end
		endcase
	end
endfunction
