`timescale 1ns / 1ps
`include "defines.vh"
module unitTest(
        input wire clk,
        input wire reset,
		  output reg result
`ifdef DEBUG
		  ,
		  wire [`TEST_I_ADDR_WIDTH-1:0] debug_program_counter
`endif
    );
	 
`ifdef DEBUG
	wire [`STAGE_COUNT-1:0]  debug_pipeline_stage;
	wire [`TEST_DATA_WIDTH-1:0] debug_alu_rr;
	wire [`TEST_DATA_WIDTH-1:0] debug_alu_rd;
	wire [`TEST_DATA_WIDTH-1:0] debug_alu_out;
	
   wire [`TEST_R_ADDR_WIDTH-1:0] debug_rr_addr;
   wire [`TEST_R_ADDR_WIDTH-1:0] debug_rd_addr;
	wire [`FLAG_COUNT-1:0] debug_flags_out;
	wire [`TEST_D_ADDR_WIDTH-1:0] debug_bus_address;
	wire [`TEST_D_ADDR_WIDTH-1:0] debug_register_Y;
	wire [`TEST_DATA_WIDTH-1:0] debug_bus_data;
	wire [11:0] debug_opcode_imd;
	
   wire [`OPCODE_COUNT-1:0] debug_opcode_type;
   wire [`GROUP_COUNT-1:0] debug_opcode_group;
	wire [`TEST_DATA_WIDTH-1:0] debug_writeback_value;
	wire [`SIGNAL_COUNT-1:0] debug_signals;
