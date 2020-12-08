module nexys_top (
        input  wire       PRI_OSC,
		  input	wire		  RESET,
        inout  wire [7:0] SWITCH,
        inout  wire [7:0] LED
    );

    cpu #(
        .INSTR_WIDTH     (16),
        .DATA_WIDTH      (8),
        .I_ADDR_WIDTH    (10),
        .ADDR_WIDTH      (16),
        .D_ADDR_WIDTH    (7),
        .IO_ADDR_WIDTH   (6),
        .R_ADDR_WIDTH    (5),
        .RST_ACTIVE_LEVEL(1)
    ) avr (
        .clk     			(PRI_OSC),
        .reset      		(RESET),
		  .pa					(LED),
		  .pb					(SWITCH)
    );
endmodule