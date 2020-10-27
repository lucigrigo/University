// Last modified: 21.10.2018 
// Author: dosarudaniel@gmail.com
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

/* test values */
`define TEST_INSTR_WIDTH     16
`define TEST_DATA_WIDTH      8
`define TEST_I_ADDR_WIDTH    10

/* States for FSM */
`define STAGE_RESET 0
`define STAGE_IF    1
`define STAGE_ID    2
`define STAGE_EX    3
`define STAGE_MEM   4
`define STAGE_WB    5

/* Operations permitted by ALU */
`define OPSEL_NOP           0
`define OPSEL_NONE          0
`define OPSEL_ADD           1
`define OPSEL_ADC           2
`define OPSEL_SUB           3
`define OPSEL_AND           4
`define OPSEL_EOR           5
`define OPSEL_OR            6
`define OPSEL_NEG           7

/* Opcode groups */
`define GROUP_ALU_TWO_OP    1
`define GROUP_ALU_ONE_OP    2
`define GROUP_ALU           3

/* Opcode types deduced by decoder */
`define TYPE_NOP            0
`define TYPE_UNKNOWN        1
`define TYPE_ADD            37
`define TYPE_ADC            38
`define TYPE_SUB            39
`define TYPE_NEG            45
`define TYPE_AND            46
`define TYPE_OR             48
`define TYPE_EOR            50

/* bus sizes */
`define OPSEL_COUNT           4
`define GROUP_COUNT           4
`define STAGE_COUNT           3
`define OPCODE_COUNT          8
`define SIGNAL_COUNT          6
`define FLAG_COUNT            8

/* Control signals */
`define CONTROL_MEM_READ        0
`define CONTROL_MEM_WRITE       1
`define CONTROL_REG_RR_READ     2
`define CONTROL_REG_RR_WRITE    3
`define CONTROL_REG_RD_READ     4
`define CONTROL_REG_RD_WRITE    5

