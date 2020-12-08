`timescale 1ns / 1ps
`include "defines.vh"

module unitTest(
        input wire clk,
        input wire reset,
		  output reg result,
			wire [`TEST_I_ADDR_WIDTH-1:0] debug_program_counter,
			wire [`STAGE_COUNT-1:0]  debug_pipeline_stage
    );

	`include "unit_tests.vh" 			// include test function in unitTest scope

	wire   [7:0] pa;
   wire   [7:0] pb;

   /* TODO 5: Modificati valoare pinilor portului B si relansati simularea
    * pentru a vedea daca secventa afisata pe portul A se modifica.
    */
	assign pb = 8'b10100101;

	// Instantiate the Unit Under Test (UUT) - cpu
	cpu #(
		.INSTR_WIDTH     (`TEST_INSTR_WIDTH),
      .DATA_WIDTH      (`TEST_DATA_WIDTH),
      .I_ADDR_WIDTH    (`TEST_I_ADDR_WIDTH),
      .RST_ACTIVE_LEVEL(1)
		) uut (
		.clk(clk),
		.reset(reset),
		.pa(pa),
		.pb(pb)
	);


	assign debug_program_counter = uut.program_counter;
	assign debug_pipeline_stage = uut.pipeline_stage;

	wire [`TEST_DATA_WIDTH-1:0] debug_alu_rr = uut.alu_rr;
	wire [`TEST_DATA_WIDTH-1:0] debug_alu_rd = uut.alu_rd;
	wire [`TEST_DATA_WIDTH-1:0] debug_alu_out = uut.alu_out;

	wire [`TEST_R_ADDR_WIDTH-1:0] debug_rr_addr = uut.rr_addr;
	wire [`TEST_R_ADDR_WIDTH-1:0] debug_rd_addr = uut.rd_addr;
	wire [`FLAG_COUNT-1:0] debug_flags_out = uut.alu_flags_out;
	wire [`TEST_D_ADDR_WIDTH-1:0] debug_bus_address = uut.bus_addr;
	wire [`TEST_DATA_WIDTH-1:0] debug_bus_data = uut.bus_data;

	wire [`TEST_D_ADDR_WIDTH-1:0] debug_register_Y = {uut.reg_file.memory[29], uut.reg_file.memory[28]};

	wire [11:0] debug_opcode_imd = uut.control.opcode_imd;
	wire [`OPCODE_COUNT-1:0] debug_opcode_type = uut.control.opcode_type;
	wire [`GROUP_COUNT-1:0] debug_opcode_group = uut.control.opcode_group;
	wire [2:0] debug_opcode_bit = uut.control.opcode_bit;
	wire [`TEST_DATA_WIDTH-1:0] debug_writeback_value = uut.control.writeback_value;
	wire [`SIGNAL_COUNT-1:0] debug_signals = uut.control.signals;

   reg [`TEST_I_ADDR_WIDTH-1:0] last_pc;

	integer reg_19, reg_20, reg_28, reg_17, reg_16;

	integer address;
	integer io_addr;
	integer rr_addr;
	integer rd_addr;
	integer value;
	integer next_pc;
	integer bit_val;

	initial begin
		$display("Init regs..");
		reg_19 = 8'dX;
		reg_20 = 8'dX;
		reg_28 = 8'dX;
		reg_17 = 8'dX;
		reg_16 = 8'dX;

		address = 16'dX;
		io_addr = 5'dX;
		rr_addr = 5'dX;
		rd_addr = 5'dX;
		bit_val = 3'bX;
		value = 8'dX;
		result = 0;
	end

	always @(posedge clk) begin
		case(debug_program_counter)
			0: /*	 ldi R16, 1		*/
			begin
				// cod executat de procesor
				rd_addr 	   = 5'd16;
				value       = 1;
				result = TEST_LDI(rd_addr, value);
				// cod pentru debug
				if (debug_pipeline_stage == `STAGE_WB) begin
					reg_16 	   = value;
				end
			end

			1: /* out 0x01, R16 */
			begin
				// cod executat de procesor
				io_addr     = 5'd1;
				rr_addr     = 5'd16;
				result = TEST_OUT(io_addr, rr_addr, reg_28);

			end

			2: /*	 sbi 0x01, 1		*/
			begin
				// cod executat de procesor
				bit_val 	   = 3'b1;
				io_addr     = 5'd1;

				result = TEST_SBI(io_addr, bit_val);

				// cod pentru debug
				//if (debug_pipeline_stage == `STAGE_WB) begin
				//	reg_17 = value;
				//end
			end

			3:	/* cbi 0x01, 0 */
			begin
				bit_val 	   = 3'b0;
				io_addr     = 5'd1;

				result = TEST_CBI(io_addr, bit_val);

			end

			4:	/* in r17, 0x01 */
			begin
				rd_addr 	   = 17;
				io_addr     = 5'd1;
				result = TEST_IN(io_addr, rd_addr);
			end

			default:
				result <= 1'bz;
		endcase
		last_pc = debug_program_counter;
	end
endmodule
