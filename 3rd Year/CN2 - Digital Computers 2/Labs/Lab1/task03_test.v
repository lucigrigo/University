`timescale 1ns / 1ps
module task03_test;

	// Inputs
	reg [7:0] in;
	reg clk;
	reg reset;

	// Outputs
	wire out;

	// Instantiate the Unit Under Test (UUT)
	task03 uut (
		.out(out),
		.in(in),
		.clk(clk),
		.reset(reset)
	);

	always begin
		#5 clk = ~clk;
	end

	initial begin
		// Initialize Inputs
		in = 0;
		clk = 0;
		reset = 1;

		// Wait 100 ns for global reset to finish
		#100;

		// Add stimulus here
		#5; // Sync with clk

		#10 reset = 0;

		#10 in = "B";
		#10 in = "B";
		#10 in = "E";
		#10 in = "A";
		#10 in = "B";
		#10 in = "A";
		#10 in = "D";
		#10 in = "C";
		#10 in = "X";
		#10 in = "a";
		#10 in = "b";
		#10 in = "e";
		#10 in = "e";
	end

endmodule
