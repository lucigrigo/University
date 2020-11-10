function TEST_PUSH;
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
			`STAGE_IF:  TEST_PUSH = 1'bx;
			`STAGE_ID:
				if(opcode_group[`GROUP_STACK] &&
					opcode_type == `TYPE_PUSH &&
					rr_addr == register_rr)
					begin
						TEST_PUSH = 1'b1;
						$display("PUSH R%2d - ID: OK", register_rr);
					end
				else
					begin
						TEST_PUSH = 1'bx;
						$display("PUSH R%2d - ID: FAILED", register_rr);
					end
			`STAGE_EX:  TEST_PUSH = 1'bx;
			`STAGE_MEM: 
				if (bus_address == address[7:0] - 8'h40)
					begin
						TEST_PUSH = 1'b1;
						$display("PUSH R%2d - MEM: OK (bus_address = %2H)", register_rr, bus_address);
					end
				else
					begin
						TEST_PUSH = 1'bx;
						$display("PUSH R%2d - MEM: FAILED => bus_address: (%2H) vs (%2H)", register_rr, address[7:0] - 8'h40, bus_address);
					end
			`STAGE_WB:  TEST_PUSH = 1'bx;
		endcase
	end
endfunction
