`include "defines.vh"
module signal_generation_unit (
        input  wire  [`STAGE_COUNT-1:0] pipeline_stage,
        input  wire [`OPCODE_COUNT-1:0] opcode_type,
        input  wire  [`GROUP_COUNT-1:0] opcode_group,
        output wire [`SIGNAL_COUNT-1:0] signals
    );

    /* Control signals */

    /* Register interface logic */
    assign signals[`CONTROL_REG_RR_READ] = 
            (pipeline_stage == `STAGE_ID) &&
            (opcode_group[`GROUP_ALU_TWO_OP]);
    assign signals[`CONTROL_REG_RR_WRITE] = 0;
    assign signals[`CONTROL_REG_RD_READ] =
            (pipeline_stage == `STAGE_ID) &&
            opcode_group[`GROUP_ALU];
    assign signals[`CONTROL_REG_RD_WRITE] = 
            (pipeline_stage == `STAGE_WB) &&
            opcode_group[`GROUP_ALU];

endmodule