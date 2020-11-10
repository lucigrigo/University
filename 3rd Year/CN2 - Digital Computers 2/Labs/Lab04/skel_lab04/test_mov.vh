function TEST_MOV;
	input [`STAGE_COUNT-1:0]       pipeline_stage;
	input [`GROUP_COUNT-1:0]       opcode_group;
	input [`OPCODE_COUNT-1:0]      opcode_type;
	input [11:0]                   opcode_imd;
	input [`TEST_DATA_WIDTH-1:0]   writeback_value;
	input [`SIGNAL_COUNT-1:0]      signals;
	input [`TEST_R_ADDR_WIDTH-1:0] rr_addr;
	input [`TEST_R_ADDR_WIDTH-1:0] rd_addr;
	input [`TEST_DATA_WIDTH-1:0]   alu_rr;
	input [`TEST_DATA_WIDTH-1:0]   alu_rd;
	input [`TEST_DATA_WIDTH-1:0]   alu_out;
	input [`TEST_D_ADDR_WIDTH-1:0] bus_address;
	input integer address;
	input integer register_rr;
	input integer register_rd;
	input integer value;
	begin
		case (pipeline_stage)
			`STAGE_IF:  TEST_MOV = 1'b1;
			`STAGE_ID:
				// because of how the STS address is defined, we need
				if(opcode_group[`GROUP_REGISTER]
				&& opcode_type == `TYPE_MOV
				&& rr_addr == register_rr)
					begin
						TEST_MOV = 1'b1;
						$display("MOV R%2d, R%2d - ID: OK", register_rd, register_rr);
					end
				else
					begin
						TEST_MOV = 1'bx;
						$display("MOV R%2d, R%2d - ID: FAILED", register_rd, register_rr);
					end
			`STAGE_EX:  TEST_MOV = 1'b1;
			`STAGE_MEM: TEST_MOV = 1'b1;
			`STAGE_WB:
				if(writeback_value == value
				&& signals[`CONTROL_REG_RD_WRITE]
				&& rd_addr == register_rd)
					begin
						TEST_MOV = 1'b1;
						$display("MOV R%2d, R%2d - WB: OK (R%2d = %3d) ", register_rd, register_rr, register_rd, writeback_value);
					end
				else
					begin
						TEST_MOV = 1'bx;
						$display("MOV R%2d, R%2d - WB: FAILED", register_rd, register_rr);
					end
		endcase
	end
endfunction
