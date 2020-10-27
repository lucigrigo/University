// Last modified: 21.10.2018 
// Author: dosarudaniel@gmail.com
`include "defines.vh"
module alu #(
        parameter DATA_WIDTH = 8
    )(
        input  wire [`OPSEL_COUNT-1:0] opsel,
        input  wire                    enable,
        input  wire   [DATA_WIDTH-1:0] rd,
        input  wire   [DATA_WIDTH-1:0] rr,
        output reg    [DATA_WIDTH-1:0] out,
        input  wire   [DATA_WIDTH-1:0] flags_in,
        output reg    [DATA_WIDTH-1:0] flags_out
    );

    /* flags_out a fost transformat in reg, pentru a putea
     * fi atribuit in interiorul unui bloc always, insa va fi
     * sintetizat tot combinational (UAL-ul nici macar nu are clk
     * drept input) */

    /* TODO: De codificat cateva operatii
     * in defines.vh si de implementat aici folosind acest instruction set manual:
	  * http://ww1.microchip.com/downloads/en/devicedoc/atmel-0856-avr-instruction-set-manual.pdf [1]
     */
    always @* begin
        case (opsel)
            /* TODO: Adaugati implementarea operatiilor aici. */
				
				`OPSEL_NOP: begin
					 flags_out[`FLAGS_I] = flags_in[`FLAGS_I];
					 flags_out[`FLAGS_T] = flags_in[`FLAGS_T];
					 flags_out[`FLAGS_H] = flags_in[`FLAGS_H];
					 flags_out[`FLAGS_V] = flags_in[`FLAGS_V];
					 flags_out[`FLAGS_N] = flags_in[`FLAGS_N];
					 flags_out[`FLAGS_S] = flags_in[`FLAGS_S];
					 flags_out[`FLAGS_Z] = flags_in[`FLAGS_Z];
					 flags_out[`FLAGS_C] = flags_in[`FLAGS_C];
				end
				
				`OPSEL_NEG: begin
					 out = -rd;
					 
					 flags_out[`FLAGS_I] = flags_in[`FLAGS_I];
					 flags_out[`FLAGS_T] = flags_in[`FLAGS_T];
					 flags_out[`FLAGS_H] = (out[3] | ~rd[3]);
					 flags_out[`FLAGS_V] = (out[7] & ~out[6] & ~out[5] & ~out[4] & ~out[3] & ~out[2] & ~out[1] & ~out[0]);
					 flags_out[`FLAGS_N] = out[7];
					 flags_out[`FLAGS_S] = flags_out[`FLAGS_N] ^ flags_out[`FLAGS_V];
					 flags_out[`FLAGS_Z] = (~out[7] & ~out[6] & ~out[5] & ~out[4] & ~out[3] & ~out[2] & ~out[1] & ~out[0]);
					 flags_out[`FLAGS_C] = (out[7] | out[6] | out[5] | out[4] | out[3] | out[2] | out[1] | out[0]);
				end
				
				`OPSEL_ADD: begin
					 out = rd + rr;
					 
					 flags_out[`FLAGS_I] = flags_in[`FLAGS_I];
					 flags_out[`FLAGS_T] = flags_in[`FLAGS_T];
					 flags_out[`FLAGS_H] = (rd[3] & rr[3]) | (rr[3] & ~out[3]) | (~out[3] & rd[3]);
					 flags_out[`FLAGS_V] = (rd[7] & rr[7] & ~out[7]) | (~rd[7] & ~rr[7] & out[7]);
					 flags_out[`FLAGS_N] = out[7];
					 flags_out[`FLAGS_S] = flags_out[`FLAGS_N] ^ flags_out[`FLAGS_V];
					 flags_out[`FLAGS_Z] = (~out[7] & ~out[6] & ~out[5] & ~out[4] & ~out[3] & ~out[2] & ~out[1] & ~out[0]);
					 flags_out[`FLAGS_C] = (rd[7] & rr[7]) | (rr[7] & ~out[7]) | (~out[7] & rd[7]);
				end
				
				`OPSEL_ADC: begin
					 out = rd + rr + flags_in[`FLAGS_C];
					 
					 flags_out[`FLAGS_I] = flags_in[`FLAGS_I];
					 flags_out[`FLAGS_T] = flags_in[`FLAGS_T];
					 flags_out[`FLAGS_H] = (rd[3] & rr[3]) | (rr[3] & ~out[3]) | (~out[3] & rd[3]);
					 flags_out[`FLAGS_V] = (rd[7] & rr[7] & ~out[7]) | (~rd[7] & ~rr[7] & out[7]);
					 flags_out[`FLAGS_N] = out[7];
					 flags_out[`FLAGS_S] = flags_out[`FLAGS_N] ^ flags_out[`FLAGS_V];
					 flags_out[`FLAGS_Z] = (~out[7] & ~out[6] & ~out[5] & ~out[4] & ~out[3] & ~out[2] & ~out[1] & ~out[0]);
					 flags_out[`FLAGS_C] = (rd[7] & rr[7]) | (rr[7] & ~out[7]) | (~out[7] & rd[7]);
				end
				
				`OPSEL_SUB: begin
					 out = rd - rr;
					 
					 flags_out[`FLAGS_I] = flags_in[`FLAGS_I];
					 flags_out[`FLAGS_T] = flags_in[`FLAGS_T];
					 flags_out[`FLAGS_H] = (~rd[3] & rr[3]) | (rr[3] & out[3]) | (out[3] & ~rd[3]);
					 flags_out[`FLAGS_V] = (rd[7] & ~rr[7] & ~out[7]) | (~rd[7] & rr[7] & out[7]);
					 flags_out[`FLAGS_N] = out[7];
					 flags_out[`FLAGS_S] = flags_out[`FLAGS_N] ^ flags_out[`FLAGS_V];
					 flags_out[`FLAGS_Z] = (~out[7] & ~out[6] & ~out[5] & ~out[4] & ~out[3] & ~out[2] & ~out[1] & ~out[0]);
					 flags_out[`FLAGS_C] = (~rd[7] & rr[7]) | (rr[7] & out[7]) | (out[7] & ~rd[7]);
				end
				
				`OPSEL_AND: begin
					 out = rd & rr;
					 
					 flags_out[`FLAGS_I] = flags_in[`FLAGS_I];
					 flags_out[`FLAGS_T] = flags_in[`FLAGS_T];
					 flags_out[`FLAGS_H] = flags_in[`FLAGS_H];
					 flags_out[`FLAGS_V] = 0;
					 flags_out[`FLAGS_N] = out[7];
					 flags_out[`FLAGS_S] = flags_out[`FLAGS_N] ^ flags_out[`FLAGS_V];
					 flags_out[`FLAGS_Z] = (~out[7] & ~out[6] & ~out[5] & ~out[4] & ~out[3] & ~out[2] & ~out[1] & ~out[0]);
					 flags_out[`FLAGS_C] = flags_in[`FLAGS_C];
				end
				
				`OPSEL_OR: begin
					 out = rd | rr;
					 
					 flags_out[`FLAGS_I] = flags_in[`FLAGS_I];
					 flags_out[`FLAGS_T] = flags_in[`FLAGS_T];
					 flags_out[`FLAGS_H] = flags_in[`FLAGS_H];
					 flags_out[`FLAGS_V] = 0;
					 flags_out[`FLAGS_N] = out[7];
					 flags_out[`FLAGS_S] = flags_out[`FLAGS_N] ^ flags_out[`FLAGS_V];
					 flags_out[`FLAGS_Z] = (~out[7] & ~out[6] & ~out[5] & ~out[4] & ~out[3] & ~out[2] & ~out[1] & ~out[0]);
					 flags_out[`FLAGS_C] = flags_in[`FLAGS_C];
				end
				
				default: begin
                out = 8'bx;
                flags_out = flags_in;
            end
        endcase
    end
endmodule
