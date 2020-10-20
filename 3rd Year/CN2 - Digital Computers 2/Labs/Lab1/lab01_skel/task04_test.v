`timescale 1ns / 1ps

module task04_test;

	// Inputs
	reg clk;
	reg rst;
	reg [3:0] address;

	// Outputs
	wire [7:0] data;

	// Instantiate the Unit Under Test (UUT)
	task04 uut (
		.clk(clk), 
		.rst(rst), 
		.address(address), 
		.data(data)
	);
	
   initial forever
        #5 clk = ~clk;

	initial begin
		// Initialize Inputs
		clk = 0;
		rst = 1;
		address = 0;

		// Wait 100 ns for global reset to finish
		#10;
        
		// Add stimulus here
		rst = 0;
		//#10;
		
		for (address = 0; address < 16; address = address + 1) 
		begin
			 #15;
		end
	end
      
endmodule

