`include "defines.vh"
module signal_generation_unit (
        input  wire  [`STAGE_COUNT-1:0] pipeline_stage,
		  input  wire        cycle_count,
        input  wire [`OPCODE_COUNT-1:0] opcode_type,
        input  wire  [`GROUP_COUNT-1:0] opcode_group,
        output wire [`SIGNAL_COUNT-1:0] signals
    );

    /* Control signals */

    /* Register interface logic */
    assign signals[`CONTROL_REG_RR_READ] =
            (pipeline_stage == `STAGE_ID) &&// || state == `STATE_EX) &&
            (opcode_group[`GROUP_ALU_TWO_OP] ||
             opcode_group[`GROUP_LOAD_INDIRECT]  ||
             opcode_group[`GROUP_STORE] ||
             opcode_type == `TYPE_MOV ||
             opcode_type == `TYPE_OUT);
    assign signals[`CONTROL_REG_RD_READ] =
            (pipeline_stage == `STAGE_ID) &&// || state == `STATE_EX) &&
            (opcode_group[`GROUP_ALU] ||
            ((opcode_group[`GROUP_STORE_INDIRECT] ||   // ?, Y sau Z
              opcode_group[`GROUP_LOAD_INDIRECT]) &&
             !opcode_group[`GROUP_STACK]));
    assign signals[`CONTROL_REG_RD_WRITE] =
            (pipeline_stage == `STAGE_WB) &&
            (opcode_group[`GROUP_ALU] ||
             opcode_group[`GROUP_REGISTER] ||
             (opcode_group[`GROUP_LOAD] && opcode_type != `TYPE_RET) ||
             opcode_type == `TYPE_IN);

    /* Memory interface logic */
    assign signals[`CONTROL_MEM_READ] =
           (pipeline_stage == `STAGE_MEM) &&// || state == `STATE_WB) &&
           opcode_group[`GROUP_LOAD];
    assign signals[`CONTROL_MEM_WRITE] =
           (pipeline_stage == `STAGE_MEM) &&
           opcode_group[`GROUP_STORE];

    /* IO interface logic */
    assign signals[`CONTROL_IO_READ] =
        opcode_group[`GROUP_IO_READ];

	 /* TODO 2:
		 Pentru grupul GROUP_ALU_AUX, semnalul apare in EX
		 (dupa ce obtinem rezultatul de la ALU). Atentie! Daca apare in EX, nu va mai aparea in WB!
			Altfel spus,
		Activati semnalul CONTROL_IO_WRITE si pentru GROUP_ALU_AUX in stagiul EX
		Dezactivati semnalul pentru GROUP_ALU_AUX in stagiul WB
	 */
	 assign signals[`CONTROL_IO_WRITE] =
       (pipeline_stage == `STAGE_WB && opcode_group[`GROUP_IO_WRITE]) ||
		 (opcode_group[`GROUP_ALU_AUX] && pipeline_stage == `STAGE_EX) &&
		 (opcode_group[`GROUP_ALU_AUX] && pipeline_stage != `STAGE_WB);

    assign signals[`CONTROL_POSTDEC] =
            (opcode_type == `TYPE_PUSH || opcode_type == `TYPE_RCALL) &&
            (pipeline_stage == `STAGE_MEM);
    assign signals[`CONTROL_PREINC] =
            (opcode_type == `TYPE_POP) ?
                (pipeline_stage == `STAGE_EX) :
            (opcode_type == `TYPE_RET) &&
                (pipeline_stage == `STAGE_EX || (pipeline_stage == `STAGE_MEM && cycle_count == 0));
endmodule
