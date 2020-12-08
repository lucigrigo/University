`define DEBUG
/* In order to disable implicit declaration of wires */
`default_nettype none

/* SREG flags */
`define FLAGS_C             3'd0
`define FLAGS_Z             3'd1
`define FLAGS_N             3'd2
`define FLAGS_V             3'd3
`define FLAGS_S             3'd4
`define FLAGS_H             3'd5
`define FLAGS_T             3'd6
`define FLAGS_I             3'd7

/* Indirect registers */
`define XL                  5'd26
`define XH                  5'd27
`define YL                  5'd28
`define YH                  5'd29
`define ZL                  5'd30
`define ZH                  5'd31

/* test values */
`define TEST_INSTR_WIDTH     16
`define TEST_DATA_WIDTH      8
`define TEST_I_ADDR_WIDTH    10
`define TEST_D_ADDR_WIDTH    7
`define TEST_R_ADDR_WIDTH    5

/* States for FSM */
`define STAGE_RESET 0
`define STAGE_IF    1
`define STAGE_ID    2
`define STAGE_EX    3
`define STAGE_MEM   4
`define STAGE_WB    5
`define STATE_COUNT 6


/* Operations permitted by ALU */
`define OPSEL_NONE          0
`define OPSEL_ADD           1
`define OPSEL_ADC           2
`define OPSEL_SUB           3
`define OPSEL_AND           4
`define OPSEL_EOR           5
`define OPSEL_OR            6
`define OPSEL_NEG           7
`define OPSEL_CP            8
`define OPSEL_XOR				 9

/* Opcode groups */
`define GROUP_ALU_TWO_OP       1
`define GROUP_ALU_ONE_OP       2
`define GROUP_ALU              3
`define GROUP_ALU_IMD          4
`define GROUP_REGISTER         5
`define GROUP_LOAD_INDIRECT    6
`define GROUP_LOAD_DIRECT      7
`define GROUP_LOAD             8
`define GROUP_STORE_INDIRECT   9
`define GROUP_STORE_DIRECT     10
`define GROUP_STORE            11
`define GROUP_MEMORY           12
`define GROUP_CONTROL_FLOW     13
`define GROUP_IO_READ          14
`define GROUP_IO_WRITE         15
`define GROUP_STACK         	 16
`define GROUP_TWO_CYCLE_MEM    17
`define GROUP_ALU_AUX          18

/* Opcode types deduced by decoder */
`define TYPE_NOP            0
`define TYPE_UNKNOWN        1
`define TYPE_LD_X           2
`define TYPE_LD_Y           5
`define TYPE_LD_Z           8
`define TYPE_LDS            11
`define TYPE_ST_X           12
`define TYPE_ST_Y           15
`define TYPE_ST_Z           18
`define TYPE_STS            21
`define TYPE_LDI            22
`define TYPE_MOV            23
`define TYPE_RJMP           26
`define TYPE_BRBS           27
`define TYPE_CP             28
`define TYPE_ADD            37
`define TYPE_ADC            38
`define TYPE_SUB            39
`define TYPE_NEG            45
`define TYPE_AND            46
`define TYPE_OR             48
`define TYPE_EOR            50
`define TYPE_IN				 51
`define TYPE_OUT				 52
`define TYPE_CBI				 53
`define TYPE_SBI				 54
`define TYPE_LDD_Y			 55
`define TYPE_POP				 56
`define TYPE_PUSH				 57
`define TYPE_RCALL			 58
`define TYPE_RET				 59
`define TYPE_SUBI				 60
`define TYPE_BRBC				 61





/* bus sizes */
`define OPSEL_COUNT           5
`define GROUP_COUNT           19
`define STAGE_COUNT           3
`define OPCODE_COUNT          62
`define SIGNAL_COUNT          10
`define FLAG_COUNT            7

/* Control signals */
`define CONTROL_MEM_READ        0
`define CONTROL_MEM_WRITE       1
`define CONTROL_REG_RR_READ     2
`define CONTROL_REG_RR_WRITE    3
`define CONTROL_REG_RD_READ     4
`define CONTROL_REG_RD_WRITE    5
`define CONTROL_IO_READ         6
`define CONTROL_IO_WRITE        7
`define CONTROL_POSTDEC			  8
`define CONTROL_PREINC			  9

/* IO addresses */
`define PUEB                6'h07
`define PORTB               6'h06
`define DDRB                6'h05
`define PINB                6'h04
`define PUEA                6'h03
`define PORTA               6'h02
`define DDRA                6'h01
`define PINA                6'h00
