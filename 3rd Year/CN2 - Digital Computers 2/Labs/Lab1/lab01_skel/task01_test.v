`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   17:05:27 10/20/2020
// Design Name:   task01
// Module Name:   C:/Users/student/Downloads/lab01_skel/task01_test.v
// Project Name:  lab01_skel
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: task01
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module task01_test;

	// Inputs
	reg [3:0] address;

	// Outputs
	wire [7:0] data;

	// Instantiate the Unit Under Test (UUT)
	task01 uut (
		.address(address), 
		.data(data)
	);

	initial begin
		address = 0;

		#200 address = 4'd7;
        
		#200 address = 4'd13; 

		#200;

	end
      
endmodule

