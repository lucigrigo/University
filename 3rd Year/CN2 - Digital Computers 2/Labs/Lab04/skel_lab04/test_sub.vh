function TEST_SUB;
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
			`STAGE_IF:  TEST_SUB = 1'b1;
			`STAGE_ID:				
				if(opcode_group[`GROUP_ALU]
				&& opcode_type == `TYPE_SUB
				&& signals[`CONTROL_REG_RR_READ]
				&& signals[`CONTROL_REG_RD_READ]
				&& rr_addr == register_rr
				&& rd_addr == register_rd)
					begin
						TEST_SUB = 1'b1;
						$display("SUB R%2d, R%2d - ID: OK", register_rd, register_rr);
					end
				else
					begin
						TEST_SUB = 1'bx;
						$display("SUB R%2d, R%2d - ID: FAILED", register_rd, register_rr);
					end
			`STAGE_EX:
				// CIOC_CIOC
				if(alu_out == value[`TEST_DATA_WIDTH-1:0])
					begin
						TEST_SUB = 1'b1;
						$display("SUB R%2d, R%2d - EX: OK (alu_out = %3d)", register_rd, register_rr, value);
					end
				else
					begin
						TEST_SUB = 1'bx;
						$display("SUB R%2d, R%2d - EX: FAILED => (%b) vs (%b)", register_rd, register_rr, alu_out, value[`TEST_DATA_WIDTH-1:0]);
					end
			`STAGE_MEM: TEST_SUB = 1'b1;
			`STAGE_WB: 
				if(writeback_value == value[`TEST_DATA_WIDTH-1:0]
				&& signals[`CONTROL_REG_RD_WRITE]
				&& rd_addr == register_rd)
					begin
						TEST_SUB = 1'b1;
						$display("SUB R%2d, R%2d - WB: OK (R%2d = %3d)", register_rd, register_rr, register_rd, value);
					end
				else
					begin
						TEST_SUB = 1'bx;
						$display("SUB R%2d, R%2d - WB: FAILED => (%b) vs (%b)", register_rd, register_rr, writeback_value, value[`TEST_DATA_WIDTH-1:0]);
					end
		endcase
	end
endfunction
