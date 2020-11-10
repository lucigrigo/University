// must declare BTN and SW as "inout" because, when assigning
// them to porta/portb, XST is complaining that those are
// inout as well, and nobody guarantees it that someone won't
// be driving an output into a wire declared as input.
module nexys_top (
		// Clock sources
		input  wire       PRI_OSC, // Primary oscillator, Linear Tech. LTC6905 Oscillator
		input  wire       SEC_OSC, // Secondary oscillator, connected on J11 socket
		// User I/O
		inout  wire [3:0] BTN,     // non-debounced push-buttons, active high
		output wire [7:0] LED,     // green LEDs, active high
		inout  wire [7:0] SW,      // slide switches
		// 7-segment display
		output wire [3:0] AN,      // common anodes for 7 segment display, active low
		output wire       CA,      // common cathode A for 7 segment display, active low
		output wire       CB,      // common cathode B for 7 segment display, active low
		output wire       CC,      // common cathode C for 7 segment display, active low
		output wire       CD,      // common cathode D for 7 segment display, active low
		output wire       CE,      // common cathode E for 7 segment display, active low
		output wire       CF,      // common cathode F for 7 segment display, active low
		output wire       CG,      // common cathode G for 7 segment display, active low
		output wire       DP,      // common decimal point for 7 segment display, active low
		// Pin headers
		output wire [3:0] JA,      // 6-pin header A, pins 1-4 (5 is GND, 6 is VCC)
		output wire [3:0] JB,      // 6-pin header B, pins 1-4 (5 is GND, 6 is VCC)
		output wire [3:0] JC,      // 6-pin header C, pins 1-4 (5 is GND, 6 is VCC)
		output wire [3:0] JD       // 6-pin header D, pins 1-4 (5 is GND, 6 is VCC)
		// Micron M45W8MW16 Cellular RAM (STUB)
	);

	assign LED[6:0] = 7'b0;

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
		.clk             (PRI_OSC),
		.reset           (SW[7])
	);
endmodule
