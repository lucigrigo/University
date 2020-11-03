`include "defines.vh"
module reg_file_interface_unit #(
        parameter INSTR_WIDTH  = 16,   // instructions are 16 bits in width
        parameter DATA_WIDTH   = 8,    // registers are 8 bits in width
        parameter R_ADDR_WIDTH = 5     // 32 registers
    )(
        input  wire [`OPCODE_COUNT-1:0] opcode_type,
        input  wire    [DATA_WIDTH-1:0] writeback_value,
		  input  wire  [R_ADDR_WIDTH-1:0] opcode_rd,
        input  wire  [R_ADDR_WIDTH-1:0] opcode_rr,
        input  wire [`SIGNAL_COUNT-1:0] signals,
        output wire  [R_ADDR_WIDTH-1:0] rr_addr,
        output wire  [R_ADDR_WIDTH-1:0] rd_addr,
        inout  wire    [DATA_WIDTH-1:0] rr_data,
        inout  wire    [DATA_WIDTH-1:0] rd_data,
        output wire                     rr_cs,
        output wire                     rd_cs,
        output wire                     rr_we,
        output wire                     rd_we,
        output wire                     rr_oe,
        output wire                     rd_oe
    );
    /* Toate asignarile de mai jos presupun ca instructiunea
     * curenta (instruction) este de tipul:
     * [opcode] Rd Rr,
     * caz in care va accesa de doua ori register file-ul:
     * o data in starea de instruction decode/register fetch,
     * pentru a citi valorile ambelor registre, si a doua oara
     * in write-back, pentru a depune rezultatul (alu_out) in
     * registrul Rd.
     * Evident, nu toate instructiunile sunt de acest tip.
     * In laburi ulterioare vom modifica aici.
     */
	  
	  
	 /* TODO : Modificati flag-urile de lucru cu registrele generale astfel incat noile instructiuni sa se execute corect. */
	 wire [R_ADDR_WIDTH-1:0] internal_rr_addr;
    wire [R_ADDR_WIDTH-1:0] internal_rd_addr;

	/* Internal */
    assign internal_rd_addr =
            signals[`CONTROL_REG_RD_READ] ?
                (opcode_type == `TYPE_LD_X || opcode_type == `TYPE_ST_X) ? `XL :
                (opcode_type == `TYPE_LD_Y || opcode_type == `TYPE_ST_Y) ? `YL :
                (opcode_type == `TYPE_LD_Z || opcode_type == `TYPE_ST_Z) ? `ZL :
                opcode_rd :
            signals[`CONTROL_REG_RD_WRITE] ?
                opcode_rd :
            {R_ADDR_WIDTH{1'bx}};
    assign internal_rr_addr =
            signals[`CONTROL_REG_RR_READ] ?
                (opcode_type == `TYPE_LD_X || opcode_type == `TYPE_ST_X) ? `XH :
                (opcode_type == `TYPE_LD_Y || opcode_type == `TYPE_ST_Y) ? `YH :
                (opcode_type == `TYPE_LD_Z || opcode_type == `TYPE_ST_Z) ? `ZH :
                 opcode_rr :
            {R_ADDR_WIDTH{1'bx}};

    assign rd_data = signals[`CONTROL_REG_RD_WRITE] ? writeback_value :
                     {DATA_WIDTH{1'bz}};
    assign rr_data = {DATA_WIDTH{1'bz}};
    assign rd_we   = signals[`CONTROL_REG_RD_READ]  ? 1'b0 :
                     signals[`CONTROL_REG_RD_WRITE] ? 1'b1 : 1'bx;
    assign rr_we   = signals[`CONTROL_REG_RR_READ]  ? 1'b0 : 1'bx;
    assign rd_oe   = signals[`CONTROL_REG_RD_READ]  ? 1'b1 : 1'bx;
    assign rr_oe   = signals[`CONTROL_REG_RR_READ]  ? 1'b1 : 1'bx;
    assign rd_cs   = signals[`CONTROL_REG_RD_READ] ||
                     signals[`CONTROL_REG_RD_WRITE];
    assign rr_cs   = signals[`CONTROL_REG_RR_READ];
    assign rd_addr = (rd_cs) ? internal_rd_addr : {R_ADDR_WIDTH{1'bx}};
    assign rr_addr = (rr_cs) ? internal_rr_addr : {R_ADDR_WIDTH{1'bx}};

endmodule
