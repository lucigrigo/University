`timescale 1ns / 1ps
module task02_test;

	// Inputs
	reg serial_in;
	reg clk;
	reg reset;

	// Outputs
	wire serial_out;

	// Instantiate the Unit Under Test (UUT)
	task02 uut (
		.serial_out(serial_out),
		.serial_in(serial_in),
		.clk(clk),
		.reset(reset)
	);

	always begin
		#5 clk = ~clk;
	end

	initial begin
		// Initialize Inputs
		serial_in = 0;
		clk = 0;
		reset = 1;

		// Wait 100 ns for global reset to finish
		#100;

		// Add stimulus here
		#5; // Sync with clk

		#10 reset = 0;

		#10 serial_in = 1;
		#10 serial_in = 0;
		#10 serial_in = 1;
		#10 serial_in = 0;
		#10 serial_in = 1;
		#10 serial_in = 0;
		#10 serial_in = 1;
		#10 serial_in = 1;
		#10 serial_in = 0;
	end

endmodule
