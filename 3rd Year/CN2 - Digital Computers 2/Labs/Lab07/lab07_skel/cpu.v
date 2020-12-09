`include "defines.vh"
module cpu #(
        parameter      INSTR_WIDTH  = 16,   // instructions are 16 bits in width
        parameter       DATA_WIDTH  = 8,    // registers are 8 bits in width
        parameter     I_ADDR_WIDTH  = 10,   // 2 * 1024 bytes of flash (or ROM in our case)
        parameter       ADDR_WIDTH  = 16,   // 64KB address space
        parameter     D_ADDR_WIDTH  = 7,    // 128 bytes of SRAM
        parameter     R_ADDR_WIDTH  = 5,    // 32 registers
        parameter    IO_ADDR_WIDTH  = 6,    // 64 I/O registers
        parameter RST_ACTIVE_LEVEL  = 1     // level on which reset is active
    )(
        input wire clk,
        input wire reset,

        inout  wire   [DATA_WIDTH-1:0] pa,
        inout  wire   [DATA_WIDTH-1:0] pb
`ifdef DEBUG
            ,
            output wire [`STAGE_COUNT-1:0]  debug_pipeline_stage,
            output wire [DATA_WIDTH-1:0] debug_alu_rr,
            output wire [DATA_WIDTH-1:0] debug_alu_rd,
            output wire [DATA_WIDTH-1:0] debug_alu_out,
            output wire [I_ADDR_WIDTH-1:0] debug_program_counter,
            output wire [`FLAG_COUNT-1:0] debug_flags_out,
            output wire [D_ADDR_WIDTH-1:0] debug_bus_address,
            output wire [DATA_WIDTH-1:0] debug_bus_data,
            output wire [D_ADDR_WIDTH-1:0] debug_register_Y,
            output wire [11:0] debug_opcode_imd,
            output wire [DATA_WIDTH-1:0] debug_writeback_value,
            output wire [`SIGNAL_COUNT-1:0] debug_signals
`endif
    );
