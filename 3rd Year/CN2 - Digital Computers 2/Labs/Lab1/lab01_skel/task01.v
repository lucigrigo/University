module task01 (
        input  wire [3:0] address,
        output reg  [7:0] data
    );
 
	always @* begin
		case(address)
            4'd0:    data = 8'd65;
            4'd1:    data = 8'd78;
            4'd2:    data = 8'd65;
            4'd3:    data = 8'd32;
            4'd4:    data = 8'd65;
            4'd5:    data = 8'd82;
            4'd6:    data = 8'd69;
            4'd7:    data = 8'd32;
            4'd8:    data = 8'd52;
            4'd9:    data = 8'd32;
            4'd10:   data = 8'd77;
				4'd11:    data = 8'd69;
				4'd12:    data = 8'd82;
				4'd13:    data = 8'd69;
				4'd14:    data = 8'd46;
				4'd15:    data = 8'd0;
				default:  data = 8'd0;
        endcase
	end
endmodule