// Last modified: 21.10.2018 
// Author: dosarudaniel@gmail.com
`include "defines.vh"

module checker(
        input   wire                                clk,
        input   wire                                reset,
        output  wire    [`TEST_I_ADDR_WIDTH - 1: 0] test,
        output  reg                                 result
    );

`ifdef DEBUG
    wire [`STAGE_COUNT - 1: 0]          debug_pipeline_stage;
    wire [`TEST_DATA_WIDTH - 1: 0]      debug_alu_rr;
    wire [`TEST_DATA_WIDTH - 1: 0]      debug_alu_rd;
    wire [`TEST_DATA_WIDTH - 1: 0]      debug_alu_out;
    wire [`TEST_I_ADDR_WIDTH - 1: 0]    debug_program_counter;
    wire [`FLAG_COUNT - 1: 0]           debug_flags_out;
`endif


    // Instantiate the Unit Under Test (UUT)
    cpu #(
        .INSTR_WIDTH(`TEST_INSTR_WIDTH),
        .DATA_WIDTH(`TEST_DATA_WIDTH),
        .I_ADDR_WIDTH(`TEST_I_ADDR_WIDTH),
        .RST_ACTIVE_LEVEL(1)
    ) uut (
        .clk(clk),
        .reset(reset)
`ifdef DEBUG
        ,
        .debug_pipeline_stage(debug_pipeline_stage),
        .debug_alu_rr(debug_alu_rr),
        .debug_alu_rd(debug_alu_rd),
        .debug_alu_out(debug_alu_out),
        .debug_program_counter(debug_program_counter),
        .debug_flags_out(debug_flags_out)
`endif
    );

    assign test = debug_program_counter;

    always @(*) begin
        /* Test instruction number, and OK if alu_rr is value we think it is
         * alu_rd is value we think it is alu_out is value we think it is flags
         * is value we think it is.
			* This instruction set manual was used for this checker:
			* http://ww1.microchip.com/downloads/en/devicedoc/atmel-0856-avr-instruction-set-manual.pdf
         */

        /* 0: nop
         * 1: neg   r1			# r1 <- 8'b0000_0010
         * 2: add   r1, r2    # r1 <- 8'b1111_1111
         * 3: sub   r1, r2		# r1 <- 8'b0000_0010
         * 4: and   r1, r2    # r1 <- 8'b0000_0000
         * 5: or    r1, r2    # r1 <- 8'b1111_1101
         */

        /* r1 is, at start, 254
         * r2 is, at start, 253
         */

        case(debug_program_counter)
            0: begin
                /* Test no register changed and no flag changed. */
                if (debug_flags_out == 8'b0000_0000 && debug_alu_rr === 8'bz &&
                        debug_alu_rd === 8'bz && debug_pipeline_stage == 3)
                    result <= 1'b1;
                else if (debug_pipeline_stage != 3)
                    result <= 1'b1;
                else
                    result <= 1'bx;
            end
				
            1: begin
					 /* neg 1111_1110 # -> out == 0000_0010 ; only carry flag is set*/
                if (debug_flags_out == 8'b0000_0001 && debug_alu_rd == 254 
							&& debug_alu_out == 2 && debug_pipeline_stage == 3)
                    result <= 1'b1;
                else if (debug_pipeline_stage != 3)
                    result <= 1'b1;
                else
                    result <= 1'bx;
            end

            2: begin
					 /* add 0000_0010, 1111_1110 # -> out == 1111_1111; N and S flags are set  */
                if (debug_flags_out == 8'b0001_0100 && debug_alu_rr == 253 &&
                        debug_alu_rd == 2 && debug_alu_out == 255 &&
                        debug_pipeline_stage == 3)
                    result <= 1'b1;
                else if (debug_pipeline_stage != 3)
                    result <= 1'b1;
                else
                    result <= 1'bx;
            end

            3: begin
					 /* sub 1111_1111, 1111_1101 # -> out == 0000_0010; no flag is set */
                if (debug_flags_out == 8'b0000_0000 && debug_alu_rr == 253 &&
                        debug_alu_rd == 255 && debug_alu_out == 2 &&
                        debug_pipeline_stage == 3)
                    result <= 1'b1;
                else if (debug_pipeline_stage != 3)
                    result <= 1'b1;
                else
                    result <= 1'bx;
            end

            4: begin
					 /* and 0000_0010, 1111_1101 # -> out == 0000_0000; only zero flag is set */
                if (debug_flags_out == 8'b0000_0010 && debug_alu_rr == 253 &&
                        debug_alu_rd == 2 && debug_alu_out == 0 &&
                        debug_pipeline_stage == 3)
                    result <= 1'b1;
                else if (debug_pipeline_stage != 3)
                    result <= 1'b1;
                else
                    result <= 1'bx;
            end

            5: begin
					 /* or 0000_0000, 1111_1101 # -> out == 1111_1101;  N and S flags are set */
                if (debug_flags_out == 8'b0001_0100 && debug_alu_rr == 253 &&
                        debug_alu_rd == 0 && debug_alu_out == 253 &&
                        debug_pipeline_stage == 3)
                    result <= 1'b1;
                else if (debug_pipeline_stage != 3)
                    result <= 1'b1;
                else
                    result <= 1'bx;
            end

            default:
                result <= 1'b1;
        endcase
    end
endmodule