`ifdef DEBUG
    assign debug_pipeline_stage   = pipeline_stage;
    assign debug_alu_rr  = alu_rr;
    assign debug_alu_rd  = alu_rd;
    assign debug_alu_out = alu_out;
     assign debug_program_counter = program_counter;
     assign debug_flags_out = alu_flags_out;
     assign debug_bus_address = bus_addr;
     assign debug_bus_data = bus_data;
`endif

    wire [`STAGE_COUNT-1:0] pipeline_stage;
    wire [I_ADDR_WIDTH-1:0]  program_counter;
    wire [INSTR_WIDTH-1:0] instruction;
    wire [R_ADDR_WIDTH-1:0]    rr_addr;
    wire [R_ADDR_WIDTH-1:0]    rd_addr;
    wire [DATA_WIDTH-1:0]  rr_data;
    wire [DATA_WIDTH-1:0]  rd_data;
    wire                   rr_cs;
    wire                   rd_cs;
    wire                   rr_we;
    wire                   rd_we;
    wire                   rr_oe;
    wire                   rd_oe;
    wire                   alu_enable;
    wire [`OPSEL_COUNT-1:0]  alu_opsel;
    wire [DATA_WIDTH-1:0]  alu_rr;
    wire [DATA_WIDTH-1:0]  alu_rd;
    wire [DATA_WIDTH-1:0]  alu_out;
    wire [`FLAG_COUNT:0]   alu_flags_in;
    wire [`FLAG_COUNT:0]   alu_flags_out;
    wire [INSTR_WIDTH-1:0] bus_addr;
    wire [DATA_WIDTH-1:0] bus_data;
    wire                    mem_cs;
    wire                    mem_we;
    wire                    mem_oe;
    wire                    io_cs;
    wire                    io_we;
    wire                    io_oe;

	initial
		begin
			$display("Start cpu ...");
			$display("Legend:");
			$display("OPERATION OP1, OP2 - STAGE: OK <=> PASS");
			$display("OPERATION OP1, OP2 - STAGE: FAILED => EXPECTED_VALUE VS COMPUTED_VALUE <=> FAIL");
		end

    control_unit #(
        .I_ADDR_WIDTH(I_ADDR_WIDTH),
        .R_ADDR_WIDTH(R_ADDR_WIDTH),
        .INSTR_WIDTH (INSTR_WIDTH)
    ) control (
        .program_counter(program_counter),
        .instruction(instruction),
        .pipeline_stage(pipeline_stage),
        .clk(clk),
        .reset(reset),
        .rr_addr(rr_addr),
        .rd_addr(rd_addr),
        .rr_data(rr_data),
        .rd_data(rd_data),
        .rr_cs(rr_cs),
        .rd_cs(rd_cs),
        .rr_we(rr_we),
        .rd_we(rd_we),
        .rr_oe(rr_oe),
        .rd_oe(rd_oe),
        .alu_enable(alu_enable),
        .alu_opsel(alu_opsel),
        .alu_flags_in(alu_flags_in),
        .alu_flags_out(alu_flags_out),
        .alu_rr(alu_rr),
        .alu_rd(alu_rd),
        .alu_out(alu_out),
        .bus_addr(bus_addr),
        .bus_data(bus_data),
        .mem_cs(mem_cs),
        .mem_we(mem_we),
        .mem_oe(mem_oe),
        .io_cs(io_cs),
        .io_we(io_we),
        .io_oe(io_oe)
`ifdef DEBUG
        ,
        .debug_opcode_imd(debug_opcode_imd),
        .debug_writeback_value(debug_writeback_value),
        .debug_signals(debug_signals)
`endif
    );

    alu #(
        .DATA_WIDTH(DATA_WIDTH)
    ) ual (
        .opsel(alu_opsel),
        .enable(alu_enable),
        .rd(alu_rd),
        .rr(alu_rr),
        .out(alu_out),
        .flags_in(alu_flags_in),
        .flags_out(alu_flags_out)
    );

    // Rom implementeaza un rom generic
    // noi vrem sa folosim Rom-ul asta ca sursa de instructiuni,
    // deci de aia avem DATA_WIDTH instantiat cu INSTR_WIDTH
    // si ADDR_WIDTH instantiat cu I_ADDR_WIDTH
    rom #(
        .DATA_WIDTH(INSTR_WIDTH),
        .ADDR_WIDTH(I_ADDR_WIDTH)
    ) instruction_mem (
        .clk (clk),
        .addr(program_counter),
        .data(instruction)
    );
    dual_port_sram #(
        .DATA_WIDTH(DATA_WIDTH),
        .ADDR_WIDTH(R_ADDR_WIDTH)
    ) reg_file (
        .clk (clk),
        .rr_addr(rr_addr),
        .rd_addr(rd_addr),
        .rr_data(rr_data),
        .rd_data(rd_data),
        .rr_cs  (rr_cs),
        .rd_cs  (rd_cs),
        .rr_we  (rr_we),
        .rd_we  (rd_we),
        .rr_oe  (rr_oe),
        .rd_oe  (rd_oe)
`ifdef DEBUG
        ,
        .debug_register_Y(debug_register_Y)
`endif
     );

    sram #(
        .ADDR_WIDTH(D_ADDR_WIDTH),
        .DATA_WIDTH(DATA_WIDTH)
    ) data_mem (
        .clk    (clk),
        .oe     (mem_oe),
        .cs     (mem_cs),
        .we     (mem_we),
        .address(bus_addr[D_ADDR_WIDTH-1:0]),
        .data   (bus_data)
    );
    io_sram #(
        .ADDR_WIDTH(IO_ADDR_WIDTH),
        .DATA_WIDTH(DATA_WIDTH)
    ) io (
        .clk    (clk),
        .reset  (reset),
        .oe     (io_oe),
        .cs     (io_cs),
        .we     (io_we),
        .address(bus_addr[IO_ADDR_WIDTH-1:0]),
        .data   (bus_data),
        .pa     (pa),
        .pb     (pb)
    );
endmodule
