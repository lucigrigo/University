`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   17:15:03 10/20/2020
// Design Name:   task02
// Module Name:   C:/Users/student/Downloads/lab01_skel/task02_test.v
// Project Name:  lab01_skel
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: task02
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module task02_test;

	// Inputs
	reg clk;
	reg oe;
	reg cs;
	reg we;
	reg [6:0] address;
	reg [7:0] data_in;

	// Outputs
	wire [7:0] data_out;

	// Instantiate the Unit Under Test (UUT)
	task02 uut (
		.clk(clk), 
		.oe(oe), 
		.cs(cs), 
		.we(we), 
		.address(address), 
		.data_in(data_in), 
		.data_out(data_out)
	);


	initial begin
		// Initialize Inputs
		clk = 0;
		oe = 0;
		cs = 1;
		we = 0;
		address = 0;
		data_in = 0;
				
		#200  clk = 1; we = 1;
				data_in = 4'd55;
				address = 4'd12;
        
		#200  clk = 0; we = 0; oe = 1;
				address = 4'd12;
		
		#200  clk = 1; we = 1;
				data_in = 4'd44;
				address = 4'd8;
		
		#200  clk = 0; we = 0; oe = 1;
				address = 4'd8;
				
		#200;

	end
      
endmodule

