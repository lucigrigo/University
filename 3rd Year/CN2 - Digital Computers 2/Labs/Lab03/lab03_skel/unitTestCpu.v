`timescale 1ns / 1ps
`include "defines.vh"
module unitTestCpu;

	// Inputs
	reg clk;
	reg reset;

	// Outputs
	wire result;
   wire [`TEST_I_ADDR_WIDTH-1:0] pc;

	// Instantiate the Unit Under Test (UUT)
	unitTest uut (
		.clk(clk), 
		.reset(reset), 
		.result(result)
`ifdef DEBUG
		,
		.debug_program_counter(pc)
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

