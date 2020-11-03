`include "defines.vh"
`timescale 1ns / 1ps
module cpu_test;
	// Inputs
	reg clk;
	reg reset;

	// Instantiate the Unit Under Test (UUT)
	cpu #(
		.INSTR_WIDTH(16),
		.DATA_WIDTH(8),
		.ADDR_WIDTH(8),
		.RF_WIDTH(4)
	) uut (
		.clk(clk),
		.reset(reset)
	);

	initial begin
		// Initialize Inputs
		clk = 1;
		reset = 1;
		// Wait 10 ns for global reset to finish
		#10;
		reset = 0;
	end
	
	always clk = #5 ~clk;

endmodule
