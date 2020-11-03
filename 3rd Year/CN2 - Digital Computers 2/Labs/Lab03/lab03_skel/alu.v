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
     * in defines.vh si de implementat aici 
     */
    always @* begin
        case (opsel)
        
            `OPSEL_ADD,
				`OPSEL_ADC:
            begin
               {flags_out[`FLAGS_C], out} = rd + rr + ((opsel == `OPSEL_ADC) && flags_in[`FLAGS_C]);
               flags_out[`FLAGS_V] = (rd[7] == 1 && rr[7] == 1 && out[7] == 0) ||
                                      (rd[7] == 0 && rr[7] == 0 && out[7] == 1);
                flags_out[`FLAGS_Z] = (out == 0);
                flags_out[`FLAGS_N] = out[7];
                flags_out[`FLAGS_S] = flags_out[`FLAGS_N] ^ flags_out[`FLAGS_V];
                flags_out[`FLAGS_H] = (rd[3] == 1 && rr[3] == 1 && out[3] == 0) ||
                                      (rd[3] == 0 && rr[3] == 0 && out[3] == 1);
                flags_out[`FLAGS_T] = flags_in[`FLAGS_T];
                flags_out[`FLAGS_I] = flags_in[`FLAGS_I];
            end

            `OPSEL_SUB:
            begin
               {flags_out[`FLAGS_C], out} = rd - rr - flags_in[`FLAGS_C];
                flags_out[`FLAGS_V] = (rd[7] == 1 && rr[7] == 1 && out[7] == 0) ||
                                      (rd[7] == 0 && rr[7] == 0 && out[7] == 1);
                flags_out[`FLAGS_Z] = (out == 0);
                flags_out[`FLAGS_N] = out[7];
                flags_out[`FLAGS_S] = flags_out[`FLAGS_N] ^ flags_out[`FLAGS_V];
                flags_out[`FLAGS_H] = (rd[3] == 1 && rr[3] == 1 && out[3] == 0) ||
                                      (rd[3] == 0 && rr[3] == 0 && out[3] == 1);
                flags_out[`FLAGS_T] = flags_in[`FLAGS_T];
                flags_out[`FLAGS_I] = flags_in[`FLAGS_I];
            end	

            `OPSEL_AND:
            begin
                out = rd & rr;
                flags_out[`FLAGS_V] = 0;
                flags_out[`FLAGS_Z] = (out == 0);
                flags_out[`FLAGS_N] = out[7];
                flags_out[`FLAGS_S] = flags_out[`FLAGS_N] ^ flags_out[`FLAGS_V];
                flags_out[`FLAGS_H] = flags_in[`FLAGS_H];
                flags_out[`FLAGS_C] = flags_in[`FLAGS_C];
                flags_out[`FLAGS_T] = flags_in[`FLAGS_T];
                flags_out[`FLAGS_I] = flags_in[`FLAGS_I];
            end

            `OPSEL_EOR:
            begin
                out = rd ^ rr;
                flags_out[`FLAGS_V] = 0;
                flags_out[`FLAGS_Z] = (out == 0);
                flags_out[`FLAGS_N] = out[7];
                flags_out[`FLAGS_S] = flags_out[`FLAGS_N] ^ flags_out[`FLAGS_V];
                flags_out[`FLAGS_H] = flags_in[`FLAGS_H];
                flags_out[`FLAGS_C] = flags_in[`FLAGS_C];
                flags_out[`FLAGS_T] = flags_in[`FLAGS_T];
                flags_out[`FLAGS_I] = flags_in[`FLAGS_I];
            end

            `OPSEL_OR:
            begin
                out = rd | rr;
                flags_out[`FLAGS_V] = 0;
                flags_out[`FLAGS_Z] = (out == 0);
                flags_out[`FLAGS_N] = out[7];
                flags_out[`FLAGS_S] = flags_out[`FLAGS_N] ^ flags_out[`FLAGS_V];
                flags_out[`FLAGS_H] = flags_in[`FLAGS_H];
                flags_out[`FLAGS_C] = flags_in[`FLAGS_C];
                flags_out[`FLAGS_T] = flags_in[`FLAGS_T];
                flags_out[`FLAGS_I] = flags_in[`FLAGS_I];
            end

            `OPSEL_NEG:
            begin
                out = 0 -rd;
                flags_out[`FLAGS_V] = 0;
                flags_out[`FLAGS_Z] = (out == 0);
                flags_out[`FLAGS_N] = out[7];
                flags_out[`FLAGS_S] = flags_out[`FLAGS_N] ^ flags_out[`FLAGS_V];
                flags_out[`FLAGS_H] = flags_in[`FLAGS_H];
                flags_out[`FLAGS_C] = flags_in[`FLAGS_C];
                flags_out[`FLAGS_T] = flags_in[`FLAGS_T];
                flags_out[`FLAGS_I] = flags_in[`FLAGS_I];
            end

			/*TODO: add your ops here*/
        default: begin
            out = 8'bx;
				flags_out = flags_in;
		  end
        endcase
    end


endmodule
