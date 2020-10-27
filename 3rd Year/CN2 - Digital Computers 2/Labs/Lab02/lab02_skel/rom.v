module rom #(
        parameter   DATA_WIDTH = 16,
        parameter   ADDR_WIDTH = 8          // 2 * 1024 bytes of ROM
    )(
        input  wire                  clk,
        input  wire [ADDR_WIDTH-1:0] addr,  // here comes the program counter
        output  reg [DATA_WIDTH-1:0] data   // here goes the instruction
    );

    reg [DATA_WIDTH-1:0] value;

    always @* begin
        case (addr)
				/*	 nop 	 		*/
				0:		value = 16'b0000000000000000;
				/*	 neg 	r1 		*/
				1:		value = 16'b1001010000010001;
				/*	 add 	r1, r2 		*/
				2:		value = 16'b0000110000010010;
				/*	 sub 	r1, r2 		*/
				3:		value = 16'b0001100000010010;
				/*	 and 	r1, r2 		*/
				4:		value = 16'b0010000000010010;
				/*	 or 	r1, r2 		*/
				5:		value = 16'b0010100000010010;
				default:		value = 16'b0000000000000000;
        endcase
    end

    always @(negedge clk) begin
        data <= value;
    end
endmodule
