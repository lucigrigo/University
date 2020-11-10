function TEST_STS;
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
			`STAGE_IF:  TEST_STS = 1'b1;
			`STAGE_ID:
				// because of how the STS address is defined, we need
				if(opcode_group[`GROUP_STORE_DIRECT]
				&& opcode_type == `TYPE_STS
				// because of how the STS address is defined, we need to force the first bit to 1
				&& opcode_imd == (address | (!(address & 128) << 7 ))
				&& rr_addr == register_rr)
					TEST_STS = 1'b1;
				else
					TEST_STS = 1'bx;
			`STAGE_EX:  
				if(alu_rr == value)
					TEST_STS = 1'b1;
				else
					TEST_STS = 1'bx;
			`STAGE_MEM:
				// we need to set the start of the of the ram too
				if(bus_address == (64 + address))
					TEST_STS = 1'b1;
				else
					TEST_STS = 1'bx;
			`STAGE_WB:	TEST_STS = 1'b1;
		endcase
	end
endfunction
