function TEST_LD;
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
			`STAGE_IF:  TEST_LD = 1'b1;
			`STAGE_ID:
				if(opcode_group[`GROUP_LOAD]
				&& opcode_type == `TYPE_LD_Y)
					TEST_LD = 1'b1;
				else
					TEST_LD = 1'bx	;
			`STAGE_EX:
				if(alu_rr == ((address + 64) >>8)
				&& alu_rd == (address + 64))
					TEST_LD = 1'b1;
				else
					TEST_LD = 1'bx;
			`STAGE_MEM:
				if(bus_address == address)
					TEST_LD = 1'b1;
				else
					TEST_LD = 1'bx;
			`STAGE_WB:
				if(writeback_value == value
				&& signals[`CONTROL_REG_RD_WRITE]
				&& rd_addr == register_rd)
					TEST_LD = 1'b1;
				else
					TEST_LD = 1'bx;
		endcase
	end
endfunction