`endif


	// Instantiate the Unit Under Test (UUT)
	cpu #(
		.INSTR_WIDTH     (`TEST_INSTR_WIDTH),
      .DATA_WIDTH      (`TEST_DATA_WIDTH),
      .I_ADDR_WIDTH    (`TEST_I_ADDR_WIDTH),
      .RST_ACTIVE_LEVEL(1)
		) uut (
		.clk(clk), 
		.reset(reset)
`ifdef DEBUG
		,
		.debug_pipeline_stage(debug_pipeline_stage),
		.debug_program_counter(debug_program_counter),
		.debug_alu_rr(debug_alu_rr),
		.debug_alu_rd(debug_alu_rd),
		.debug_alu_out(debug_alu_out),
		.debug_flags_out(debug_flags_out),
		.debug_bus_address(debug_bus_address),
		.debug_register_Y(debug_register_Y),
		.debug_bus_data(debug_bus_data),
		.debug_opcode_type(debug_opcode_type),
		.debug_opcode_group(debug_opcode_group),
		.debug_opcode_imd(debug_opcode_imd),
		.debug_writeback_value(debug_writeback_value),
		.debug_signals(debug_signals),
		.debug_rd_addr(debug_rd_addr),
		.debug_rr_addr(debug_rr_addr)
`endif
	);
	always @(*) begin

		case(debug_program_counter)
			0: /*	 ldi 	r29, 10 		*/
				case (debug_pipeline_stage)
					`STAGE_IF:  result <= 1'b1;
					`STAGE_ID:  
						if(debug_opcode_group[`GROUP_REGISTER]
						&& debug_opcode_type == `TYPE_LDI 
						&& debug_opcode_imd == 10)
							result <= 1'b1;
						else
							result <= 1'bx;
					`STAGE_EX:  result <= 1'b1;
					`STAGE_MEM: result <= 1'b1;
					`STAGE_WB:	
						if(debug_writeback_value == 10 
						&& debug_signals[`CONTROL_REG_RD_WRITE] 
						&& debug_rd_addr == 29)
							result <= 1'b1;
						else
							result <= 1'bx;
				endcase
			1: /*	 sts 	r29, 10 		*/
				case (debug_pipeline_stage)
					`STAGE_IF:  result <= 1'b1;
					`STAGE_ID:
					   // because of how the STS address is defined, we need 
						if(debug_opcode_group[`GROUP_STORE_DIRECT] 
						&& debug_opcode_type == `TYPE_STS 
					   // because of how the STS address is defined, we need to force the first bit to 1
						&& debug_opcode_imd == (10 | 128)
						&& debug_rr_addr == 29)
							result <= 1'b1;
						else
							result <= 1'bx;
					`STAGE_EX:  result <= 1'b1;
					`STAGE_MEM: 
					   // we need to set the start of the of the ram too
						if(debug_bus_address == (64 | 10))
							result <= 1'b1;
						else
							result <= 1'bx;
					`STAGE_WB:	result <= 1'b1;
				endcase
			2: /*	 ldi 	r29, 0 		*/
				case (debug_pipeline_stage)
					`STAGE_IF:  result <= 1'b1;
					`STAGE_ID:  
						if(debug_opcode_group[`GROUP_REGISTER]
						&& debug_opcode_type == `TYPE_LDI 
						&& debug_opcode_imd == 0)
							result <= 1'b1;
						else
							result <= 1'bx;
					`STAGE_EX:  result <= 1'b1;
					`STAGE_MEM: result <= 1'b1;
					`STAGE_WB:	
						if(debug_writeback_value == 0 
						&& debug_signals[`CONTROL_REG_RD_WRITE] 
						&& debug_rd_addr == 29)
							result <= 1'b1;
						else
							result <= 1'bx;
				endcase
			3: /*	 ldi 	r28, 138		*/
				case (debug_pipeline_stage)
					`STAGE_IF:  result <= 1'b1;
					`STAGE_ID:  
						if(debug_opcode_group[`GROUP_REGISTER]
						&& debug_opcode_type == `TYPE_LDI 
						&& debug_opcode_imd == 138)
							result <= 1'b1;
						else
							result <= 1'bx;
					`STAGE_EX:  result <= 1'b1;
					`STAGE_MEM: result <= 1'b1;
					`STAGE_WB:	
						if(debug_writeback_value == 138
						&& debug_signals[`CONTROL_REG_RD_WRITE] 
						&& debug_rd_addr == 28)
							result <= 1'b1;
						else
							result <= 1'bx;
				endcase
			4: /*	 ld 	r27, y		*/
				case (debug_pipeline_stage)
					`STAGE_IF:  result <= 1'b1;
					`STAGE_ID:  
						if(debug_opcode_group[`GROUP_LOAD]
						&& debug_opcode_type == `TYPE_LD_Y)
							result <= 1'b1;
						else
							result <= 1'bx;
					`STAGE_EX:  
						if(debug_alu_rr == 0
						&& debug_alu_rd == 138)
							result <= 1'b1;
						else
							result <= 1'bx;
					`STAGE_MEM:
						if(debug_bus_address == (74))
							result <= 1'b1;
						else
							result <= 1'bx;
					`STAGE_WB:	
						if(debug_writeback_value == 10
						&& debug_signals[`CONTROL_REG_RD_WRITE] 
						&& debug_rd_addr == 27)
							result <= 1'b1;
						else
							result <= 1'bx;
				endcase
			5: /*	 lds 	r28, 10 		*/
				case (debug_pipeline_stage)
					`STAGE_IF:  result <= 1'b1;
					`STAGE_ID:
					   // because of how the STS address is defined, we need 
						if(debug_opcode_group[`GROUP_LOAD] 
						&& debug_opcode_type == `TYPE_LDS 
					   // because of how the LDS address is defined, we need to force the first bit to 1
						&& debug_opcode_imd == (10 | 128))
							result <= 1'b1;
						else
							result <= 1'bx;
					`STAGE_EX:  result <= 1'b1;
					`STAGE_MEM: 
					   // we need to set the start of the of the ram too
						if(debug_bus_address == (64 | 10))
							result <= 1'b1;
						else
							result <= 1'bx;
					`STAGE_WB:	
						if(debug_writeback_value == 10
						&& debug_signals[`CONTROL_REG_RD_WRITE] 
						&& debug_rd_addr == 28)
							result <= 1'b1;
						else 
							result <= 1'bx;
				endcase
			6: /*	 mov 	r27, r28 		*/
				case (debug_pipeline_stage)
					`STAGE_IF:  result <= 1'b1;
					`STAGE_ID:
					   // because of how the STS address is defined, we need 
						if(debug_opcode_group[`GROUP_REGISTER] 
						&& debug_opcode_type == `TYPE_MOV 
						&& debug_rr_addr == 28)
							result <= 1'b1;
						else
							result <= 1'bx;
					`STAGE_EX:  result <= 1'b1;
					`STAGE_MEM: result <= 1'b1;
					`STAGE_WB:	
						if(debug_writeback_value == 10
						&& debug_signals[`CONTROL_REG_RD_WRITE] 
						&& debug_rd_addr == 27)
							result <= 1'b1;
						else 
							result <= 1'bx;
				endcase
				
			default:
				result <= 1'bz;
		endcase
	end
endmodule
