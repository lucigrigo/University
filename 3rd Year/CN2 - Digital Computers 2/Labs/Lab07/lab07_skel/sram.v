`include "defines.vh"
module sram #(
        parameter DATA_WIDTH  = 8,
        parameter ADDR_WIDTH  = 8       // 256 bytes address space
    )(
        input  wire                  clk,
        input  wire                  oe,
        input  wire                  cs,
        input  wire                  we,
        input  wire [ADDR_WIDTH-1:0] address,
        inout  wire [DATA_WIDTH-1:0] data
    );
 
    reg [DATA_WIDTH-1:0] memory[0:(1<<ADDR_WIDTH)-1];
    reg [ADDR_WIDTH-1:0] addr_buf;
    
    reg [ADDR_WIDTH:0] i;
    initial begin
        for (i = 0; i < (1<<ADDR_WIDTH); i = i + 1) begin
            memory[i] <= 0;
        end
    end

    always @(negedge clk)
    begin
        if (cs) begin
            if (we) begin
                memory[address] <= data;
            end else begin
                addr_buf <= address;
            end
        end
    end
 
    assign data = (cs && oe && !we) ? memory[addr_buf] : {DATA_WIDTH{1'bz}};
 
endmodule