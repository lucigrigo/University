function TEST_RJMP;
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
			`STAGE_IF:  TEST_RJMP = 1'b1;
			`STAGE_ID:
				if(opcode_group[`GROUP_CONTROL_FLOW]
					&& opcode_type == `TYPE_RJMP)
					begin
						TEST_RJMP = 1'b1;
						$display("RJMP LABEL - ID: OK");
					end
				else
					begin
						TEST_RJMP = 1'bx;
						$display("RJMP LABEL - ID: FAILED => OPCODE_TYPE: (%b) vs %(%b). Check defines.vh.",
									`TYPE_RJMP, opcode_type);
					end
			`STAGE_EX:  TEST_RJMP = 1'b1;
			`STAGE_MEM: TEST_RJMP = 1'b1;
			`STAGE_WB:  TEST_RJMP = 1'b1;
		endcase
	end
endfunction