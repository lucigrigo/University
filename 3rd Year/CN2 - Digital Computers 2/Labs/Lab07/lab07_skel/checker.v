`timescale 1ns / 1ps
`include "defines.vh"
module checker(
        input wire clk,
        input wire reset,
        output reg result
    );
     
`ifdef DEBUG
    wire [`STAGE_COUNT-1:0]  debug_pipeline_stage;
    wire [`TEST_I_ADDR_WIDTH-1:0] debug_program_counter;
//  wire [`TEST_DATA_WIDTH-1:0] debug_alu_rr;
//  wire [`TEST_DATA_WIDTH-1:0] debug_alu_rd;
//  wire [`TEST_DATA_WIDTH-1:0] debug_alu_out;
//  wire [`FLAG_COUNT-1:0] debug_flags_out;
    wire [`TEST_D_ADDR_WIDTH-1:0] debug_bus_address;
    wire [`TEST_D_ADDR_WIDTH-1:0] debug_register_Y;
    wire [`TEST_DATA_WIDTH-1:0] debug_bus_data;
    wire [11:0] debug_opcode_imd;
    wire [`TEST_DATA_WIDTH-1:0] debug_writeback_value;
    wire [`SIGNAL_COUNT-1:0] debug_signals;
`endif


    // Instantiate the Unit Under Test (UUT)
    cpu #(
        .INSTR_WIDTH     (`TEST_INSTR_WIDTH),
      .DATA_WIDTH      (`TEST_DATA_WIDTH),
      .I_ADDR_WIDTH    (`TEST_I_ADDR_WIDTH),
      .RST_ACTIVE_LEVEL(1)
        ) uut (
        .clk(clk), 
        .reset(reset)
`ifdef DEBUG
        ,
        .debug_pipeline_stage(debug_pipeline_stage),
        .debug_program_counter(debug_program_counter),
//      .debug_alu_rr(debug_alu_rr),
//      .debug_alu_rd(debug_alu_rd),
//      .debug_alu_out(debug_alu_out),
//      .debug_flags_out(debug_flags_out)
        .debug_bus_address(debug_bus_address),
        .debug_register_Y(debug_register_Y),
        .debug_bus_data(debug_bus_data),
        .debug_opcode_imd(debug_opcode_imd),
        .debug_writeback_value(debug_writeback_value),
        .debug_signals(debug_signals)
`endif
    );
    always @(*) begin
        /*
            test instruction number, and ok if
                alu_rr is value we think it is
                alu_rd is value we think it is
                alu_out is value we think it is
                flags is value we think it is
        0:      nop
        1:      add   r1, r2
        2:      adc     r1, r2
        3:     neg  r1  
        4:      and     r1, r2 
        5:      eor     r1, r2
        6:      or  r1, r2      
        7:      sub     r1, r2
        r1 should be, at start, 254
        r2 should be, at start, 253
        */
        case(debug_program_counter)
            0:
                result <= 1'b1;
            1:
                // ldi r29, 0 
                if (debug_writeback_value == 0 && debug_signals[`CONTROL_REG_RD_WRITE] == 0 && debug_pipeline_stage == 2)
                    result <= 1'b1;
                else if (debug_pipeline_stage != 2)
                    result <= 1'b1;
                else
                    result <= 1'bx;
            2:
                // ldi r28, 65 
                if (debug_writeback_value == 0 && debug_signals[`CONTROL_REG_RD_WRITE] == 0 && debug_pipeline_stage == 2)
                    result <= 1'b1;
                else if (debug_pipeline_stage != 2)
                    result <= 1'b1;
                else
                    result <= 1'bx;

            3:
                // ldd r17, Y
                if (debug_writeback_value == 65 && debug_register_Y == 65 && debug_signals[`CONTROL_REG_RD_WRITE] == 0 && debug_bus_data === 8'bx && debug_pipeline_stage == 2)
                    result <= 1'b1;
                else if (debug_pipeline_stage != 2)
                    result <= 1'b1;
                else
                    result <= 1'bx;

            4:
                // sts r28, 10
                if (debug_bus_address == 74 && debug_bus_data == 65 && debug_pipeline_stage == 4)
                    result <= 1'b1;
                else if (debug_pipeline_stage != 4)
                    result <= 1'b1;
                else
                    result <= 1'bx;

            5:
                // lds r28, 10
                if (debug_bus_address == 74 && debug_bus_data === 8'bx && debug_writeback_value == 0 && debug_signals[`CONTROL_REG_RR_READ] == 0 && debug_pipeline_stage == 2)
                    result <= 1'b1;
                else if (debug_pipeline_stage != 2)
                    result <= 1'b1;
                else
                    result <= 1'bx;

            6:
                // mov  r17, r28
                if (debug_writeback_value == 65 && debug_pipeline_stage == 4)
                    result <= 1'b1;
                else if (debug_pipeline_stage != 4)
                    result <= 1'b1;
                else
                    result <= 1'bx;

            default:
                result <= 1'b1;
        endcase
    end
endmodule
