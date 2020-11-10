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


/* IO addresses */
`define SREG                6'h3F
`define SPH                 6'h3E
`define SPL                 6'h3D
`define STACK_START			 8'hBF // adresa de incepu a stivei (stiva creste in jos)s

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

/* Operations permitted by ALU */
`define OPSEL_NONE          0
`define OPSEL_ADD           1
`define OPSEL_ADC           2
`define OPSEL_SUB           3
`define OPSEL_AND           4
`define OPSEL_EOR           5
`define OPSEL_OR            6
`define OPSEL_NEG           7

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
`define GROUP_STACK				 12
`define GROUP_MEMORY           13
`define GROUP_CONTROL_FLOW     14 

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
`define TYPE_BRBS           24 // Jump conditionat de un anumit bit din SREG (SREG[bit] == 1)
`define TYPE_BRBC           25 // Jump conditionat de un anumit bit din SREG (SREG[bit] == 0)
`define TYPE_RJMP           26 // Jump neconditionat
`define TYPE_POP            29 // STACK.POP
`define TYPE_PUSH           30 // STACK.PUSH
`define TYPE_ADD            37
`define TYPE_ADC            38
`define TYPE_SUB            39
`define TYPE_NEG            45
`define TYPE_AND            46
`define TYPE_OR             48
`define TYPE_EOR            50


/* bus sizes */
`define OPSEL_COUNT           4
`define GROUP_COUNT           15
`define STAGE_COUNT           3
`define OPCODE_COUNT          8
`define SIGNAL_COUNT          8
`define FLAG_COUNT            7

/* Control signals */
`define CONTROL_MEM_READ        0 // semnal activat de instructiunile care pot citi din memorie
`define CONTROL_MEM_WRITE       1 // semnal activat de instructiunile care pot scrie in memorie
`define CONTROL_REG_RR_READ     2 // semnal activat de instructiunile care pot citi Rr
`define CONTROL_REG_RR_WRITE    3 // semnal activat de instructiunile care pot scrie Rr
`define CONTROL_REG_RD_READ     4 // semnal activat de instructiunile care pot citi Rd
`define CONTROL_REG_RD_WRITE    5 // semnal activat de instructiunile care pot scrie Rd
`define CONTROL_STACK_POSTDEC   6 // semnal care va mari stiva (sp-- <=> st.push) - stiva creste in jos 
`define CONTROL_STACK_PREINC    7 // semnal care va micsora stiva (sp++ <=> st.pop)