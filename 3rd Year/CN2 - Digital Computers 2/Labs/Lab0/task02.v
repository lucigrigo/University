module task02(
	output reg serial_out,
	input serial_in,
	input clk,
	input reset
);
	reg [7:0]arr;
	
	always @(posedge clk) begin
		if(reset) begin
			arr <= 8'b00000000;
		end 

		serial_out = arr[7];

		arr <= arr << 1;
		arr[0] <= serial_in;
	end

endmodule
