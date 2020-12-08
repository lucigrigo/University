`include "defines.vh"
module state_machine (
        output reg  [`STAGE_COUNT-1:0] pipeline_stage,
        input  wire                    clk,
        input  wire                    reset
    );

    reg [`STAGE_COUNT-1:0] next_stage;

    always @(posedge clk, posedge reset)
        if (reset)
            pipeline_stage <= `STAGE_RESET;
        else
            pipeline_stage <= next_stage;

    always @* begin
        case (pipeline_stage)
        `STAGE_RESET:
            next_stage = `STAGE_IF;
        `STAGE_IF:
            next_stage = `STAGE_ID;
        `STAGE_ID:
            next_stage = `STAGE_EX;
        `STAGE_EX:
            next_stage = `STAGE_MEM;
        `STAGE_MEM:
            next_stage = `STAGE_WB;
        `STAGE_WB:
            next_stage = `STAGE_IF;
        /* Should never get here, but anyway */
        default:
            next_stage = `STAGE_RESET;
        endcase
    end

endmodule
