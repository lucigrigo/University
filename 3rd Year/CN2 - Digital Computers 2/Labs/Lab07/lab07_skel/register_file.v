/* Traducerea si adaptarea:
 * http://www.asic-world.com/examples/verilog/ram_dp_sr_sw.html
 */
`include "defines.vh"
module dual_port_sram #(
        parameter DATA_WIDTH = 8,    // registers are 8 bits in width
        parameter ADDR_WIDTH = 5     // 32 registers
    )(
        input  wire                  clk,
        input  wire [ADDR_WIDTH-1:0] rr_addr,
        input  wire [ADDR_WIDTH-1:0] rd_addr,
        inout  wire [DATA_WIDTH-1:0] rr_data,
        inout  wire [DATA_WIDTH-1:0] rd_data,
        input  wire                  rr_cs,
        input  wire                  rd_cs,
        input  wire                  rr_we,
        input  wire                  rd_we,
        input  wire                  rr_oe,
        input  wire                  rd_oe
`ifdef DEBUG
        ,
        output wire [DATA_WIDTH+DATA_WIDTH-1:0]  debug_register_X,
        output wire [DATA_WIDTH+DATA_WIDTH-1:0]  debug_register_Y,
        output wire [DATA_WIDTH+DATA_WIDTH-1:0]  debug_register_Z
`endif
    );
    reg [DATA_WIDTH-1:0] memory[0:(1<<ADDR_WIDTH)-1];
    reg [ADDR_WIDTH-1:0] rr_addr_buf;
    reg [ADDR_WIDTH-1:0] rd_addr_buf;

`ifdef DEBUG
    assign debug_register_X = {memory[27], memory[26]};
    assign debug_register_Y = {memory[29], memory[28]};
    assign debug_register_Z = {memory[31], memory[30]};
`endif

    reg [ADDR_WIDTH:0] i;
    initial begin
        for (i = 0; i < (1<<ADDR_WIDTH); i = i + 1)
            memory[i] <= 0;
    end

    /* Memory Write Block 
     * Write Operation : When we = 1, cs = 1
     */
    always @(negedge clk)
    begin : MEM_WRITE
        if (rr_cs && rr_we) begin
            memory[rr_addr] <= rr_data;
        end else if (rd_cs && rd_we) begin 
            memory[rd_addr] <= rd_data;
        end
    end

    /* First port of RAM
     * Memory Read Block
     * Read Operation : When we = 0, oe = 1, cs = 1
     */
    always @(negedge clk)
    begin : RR_MEM_READ
        if (rr_cs && !rr_we) begin
            rr_addr_buf <= rr_addr;
        end
    end

    /* Second port of RAM
     * Memory Read Block 1
     * Read Operation : When we = 0, oe = 1, cs = 1
     */
    always @(negedge clk)
    begin : RD_MEM_READ
        if (rd_cs && !rd_we) begin
            rd_addr_buf <= rd_addr;
        end
    end

    /* Tri-State Buffer control
     * output : When we = 0, oe = 1, cs = 1
     */
    assign rr_data = (rr_cs && rr_oe && !rr_we) ? memory[rr_addr_buf] : {DATA_WIDTH{1'bz}};
    assign rd_data = (rd_cs && rd_oe && !rd_we) ? memory[rd_addr_buf] : {DATA_WIDTH{1'bz}};

endmodule
