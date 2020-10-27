`include "defines.vh"
module control_unit #(
        parameter  INSTR_WIDTH = 16,   // instructions are 16 bits in width
        parameter   DATA_WIDTH = 8,    // registers are 8 bits in width
        parameter I_ADDR_WIDTH = 10,   // 2*1024 bytes of flash (or ROM in our case)
        parameter R_ADDR_WIDTH = 5     // 32 registers
    )(
        input  wire                    clk,
        input  wire                    reset,
        // To/from instruction memory
        output reg  [I_ADDR_WIDTH-1:0] program_counter,
        input  wire  [INSTR_WIDTH-1:0] instruction,
        // From FSM
        output wire [`STAGE_COUNT-1:0] pipeline_stage,
        // To/from register file
        output wire [R_ADDR_WIDTH-1:0] rr_addr,
        output wire [R_ADDR_WIDTH-1:0] rd_addr,
        inout  wire   [DATA_WIDTH-1:0] rr_data,
        inout  wire   [DATA_WIDTH-1:0] rd_data,
        output wire                    rr_cs,
        output wire                    rd_cs,
        output wire                    rr_we,
        output wire                    rd_we,
        output wire                    rr_oe,
        output wire                    rd_oe,
        // To/from ALU
        output wire                    alu_enable,
        output reg    [`OPSEL_COUNT-1:0] alu_opsel,
        output wire   [DATA_WIDTH-1:0] alu_flags_in,
        input  wire   [DATA_WIDTH-1:0] alu_flags_out,
        output reg    [DATA_WIDTH-1:0] alu_rr,
        output reg    [DATA_WIDTH-1:0] alu_rd,
        input  wire   [DATA_WIDTH-1:0] alu_out
    );
    // From decode unit
    wire [`SIGNAL_COUNT-1:0] signals;
    wire [`OPCODE_COUNT-1:0] opcode_type;
    wire  [`GROUP_COUNT-1:0] opcode_group;
    // Buffers for various stuff
    reg    [INSTR_WIDTH-1:0] instr_buffer;
    reg     [DATA_WIDTH-1:0] alu_out_buffer;
    reg     [DATA_WIDTH-1:0] writeback_value;
    reg     [DATA_WIDTH-1:0] sreg;

    state_machine fsm (
        .pipeline_stage       (pipeline_stage),
        .clk         (clk),
        .reset       (reset)
    );

    decode_unit #(
        .INSTR_WIDTH(INSTR_WIDTH)
    ) decode (
        .instruction (instr_buffer),
        .opcode_type (opcode_type),
        .opcode_group(opcode_group),
        .opcode_rd(rd_addr),
        .opcode_rr(rr_addr)
    );

    signal_generation_unit sig (
        .pipeline_stage (pipeline_stage),
        .signals (signals),
        .opcode_type (opcode_type),
        .opcode_group(opcode_group)
    );

    reg_file_interface_unit #(
        .DATA_WIDTH  (DATA_WIDTH),
        .INSTR_WIDTH (INSTR_WIDTH),
        .R_ADDR_WIDTH(R_ADDR_WIDTH)
    ) rf_int (
        .opcode_type    (opcode_type),
        .writeback_value(writeback_value),
        .signals        (signals),
        .rr_addr        (rr_addr),
        .rd_addr        (rd_addr),
        .rr_data        (rr_data),
        .rd_data        (rd_data),
        .rr_cs          (rr_cs),
        .rd_cs          (rd_cs),
        .rr_we          (rr_we),
        .rd_we          (rd_we),
        .rr_oe          (rr_oe),
        .rd_oe          (rd_oe)
    );

    /* Bloc de atribuire al program counter-ului */
    always @(posedge clk, posedge reset) begin
        if (reset) begin
            program_counter <= 0;
        end else if (pipeline_stage == `STAGE_WB) begin
            program_counter <= program_counter + 1;
        end
    end

    assign alu_flags_in = sreg;
    /* Bloc de atribuire al sreg-ului */
    always @(posedge clk, posedge reset)
        if (reset)
            sreg <= 0;
        else sreg <= alu_flags_out;

    always @(posedge clk, posedge reset) begin
        if (reset)
            writeback_value <= {DATA_WIDTH{1'b0}};
        else
            writeback_value <= alu_out_buffer;
    end

    /* Buffer pentru instructiunea citita */
    always @(posedge clk, posedge reset)
        if (reset)
            instr_buffer <= 0;
        else if (pipeline_stage == `STAGE_IF)
             instr_buffer <= instruction;

    always @(posedge clk, posedge reset)
        if (reset)
            alu_out_buffer <= 0;
        else if (pipeline_stage == `STAGE_EX)
             alu_out_buffer <= alu_out;

    /* Buffer pentru rd_data si rr_data */
    always @(posedge clk, posedge reset)
        if (reset) begin
            alu_rd <= 0;
            alu_rr <= 0;
        end else begin
              alu_rd <= rd_data;
              alu_rr <= rr_data;
        end

    assign alu_enable = (pipeline_stage == `STAGE_EX);

    /* Set alu_opsel to appropriate operation,
     * according to opcode_type and alu_enable */
    always @* begin
        if (alu_enable == 0)
            alu_opsel = `OPSEL_COUNT'bx;
        else begin
            case (opcode_type)
            /* TODO: Translatati din opcode_type in alu_opsel. */
            `TYPE_NOP:
                alu_opsel = `OPSEL_NOP;
					 
            `TYPE_NEG:
                alu_opsel = `OPSEL_NEG;
					 
            `TYPE_ADD:
                alu_opsel = `OPSEL_ADD;
					 
            `TYPE_ADC:
                alu_opsel = `OPSEL_ADC;
					 
            `TYPE_SUB:
                alu_opsel = `OPSEL_SUB;
					 
            `TYPE_AND:
                alu_opsel = `OPSEL_AND;
					 
            `TYPE_OR:
                alu_opsel = `OPSEL_OR;
					 
            default:
                alu_opsel = `OPSEL_NONE;
            endcase
        end
    end

endmodule
