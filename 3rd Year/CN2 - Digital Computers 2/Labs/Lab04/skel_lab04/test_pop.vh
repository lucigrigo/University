function TEST_POP;
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
			`STAGE_IF:  TEST_POP = 1'bx;
			`STAGE_ID:  TEST_POP = 1'bx;
			`STAGE_EX:
				// CIOC_CIOC
				if(opcode_group[`GROUP_STACK]
				&& opcode_type == `TYPE_POP)
				begin
						TEST_POP = 1'b1;
						$display("POP R%2d - EX: OK", register_rd);
					end
				else
					begin
						TEST_POP = 1'bx;
						$display("POP R%2d - EX: FAILED", register_rd);
					end
			`STAGE_MEM:
				if (opcode_group[`GROUP_STACK] &&
				    opcode_type == `TYPE_POP &&
					 bus_address == address[7:0] - 8'h40)
				begin
						TEST_POP = 1'b1;
						$display("POP R%2d - MEM: OK (bus_addr = %2H)", register_rd,  bus_address);
					end
				else
					begin
						TEST_POP = 1'bx;
						$display("POP R%2d - MEM: FAILED => bus_addr: (%2H) vs (%2H)", register_rd, address[7:0] - 8'h40, bus_address);
					end
			`STAGE_WB:
				if (opcode_group[`GROUP_STACK] &&
				    opcode_type == `TYPE_POP &&
					 writeback_value == value)
				begin
						TEST_POP = 1'b1;
						$display("POP R%2d - WB: OK (R%2d = %3d)", register_rd, register_rd, value);
					end
				else
					begin
						TEST_POP = 1'bx;
						$display("POP R%2d - WB: FAILED => R%2d:(%3d) vs (%3d)", register_rd, register_rd, writeback_value, value);
					end
		endcase
	end
endfunction
