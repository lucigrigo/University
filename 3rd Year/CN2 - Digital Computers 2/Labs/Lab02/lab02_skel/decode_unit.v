`include "defines.vh"
module decode_unit #(
        parameter  INSTR_WIDTH  = 16,   // instructions are 16 bits in width
        parameter  R_ADDR_WIDTH = 5

    )(
        input  wire   [INSTR_WIDTH-1:0] instruction,
        output reg  [`OPCODE_COUNT-1:0] opcode_type,
        output wire  [`GROUP_COUNT-1:0] opcode_group,
        output reg   [R_ADDR_WIDTH-1:0] opcode_rd,
        output reg   [R_ADDR_WIDTH-1:0] opcode_rr
    );

    always @* begin
        casez (instruction)
            /* TODO: Decodificati instructiunile. */
				
				// NOP - No Operation
				16'b0000000000000000: begin
					opcode_type = `TYPE_NOP;
               opcode_rd   = {R_ADDR_WIDTH{1'bx}};
               opcode_rr   = {R_ADDR_WIDTH{1'bx}};
				end
				
				// NEG - Two's Complement
				16'b1001_010?_????_0001: begin
					opcode_type = `TYPE_NEG;
					opcode_rd = instruction[8:4];
               opcode_rr   = {R_ADDR_WIDTH{1'bx}};
				end
				
				// ADD - Add Without Carry
				16'b0000_11??_????_????: begin
					
                opcode_type = `TYPE_ADD;
                opcode_rd   = instruction[8:4];
                opcode_rr   = {instruction[9], instruction[3:0]};
				end
				
				// ADC - Add With Carry
				16'b0001_11??_????_????: begin
					
                opcode_type = `TYPE_ADC;
                opcode_rd   = instruction[8:4];
                opcode_rr   = {instruction[9], instruction[3:0]};
				end
				
				// SUB - Subtract Without Carry
				16'b0001_10??_????_????: begin
					 opcode_type = `TYPE_SUB;
                opcode_rd   = instruction[8:4];
                opcode_rr   = {instruction[9], instruction[3:0]};
				end
				
				// AND - Logical AND
				16'b0010_00??_????_????: begin
					 opcode_type = `TYPE_AND;
                opcode_rd   = instruction[8:4];
                opcode_rr   = {instruction[9], instruction[3:0]};
				end
				
				// OR - Logical OR
				16'b0010_10??_????_????: begin
					 opcode_type = `TYPE_OR;
                opcode_rd   = instruction[8:4];
                opcode_rr   = {instruction[9], instruction[3:0]};
				end
				
            default: begin
                opcode_type = `TYPE_UNKNOWN;
                opcode_rd   = {R_ADDR_WIDTH{1'bx}};
                opcode_rr   = {R_ADDR_WIDTH{1'bx}};
            end
       endcase
   end

   /* TODO: Adauga operatiile care folosesc un operand. */
   assign opcode_group[`GROUP_ALU_ONE_OP] =
       (opcode_type == `TYPE_NEG);

   /* TODO: Adauga operatiile care folosesc doi operanzi. */
   assign opcode_group[`GROUP_ALU_TWO_OP] =
       (opcode_type == `TYPE_ADD) ||
       (opcode_type == `TYPE_ADC) ||
		 (opcode_type == `TYPE_SUB) ||
		 (opcode_type == `TYPE_AND) ||
		 (opcode_type == `TYPE_OR);

   assign opcode_group[`GROUP_ALU] =
       opcode_group[`GROUP_ALU_ONE_OP] ||
       opcode_group[`GROUP_ALU_TWO_OP];
endmodule
