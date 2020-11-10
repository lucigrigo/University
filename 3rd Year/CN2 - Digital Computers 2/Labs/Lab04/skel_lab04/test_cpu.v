`timescale 1ns / 1ps
`include "defines.vh"
module test_cpu;

	// Inputs
	reg clk;
	reg reset;
`ifdef DEBUG
	wire [`STAGE_COUNT-1:0]  debug_pipeline_stage;
	wire [`TEST_I_ADDR_WIDTH-1:0] debug_program_counter;
	//wire [`FLAG_COUNT-1:0] debug_flags_out;
	//wire [`TEST_DATA_WIDTH-1:0] debug_alu_rr;
	//wire [`TEST_DATA_WIDTH-1:0] debug_alu_rd;
	//wire [`TEST_DATA_WIDTH-1:0] debug_alu_out;
	wire [`TEST_D_ADDR_WIDTH-1:0] debug_bus_address;
	wire [`TEST_D_ADDR_WIDTH-1:0] debug_register_Y;
	wire [`TEST_DATA_WIDTH-1:0] debug_bus_data;
	wire [11:0] debug_opcode_imd;
	wire [`TEST_DATA_WIDTH-1:0] debug_writeback_value;
				wire [`SIGNAL_COUNT-1:0] debug_signals;

`endif

	// Instantiate the Unit Under Test (UUT)
	cpu uut (
		.clk(clk), 
		.reset(reset)
`ifdef DEBUG
		,
		.debug_pipeline_stage(debug_pipeline_stage),
		.debug_program_counter(debug_program_counter),
		.debug_bus_address(debug_bus_address),
		.debug_register_Y(debug_register_Y),
		.debug_bus_data(debug_bus_data),
		.debug_opcode_imd(debug_opcode_imd),
		.debug_writeback_value(debug_writeback_value),		
		.debug_signals(debug_signals)
		
`endif
	);
	
	always #10 clk = ~clk;

	initial begin
		// Initialize Inputs
		clk = 0;
		reset = 1;

		// Wait 100 ns for global reset to finish
		#10;
      reset = 0;
		// Add stimulus here

	end
      
endmodule

