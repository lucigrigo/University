`timescale 1ns / 1ps
`include "defines.vh"
module unitTest(
        input wire clk,
        input wire reset,
		  output reg result,
			wire [`TEST_I_ADDR_WIDTH-1:0] debug_program_counter,
			wire [`STAGE_COUNT-1:0]  debug_pipeline_stage
    );
	 


	// Instantiate the Unit Under Test (UUT)
	cpu #(
		.INSTR_WIDTH     (`TEST_INSTR_WIDTH),
      .DATA_WIDTH      (`TEST_DATA_WIDTH),
      .I_ADDR_WIDTH    (`TEST_I_ADDR_WIDTH),
      .RST_ACTIVE_LEVEL(1)
		) uut (
		.clk(clk), 
		.reset(reset)
	);
	assign debug_program_counter = uut.program_counter;
    assign debug_pipeline_stage = uut.pipeline_stage;
	
    wire [`TEST_DATA_WIDTH-1:0] debug_alu_rr = uut.alu_rr;
    wire [`TEST_DATA_WIDTH-1:0] debug_alu_rd = uut.alu_rd;
    wire [`TEST_DATA_WIDTH-1:0] debug_alu_out = uut.alu_out;
    
    wire [`TEST_R_ADDR_WIDTH-1:0] debug_rr_addr = uut.rr_addr;
    wire [`TEST_R_ADDR_WIDTH-1:0] debug_rd_addr = uut.rd_addr;
    wire [`FLAG_COUNT-1:0] debug_flags_out = uut.alu_flags_out;
    wire [`TEST_D_ADDR_WIDTH-1:0] debug_bus_address = uut.bus_addr;
    wire [`TEST_DATA_WIDTH-1:0] debug_bus_data = uut.bus_data;
    
    wire [`TEST_D_ADDR_WIDTH-1:0] debug_register_Y = {uut.reg_file.memory[29], uut.reg_file.memory[28]};
    
    wire [11:0] debug_opcode_imd = uut.control.opcode_imd;
    wire [`OPCODE_COUNT-1:0] debug_opcode_type = uut.control.opcode_type;
    wire [`GROUP_COUNT-1:0] debug_opcode_group = uut.control.opcode_group;
    wire [2:0] debug_opcode_bit = uut.control.opcode_bit;
    wire [`TEST_DATA_WIDTH-1:0] debug_writeback_value = uut.control.writeback_value;
    wire [`SIGNAL_COUNT-1:0] debug_signals = uut.control.signals;
    
    reg [`TEST_I_ADDR_WIDTH-1:0] last_pc;
	
`include "unit_tests.vh"
	integer reg_16, reg_17, reg_22, reg_21, reg_20, reg_30;
	integer stack[`STACK_START:0];
	integer sp;
	
	integer address;
	integer rr_addr;
	integer rd_addr;
	integer value;
	
	
	
	initial begin
		$display("Init regs..");
		reg_16 = 32'dX;
		reg_17 = 32'dX;
		reg_22 = 32'dX;
		
		sp = `STACK_START;
		
		address = 32'dX;
		rr_addr = 32'dX;
		rd_addr = 32'dX;
		value = 32'dX;
	end
	
	always @(posedge clk) begin
		case(debug_program_counter)
			0: /*	 ldi 	r16, 5 		*/
			begin
				// cod executat de procesor
				address     = 32'dX;
				rr_addr 		= 32'dX;
				rd_addr 	   = 32'd16;
				value       = 5;
				result = TEST_LDI(debug_pipeline_stage, debug_opcode_group, debug_opcode_type, debug_opcode_imd, debug_writeback_value, 
										debug_signals, debug_rr_addr, debug_rd_addr, debug_alu_rr, debug_alu_rd, debug_alu_out, debug_bus_address,
										address, rr_addr, rd_addr, value);
				// cod pentru debug
				if (debug_pipeline_stage == `STAGE_WB) begin
					reg_16 	   = value;
				end
			end
			
			1: /*	 ldi 	r17, 15 		*/
			begin
				// cod executat de procesor
				address     = 32'dX;
				rr_addr 		= 32'dX;
				rd_addr 	   = 32'd17;
				value       = 15;
				result = TEST_LDI(debug_pipeline_stage, debug_opcode_group, debug_opcode_type, debug_opcode_imd, debug_writeback_value, 
										debug_signals, debug_rr_addr, debug_rd_addr, debug_alu_rr, debug_alu_rd, debug_alu_out, debug_bus_address,
										address, rr_addr, rd_addr, value);
										
				// cod pentru debug
				if (debug_pipeline_stage == `STAGE_WB) begin
					reg_17 	   = value;
				end
			end
			
			2: /*	 push r16		*/
			begin
				// cod executat de procesor
				address     = sp;
				rr_addr 		= 32'd16;
				rd_addr 	   = 32'dX;
				value       = reg_16;
				result = TEST_PUSH(debug_pipeline_stage, debug_opcode_group, debug_opcode_type, debug_opcode_imd, debug_writeback_value, 
										debug_signals, debug_rr_addr, debug_rd_addr, debug_alu_rr, debug_alu_rd, debug_alu_out, debug_bus_address,
										address, rr_addr, rd_addr, value);
										
				// cod pentru debug
				if (debug_pipeline_stage == `STAGE_WB) begin
					stack[sp]   = value;
					sp          = sp - 1;
				end
			end
			
			3: /*	 push r17 		*/
			begin
				// cod executat de procesor
				address     = sp;
				rr_addr 		= 32'd17;
				rd_addr 	   = 32'dX;
				value       = reg_17;
				result = TEST_PUSH(debug_pipeline_stage, debug_opcode_group, debug_opcode_type, debug_opcode_imd, debug_writeback_value, 
										debug_signals, debug_rr_addr, debug_rd_addr, debug_alu_rr, debug_alu_rd, debug_alu_out, debug_bus_address,
										address, rr_addr, rd_addr, value);
										
				// cod pentru debug
				if (debug_pipeline_stage == `STAGE_WB) begin
					stack[sp]   = value;
					sp          = sp - 1;
				end
			end
			
			4: /*	 mov 	r30, r16 */
			begin
				// cod executat de procesor
				address     = 32'dX;
				rr_addr 		= 32'd16;
				rd_addr 	   = 32'd30;
				value       = reg_16;
				result = TEST_MOV(debug_pipeline_stage, debug_opcode_group, debug_opcode_type, debug_opcode_imd, debug_writeback_value, 
										debug_signals, debug_rr_addr, debug_rd_addr, debug_alu_rr, debug_alu_rd, debug_alu_out, debug_bus_address,
										address, rr_addr, rd_addr, value);
			
				// cod pentru debug
				if (debug_pipeline_stage == `STAGE_WB) begin
					reg_30 	   = value;
				end
			end
			
			5: /*	 sub 	r30, r17  		*/
			begin
				// cod executat de procesor
				address     = 32'dX;
				rr_addr 		= 32'd17;
				rd_addr 	   = 32'd30;
				value       = reg_30 - reg_17;
				
				result = TEST_SUB(debug_pipeline_stage, debug_opcode_group, debug_opcode_type, debug_opcode_imd, debug_writeback_value, 
										debug_signals, debug_rr_addr, debug_rd_addr, debug_alu_rr, debug_alu_rd, debug_alu_out, debug_bus_address,
										address, rr_addr, rd_addr, value);
										
				// cod pentru debug
				if (debug_pipeline_stage == `STAGE_WB) begin
					reg_30 	   = value;
				end
			end
			
			6: /*	 breq 	gigel_is_done 		*/
			begin
				// cod pentru debug
				
				// cod executat de procesor
				address     = `FLAGS_Z;
				rr_addr 		= 32'dX;
				rd_addr 	   = 32'dX;
				value       = 32'dX;
				result = TEST_BRBS(debug_pipeline_stage, debug_opcode_group, debug_opcode_type, debug_opcode_imd, debug_opcode_bit, debug_writeback_value, 
										debug_signals, debug_rr_addr, debug_rd_addr, debug_alu_rr, debug_alu_rd, debug_alu_out, debug_bus_address,
										address, rr_addr, rd_addr, value);
			end
			
			7: /*	 brmi 	r17_is_greater 		*/
			begin
				// cod pentru debug
				
				// cod executat de procesor
				address     = `FLAGS_N;
				rr_addr 		= 32'dX;
				rd_addr 	   = 32'dX;
				value       = 32'dX;
				result = TEST_BRBS(debug_pipeline_stage, debug_opcode_group, debug_opcode_type, debug_opcode_imd, debug_opcode_bit, debug_writeback_value, 
										debug_signals, debug_rr_addr, debug_rd_addr, debug_alu_rr, debug_alu_rd, debug_alu_out, debug_bus_address,
										address, rr_addr, rd_addr, value);
			end
			
			8: /*	  sub 	r16, r17 		*/
			begin
				
				// cod executat de procesor
				address     = 32'dX;
				rr_addr 		= 32'd17;
				rd_addr 	   = 32'd16;
				value       = reg_16 - reg_17;
				result = TEST_SUB(debug_pipeline_stage, debug_opcode_group, debug_opcode_type, debug_opcode_imd, debug_writeback_value, 
										debug_signals, debug_rr_addr, debug_rd_addr, debug_alu_rr, debug_alu_rd, debug_alu_out, debug_bus_address,
										address, rr_addr, rd_addr, value);
				
				// cod pentru debug
				if (debug_pipeline_stage == `STAGE_WB) begin
					reg_16 	   = value;
				end
			end
			
			9: /*	 rjmp 	main_loop 		*/
			begin
				// cod executat de procesor
				address     = 32'dX;
				rr_addr 		= 32'dX;
				rd_addr 	   = 32'dX;
				value       = 32'dX;
				result = TEST_RJMP(debug_pipeline_stage, debug_opcode_group, debug_opcode_type, debug_opcode_imd, debug_writeback_value, 
										debug_signals, debug_rr_addr, debug_rd_addr, debug_alu_rr, debug_alu_rd, debug_alu_out, debug_bus_address,
										address, rr_addr, rd_addr, value);
										
				// cod pentru debug
			end
			
			10: /*	 sub 	r17, r16 		*/
			begin
				// cod executat de procesor
				address     = 32'dX;
				rr_addr 		= 32'd16;
				rd_addr 	   = 32'd17;
				value       = reg_17 - reg_16;
				
				result = TEST_SUB(debug_pipeline_stage, debug_opcode_group, debug_opcode_type, debug_opcode_imd, debug_writeback_value, 
										debug_signals, debug_rr_addr, debug_rd_addr, debug_alu_rr, debug_alu_rd, debug_alu_out, debug_bus_address,
										address, rr_addr, rd_addr, value);
										
				// cod pentru debug	
				if (debug_pipeline_stage == `STAGE_WB) begin
					reg_17 	   = value;
				end
			end
			
			11: /*	 rjmp 	main_loop 		*/
			begin		
				// cod executat de procesor
				address     = 32'dX;
				rr_addr 		= 32'dX;
				rd_addr 	   = 32'd17;
				value       = reg_17;
				result = TEST_RJMP(debug_pipeline_stage, debug_opcode_group, debug_opcode_type, debug_opcode_imd, debug_writeback_value, 
										debug_signals, debug_rr_addr, debug_rd_addr, debug_alu_rr, debug_alu_rd, debug_alu_out, debug_bus_address,
										address, rr_addr, rd_addr, value);
										
				// cod pentru debug
			end
			
			12: /*	 push 	r16 		*/
			begin
				// cod executat de procesor
				address     = sp;
				rr_addr 		= 32'd16;
				rd_addr 	   = 32'dX;
				value       = reg_16;
				result = TEST_PUSH(debug_pipeline_stage, debug_opcode_group, debug_opcode_type, debug_opcode_imd, debug_writeback_value, 
										debug_signals, debug_rr_addr, debug_rd_addr, debug_alu_rr, debug_alu_rd, debug_alu_out, debug_bus_address,
										address, rr_addr, rd_addr, value);
										
				// cod pentru debug
				if (debug_pipeline_stage == `STAGE_WB) begin
					stack[sp]   = value;
					sp          = sp - 1;
				end
			end
			
			13: /*	 pop 20 		*/
			begin
				// cod executat de procesor
				address     = sp + 1;
				rr_addr 		= 32'dX;
				rd_addr 	   = 32'd20;
				value       = stack[sp + 1];
				result = TEST_POP(debug_pipeline_stage, debug_opcode_group, debug_opcode_type, debug_opcode_imd, debug_writeback_value, 
										debug_signals, debug_rr_addr, debug_rd_addr, debug_alu_rr, debug_alu_rd, debug_alu_out, debug_bus_address,
										address, rr_addr, rd_addr, value);
										
				// cod pentru debug
				if (debug_pipeline_stage == `STAGE_WB) begin
					sp          = sp + 1;
					reg_20 		= value;
				end
			end

			14: /*	 pop 21 		*/
			begin
				// cod executat de procesor
				address     = sp + 1;
				rr_addr 		= 32'dX;
				rd_addr 	   = 32'd21;
				value       = stack[sp + 1];
				result = TEST_POP(debug_pipeline_stage, debug_opcode_group, debug_opcode_type, debug_opcode_imd, debug_writeback_value, 
										debug_signals, debug_rr_addr, debug_rd_addr, debug_alu_rr, debug_alu_rd, debug_alu_out, debug_bus_address,
										address, rr_addr, rd_addr, value);
										
				// cod pentru debug
				if (debug_pipeline_stage == `STAGE_WB) begin
					sp          = sp + 1;
					reg_21 		= value;
				end
			end
			
			15: /*	 pop 22 		*/
			begin
				// cod executat de procesor
				address     = sp + 1;
				rr_addr 		= 32'dX;
				rd_addr 	   = 32'd22;
				value       = stack[sp + 1];
				result = TEST_POP(debug_pipeline_stage, debug_opcode_group, debug_opcode_type, debug_opcode_imd, debug_writeback_value, 
										debug_signals, debug_rr_addr, debug_rd_addr, debug_alu_rr, debug_alu_rd, debug_alu_out, debug_bus_address,
										address, rr_addr, rd_addr, value);
										
				// cod pentru debug
				if (debug_pipeline_stage == `STAGE_WB) begin
					sp          = sp + 1;
					reg_22 		= value;
				end
			end
			default:
				result <= 1'bz;
		endcase
		last_pc = debug_program_counter;
	end
endmodule
