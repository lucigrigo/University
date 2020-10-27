`timescale 1ns / 1ps
module task01a_test;

	// Inputs
	reg in0;
	reg in1;
	reg in2;
	reg in3;

	// Outputs
	wire out;

	// Instantiate the Unit Under Test (UUT)
	task01a uut (
		.out(out),
		.in0(in0),
		.in1(in1),
		.in2(in2),
		.in3(in3)
	);

	initial begin
		// Initialize Inputs
		in0 = 0;
		in1 = 0;
		in2 = 0;
		in3 = 0;

		// Wait 100 ns for global reset to finish
		#100;

		// Add stimulus here
		#10 in0 = 1;
		#10 in1 = 1;
		#10 in2 = 1;
		#10 in3 = 1;
		#10 in0 = 0;
		#10 in1 = 0;
		#10 in2 = 0;
		#10 in3 = 0;
	end

endmodule
