module task03(
	output reg out,
	input [7:0] in,
	input clk,
	input reset
);

	localparam STATE_NONE = 3'b000;
	localparam STATE_B = 3'b001; // 'B'
	localparam STATE_BA = 3'b010; // 'BA'
	localparam STATE_BAD = 3'b100; // 'BAD'

	reg [2:0] state;

	always @(posedge clk) begin
		if (reset) begin
			state <= STATE_NONE;
		end else begin
			case (state)
			STATE_NONE :
			begin
				out = 0;
				if(in == "B")
					state <= STATE_B;
			end
			STATE_B:
			begin
				if(in == "A")
					state <= STATE_BA;
				else 
					state <= STATE_NONE;
			end
			STATE_BA:
			begin
				if(in == "D")
					state <= STATE_BAD;
				else
					state <= STATE_NONE;
			end
			STATE_BAD:
			begin
				if(in == "C") begin
					out = 1;
				end
				state <= STATE_NONE;
			end
		end
	end

endmodule
