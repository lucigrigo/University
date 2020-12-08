/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "C:/Users/student/Desktop/lab07_skel/test_ldi.vh";
static int ng1[] = {1, 0};
static unsigned int ng2[] = {1U, 0U};
static int ng3[] = {2, 0};
static int ng4[] = {5, 0};
static int ng5[] = {22, 0, 0, 0};
static const char *ng6 = "LDI R%2d, %3d - ID: OK";
static unsigned int ng7[] = {1U, 1U};
static const char *ng8 = "LDI R%2d, %3d - ID: FAILED";
static int ng9[] = {3, 0};
static int ng10[] = {4, 0};
static const char *ng11 = "LDI R%2d, %3d - WB: OK (R%2d = %3d)";
static const char *ng12 = "LDI R%2d, %3d - WB: FAILED => (%3d) vs (%3d)";
static const char *ng13 = "C:/Users/student/Desktop/lab07_skel/test_in.vh";
static int ng14[] = {51, 0, 0, 0};
static const char *ng15 = "IN R%2d, %d - ID: FAILED, check opcode_type: %d vs %d";
static int ng16[] = {51, 0};
static const char *ng17 = "IN R%2d, %d - ID: FAILED, check opcode_rd: %d vs %d";
static const char *ng18 = "IN R%2d, %d - ID: FAILED, check opcode_imd: %d vs %d";
static int ng19[] = {14, 0};
static const char *ng20 = "IN R%2d, %d - ID: FAILED - IN instruction should be in GROUP_IO_READ";
static int ng21[] = {6, 0};
static const char *ng22 = "IN R%2d, %d - ID: FAILED, signal CONTROL_IO_READ should be active for IN instruction";
static const char *ng23 = "IN R%2d, %d - ID: FAILED, check bus_addr in bus_interface_unit.v: %d vs %d";
static const char *ng24 = "IN R%2d, %d - ID: OK";
static const char *ng25 = "IN R%2d, %d - WB: FAILED, signal CONTROL_REG_RD_WRITE should be active for IN instruction";
static const char *ng26 = "IN R%2d, %d - WB: FAILED, check writeback_value : %d vs %d";
static const char *ng27 = "IN R%2d, %d - WB: OK";
static const char *ng28 = "C:/Users/student/Desktop/lab07_skel/test_out.vh";
static int ng29[] = {52, 0, 0, 0};
static const char *ng30 = "OUT %d, R%2d - ID: FAILED, check opcode_type: %d vs %d";
static int ng31[] = {52, 0};
static const char *ng32 = "OUT %d, R%2d - ID: FAILED, check opcode_rr: %d vs %d";
static const char *ng33 = "OUT %d, R%2d - ID: FAILED, check opcode_imd: %d vs %d";
static int ng34[] = {15, 0};
static const char *ng35 = "OUT %d, R%2d - ID: FAILED - OUT instruction should be in GROUP_IO_WRITE";
static const char *ng36 = "OUT %d, R%2d - ID: FAILED, signal CONTROL_REG_RR_READ should be active for OUT instruction";
static const char *ng37 = "OUT %d, R%2d - ID: FAILED, check bus_addr in bus_interface_unit.v: %d vs %d";
static const char *ng38 = "OUT %d, R%2d - ID: OK";
static const char *ng39 = " ";
static int ng40[] = {7, 0};
static const char *ng41 = "OUT %d, R%2d - WB: FAILED, signal CONTROL_IO_WRITE should be active for OUT instruction";
static const char *ng42 = "OUT %d, R%2d - WB: OK";
static const char *ng43 = "C:/Users/student/Desktop/lab07_skel/test_sbi.vh";
static int ng44[] = {54, 0, 0, 0};
static const char *ng45 = "SBI  %d,R%2d - ID: FAILED, check opcode_type: %d vs %d";
static int ng46[] = {54, 0};
static const char *ng47 = "SBI  %d,R%2d - ID: FAILED, check opcode_bit: %d vs %d";
static const char *ng48 = "SBI  %d,R%2d - ID: FAILED, check opcode_imd: %d vs %d";
static const char *ng49 = "SBI  %d,R%2d,  - ID: FAILED - SBI instruction should be in GROUP_IO_READ";
static int ng50[] = {18, 0};
static const char *ng51 = "SBI  %d,R%2d,  - ID: FAILED - SBI instruction should be in GROUP_ALU_AUX";
static const char *ng52 = "SBI %d,R%2d, - ID: FAILED, check bus_addr in bus_interface_unit.v: %d vs %d";
static const char *ng53 = "SBI R%2d, %d - ID: FAILED, signal alu_rr should have other value for SBI instruction";
static const char *ng54 = "SBI R%2d, %d - ID: OK";
static const char *ng55 = "SBI R%2d, %d - ID: FAILED, signal CONTROL_IO_WRITE should be active for SBI instruction";
static const char *ng56 = "SBI R%2d, %d - ID: FAILED, signal alu_enable should be active for SBI instruction";
static const char *ng57 = "SBI R%2d, %d - ID: FAILED, signal alu_rd should have other value for SBI instruction";
static const char *ng58 = "SBI R%2d, %d - EX: OK";
static const char *ng59 = "C:/Users/student/Desktop/lab07_skel/test_cbi.vh";
static int ng60[] = {53, 0, 0, 0};
static const char *ng61 = "CBI  %d,R%2d - ID: FAILED, check opcode_type: %d vs %d";
static int ng62[] = {53, 0};
static const char *ng63 = "CBI  %d,R%2d - ID: FAILED, check opcode_bit: %d vs %d";
static const char *ng64 = "CBI  %d,R%2d - ID: FAILED, check opcode_imd: %d vs %d";
static const char *ng65 = "CBI  %d,R%2d,  - ID: FAILED - CBI instruction should be in GROUP_IO_READ";
static const char *ng66 = "CBI  %d,R%2d,  - ID: FAILED - CBI instruction should be in GROUP_ALU_AUX";
static const char *ng67 = "CBI %d,R%2d, - ID: FAILED, check bus_addr in bus_interface_unit.v: %d vs %d";
static const char *ng68 = "CBI R%2d, %d - ID: OK";
static const char *ng69 = "CBI R%2d, %d - ID: FAILED, signal CONTROL_IO_WRITE should be active for CBI instruction";
static const char *ng70 = "CBI R%2d, %d - ID: FAILED, signal alu_enable should be active for CBI instruction";
static const char *ng71 = "CBI R%2d, %d - EX: OK";
static const char *ng72 = "C:/Users/student/Desktop/lab07_skel/unitTest.v";
static unsigned int ng73[] = {165U, 0U};
static int ng74[] = {28, 0};
static int ng75[] = {29, 0};
static const char *ng76 = "Init regs..";
static unsigned int ng77[] = {255U, 255U};
static unsigned int ng78[] = {65535U, 65535U};
static unsigned int ng79[] = {31U, 31U};
static unsigned int ng80[] = {7U, 7U};
static int ng81[] = {0, 0};
static unsigned int ng82[] = {16U, 0U};
static unsigned int ng83[] = {0U, 0U};
static int ng84[] = {17, 0};
static unsigned int ng85[] = {0U, 1U};



static int sp_TEST_LDI(char *t1, char *t2)
{
    char t10[8];
    char t15[8];
    char t31[16];
    char t32[8];
    char t40[8];
    char t72[8];
    char t90[8];
    char t106[8];
    char t114[8];
    char t154[8];
    int t0;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    int t7;
    char *t8;
    char *t9;
    char *t11;
    char *t12;
    char *t13;
    char *t14;
    char *t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    char *t22;
    char *t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    char *t27;
    char *t28;
    char *t29;
    char *t30;
    char *t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    char *t39;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    char *t44;
    char *t45;
    char *t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    unsigned int t52;
    unsigned int t53;
    char *t54;
    char *t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    unsigned int t59;
    unsigned int t60;
    unsigned int t61;
    unsigned int t62;
    unsigned int t63;
    int t64;
    int t65;
    unsigned int t66;
    unsigned int t67;
    unsigned int t68;
    unsigned int t69;
    unsigned int t70;
    unsigned int t71;
    char *t73;
    unsigned int t74;
    unsigned int t75;
    unsigned int t76;
    unsigned int t77;
    unsigned int t78;
    char *t79;
    char *t80;
    unsigned int t81;
    unsigned int t82;
    unsigned int t83;
    char *t84;
    char *t85;
    char *t86;
    char *t87;
    char *t88;
    char *t89;
    char *t91;
    char *t92;
    unsigned int t93;
    unsigned int t94;
    unsigned int t95;
    unsigned int t96;
    unsigned int t97;
    unsigned int t98;
    unsigned int t99;
    unsigned int t100;
    unsigned int t101;
    unsigned int t102;
    unsigned int t103;
    unsigned int t104;
    char *t105;
    char *t107;
    unsigned int t108;
    unsigned int t109;
    unsigned int t110;
    unsigned int t111;
    unsigned int t112;
    char *t113;
    unsigned int t115;
    unsigned int t116;
    unsigned int t117;
    char *t118;
    char *t119;
    char *t120;
    unsigned int t121;
    unsigned int t122;
    unsigned int t123;
    unsigned int t124;
    unsigned int t125;
    unsigned int t126;
    unsigned int t127;
    char *t128;
    char *t129;
    unsigned int t130;
    unsigned int t131;
    unsigned int t132;
    unsigned int t133;
    unsigned int t134;
    unsigned int t135;
    unsigned int t136;
    unsigned int t137;
    int t138;
    int t139;
    unsigned int t140;
    unsigned int t141;
    unsigned int t142;
    unsigned int t143;
    unsigned int t144;
    unsigned int t145;
    char *t146;
    unsigned int t147;
    unsigned int t148;
    unsigned int t149;
    unsigned int t150;
    unsigned int t151;
    char *t152;
    char *t153;
    char *t155;
    char *t156;
    char *t157;
    unsigned int t158;
    unsigned int t159;
    unsigned int t160;
    unsigned int t161;
    unsigned int t162;
    unsigned int t163;
    unsigned int t164;
    char *t165;
    unsigned int t166;
    unsigned int t167;
    unsigned int t168;
    unsigned int t169;
    unsigned int t170;
    char *t171;
    char *t172;

LAB0:    t0 = 1;
    xsi_set_current_line(4, ng0);

LAB2:    xsi_set_current_line(5, ng0);
    t3 = (t1 + 23332);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t6 = *((char **)t5);

LAB3:    t5 = ((char*)((ng1)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t5, 32);
    if (t7 == 1)
        goto LAB4;

LAB5:    t3 = ((char*)((ng3)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB6;

LAB7:    t3 = ((char*)((ng9)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB8;

LAB9:    t3 = ((char*)((ng10)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB10;

LAB11:    t3 = ((char*)((ng4)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB12;

LAB13:
LAB14:    t0 = 0;

LAB1:    return t0;
LAB4:    xsi_set_current_line(6, ng0);
    t8 = ((char*)((ng2)));
    t9 = (t1 + 9048);
    xsi_vlogvar_assign_value(t9, t8, 0, 0, 1);
    goto LAB14;

LAB6:    xsi_set_current_line(8, ng0);
    t4 = (t1 + 23372);
    t5 = *((char **)t4);
    t8 = ((((char*)(t5))) + 40U);
    t9 = *((char **)t8);
    t8 = (t1 + 23412);
    t11 = *((char **)t8);
    t12 = ((((char*)(t11))) + 72U);
    t13 = *((char **)t12);
    t14 = ((char*)((ng4)));
    xsi_vlog_generic_get_index_select_value(t10, 1, t9, t13, 2, t14, 32, 1);
    memset(t15, 0, 8);
    t16 = (t10 + 4);
    t17 = *((unsigned int *)t16);
    t18 = (~(t17));
    t19 = *((unsigned int *)t10);
    t20 = (t19 & t18);
    t21 = (t20 & 1U);
    if (t21 != 0)
        goto LAB15;

LAB16:    if (*((unsigned int *)t16) != 0)
        goto LAB17;

LAB18:    t23 = (t15 + 4);
    t24 = *((unsigned int *)t15);
    t25 = *((unsigned int *)t23);
    t26 = (t24 || t25);
    if (t26 > 0)
        goto LAB19;

LAB20:    memcpy(t40, t15, 8);

LAB21:    memset(t72, 0, 8);
    t73 = (t40 + 4);
    t74 = *((unsigned int *)t73);
    t75 = (~(t74));
    t76 = *((unsigned int *)t40);
    t77 = (t76 & t75);
    t78 = (t77 & 1U);
    if (t78 != 0)
        goto LAB29;

LAB30:    if (*((unsigned int *)t73) != 0)
        goto LAB31;

LAB32:    t80 = (t72 + 4);
    t81 = *((unsigned int *)t72);
    t82 = *((unsigned int *)t80);
    t83 = (t81 || t82);
    if (t83 > 0)
        goto LAB33;

LAB34:    memcpy(t114, t72, 8);

LAB35:    t146 = (t114 + 4);
    t147 = *((unsigned int *)t146);
    t148 = (~(t147));
    t149 = *((unsigned int *)t114);
    t150 = (t149 & t148);
    t151 = (t150 != 0);
    if (t151 > 0)
        goto LAB47;

LAB48:    xsi_set_current_line(16, ng0);

LAB51:    xsi_set_current_line(17, ng0);
    t3 = ((char*)((ng7)));
    t4 = (t1 + 9048);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(18, ng0);
    t3 = (t1 + 23572);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 23604);
    t9 = *((char **)t5);
    t11 = ((((char*)(t9))) + 40U);
    t12 = *((char **)t11);
    t11 = (t1 + 848);
    xsi_vlogfile_write(1, 0, 0, ng8, 3, t11, (char)118, t8, 5, (char)118, t12, 12);

LAB49:    goto LAB14;

LAB8:    xsi_set_current_line(20, ng0);
    t4 = ((char*)((ng2)));
    t5 = (t1 + 9048);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 1);
    goto LAB14;

LAB10:    xsi_set_current_line(21, ng0);
    t4 = ((char*)((ng2)));
    t5 = (t1 + 9048);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 1);
    goto LAB14;

LAB12:    xsi_set_current_line(23, ng0);
    t4 = (t1 + 23644);
    t5 = *((char **)t4);
    t8 = ((((char*)(t5))) + 56U);
    t9 = *((char **)t8);
    t11 = (t1 + 9368);
    t12 = (t11 + 56U);
    t13 = *((char **)t12);
    memset(t10, 0, 8);
    t14 = (t9 + 4);
    t16 = (t13 + 4);
    t17 = *((unsigned int *)t9);
    t18 = *((unsigned int *)t13);
    t19 = (t17 ^ t18);
    t20 = *((unsigned int *)t14);
    t21 = *((unsigned int *)t16);
    t24 = (t20 ^ t21);
    t25 = (t19 | t24);
    t26 = *((unsigned int *)t14);
    t34 = *((unsigned int *)t16);
    t35 = (t26 | t34);
    t36 = (~(t35));
    t37 = (t25 & t36);
    if (t37 != 0)
        goto LAB55;

LAB52:    if (t35 != 0)
        goto LAB54;

LAB53:    *((unsigned int *)t10) = 1;

LAB55:    memset(t15, 0, 8);
    t23 = (t10 + 4);
    t38 = *((unsigned int *)t23);
    t41 = (~(t38));
    t42 = *((unsigned int *)t10);
    t43 = (t42 & t41);
    t47 = (t43 & 1U);
    if (t47 != 0)
        goto LAB56;

LAB57:    if (*((unsigned int *)t23) != 0)
        goto LAB58;

LAB59:    t28 = (t15 + 4);
    t48 = *((unsigned int *)t15);
    t49 = *((unsigned int *)t28);
    t50 = (t48 || t49);
    if (t50 > 0)
        goto LAB60;

LAB61:    memcpy(t72, t15, 8);

LAB62:    memset(t90, 0, 8);
    t87 = (t72 + 4);
    t97 = *((unsigned int *)t87);
    t98 = (~(t97));
    t99 = *((unsigned int *)t72);
    t100 = (t99 & t98);
    t101 = (t100 & 1U);
    if (t101 != 0)
        goto LAB70;

LAB71:    if (*((unsigned int *)t87) != 0)
        goto LAB72;

LAB73:    t89 = (t90 + 4);
    t102 = *((unsigned int *)t90);
    t103 = *((unsigned int *)t89);
    t104 = (t102 || t103);
    if (t104 > 0)
        goto LAB74;

LAB75:    memcpy(t154, t90, 8);

LAB76:    t165 = (t154 + 4);
    t166 = *((unsigned int *)t165);
    t167 = (~(t166));
    t168 = *((unsigned int *)t154);
    t169 = (t168 & t167);
    t170 = (t169 != 0);
    if (t170 > 0)
        goto LAB88;

LAB89:    xsi_set_current_line(35, ng0);

LAB92:    xsi_set_current_line(36, ng0);
    t3 = ((char*)((ng7)));
    t4 = (t1 + 9048);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(37, ng0);
    t3 = (t1 + 9208);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 9368);
    t9 = (t8 + 56U);
    t11 = *((char **)t9);
    t12 = (t1 + 23852);
    t13 = *((char **)t12);
    t14 = ((((char*)(t13))) + 56U);
    t16 = *((char **)t14);
    t22 = (t1 + 9368);
    t23 = (t22 + 56U);
    t27 = *((char **)t23);
    t28 = (t1 + 848);
    xsi_vlogfile_write(1, 0, 0, ng12, 5, t28, (char)119, t5, 32, (char)119, t11, 32, (char)118, t16, 8, (char)119, t27, 32);

LAB90:    goto LAB14;

LAB15:    *((unsigned int *)t15) = 1;
    goto LAB18;

LAB17:    t22 = (t15 + 4);
    *((unsigned int *)t15) = 1;
    *((unsigned int *)t22) = 1;
    goto LAB18;

LAB19:    t27 = (t1 + 23444);
    t28 = *((char **)t27);
    t29 = ((((char*)(t28))) + 40U);
    t30 = *((char **)t29);
    t29 = ((char*)((ng5)));
    xsi_vlog_unsigned_equal(t31, 62, t30, 62, t29, 32);
    memset(t32, 0, 8);
    t33 = (t31 + 4);
    t34 = *((unsigned int *)t33);
    t35 = (~(t34));
    t36 = *((unsigned int *)t31);
    t37 = (t36 & t35);
    t38 = (t37 & 1U);
    if (t38 != 0)
        goto LAB22;

LAB23:    if (*((unsigned int *)t33) != 0)
        goto LAB24;

LAB25:    t41 = *((unsigned int *)t15);
    t42 = *((unsigned int *)t32);
    t43 = (t41 & t42);
    *((unsigned int *)t40) = t43;
    t44 = (t15 + 4);
    t45 = (t32 + 4);
    t46 = (t40 + 4);
    t47 = *((unsigned int *)t44);
    t48 = *((unsigned int *)t45);
    t49 = (t47 | t48);
    *((unsigned int *)t46) = t49;
    t50 = *((unsigned int *)t46);
    t51 = (t50 != 0);
    if (t51 == 1)
        goto LAB26;

LAB27:
LAB28:    goto LAB21;

LAB22:    *((unsigned int *)t32) = 1;
    goto LAB25;

LAB24:    t39 = (t32 + 4);
    *((unsigned int *)t32) = 1;
    *((unsigned int *)t39) = 1;
    goto LAB25;

LAB26:    t52 = *((unsigned int *)t40);
    t53 = *((unsigned int *)t46);
    *((unsigned int *)t40) = (t52 | t53);
    t54 = (t15 + 4);
    t55 = (t32 + 4);
    t56 = *((unsigned int *)t15);
    t57 = (~(t56));
    t58 = *((unsigned int *)t54);
    t59 = (~(t58));
    t60 = *((unsigned int *)t32);
    t61 = (~(t60));
    t62 = *((unsigned int *)t55);
    t63 = (~(t62));
    t64 = (t57 & t59);
    t65 = (t61 & t63);
    t66 = (~(t64));
    t67 = (~(t65));
    t68 = *((unsigned int *)t46);
    *((unsigned int *)t46) = (t68 & t66);
    t69 = *((unsigned int *)t46);
    *((unsigned int *)t46) = (t69 & t67);
    t70 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t70 & t66);
    t71 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t71 & t67);
    goto LAB28;

LAB29:    *((unsigned int *)t72) = 1;
    goto LAB32;

LAB31:    t79 = (t72 + 4);
    *((unsigned int *)t72) = 1;
    *((unsigned int *)t79) = 1;
    goto LAB32;

LAB33:    t84 = (t1 + 23476);
    t85 = *((char **)t84);
    t86 = ((((char*)(t85))) + 40U);
    t87 = *((char **)t86);
    t86 = (t1 + 9368);
    t88 = (t86 + 56U);
    t89 = *((char **)t88);
    memset(t90, 0, 8);
    t91 = (t87 + 4);
    t92 = (t89 + 4);
    t93 = *((unsigned int *)t87);
    t94 = *((unsigned int *)t89);
    t95 = (t93 ^ t94);
    t96 = *((unsigned int *)t91);
    t97 = *((unsigned int *)t92);
    t98 = (t96 ^ t97);
    t99 = (t95 | t98);
    t100 = *((unsigned int *)t91);
    t101 = *((unsigned int *)t92);
    t102 = (t100 | t101);
    t103 = (~(t102));
    t104 = (t99 & t103);
    if (t104 != 0)
        goto LAB39;

LAB36:    if (t102 != 0)
        goto LAB38;

LAB37:    *((unsigned int *)t90) = 1;

LAB39:    memset(t106, 0, 8);
    t107 = (t90 + 4);
    t108 = *((unsigned int *)t107);
    t109 = (~(t108));
    t110 = *((unsigned int *)t90);
    t111 = (t110 & t109);
    t112 = (t111 & 1U);
    if (t112 != 0)
        goto LAB40;

LAB41:    if (*((unsigned int *)t107) != 0)
        goto LAB42;

LAB43:    t115 = *((unsigned int *)t72);
    t116 = *((unsigned int *)t106);
    t117 = (t115 & t116);
    *((unsigned int *)t114) = t117;
    t118 = (t72 + 4);
    t119 = (t106 + 4);
    t120 = (t114 + 4);
    t121 = *((unsigned int *)t118);
    t122 = *((unsigned int *)t119);
    t123 = (t121 | t122);
    *((unsigned int *)t120) = t123;
    t124 = *((unsigned int *)t120);
    t125 = (t124 != 0);
    if (t125 == 1)
        goto LAB44;

LAB45:
LAB46:    goto LAB35;

LAB38:    t105 = (t90 + 4);
    *((unsigned int *)t90) = 1;
    *((unsigned int *)t105) = 1;
    goto LAB39;

LAB40:    *((unsigned int *)t106) = 1;
    goto LAB43;

LAB42:    t113 = (t106 + 4);
    *((unsigned int *)t106) = 1;
    *((unsigned int *)t113) = 1;
    goto LAB43;

LAB44:    t126 = *((unsigned int *)t114);
    t127 = *((unsigned int *)t120);
    *((unsigned int *)t114) = (t126 | t127);
    t128 = (t72 + 4);
    t129 = (t106 + 4);
    t130 = *((unsigned int *)t72);
    t131 = (~(t130));
    t132 = *((unsigned int *)t128);
    t133 = (~(t132));
    t134 = *((unsigned int *)t106);
    t135 = (~(t134));
    t136 = *((unsigned int *)t129);
    t137 = (~(t136));
    t138 = (t131 & t133);
    t139 = (t135 & t137);
    t140 = (~(t138));
    t141 = (~(t139));
    t142 = *((unsigned int *)t120);
    *((unsigned int *)t120) = (t142 & t140);
    t143 = *((unsigned int *)t120);
    *((unsigned int *)t120) = (t143 & t141);
    t144 = *((unsigned int *)t114);
    *((unsigned int *)t114) = (t144 & t140);
    t145 = *((unsigned int *)t114);
    *((unsigned int *)t114) = (t145 & t141);
    goto LAB46;

LAB47:    xsi_set_current_line(11, ng0);

LAB50:    xsi_set_current_line(12, ng0);
    t152 = ((char*)((ng2)));
    t153 = (t1 + 9048);
    xsi_vlogvar_assign_value(t153, t152, 0, 0, 1);
    xsi_set_current_line(13, ng0);
    t3 = (t1 + 23508);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 23540);
    t9 = *((char **)t5);
    t11 = ((((char*)(t9))) + 40U);
    t12 = *((char **)t11);
    t11 = (t1 + 848);
    xsi_vlogfile_write(1, 0, 0, ng6, 3, t11, (char)118, t8, 5, (char)118, t12, 12);
    goto LAB49;

LAB54:    t22 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t22) = 1;
    goto LAB55;

LAB56:    *((unsigned int *)t15) = 1;
    goto LAB59;

LAB58:    t27 = (t15 + 4);
    *((unsigned int *)t15) = 1;
    *((unsigned int *)t27) = 1;
    goto LAB59;

LAB60:    t29 = (t1 + 23676);
    t30 = *((char **)t29);
    t33 = ((((char*)(t30))) + 40U);
    t39 = *((char **)t33);
    t33 = (t1 + 23708);
    t44 = *((char **)t33);
    t45 = ((((char*)(t44))) + 72U);
    t46 = *((char **)t45);
    t54 = ((char*)((ng4)));
    xsi_vlog_generic_get_index_select_value(t32, 1, t39, t46, 2, t54, 32, 1);
    memset(t40, 0, 8);
    t55 = (t32 + 4);
    t51 = *((unsigned int *)t55);
    t52 = (~(t51));
    t53 = *((unsigned int *)t32);
    t56 = (t53 & t52);
    t57 = (t56 & 1U);
    if (t57 != 0)
        goto LAB63;

LAB64:    if (*((unsigned int *)t55) != 0)
        goto LAB65;

LAB66:    t58 = *((unsigned int *)t15);
    t59 = *((unsigned int *)t40);
    t60 = (t58 & t59);
    *((unsigned int *)t72) = t60;
    t79 = (t15 + 4);
    t80 = (t40 + 4);
    t84 = (t72 + 4);
    t61 = *((unsigned int *)t79);
    t62 = *((unsigned int *)t80);
    t63 = (t61 | t62);
    *((unsigned int *)t84) = t63;
    t66 = *((unsigned int *)t84);
    t67 = (t66 != 0);
    if (t67 == 1)
        goto LAB67;

LAB68:
LAB69:    goto LAB62;

LAB63:    *((unsigned int *)t40) = 1;
    goto LAB66;

LAB65:    t73 = (t40 + 4);
    *((unsigned int *)t40) = 1;
    *((unsigned int *)t73) = 1;
    goto LAB66;

LAB67:    t68 = *((unsigned int *)t72);
    t69 = *((unsigned int *)t84);
    *((unsigned int *)t72) = (t68 | t69);
    t85 = (t15 + 4);
    t86 = (t40 + 4);
    t70 = *((unsigned int *)t15);
    t71 = (~(t70));
    t74 = *((unsigned int *)t85);
    t75 = (~(t74));
    t76 = *((unsigned int *)t40);
    t77 = (~(t76));
    t78 = *((unsigned int *)t86);
    t81 = (~(t78));
    t64 = (t71 & t75);
    t65 = (t77 & t81);
    t82 = (~(t64));
    t83 = (~(t65));
    t93 = *((unsigned int *)t84);
    *((unsigned int *)t84) = (t93 & t82);
    t94 = *((unsigned int *)t84);
    *((unsigned int *)t84) = (t94 & t83);
    t95 = *((unsigned int *)t72);
    *((unsigned int *)t72) = (t95 & t82);
    t96 = *((unsigned int *)t72);
    *((unsigned int *)t72) = (t96 & t83);
    goto LAB69;

LAB70:    *((unsigned int *)t90) = 1;
    goto LAB73;

LAB72:    t88 = (t90 + 4);
    *((unsigned int *)t90) = 1;
    *((unsigned int *)t88) = 1;
    goto LAB73;

LAB74:    t91 = (t1 + 23732);
    t92 = *((char **)t91);
    t105 = ((((char*)(t92))) + 40U);
    t107 = *((char **)t105);
    t105 = (t1 + 9208);
    t113 = (t105 + 56U);
    t118 = *((char **)t113);
    memset(t106, 0, 8);
    t119 = (t107 + 4);
    t120 = (t118 + 4);
    t108 = *((unsigned int *)t107);
    t109 = *((unsigned int *)t118);
    t110 = (t108 ^ t109);
    t111 = *((unsigned int *)t119);
    t112 = *((unsigned int *)t120);
    t115 = (t111 ^ t112);
    t116 = (t110 | t115);
    t117 = *((unsigned int *)t119);
    t121 = *((unsigned int *)t120);
    t122 = (t117 | t121);
    t123 = (~(t122));
    t124 = (t116 & t123);
    if (t124 != 0)
        goto LAB80;

LAB77:    if (t122 != 0)
        goto LAB79;

LAB78:    *((unsigned int *)t106) = 1;

LAB80:    memset(t114, 0, 8);
    t129 = (t106 + 4);
    t125 = *((unsigned int *)t129);
    t126 = (~(t125));
    t127 = *((unsigned int *)t106);
    t130 = (t127 & t126);
    t131 = (t130 & 1U);
    if (t131 != 0)
        goto LAB81;

LAB82:    if (*((unsigned int *)t129) != 0)
        goto LAB83;

LAB84:    t132 = *((unsigned int *)t90);
    t133 = *((unsigned int *)t114);
    t134 = (t132 & t133);
    *((unsigned int *)t154) = t134;
    t152 = (t90 + 4);
    t153 = (t114 + 4);
    t155 = (t154 + 4);
    t135 = *((unsigned int *)t152);
    t136 = *((unsigned int *)t153);
    t137 = (t135 | t136);
    *((unsigned int *)t155) = t137;
    t140 = *((unsigned int *)t155);
    t141 = (t140 != 0);
    if (t141 == 1)
        goto LAB85;

LAB86:
LAB87:    goto LAB76;

LAB79:    t128 = (t106 + 4);
    *((unsigned int *)t106) = 1;
    *((unsigned int *)t128) = 1;
    goto LAB80;

LAB81:    *((unsigned int *)t114) = 1;
    goto LAB84;

LAB83:    t146 = (t114 + 4);
    *((unsigned int *)t114) = 1;
    *((unsigned int *)t146) = 1;
    goto LAB84;

LAB85:    t142 = *((unsigned int *)t154);
    t143 = *((unsigned int *)t155);
    *((unsigned int *)t154) = (t142 | t143);
    t156 = (t90 + 4);
    t157 = (t114 + 4);
    t144 = *((unsigned int *)t90);
    t145 = (~(t144));
    t147 = *((unsigned int *)t156);
    t148 = (~(t147));
    t149 = *((unsigned int *)t114);
    t150 = (~(t149));
    t151 = *((unsigned int *)t157);
    t158 = (~(t151));
    t138 = (t145 & t148);
    t139 = (t150 & t158);
    t159 = (~(t138));
    t160 = (~(t139));
    t161 = *((unsigned int *)t155);
    *((unsigned int *)t155) = (t161 & t159);
    t162 = *((unsigned int *)t155);
    *((unsigned int *)t155) = (t162 & t160);
    t163 = *((unsigned int *)t154);
    *((unsigned int *)t154) = (t163 & t159);
    t164 = *((unsigned int *)t154);
    *((unsigned int *)t154) = (t164 & t160);
    goto LAB87;

LAB88:    xsi_set_current_line(26, ng0);

LAB91:    xsi_set_current_line(27, ng0);
    t171 = ((char*)((ng2)));
    t172 = (t1 + 9048);
    xsi_vlogvar_assign_value(t172, t171, 0, 0, 1);
    xsi_set_current_line(28, ng0);
    t3 = (t1 + 23756);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 23788);
    t9 = *((char **)t5);
    t11 = ((((char*)(t9))) + 40U);
    t12 = *((char **)t11);
    t11 = (t1 + 23812);
    t13 = *((char **)t11);
    t14 = ((((char*)(t13))) + 40U);
    t16 = *((char **)t14);
    t14 = (t1 + 9368);
    t22 = (t14 + 56U);
    t23 = *((char **)t22);
    t27 = (t1 + 848);
    xsi_vlogfile_write(1, 0, 0, ng11, 5, t27, (char)118, t8, 5, (char)118, t12, 12, (char)118, t16, 5, (char)119, t23, 32);
    goto LAB90;

}

static int sp_TEST_IN(char *t1, char *t2)
{
    char t10[8];
    char t11[16];
    char t28[8];
    int t0;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    int t7;
    char *t8;
    char *t9;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;
    char *t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    char *t25;
    char *t26;
    char *t27;
    char *t29;
    char *t30;
    char *t31;

LAB0:    t0 = 1;
    xsi_set_current_line(4, ng13);

LAB2:    xsi_set_current_line(5, ng13);
    t3 = (t1 + 23884);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t6 = *((char **)t5);

LAB3:    t5 = ((char*)((ng1)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t5, 32);
    if (t7 == 1)
        goto LAB4;

LAB5:    t3 = ((char*)((ng3)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB6;

LAB7:    t3 = ((char*)((ng9)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB8;

LAB9:    t3 = ((char*)((ng10)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB10;

LAB11:    t3 = ((char*)((ng4)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB12;

LAB13:
LAB14:    t0 = 0;

LAB1:    return t0;
LAB4:    xsi_set_current_line(7, ng13);
    t8 = ((char*)((ng2)));
    t9 = (t1 + 9528);
    xsi_vlogvar_assign_value(t9, t8, 0, 0, 1);
    goto LAB14;

LAB6:    xsi_set_current_line(9, ng13);
    t4 = (t1 + 23916);
    t5 = *((char **)t4);
    t8 = ((((char*)(t5))) + 40U);
    t9 = *((char **)t8);
    t8 = ((char*)((ng14)));
    xsi_vlog_unsigned_case_eq(t11, 62, t9, 62, t8, 32);
    memset(t10, 0, 8);
    t12 = (t11 + 4);
    t13 = *((unsigned int *)t12);
    t14 = (~(t13));
    t15 = *((unsigned int *)t11);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB18;

LAB16:    if (*((unsigned int *)t12) == 0)
        goto LAB15;

LAB17:    t18 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t18) = 1;

LAB18:    t19 = (t10 + 4);
    t20 = *((unsigned int *)t19);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB19;

LAB20:    xsi_set_current_line(16, ng13);
    t3 = (t1 + 23980);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 9848);
    t9 = (t5 + 56U);
    t12 = *((char **)t9);
    memset(t28, 0, 8);
    if (*((unsigned int *)t8) != *((unsigned int *)t12))
        goto LAB25;

LAB23:    t18 = (t8 + 4);
    t19 = (t12 + 4);
    if (*((unsigned int *)t18) != *((unsigned int *)t19))
        goto LAB25;

LAB24:    *((unsigned int *)t28) = 1;

LAB25:    memset(t10, 0, 8);
    t25 = (t28 + 4);
    t13 = *((unsigned int *)t25);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB29;

LAB27:    if (*((unsigned int *)t25) == 0)
        goto LAB26;

LAB28:    t26 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t26) = 1;

LAB29:    t27 = (t10 + 4);
    t20 = *((unsigned int *)t27);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB30;

LAB31:    xsi_set_current_line(23, ng13);
    t3 = (t1 + 24044);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 9688);
    t9 = (t5 + 56U);
    t12 = *((char **)t9);
    memset(t28, 0, 8);
    if (*((unsigned int *)t8) != *((unsigned int *)t12))
        goto LAB36;

LAB34:    t18 = (t8 + 4);
    t19 = (t12 + 4);
    if (*((unsigned int *)t18) != *((unsigned int *)t19))
        goto LAB36;

LAB35:    *((unsigned int *)t28) = 1;

LAB36:    memset(t10, 0, 8);
    t25 = (t28 + 4);
    t13 = *((unsigned int *)t25);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB40;

LAB38:    if (*((unsigned int *)t25) == 0)
        goto LAB37;

LAB39:    t26 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t26) = 1;

LAB40:    t27 = (t10 + 4);
    t20 = *((unsigned int *)t27);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB41;

LAB42:    xsi_set_current_line(30, ng13);
    t3 = (t1 + 24116);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 24156);
    t9 = *((char **)t5);
    t12 = ((((char*)(t9))) + 72U);
    t18 = *((char **)t12);
    t19 = ((char*)((ng19)));
    xsi_vlog_generic_get_index_select_value(t28, 1, t8, t18, 2, t19, 32, 1);
    memset(t10, 0, 8);
    t25 = (t28 + 4);
    t13 = *((unsigned int *)t25);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB48;

LAB46:    if (*((unsigned int *)t25) == 0)
        goto LAB45;

LAB47:    t26 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t26) = 1;

LAB48:    t27 = (t10 + 4);
    t20 = *((unsigned int *)t27);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB49;

LAB50:    xsi_set_current_line(35, ng13);
    t3 = (t1 + 24188);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 24220);
    t9 = *((char **)t5);
    t12 = ((((char*)(t9))) + 72U);
    t18 = *((char **)t12);
    t19 = ((char*)((ng21)));
    xsi_vlog_generic_get_index_select_value(t28, 1, t8, t18, 2, t19, 32, 1);
    memset(t10, 0, 8);
    t25 = (t28 + 4);
    t13 = *((unsigned int *)t25);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB56;

LAB54:    if (*((unsigned int *)t25) == 0)
        goto LAB53;

LAB55:    t26 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t26) = 1;

LAB56:    t27 = (t10 + 4);
    t20 = *((unsigned int *)t27);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB57;

LAB58:    xsi_set_current_line(40, ng13);
    t3 = (t1 + 24260);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 56U);
    t8 = *((char **)t5);
    t9 = (t1 + 9688);
    t12 = (t9 + 56U);
    t18 = *((char **)t12);
    memset(t28, 0, 8);
    if (*((unsigned int *)t8) != *((unsigned int *)t18))
        goto LAB63;

LAB61:    t19 = (t8 + 4);
    t25 = (t18 + 4);
    if (*((unsigned int *)t19) != *((unsigned int *)t25))
        goto LAB63;

LAB62:    *((unsigned int *)t28) = 1;

LAB63:    memset(t10, 0, 8);
    t26 = (t28 + 4);
    t13 = *((unsigned int *)t26);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB67;

LAB65:    if (*((unsigned int *)t26) == 0)
        goto LAB64;

LAB66:    t27 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t27) = 1;

LAB67:    t29 = (t10 + 4);
    t20 = *((unsigned int *)t29);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB68;

LAB69:    xsi_set_current_line(47, ng13);

LAB72:    xsi_set_current_line(48, ng13);
    t3 = ((char*)((ng2)));
    t4 = (t1 + 9528);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(49, ng13);
    t3 = (t1 + 9848);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 9688);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 1280);
    xsi_vlogfile_write(1, 0, 0, ng24, 3, t18, (char)119, t5, 32, (char)119, t12, 32);

LAB70:
LAB59:
LAB51:
LAB43:
LAB32:
LAB21:    goto LAB14;

LAB8:    xsi_set_current_line(52, ng13);
    t4 = ((char*)((ng2)));
    t5 = (t1 + 9528);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 1);
    goto LAB14;

LAB10:    xsi_set_current_line(54, ng13);
    t4 = ((char*)((ng2)));
    t5 = (t1 + 9528);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 1);
    goto LAB14;

LAB12:    xsi_set_current_line(56, ng13);
    t4 = (t1 + 24332);
    t5 = *((char **)t4);
    t8 = ((((char*)(t5))) + 40U);
    t9 = *((char **)t8);
    t8 = (t1 + 24364);
    t12 = *((char **)t8);
    t18 = ((((char*)(t12))) + 72U);
    t19 = *((char **)t18);
    t25 = ((char*)((ng4)));
    xsi_vlog_generic_get_index_select_value(t28, 1, t9, t19, 2, t25, 32, 1);
    memset(t10, 0, 8);
    t26 = (t28 + 4);
    t13 = *((unsigned int *)t26);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB76;

LAB74:    if (*((unsigned int *)t26) == 0)
        goto LAB73;

LAB75:    t27 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t27) = 1;

LAB76:    t29 = (t10 + 4);
    t20 = *((unsigned int *)t29);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB77;

LAB78:    xsi_set_current_line(61, ng13);
    t3 = (t1 + 24404);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 56U);
    t8 = *((char **)t5);
    t9 = (t1 + 24436);
    t12 = *((char **)t9);
    t18 = ((((char*)(t12))) + 40U);
    t19 = *((char **)t18);
    memset(t28, 0, 8);
    if (*((unsigned int *)t8) != *((unsigned int *)t19))
        goto LAB83;

LAB81:    t18 = (t8 + 4);
    t25 = (t19 + 4);
    if (*((unsigned int *)t18) != *((unsigned int *)t25))
        goto LAB83;

LAB82:    *((unsigned int *)t28) = 1;

LAB83:    memset(t10, 0, 8);
    t26 = (t28 + 4);
    t13 = *((unsigned int *)t26);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB87;

LAB85:    if (*((unsigned int *)t26) == 0)
        goto LAB84;

LAB86:    t27 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t27) = 1;

LAB87:    t29 = (t10 + 4);
    t20 = *((unsigned int *)t29);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB88;

LAB89:    xsi_set_current_line(68, ng13);

LAB92:    xsi_set_current_line(69, ng13);
    t3 = ((char*)((ng2)));
    t4 = (t1 + 9528);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(70, ng13);
    t3 = (t1 + 9848);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 9688);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 1280);
    xsi_vlogfile_write(1, 0, 0, ng27, 3, t18, (char)119, t5, 32, (char)119, t12, 32);

LAB90:
LAB79:    goto LAB14;

LAB15:    *((unsigned int *)t10) = 1;
    goto LAB18;

LAB19:    xsi_set_current_line(9, ng13);

LAB22:    xsi_set_current_line(10, ng13);
    t25 = ((char*)((ng7)));
    t26 = (t1 + 9528);
    xsi_vlogvar_assign_value(t26, t25, 0, 0, 1);
    xsi_set_current_line(11, ng13);
    t3 = (t1 + 9848);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 9688);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = ((char*)((ng16)));
    t19 = (t1 + 23948);
    t25 = *((char **)t19);
    t26 = ((((char*)(t25))) + 40U);
    t27 = *((char **)t26);
    t26 = (t1 + 1280);
    xsi_vlogfile_write(1, 0, 0, ng15, 5, t26, (char)119, t5, 32, (char)119, t12, 32, (char)119, t18, 32, (char)118, t27, 62);
    goto LAB21;

LAB26:    *((unsigned int *)t10) = 1;
    goto LAB29;

LAB30:    xsi_set_current_line(16, ng13);

LAB33:    xsi_set_current_line(17, ng13);
    t29 = ((char*)((ng7)));
    t30 = (t1 + 9528);
    xsi_vlogvar_assign_value(t30, t29, 0, 0, 1);
    xsi_set_current_line(18, ng13);
    t3 = (t1 + 9848);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 9688);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 9848);
    t19 = (t18 + 56U);
    t25 = *((char **)t19);
    t26 = (t1 + 24012);
    t27 = *((char **)t26);
    t29 = ((((char*)(t27))) + 40U);
    t30 = *((char **)t29);
    t29 = (t1 + 1280);
    xsi_vlogfile_write(1, 0, 0, ng17, 5, t29, (char)119, t5, 32, (char)119, t12, 32, (char)119, t25, 32, (char)118, t30, 5);
    goto LAB32;

LAB37:    *((unsigned int *)t10) = 1;
    goto LAB40;

LAB41:    xsi_set_current_line(23, ng13);

LAB44:    xsi_set_current_line(24, ng13);
    t29 = ((char*)((ng7)));
    t30 = (t1 + 9528);
    xsi_vlogvar_assign_value(t30, t29, 0, 0, 1);
    xsi_set_current_line(25, ng13);
    t3 = (t1 + 9848);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 9688);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 9688);
    t19 = (t18 + 56U);
    t25 = *((char **)t19);
    t26 = (t1 + 24076);
    t27 = *((char **)t26);
    t29 = ((((char*)(t27))) + 40U);
    t30 = *((char **)t29);
    t29 = (t1 + 1280);
    xsi_vlogfile_write(1, 0, 0, ng18, 5, t29, (char)119, t5, 32, (char)119, t12, 32, (char)119, t25, 32, (char)118, t30, 12);
    goto LAB43;

LAB45:    *((unsigned int *)t10) = 1;
    goto LAB48;

LAB49:    xsi_set_current_line(30, ng13);

LAB52:    xsi_set_current_line(31, ng13);
    t29 = ((char*)((ng7)));
    t30 = (t1 + 9528);
    xsi_vlogvar_assign_value(t30, t29, 0, 0, 1);
    xsi_set_current_line(32, ng13);
    t3 = (t1 + 9848);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 9688);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 1280);
    xsi_vlogfile_write(1, 0, 0, ng20, 3, t18, (char)119, t5, 32, (char)119, t12, 32);
    goto LAB51;

LAB53:    *((unsigned int *)t10) = 1;
    goto LAB56;

LAB57:    xsi_set_current_line(35, ng13);

LAB60:    xsi_set_current_line(36, ng13);
    t29 = ((char*)((ng7)));
    t30 = (t1 + 9528);
    xsi_vlogvar_assign_value(t30, t29, 0, 0, 1);
    xsi_set_current_line(37, ng13);
    t3 = (t1 + 9848);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 9688);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 1280);
    xsi_vlogfile_write(1, 0, 0, ng22, 3, t18, (char)119, t5, 32, (char)119, t12, 32);
    goto LAB59;

LAB64:    *((unsigned int *)t10) = 1;
    goto LAB67;

LAB68:    xsi_set_current_line(40, ng13);

LAB71:    xsi_set_current_line(41, ng13);
    t30 = ((char*)((ng7)));
    t31 = (t1 + 9528);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 1);
    xsi_set_current_line(42, ng13);
    t3 = (t1 + 9848);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 9688);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 9688);
    t19 = (t18 + 56U);
    t25 = *((char **)t19);
    t26 = (t1 + 24300);
    t27 = *((char **)t26);
    t29 = ((((char*)(t27))) + 56U);
    t30 = *((char **)t29);
    t31 = (t1 + 1280);
    xsi_vlogfile_write(1, 0, 0, ng23, 5, t31, (char)119, t5, 32, (char)119, t12, 32, (char)119, t25, 32, (char)118, t30, 16);
    goto LAB70;

LAB73:    *((unsigned int *)t10) = 1;
    goto LAB76;

LAB77:    xsi_set_current_line(56, ng13);

LAB80:    xsi_set_current_line(57, ng13);
    t30 = ((char*)((ng7)));
    t31 = (t1 + 9528);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 1);
    xsi_set_current_line(58, ng13);
    t3 = (t1 + 9848);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 9688);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 1280);
    xsi_vlogfile_write(1, 0, 0, ng25, 3, t18, (char)119, t5, 32, (char)119, t12, 32);
    goto LAB79;

LAB84:    *((unsigned int *)t10) = 1;
    goto LAB87;

LAB88:    xsi_set_current_line(61, ng13);

LAB91:    xsi_set_current_line(62, ng13);
    t30 = ((char*)((ng7)));
    t31 = (t1 + 9528);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 1);
    xsi_set_current_line(63, ng13);
    t3 = (t1 + 9848);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 9688);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 24468);
    t19 = *((char **)t18);
    t25 = ((((char*)(t19))) + 40U);
    t26 = *((char **)t25);
    t25 = (t1 + 24508);
    t27 = *((char **)t25);
    t29 = ((((char*)(t27))) + 56U);
    t30 = *((char **)t29);
    t31 = (t1 + 1280);
    xsi_vlogfile_write(1, 0, 0, ng26, 5, t31, (char)119, t5, 32, (char)119, t12, 32, (char)118, t26, 8, (char)118, t30, 8);
    goto LAB90;

}

static int sp_TEST_OUT(char *t1, char *t2)
{
    char t10[8];
    char t11[16];
    char t28[8];
    int t0;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    int t7;
    char *t8;
    char *t9;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;
    char *t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    char *t25;
    char *t26;
    char *t27;
    char *t29;
    char *t30;
    char *t31;

LAB0:    t0 = 1;
    xsi_set_current_line(5, ng28);

LAB2:    xsi_set_current_line(6, ng28);
    t3 = (t1 + 24540);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t6 = *((char **)t5);

LAB3:    t5 = ((char*)((ng1)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t5, 32);
    if (t7 == 1)
        goto LAB4;

LAB5:    t3 = ((char*)((ng3)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB6;

LAB7:    t3 = ((char*)((ng9)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB8;

LAB9:    t3 = ((char*)((ng10)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB10;

LAB11:    t3 = ((char*)((ng4)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB12;

LAB13:
LAB14:    t0 = 0;

LAB1:    return t0;
LAB4:    xsi_set_current_line(7, ng28);
    t8 = ((char*)((ng2)));
    t9 = (t1 + 10008);
    xsi_vlogvar_assign_value(t9, t8, 0, 0, 1);
    goto LAB14;

LAB6:    xsi_set_current_line(9, ng28);
    t4 = (t1 + 24572);
    t5 = *((char **)t4);
    t8 = ((((char*)(t5))) + 40U);
    t9 = *((char **)t8);
    t8 = ((char*)((ng29)));
    xsi_vlog_unsigned_case_eq(t11, 62, t9, 62, t8, 32);
    memset(t10, 0, 8);
    t12 = (t11 + 4);
    t13 = *((unsigned int *)t12);
    t14 = (~(t13));
    t15 = *((unsigned int *)t11);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB18;

LAB16:    if (*((unsigned int *)t12) == 0)
        goto LAB15;

LAB17:    t18 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t18) = 1;

LAB18:    t19 = (t10 + 4);
    t20 = *((unsigned int *)t19);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB19;

LAB20:    xsi_set_current_line(16, ng28);
    t3 = (t1 + 24636);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 10328);
    t9 = (t5 + 56U);
    t12 = *((char **)t9);
    memset(t28, 0, 8);
    if (*((unsigned int *)t8) != *((unsigned int *)t12))
        goto LAB25;

LAB23:    t18 = (t8 + 4);
    t19 = (t12 + 4);
    if (*((unsigned int *)t18) != *((unsigned int *)t19))
        goto LAB25;

LAB24:    *((unsigned int *)t28) = 1;

LAB25:    memset(t10, 0, 8);
    t25 = (t28 + 4);
    t13 = *((unsigned int *)t25);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB29;

LAB27:    if (*((unsigned int *)t25) == 0)
        goto LAB26;

LAB28:    t26 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t26) = 1;

LAB29:    t27 = (t10 + 4);
    t20 = *((unsigned int *)t27);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB30;

LAB31:    xsi_set_current_line(23, ng28);
    t3 = (t1 + 24700);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 10168);
    t9 = (t5 + 56U);
    t12 = *((char **)t9);
    memset(t28, 0, 8);
    if (*((unsigned int *)t8) != *((unsigned int *)t12))
        goto LAB36;

LAB34:    t18 = (t8 + 4);
    t19 = (t12 + 4);
    if (*((unsigned int *)t18) != *((unsigned int *)t19))
        goto LAB36;

LAB35:    *((unsigned int *)t28) = 1;

LAB36:    memset(t10, 0, 8);
    t25 = (t28 + 4);
    t13 = *((unsigned int *)t25);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB40;

LAB38:    if (*((unsigned int *)t25) == 0)
        goto LAB37;

LAB39:    t26 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t26) = 1;

LAB40:    t27 = (t10 + 4);
    t20 = *((unsigned int *)t27);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB41;

LAB42:    xsi_set_current_line(30, ng28);
    t3 = (t1 + 24772);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 24812);
    t9 = *((char **)t5);
    t12 = ((((char*)(t9))) + 72U);
    t18 = *((char **)t12);
    t19 = ((char*)((ng34)));
    xsi_vlog_generic_get_index_select_value(t28, 1, t8, t18, 2, t19, 32, 1);
    memset(t10, 0, 8);
    t25 = (t28 + 4);
    t13 = *((unsigned int *)t25);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB48;

LAB46:    if (*((unsigned int *)t25) == 0)
        goto LAB45;

LAB47:    t26 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t26) = 1;

LAB48:    t27 = (t10 + 4);
    t20 = *((unsigned int *)t27);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB49;

LAB50:    xsi_set_current_line(35, ng28);
    t3 = (t1 + 24868);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 24900);
    t9 = *((char **)t5);
    t12 = ((((char*)(t9))) + 72U);
    t18 = *((char **)t12);
    t19 = ((char*)((ng3)));
    xsi_vlog_generic_get_index_select_value(t28, 1, t8, t18, 2, t19, 32, 1);
    memset(t10, 0, 8);
    t25 = (t28 + 4);
    t13 = *((unsigned int *)t25);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB56;

LAB54:    if (*((unsigned int *)t25) == 0)
        goto LAB53;

LAB55:    t26 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t26) = 1;

LAB56:    t27 = (t10 + 4);
    t20 = *((unsigned int *)t27);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB57;

LAB58:    xsi_set_current_line(40, ng28);
    t3 = (t1 + 24940);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 56U);
    t8 = *((char **)t5);
    t9 = (t1 + 10168);
    t12 = (t9 + 56U);
    t18 = *((char **)t12);
    memset(t28, 0, 8);
    if (*((unsigned int *)t8) != *((unsigned int *)t18))
        goto LAB63;

LAB61:    t19 = (t8 + 4);
    t25 = (t18 + 4);
    if (*((unsigned int *)t19) != *((unsigned int *)t25))
        goto LAB63;

LAB62:    *((unsigned int *)t28) = 1;

LAB63:    memset(t10, 0, 8);
    t26 = (t28 + 4);
    t13 = *((unsigned int *)t26);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB67;

LAB65:    if (*((unsigned int *)t26) == 0)
        goto LAB64;

LAB66:    t27 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t27) = 1;

LAB67:    t29 = (t10 + 4);
    t20 = *((unsigned int *)t29);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB68;

LAB69:    xsi_set_current_line(47, ng28);

LAB72:    xsi_set_current_line(48, ng28);
    t3 = ((char*)((ng2)));
    t4 = (t1 + 10008);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(49, ng28);
    t3 = (t1 + 10168);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10328);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 1712);
    xsi_vlogfile_write(0, 0, 0, ng38, 3, t18, (char)119, t5, 32, (char)119, t12, 32);
    t19 = (t1 + 1712);
    xsi_vlogfile_write(1, 0, 0, ng39, 1, t19);

LAB70:
LAB59:
LAB51:
LAB43:
LAB32:
LAB21:    goto LAB14;

LAB8:    xsi_set_current_line(51, ng28);
    t4 = ((char*)((ng2)));
    t5 = (t1 + 10008);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 1);
    goto LAB14;

LAB10:    xsi_set_current_line(52, ng28);
    t4 = ((char*)((ng2)));
    t5 = (t1 + 10008);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 1);
    goto LAB14;

LAB12:    xsi_set_current_line(54, ng28);
    t4 = (t1 + 25012);
    t5 = *((char **)t4);
    t8 = ((((char*)(t5))) + 40U);
    t9 = *((char **)t8);
    t8 = (t1 + 25044);
    t12 = *((char **)t8);
    t18 = ((((char*)(t12))) + 72U);
    t19 = *((char **)t18);
    t25 = ((char*)((ng40)));
    xsi_vlog_generic_get_index_select_value(t28, 1, t9, t19, 2, t25, 32, 1);
    memset(t10, 0, 8);
    t26 = (t28 + 4);
    t13 = *((unsigned int *)t26);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB76;

LAB74:    if (*((unsigned int *)t26) == 0)
        goto LAB73;

LAB75:    t27 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t27) = 1;

LAB76:    t29 = (t10 + 4);
    t20 = *((unsigned int *)t29);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB77;

LAB78:    xsi_set_current_line(58, ng28);

LAB81:    xsi_set_current_line(59, ng28);
    t3 = ((char*)((ng2)));
    t4 = (t1 + 10008);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(60, ng28);
    t3 = (t1 + 10168);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10328);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 1712);
    xsi_vlogfile_write(1, 0, 0, ng42, 3, t18, (char)119, t5, 32, (char)119, t12, 32);

LAB79:    goto LAB14;

LAB15:    *((unsigned int *)t10) = 1;
    goto LAB18;

LAB19:    xsi_set_current_line(9, ng28);

LAB22:    xsi_set_current_line(10, ng28);
    t25 = ((char*)((ng7)));
    t26 = (t1 + 10008);
    xsi_vlogvar_assign_value(t26, t25, 0, 0, 1);
    xsi_set_current_line(11, ng28);
    t3 = (t1 + 10168);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10328);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = ((char*)((ng31)));
    t19 = (t1 + 24604);
    t25 = *((char **)t19);
    t26 = ((((char*)(t25))) + 40U);
    t27 = *((char **)t26);
    t26 = (t1 + 1712);
    xsi_vlogfile_write(1, 0, 0, ng30, 5, t26, (char)119, t5, 32, (char)119, t12, 32, (char)119, t18, 32, (char)118, t27, 62);
    goto LAB21;

LAB26:    *((unsigned int *)t10) = 1;
    goto LAB29;

LAB30:    xsi_set_current_line(16, ng28);

LAB33:    xsi_set_current_line(17, ng28);
    t29 = ((char*)((ng7)));
    t30 = (t1 + 10008);
    xsi_vlogvar_assign_value(t30, t29, 0, 0, 1);
    xsi_set_current_line(18, ng28);
    t3 = (t1 + 10168);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10328);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 10328);
    t19 = (t18 + 56U);
    t25 = *((char **)t19);
    t26 = (t1 + 24668);
    t27 = *((char **)t26);
    t29 = ((((char*)(t27))) + 40U);
    t30 = *((char **)t29);
    t29 = (t1 + 1712);
    xsi_vlogfile_write(1, 0, 0, ng32, 5, t29, (char)119, t5, 32, (char)119, t12, 32, (char)119, t25, 32, (char)118, t30, 5);
    goto LAB32;

LAB37:    *((unsigned int *)t10) = 1;
    goto LAB40;

LAB41:    xsi_set_current_line(23, ng28);

LAB44:    xsi_set_current_line(24, ng28);
    t29 = ((char*)((ng7)));
    t30 = (t1 + 10008);
    xsi_vlogvar_assign_value(t30, t29, 0, 0, 1);
    xsi_set_current_line(25, ng28);
    t3 = (t1 + 10168);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10328);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 10168);
    t19 = (t18 + 56U);
    t25 = *((char **)t19);
    t26 = (t1 + 24732);
    t27 = *((char **)t26);
    t29 = ((((char*)(t27))) + 40U);
    t30 = *((char **)t29);
    t29 = (t1 + 1712);
    xsi_vlogfile_write(1, 0, 0, ng33, 5, t29, (char)119, t5, 32, (char)119, t12, 32, (char)119, t25, 32, (char)118, t30, 12);
    goto LAB43;

LAB45:    *((unsigned int *)t10) = 1;
    goto LAB48;

LAB49:    xsi_set_current_line(30, ng28);

LAB52:    xsi_set_current_line(31, ng28);
    t29 = ((char*)((ng7)));
    t30 = (t1 + 10008);
    xsi_vlogvar_assign_value(t30, t29, 0, 0, 1);
    xsi_set_current_line(32, ng28);
    t3 = (t1 + 10168);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 24836);
    t9 = *((char **)t8);
    t12 = ((((char*)(t9))) + 40U);
    t18 = *((char **)t12);
    t12 = (t1 + 1712);
    xsi_vlogfile_write(1, 0, 0, ng35, 3, t12, (char)119, t5, 32, (char)118, t18, 5);
    goto LAB51;

LAB53:    *((unsigned int *)t10) = 1;
    goto LAB56;

LAB57:    xsi_set_current_line(35, ng28);

LAB60:    xsi_set_current_line(36, ng28);
    t29 = ((char*)((ng7)));
    t30 = (t1 + 10008);
    xsi_vlogvar_assign_value(t30, t29, 0, 0, 1);
    xsi_set_current_line(37, ng28);
    t3 = (t1 + 10168);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10328);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 1712);
    xsi_vlogfile_write(1, 0, 0, ng36, 3, t18, (char)119, t5, 32, (char)119, t12, 32);
    goto LAB59;

LAB64:    *((unsigned int *)t10) = 1;
    goto LAB67;

LAB68:    xsi_set_current_line(40, ng28);

LAB71:    xsi_set_current_line(41, ng28);
    t30 = ((char*)((ng7)));
    t31 = (t1 + 10008);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 1);
    xsi_set_current_line(42, ng28);
    t3 = (t1 + 10168);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10328);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 10168);
    t19 = (t18 + 56U);
    t25 = *((char **)t19);
    t26 = (t1 + 24980);
    t27 = *((char **)t26);
    t29 = ((((char*)(t27))) + 56U);
    t30 = *((char **)t29);
    t31 = (t1 + 1712);
    xsi_vlogfile_write(1, 0, 0, ng37, 5, t31, (char)119, t5, 32, (char)119, t12, 32, (char)119, t25, 32, (char)118, t30, 16);
    goto LAB70;

LAB73:    *((unsigned int *)t10) = 1;
    goto LAB76;

LAB77:    xsi_set_current_line(54, ng28);

LAB80:    xsi_set_current_line(55, ng28);
    t30 = ((char*)((ng7)));
    t31 = (t1 + 10008);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 1);
    xsi_set_current_line(56, ng28);
    t3 = (t1 + 10168);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10328);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 1712);
    xsi_vlogfile_write(1, 0, 0, ng41, 3, t18, (char)119, t5, 32, (char)119, t12, 32);
    goto LAB79;

}

static int sp_TEST_SBI(char *t1, char *t2)
{
    char t10[8];
    char t11[16];
    char t28[8];
    char t45[8];
    int t0;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    int t7;
    char *t8;
    char *t9;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;
    char *t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    char *t25;
    char *t26;
    char *t27;
    char *t29;
    char *t30;
    char *t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    char *t44;
    char *t46;

LAB0:    t0 = 1;
    xsi_set_current_line(4, ng43);

LAB2:    xsi_set_current_line(5, ng43);
    t3 = (t1 + 25076);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t6 = *((char **)t5);

LAB3:    t5 = ((char*)((ng1)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t5, 32);
    if (t7 == 1)
        goto LAB4;

LAB5:    t3 = ((char*)((ng3)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB6;

LAB7:    t3 = ((char*)((ng9)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB8;

LAB9:    t3 = ((char*)((ng10)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB10;

LAB11:    t3 = ((char*)((ng4)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB12;

LAB13:
LAB14:    t0 = 0;

LAB1:    return t0;
LAB4:    xsi_set_current_line(7, ng43);
    t8 = ((char*)((ng2)));
    t9 = (t1 + 10648);
    xsi_vlogvar_assign_value(t9, t8, 0, 0, 1);
    goto LAB14;

LAB6:    xsi_set_current_line(9, ng43);
    t4 = (t1 + 25108);
    t5 = *((char **)t4);
    t8 = ((((char*)(t5))) + 40U);
    t9 = *((char **)t8);
    t8 = ((char*)((ng44)));
    xsi_vlog_unsigned_case_eq(t11, 62, t9, 62, t8, 32);
    memset(t10, 0, 8);
    t12 = (t11 + 4);
    t13 = *((unsigned int *)t12);
    t14 = (~(t13));
    t15 = *((unsigned int *)t11);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB18;

LAB16:    if (*((unsigned int *)t12) == 0)
        goto LAB15;

LAB17:    t18 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t18) = 1;

LAB18:    t19 = (t10 + 4);
    t20 = *((unsigned int *)t19);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB19;

LAB20:    xsi_set_current_line(17, ng43);
    t3 = (t1 + 25172);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 10968);
    t9 = (t5 + 56U);
    t12 = *((char **)t9);
    memset(t28, 0, 8);
    if (*((unsigned int *)t8) != *((unsigned int *)t12))
        goto LAB25;

LAB23:    t18 = (t8 + 4);
    t19 = (t12 + 4);
    if (*((unsigned int *)t18) != *((unsigned int *)t19))
        goto LAB25;

LAB24:    *((unsigned int *)t28) = 1;

LAB25:    memset(t10, 0, 8);
    t25 = (t28 + 4);
    t13 = *((unsigned int *)t25);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB29;

LAB27:    if (*((unsigned int *)t25) == 0)
        goto LAB26;

LAB28:    t26 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t26) = 1;

LAB29:    t27 = (t10 + 4);
    t20 = *((unsigned int *)t27);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB30;

LAB31:    xsi_set_current_line(25, ng43);
    t3 = (t1 + 25236);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 10808);
    t9 = (t5 + 56U);
    t12 = *((char **)t9);
    memset(t28, 0, 8);
    if (*((unsigned int *)t8) != *((unsigned int *)t12))
        goto LAB36;

LAB34:    t18 = (t8 + 4);
    t19 = (t12 + 4);
    if (*((unsigned int *)t18) != *((unsigned int *)t19))
        goto LAB36;

LAB35:    *((unsigned int *)t28) = 1;

LAB36:    memset(t10, 0, 8);
    t25 = (t28 + 4);
    t13 = *((unsigned int *)t25);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB40;

LAB38:    if (*((unsigned int *)t25) == 0)
        goto LAB37;

LAB39:    t26 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t26) = 1;

LAB40:    t27 = (t10 + 4);
    t20 = *((unsigned int *)t27);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB41;

LAB42:    xsi_set_current_line(33, ng43);
    t3 = (t1 + 25308);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 25348);
    t9 = *((char **)t5);
    t12 = ((((char*)(t9))) + 72U);
    t18 = *((char **)t12);
    t19 = ((char*)((ng19)));
    xsi_vlog_generic_get_index_select_value(t28, 1, t8, t18, 2, t19, 32, 1);
    memset(t10, 0, 8);
    t25 = (t28 + 4);
    t13 = *((unsigned int *)t25);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB48;

LAB46:    if (*((unsigned int *)t25) == 0)
        goto LAB45;

LAB47:    t26 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t26) = 1;

LAB48:    t27 = (t10 + 4);
    t20 = *((unsigned int *)t27);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB49;

LAB50:    xsi_set_current_line(39, ng43);
    t3 = (t1 + 25388);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 25428);
    t9 = *((char **)t5);
    t12 = ((((char*)(t9))) + 72U);
    t18 = *((char **)t12);
    t19 = ((char*)((ng19)));
    xsi_vlog_generic_get_index_select_value(t28, 1, t8, t18, 2, t19, 32, 1);
    memset(t10, 0, 8);
    t25 = (t28 + 4);
    t13 = *((unsigned int *)t25);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB56;

LAB54:    if (*((unsigned int *)t25) == 0)
        goto LAB53;

LAB55:    t26 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t26) = 1;

LAB56:    t27 = (t10 + 4);
    t20 = *((unsigned int *)t27);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB57;

LAB58:    xsi_set_current_line(46, ng43);
    t3 = (t1 + 25468);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 25508);
    t9 = *((char **)t5);
    t12 = ((((char*)(t9))) + 72U);
    t18 = *((char **)t12);
    t19 = ((char*)((ng50)));
    xsi_vlog_generic_get_index_select_value(t28, 1, t8, t18, 2, t19, 32, 1);
    memset(t10, 0, 8);
    t25 = (t28 + 4);
    t13 = *((unsigned int *)t25);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB64;

LAB62:    if (*((unsigned int *)t25) == 0)
        goto LAB61;

LAB63:    t26 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t26) = 1;

LAB64:    t27 = (t10 + 4);
    t20 = *((unsigned int *)t27);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB65;

LAB66:    xsi_set_current_line(51, ng43);
    t3 = (t1 + 25548);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 56U);
    t8 = *((char **)t5);
    t9 = (t1 + 10808);
    t12 = (t9 + 56U);
    t18 = *((char **)t12);
    memset(t28, 0, 8);
    if (*((unsigned int *)t8) != *((unsigned int *)t18))
        goto LAB71;

LAB69:    t19 = (t8 + 4);
    t25 = (t18 + 4);
    if (*((unsigned int *)t19) != *((unsigned int *)t25))
        goto LAB71;

LAB70:    *((unsigned int *)t28) = 1;

LAB71:    memset(t10, 0, 8);
    t26 = (t28 + 4);
    t13 = *((unsigned int *)t26);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB75;

LAB73:    if (*((unsigned int *)t26) == 0)
        goto LAB72;

LAB74:    t27 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t27) = 1;

LAB75:    t29 = (t10 + 4);
    t20 = *((unsigned int *)t29);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB76;

LAB77:    xsi_set_current_line(59, ng43);
    t3 = (t1 + 25620);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 56U);
    t8 = *((char **)t5);
    t9 = (t1 + 25652);
    t12 = *((char **)t9);
    t18 = ((((char*)(t12))) + 40U);
    t19 = *((char **)t18);
    memset(t28, 0, 8);
    t18 = (t8 + 4);
    t25 = (t19 + 4);
    t13 = *((unsigned int *)t8);
    t14 = *((unsigned int *)t19);
    t15 = (t13 ^ t14);
    t16 = *((unsigned int *)t18);
    t17 = *((unsigned int *)t25);
    t20 = (t16 ^ t17);
    t21 = (t15 | t20);
    t22 = *((unsigned int *)t18);
    t23 = *((unsigned int *)t25);
    t24 = (t22 | t23);
    t32 = (~(t24));
    t33 = (t21 & t32);
    if (t33 != 0)
        goto LAB83;

LAB80:    if (t24 != 0)
        goto LAB82;

LAB81:    *((unsigned int *)t28) = 1;

LAB83:    memset(t10, 0, 8);
    t27 = (t28 + 4);
    t34 = *((unsigned int *)t27);
    t35 = (~(t34));
    t36 = *((unsigned int *)t28);
    t37 = (t36 & t35);
    t38 = (t37 & 1U);
    if (t38 != 0)
        goto LAB87;

LAB85:    if (*((unsigned int *)t27) == 0)
        goto LAB84;

LAB86:    t29 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t29) = 1;

LAB87:    t30 = (t10 + 4);
    t39 = *((unsigned int *)t30);
    t40 = (~(t39));
    t41 = *((unsigned int *)t10);
    t42 = (t41 & t40);
    t43 = (t42 != 0);
    if (t43 > 0)
        goto LAB88;

LAB89:    xsi_set_current_line(65, ng43);

LAB92:    xsi_set_current_line(66, ng43);
    t3 = ((char*)((ng2)));
    t4 = (t1 + 10648);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(67, ng43);
    t3 = (t1 + 10808);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10968);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 2144);
    xsi_vlogfile_write(1, 0, 0, ng54, 3, t18, (char)119, t5, 32, (char)119, t12, 32);

LAB90:
LAB78:
LAB67:
LAB59:
LAB51:
LAB43:
LAB32:
LAB21:    goto LAB14;

LAB8:    xsi_set_current_line(70, ng43);
    t4 = (t1 + 25684);
    t5 = *((char **)t4);
    t8 = ((((char*)(t5))) + 40U);
    t9 = *((char **)t8);
    t8 = (t1 + 25716);
    t12 = *((char **)t8);
    t18 = ((((char*)(t12))) + 72U);
    t19 = *((char **)t18);
    t25 = ((char*)((ng40)));
    xsi_vlog_generic_get_index_select_value(t28, 1, t9, t19, 2, t25, 32, 1);
    memset(t10, 0, 8);
    t26 = (t28 + 4);
    t13 = *((unsigned int *)t26);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB96;

LAB94:    if (*((unsigned int *)t26) == 0)
        goto LAB93;

LAB95:    t27 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t27) = 1;

LAB96:    t29 = (t10 + 4);
    t20 = *((unsigned int *)t29);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB97;

LAB98:    xsi_set_current_line(76, ng43);
    t3 = (t1 + 25748);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    memset(t10, 0, 8);
    t5 = (t8 + 4);
    t13 = *((unsigned int *)t5);
    t14 = (~(t13));
    t15 = *((unsigned int *)t8);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB104;

LAB102:    if (*((unsigned int *)t5) == 0)
        goto LAB101;

LAB103:    t9 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t9) = 1;

LAB104:    t12 = (t10 + 4);
    t20 = *((unsigned int *)t12);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB105;

LAB106:    xsi_set_current_line(82, ng43);
    t3 = (t1 + 25780);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 56U);
    t8 = *((char **)t5);
    t9 = ((char*)((ng1)));
    t12 = (t1 + 10968);
    t18 = (t12 + 56U);
    t19 = *((char **)t18);
    memset(t28, 0, 8);
    xsi_vlog_unsigned_lshift(t28, 32, t9, 32, t19, 32);
    memset(t45, 0, 8);
    t25 = (t8 + 4);
    t26 = (t28 + 4);
    t13 = *((unsigned int *)t8);
    t14 = *((unsigned int *)t28);
    t15 = (t13 ^ t14);
    t16 = *((unsigned int *)t25);
    t17 = *((unsigned int *)t26);
    t20 = (t16 ^ t17);
    t21 = (t15 | t20);
    t22 = *((unsigned int *)t25);
    t23 = *((unsigned int *)t26);
    t24 = (t22 | t23);
    t32 = (~(t24));
    t33 = (t21 & t32);
    if (t33 != 0)
        goto LAB112;

LAB109:    if (t24 != 0)
        goto LAB111;

LAB110:    *((unsigned int *)t45) = 1;

LAB112:    memset(t10, 0, 8);
    t29 = (t45 + 4);
    t34 = *((unsigned int *)t29);
    t35 = (~(t34));
    t36 = *((unsigned int *)t45);
    t37 = (t36 & t35);
    t38 = (t37 & 1U);
    if (t38 != 0)
        goto LAB116;

LAB114:    if (*((unsigned int *)t29) == 0)
        goto LAB113;

LAB115:    t30 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t30) = 1;

LAB116:    t31 = (t10 + 4);
    t39 = *((unsigned int *)t31);
    t40 = (~(t39));
    t41 = *((unsigned int *)t10);
    t42 = (t41 & t40);
    t43 = (t42 != 0);
    if (t43 > 0)
        goto LAB117;

LAB118:    xsi_set_current_line(88, ng43);

LAB121:    xsi_set_current_line(89, ng43);
    t3 = ((char*)((ng2)));
    t4 = (t1 + 10648);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(90, ng43);
    t3 = (t1 + 10808);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10968);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 2144);
    xsi_vlogfile_write(1, 0, 0, ng58, 3, t18, (char)119, t5, 32, (char)119, t12, 32);

LAB119:
LAB107:
LAB99:    goto LAB14;

LAB10:    xsi_set_current_line(92, ng43);
    t4 = ((char*)((ng2)));
    t5 = (t1 + 10648);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 1);
    goto LAB14;

LAB12:    xsi_set_current_line(93, ng43);
    t4 = ((char*)((ng2)));
    t5 = (t1 + 10648);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 1);
    goto LAB14;

LAB15:    *((unsigned int *)t10) = 1;
    goto LAB18;

LAB19:    xsi_set_current_line(9, ng43);

LAB22:    xsi_set_current_line(10, ng43);
    t25 = ((char*)((ng7)));
    t26 = (t1 + 10648);
    xsi_vlogvar_assign_value(t26, t25, 0, 0, 1);
    xsi_set_current_line(11, ng43);
    t3 = (t1 + 10808);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10968);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = ((char*)((ng46)));
    t19 = (t1 + 25140);
    t25 = *((char **)t19);
    t26 = ((((char*)(t25))) + 40U);
    t27 = *((char **)t26);
    t26 = (t1 + 2144);
    xsi_vlogfile_write(1, 0, 0, ng45, 5, t26, (char)119, t5, 32, (char)119, t12, 32, (char)119, t18, 32, (char)118, t27, 62);
    goto LAB21;

LAB26:    *((unsigned int *)t10) = 1;
    goto LAB29;

LAB30:    xsi_set_current_line(17, ng43);

LAB33:    xsi_set_current_line(18, ng43);
    t29 = ((char*)((ng7)));
    t30 = (t1 + 10648);
    xsi_vlogvar_assign_value(t30, t29, 0, 0, 1);
    xsi_set_current_line(19, ng43);
    t3 = (t1 + 10808);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10968);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 10968);
    t19 = (t18 + 56U);
    t25 = *((char **)t19);
    t26 = (t1 + 25204);
    t27 = *((char **)t26);
    t29 = ((((char*)(t27))) + 40U);
    t30 = *((char **)t29);
    t29 = (t1 + 2144);
    xsi_vlogfile_write(1, 0, 0, ng47, 5, t29, (char)119, t5, 32, (char)119, t12, 32, (char)119, t25, 32, (char)118, t30, 3);
    goto LAB32;

LAB37:    *((unsigned int *)t10) = 1;
    goto LAB40;

LAB41:    xsi_set_current_line(25, ng43);

LAB44:    xsi_set_current_line(26, ng43);
    t29 = ((char*)((ng7)));
    t30 = (t1 + 10648);
    xsi_vlogvar_assign_value(t30, t29, 0, 0, 1);
    xsi_set_current_line(27, ng43);
    t3 = (t1 + 10808);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10968);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 10808);
    t19 = (t18 + 56U);
    t25 = *((char **)t19);
    t26 = (t1 + 25268);
    t27 = *((char **)t26);
    t29 = ((((char*)(t27))) + 40U);
    t30 = *((char **)t29);
    t29 = (t1 + 2144);
    xsi_vlogfile_write(1, 0, 0, ng48, 5, t29, (char)119, t5, 32, (char)119, t12, 32, (char)119, t25, 32, (char)118, t30, 12);
    goto LAB43;

LAB45:    *((unsigned int *)t10) = 1;
    goto LAB48;

LAB49:    xsi_set_current_line(33, ng43);

LAB52:    xsi_set_current_line(34, ng43);
    t29 = ((char*)((ng7)));
    t30 = (t1 + 10648);
    xsi_vlogvar_assign_value(t30, t29, 0, 0, 1);
    xsi_set_current_line(35, ng43);
    t3 = (t1 + 10808);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10968);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 2144);
    xsi_vlogfile_write(1, 0, 0, ng49, 3, t18, (char)119, t5, 32, (char)119, t12, 32);
    goto LAB51;

LAB53:    *((unsigned int *)t10) = 1;
    goto LAB56;

LAB57:    xsi_set_current_line(39, ng43);

LAB60:    xsi_set_current_line(40, ng43);
    t29 = ((char*)((ng7)));
    t30 = (t1 + 10648);
    xsi_vlogvar_assign_value(t30, t29, 0, 0, 1);
    xsi_set_current_line(41, ng43);
    t3 = (t1 + 10808);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10968);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 2144);
    xsi_vlogfile_write(1, 0, 0, ng49, 3, t18, (char)119, t5, 32, (char)119, t12, 32);
    goto LAB59;

LAB61:    *((unsigned int *)t10) = 1;
    goto LAB64;

LAB65:    xsi_set_current_line(46, ng43);

LAB68:    xsi_set_current_line(47, ng43);
    t29 = ((char*)((ng7)));
    t30 = (t1 + 10648);
    xsi_vlogvar_assign_value(t30, t29, 0, 0, 1);
    xsi_set_current_line(48, ng43);
    t3 = (t1 + 10808);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10968);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 2144);
    xsi_vlogfile_write(1, 0, 0, ng51, 3, t18, (char)119, t5, 32, (char)119, t12, 32);
    goto LAB67;

LAB72:    *((unsigned int *)t10) = 1;
    goto LAB75;

LAB76:    xsi_set_current_line(51, ng43);

LAB79:    xsi_set_current_line(52, ng43);
    t30 = ((char*)((ng7)));
    t31 = (t1 + 10648);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 1);
    xsi_set_current_line(53, ng43);
    t3 = (t1 + 10808);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10968);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 10808);
    t19 = (t18 + 56U);
    t25 = *((char **)t19);
    t26 = (t1 + 25588);
    t27 = *((char **)t26);
    t29 = ((((char*)(t27))) + 56U);
    t30 = *((char **)t29);
    t31 = (t1 + 2144);
    xsi_vlogfile_write(1, 0, 0, ng52, 5, t31, (char)119, t5, 32, (char)119, t12, 32, (char)119, t25, 32, (char)118, t30, 16);
    goto LAB78;

LAB82:    t26 = (t28 + 4);
    *((unsigned int *)t28) = 1;
    *((unsigned int *)t26) = 1;
    goto LAB83;

LAB84:    *((unsigned int *)t10) = 1;
    goto LAB87;

LAB88:    xsi_set_current_line(59, ng43);

LAB91:    xsi_set_current_line(60, ng43);
    t31 = ((char*)((ng7)));
    t44 = (t1 + 10648);
    xsi_vlogvar_assign_value(t44, t31, 0, 0, 1);
    xsi_set_current_line(61, ng43);
    t3 = (t1 + 10808);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10968);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 2144);
    xsi_vlogfile_write(1, 0, 0, ng53, 3, t18, (char)119, t5, 32, (char)119, t12, 32);
    goto LAB90;

LAB93:    *((unsigned int *)t10) = 1;
    goto LAB96;

LAB97:    xsi_set_current_line(70, ng43);

LAB100:    xsi_set_current_line(71, ng43);
    t30 = ((char*)((ng7)));
    t31 = (t1 + 10648);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 1);
    xsi_set_current_line(72, ng43);
    t3 = (t1 + 10808);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10968);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 2144);
    xsi_vlogfile_write(1, 0, 0, ng55, 3, t18, (char)119, t5, 32, (char)119, t12, 32);
    goto LAB99;

LAB101:    *((unsigned int *)t10) = 1;
    goto LAB104;

LAB105:    xsi_set_current_line(76, ng43);

LAB108:    xsi_set_current_line(77, ng43);
    t18 = ((char*)((ng7)));
    t19 = (t1 + 10648);
    xsi_vlogvar_assign_value(t19, t18, 0, 0, 1);
    xsi_set_current_line(78, ng43);
    t3 = (t1 + 10808);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10968);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 2144);
    xsi_vlogfile_write(1, 0, 0, ng56, 3, t18, (char)119, t5, 32, (char)119, t12, 32);
    goto LAB107;

LAB111:    t27 = (t45 + 4);
    *((unsigned int *)t45) = 1;
    *((unsigned int *)t27) = 1;
    goto LAB112;

LAB113:    *((unsigned int *)t10) = 1;
    goto LAB116;

LAB117:    xsi_set_current_line(82, ng43);

LAB120:    xsi_set_current_line(83, ng43);
    t44 = ((char*)((ng7)));
    t46 = (t1 + 10648);
    xsi_vlogvar_assign_value(t46, t44, 0, 0, 1);
    xsi_set_current_line(84, ng43);
    t3 = (t1 + 10808);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 10968);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 2144);
    xsi_vlogfile_write(1, 0, 0, ng57, 3, t18, (char)119, t5, 32, (char)119, t12, 32);
    goto LAB119;

}

static int sp_TEST_CBI(char *t1, char *t2)
{
    char t10[8];
    char t11[16];
    char t28[8];
    int t0;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    int t7;
    char *t8;
    char *t9;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;
    char *t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    char *t25;
    char *t26;
    char *t27;
    char *t29;
    char *t30;
    char *t31;

LAB0:    t0 = 1;
    xsi_set_current_line(4, ng59);

LAB2:    xsi_set_current_line(5, ng59);
    t3 = (t1 + 25812);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t6 = *((char **)t5);

LAB3:    t5 = ((char*)((ng1)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t5, 32);
    if (t7 == 1)
        goto LAB4;

LAB5:    t3 = ((char*)((ng3)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB6;

LAB7:    t3 = ((char*)((ng9)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB8;

LAB9:    t3 = ((char*)((ng10)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB10;

LAB11:    t3 = ((char*)((ng4)));
    t7 = xsi_vlog_unsigned_case_compare(t6, 3, t3, 32);
    if (t7 == 1)
        goto LAB12;

LAB13:
LAB14:    t0 = 0;

LAB1:    return t0;
LAB4:    xsi_set_current_line(7, ng59);
    t8 = ((char*)((ng2)));
    t9 = (t1 + 11128);
    xsi_vlogvar_assign_value(t9, t8, 0, 0, 1);
    goto LAB14;

LAB6:    xsi_set_current_line(9, ng59);
    t4 = (t1 + 25844);
    t5 = *((char **)t4);
    t8 = ((((char*)(t5))) + 40U);
    t9 = *((char **)t8);
    t8 = ((char*)((ng60)));
    xsi_vlog_unsigned_case_eq(t11, 62, t9, 62, t8, 32);
    memset(t10, 0, 8);
    t12 = (t11 + 4);
    t13 = *((unsigned int *)t12);
    t14 = (~(t13));
    t15 = *((unsigned int *)t11);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB18;

LAB16:    if (*((unsigned int *)t12) == 0)
        goto LAB15;

LAB17:    t18 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t18) = 1;

LAB18:    t19 = (t10 + 4);
    t20 = *((unsigned int *)t19);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB19;

LAB20:    xsi_set_current_line(16, ng59);
    t3 = (t1 + 25908);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 11448);
    t9 = (t5 + 56U);
    t12 = *((char **)t9);
    memset(t28, 0, 8);
    if (*((unsigned int *)t8) != *((unsigned int *)t12))
        goto LAB25;

LAB23:    t18 = (t8 + 4);
    t19 = (t12 + 4);
    if (*((unsigned int *)t18) != *((unsigned int *)t19))
        goto LAB25;

LAB24:    *((unsigned int *)t28) = 1;

LAB25:    memset(t10, 0, 8);
    t25 = (t28 + 4);
    t13 = *((unsigned int *)t25);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB29;

LAB27:    if (*((unsigned int *)t25) == 0)
        goto LAB26;

LAB28:    t26 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t26) = 1;

LAB29:    t27 = (t10 + 4);
    t20 = *((unsigned int *)t27);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB30;

LAB31:    xsi_set_current_line(23, ng59);
    t3 = (t1 + 25972);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 11288);
    t9 = (t5 + 56U);
    t12 = *((char **)t9);
    memset(t28, 0, 8);
    if (*((unsigned int *)t8) != *((unsigned int *)t12))
        goto LAB36;

LAB34:    t18 = (t8 + 4);
    t19 = (t12 + 4);
    if (*((unsigned int *)t18) != *((unsigned int *)t19))
        goto LAB36;

LAB35:    *((unsigned int *)t28) = 1;

LAB36:    memset(t10, 0, 8);
    t25 = (t28 + 4);
    t13 = *((unsigned int *)t25);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB40;

LAB38:    if (*((unsigned int *)t25) == 0)
        goto LAB37;

LAB39:    t26 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t26) = 1;

LAB40:    t27 = (t10 + 4);
    t20 = *((unsigned int *)t27);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB41;

LAB42:    xsi_set_current_line(30, ng59);
    t3 = (t1 + 26044);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 26084);
    t9 = *((char **)t5);
    t12 = ((((char*)(t9))) + 72U);
    t18 = *((char **)t12);
    t19 = ((char*)((ng19)));
    xsi_vlog_generic_get_index_select_value(t28, 1, t8, t18, 2, t19, 32, 1);
    memset(t10, 0, 8);
    t25 = (t28 + 4);
    t13 = *((unsigned int *)t25);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB48;

LAB46:    if (*((unsigned int *)t25) == 0)
        goto LAB45;

LAB47:    t26 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t26) = 1;

LAB48:    t27 = (t10 + 4);
    t20 = *((unsigned int *)t27);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB49;

LAB50:    xsi_set_current_line(35, ng59);
    t3 = (t1 + 26124);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 26164);
    t9 = *((char **)t5);
    t12 = ((((char*)(t9))) + 72U);
    t18 = *((char **)t12);
    t19 = ((char*)((ng19)));
    xsi_vlog_generic_get_index_select_value(t28, 1, t8, t18, 2, t19, 32, 1);
    memset(t10, 0, 8);
    t25 = (t28 + 4);
    t13 = *((unsigned int *)t25);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB56;

LAB54:    if (*((unsigned int *)t25) == 0)
        goto LAB53;

LAB55:    t26 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t26) = 1;

LAB56:    t27 = (t10 + 4);
    t20 = *((unsigned int *)t27);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB57;

LAB58:    xsi_set_current_line(41, ng59);
    t3 = (t1 + 26204);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    t5 = (t1 + 26244);
    t9 = *((char **)t5);
    t12 = ((((char*)(t9))) + 72U);
    t18 = *((char **)t12);
    t19 = ((char*)((ng50)));
    xsi_vlog_generic_get_index_select_value(t28, 1, t8, t18, 2, t19, 32, 1);
    memset(t10, 0, 8);
    t25 = (t28 + 4);
    t13 = *((unsigned int *)t25);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB64;

LAB62:    if (*((unsigned int *)t25) == 0)
        goto LAB61;

LAB63:    t26 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t26) = 1;

LAB64:    t27 = (t10 + 4);
    t20 = *((unsigned int *)t27);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB65;

LAB66:    xsi_set_current_line(46, ng59);
    t3 = (t1 + 26284);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 56U);
    t8 = *((char **)t5);
    t9 = (t1 + 11288);
    t12 = (t9 + 56U);
    t18 = *((char **)t12);
    memset(t28, 0, 8);
    if (*((unsigned int *)t8) != *((unsigned int *)t18))
        goto LAB71;

LAB69:    t19 = (t8 + 4);
    t25 = (t18 + 4);
    if (*((unsigned int *)t19) != *((unsigned int *)t25))
        goto LAB71;

LAB70:    *((unsigned int *)t28) = 1;

LAB71:    memset(t10, 0, 8);
    t26 = (t28 + 4);
    t13 = *((unsigned int *)t26);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB75;

LAB73:    if (*((unsigned int *)t26) == 0)
        goto LAB72;

LAB74:    t27 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t27) = 1;

LAB75:    t29 = (t10 + 4);
    t20 = *((unsigned int *)t29);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB76;

LAB77:    xsi_set_current_line(53, ng59);

LAB80:    xsi_set_current_line(54, ng59);
    t3 = ((char*)((ng2)));
    t4 = (t1 + 11128);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(55, ng59);
    t3 = (t1 + 11288);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 11448);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 2576);
    xsi_vlogfile_write(1, 0, 0, ng68, 3, t18, (char)119, t5, 32, (char)119, t12, 32);

LAB78:
LAB67:
LAB59:
LAB51:
LAB43:
LAB32:
LAB21:    goto LAB14;

LAB8:    xsi_set_current_line(58, ng59);
    t4 = (t1 + 26356);
    t5 = *((char **)t4);
    t8 = ((((char*)(t5))) + 40U);
    t9 = *((char **)t8);
    t8 = (t1 + 26388);
    t12 = *((char **)t8);
    t18 = ((((char*)(t12))) + 72U);
    t19 = *((char **)t18);
    t25 = ((char*)((ng40)));
    xsi_vlog_generic_get_index_select_value(t28, 1, t9, t19, 2, t25, 32, 1);
    memset(t10, 0, 8);
    t26 = (t28 + 4);
    t13 = *((unsigned int *)t26);
    t14 = (~(t13));
    t15 = *((unsigned int *)t28);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB84;

LAB82:    if (*((unsigned int *)t26) == 0)
        goto LAB81;

LAB83:    t27 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t27) = 1;

LAB84:    t29 = (t10 + 4);
    t20 = *((unsigned int *)t29);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB85;

LAB86:    xsi_set_current_line(63, ng59);
    t3 = (t1 + 26420);
    t4 = *((char **)t3);
    t5 = ((((char*)(t4))) + 40U);
    t8 = *((char **)t5);
    memset(t10, 0, 8);
    t5 = (t8 + 4);
    t13 = *((unsigned int *)t5);
    t14 = (~(t13));
    t15 = *((unsigned int *)t8);
    t16 = (t15 & t14);
    t17 = (t16 & 1U);
    if (t17 != 0)
        goto LAB92;

LAB90:    if (*((unsigned int *)t5) == 0)
        goto LAB89;

LAB91:    t9 = (t10 + 4);
    *((unsigned int *)t10) = 1;
    *((unsigned int *)t9) = 1;

LAB92:    t12 = (t10 + 4);
    t20 = *((unsigned int *)t12);
    t21 = (~(t20));
    t22 = *((unsigned int *)t10);
    t23 = (t22 & t21);
    t24 = (t23 != 0);
    if (t24 > 0)
        goto LAB93;

LAB94:    xsi_set_current_line(68, ng59);

LAB97:    xsi_set_current_line(69, ng59);
    t3 = ((char*)((ng2)));
    t4 = (t1 + 11128);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(70, ng59);
    t3 = (t1 + 11288);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 11448);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 2576);
    xsi_vlogfile_write(1, 0, 0, ng71, 3, t18, (char)119, t5, 32, (char)119, t12, 32);

LAB95:
LAB87:    goto LAB14;

LAB10:    xsi_set_current_line(72, ng59);
    t4 = ((char*)((ng2)));
    t5 = (t1 + 11128);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 1);
    goto LAB14;

LAB12:    xsi_set_current_line(73, ng59);
    t4 = ((char*)((ng2)));
    t5 = (t1 + 11128);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 1);
    goto LAB14;

LAB15:    *((unsigned int *)t10) = 1;
    goto LAB18;

LAB19:    xsi_set_current_line(9, ng59);

LAB22:    xsi_set_current_line(10, ng59);
    t25 = ((char*)((ng7)));
    t26 = (t1 + 11128);
    xsi_vlogvar_assign_value(t26, t25, 0, 0, 1);
    xsi_set_current_line(11, ng59);
    t3 = (t1 + 11288);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 11448);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = ((char*)((ng62)));
    t19 = (t1 + 25876);
    t25 = *((char **)t19);
    t26 = ((((char*)(t25))) + 40U);
    t27 = *((char **)t26);
    t26 = (t1 + 2576);
    xsi_vlogfile_write(1, 0, 0, ng61, 5, t26, (char)119, t5, 32, (char)119, t12, 32, (char)119, t18, 32, (char)118, t27, 62);
    goto LAB21;

LAB26:    *((unsigned int *)t10) = 1;
    goto LAB29;

LAB30:    xsi_set_current_line(16, ng59);

LAB33:    xsi_set_current_line(17, ng59);
    t29 = ((char*)((ng7)));
    t30 = (t1 + 11128);
    xsi_vlogvar_assign_value(t30, t29, 0, 0, 1);
    xsi_set_current_line(18, ng59);
    t3 = (t1 + 11288);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 11448);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 11448);
    t19 = (t18 + 56U);
    t25 = *((char **)t19);
    t26 = (t1 + 25940);
    t27 = *((char **)t26);
    t29 = ((((char*)(t27))) + 40U);
    t30 = *((char **)t29);
    t29 = (t1 + 2576);
    xsi_vlogfile_write(1, 0, 0, ng63, 5, t29, (char)119, t5, 32, (char)119, t12, 32, (char)119, t25, 32, (char)118, t30, 3);
    goto LAB32;

LAB37:    *((unsigned int *)t10) = 1;
    goto LAB40;

LAB41:    xsi_set_current_line(23, ng59);

LAB44:    xsi_set_current_line(24, ng59);
    t29 = ((char*)((ng7)));
    t30 = (t1 + 11128);
    xsi_vlogvar_assign_value(t30, t29, 0, 0, 1);
    xsi_set_current_line(25, ng59);
    t3 = (t1 + 11288);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 11448);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 11288);
    t19 = (t18 + 56U);
    t25 = *((char **)t19);
    t26 = (t1 + 26004);
    t27 = *((char **)t26);
    t29 = ((((char*)(t27))) + 40U);
    t30 = *((char **)t29);
    t29 = (t1 + 2576);
    xsi_vlogfile_write(1, 0, 0, ng64, 5, t29, (char)119, t5, 32, (char)119, t12, 32, (char)119, t25, 32, (char)118, t30, 12);
    goto LAB43;

LAB45:    *((unsigned int *)t10) = 1;
    goto LAB48;

LAB49:    xsi_set_current_line(30, ng59);

LAB52:    xsi_set_current_line(31, ng59);
    t29 = ((char*)((ng7)));
    t30 = (t1 + 11128);
    xsi_vlogvar_assign_value(t30, t29, 0, 0, 1);
    xsi_set_current_line(32, ng59);
    t3 = (t1 + 11288);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 11448);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 2576);
    xsi_vlogfile_write(1, 0, 0, ng65, 3, t18, (char)119, t5, 32, (char)119, t12, 32);
    goto LAB51;

LAB53:    *((unsigned int *)t10) = 1;
    goto LAB56;

LAB57:    xsi_set_current_line(35, ng59);

LAB60:    xsi_set_current_line(36, ng59);
    t29 = ((char*)((ng7)));
    t30 = (t1 + 11128);
    xsi_vlogvar_assign_value(t30, t29, 0, 0, 1);
    xsi_set_current_line(37, ng59);
    t3 = (t1 + 11288);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 11448);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 2576);
    xsi_vlogfile_write(1, 0, 0, ng65, 3, t18, (char)119, t5, 32, (char)119, t12, 32);
    goto LAB59;

LAB61:    *((unsigned int *)t10) = 1;
    goto LAB64;

LAB65:    xsi_set_current_line(41, ng59);

LAB68:    xsi_set_current_line(42, ng59);
    t29 = ((char*)((ng7)));
    t30 = (t1 + 11128);
    xsi_vlogvar_assign_value(t30, t29, 0, 0, 1);
    xsi_set_current_line(43, ng59);
    t3 = (t1 + 11288);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 11448);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 2576);
    xsi_vlogfile_write(1, 0, 0, ng66, 3, t18, (char)119, t5, 32, (char)119, t12, 32);
    goto LAB67;

LAB72:    *((unsigned int *)t10) = 1;
    goto LAB75;

LAB76:    xsi_set_current_line(46, ng59);

LAB79:    xsi_set_current_line(47, ng59);
    t30 = ((char*)((ng7)));
    t31 = (t1 + 11128);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 1);
    xsi_set_current_line(48, ng59);
    t3 = (t1 + 11288);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 11448);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 11288);
    t19 = (t18 + 56U);
    t25 = *((char **)t19);
    t26 = (t1 + 26324);
    t27 = *((char **)t26);
    t29 = ((((char*)(t27))) + 56U);
    t30 = *((char **)t29);
    t31 = (t1 + 2576);
    xsi_vlogfile_write(1, 0, 0, ng67, 5, t31, (char)119, t5, 32, (char)119, t12, 32, (char)119, t25, 32, (char)118, t30, 16);
    goto LAB78;

LAB81:    *((unsigned int *)t10) = 1;
    goto LAB84;

LAB85:    xsi_set_current_line(58, ng59);

LAB88:    xsi_set_current_line(59, ng59);
    t30 = ((char*)((ng7)));
    t31 = (t1 + 11128);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 1);
    xsi_set_current_line(60, ng59);
    t3 = (t1 + 11288);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 11448);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 2576);
    xsi_vlogfile_write(1, 0, 0, ng69, 3, t18, (char)119, t5, 32, (char)119, t12, 32);
    goto LAB87;

LAB89:    *((unsigned int *)t10) = 1;
    goto LAB92;

LAB93:    xsi_set_current_line(63, ng59);

LAB96:    xsi_set_current_line(64, ng59);
    t18 = ((char*)((ng7)));
    t19 = (t1 + 11128);
    xsi_vlogvar_assign_value(t19, t18, 0, 0, 1);
    xsi_set_current_line(65, ng59);
    t3 = (t1 + 11288);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t8 = (t1 + 11448);
    t9 = (t8 + 56U);
    t12 = *((char **)t9);
    t18 = (t1 + 2576);
    xsi_vlogfile_write(1, 0, 0, ng70, 3, t18, (char)119, t5, 32, (char)119, t12, 32);
    goto LAB95;

}

static void Cont_20_0(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    char *t10;
    unsigned int t11;
    unsigned int t12;
    char *t13;
    unsigned int t14;
    unsigned int t15;

LAB0:    t1 = (t0 + 12368U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(20, ng72);
    t2 = ((char*)((ng73)));
    t3 = (t0 + 17752);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    memset(t7, 0, 8);
    t8 = 255U;
    t9 = t8;
    t10 = (t2 + 4);
    t11 = *((unsigned int *)t2);
    t8 = (t8 & t11);
    t12 = *((unsigned int *)t10);
    t9 = (t9 & t12);
    t13 = (t7 + 4);
    t14 = *((unsigned int *)t7);
    *((unsigned int *)t7) = (t14 | t8);
    t15 = *((unsigned int *)t13);
    *((unsigned int *)t13) = (t15 | t9);
    xsi_driver_vfirst_trans(t3, 0, 7);

LAB1:    return;
}

static void Cont_36_1(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 12616U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(36, ng72);
    t2 = (t0 + 26452);
    t3 = *((char **)t2);
    t4 = ((((char*)(t3))) + 40U);
    t5 = *((char **)t4);
    t4 = (t0 + 17816);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t9, 0, 8);
    t10 = 1023U;
    t11 = t10;
    t12 = (t5 + 4);
    t13 = *((unsigned int *)t5);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t12);
    t11 = (t11 & t14);
    t15 = (t9 + 4);
    t16 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t16 | t10);
    t17 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t17 | t11);
    xsi_driver_vfirst_trans(t4, 0, 9);
    t18 = (t0 + 17400);
    *((int *)t18) = 1;

LAB1:    return;
}

static void Cont_37_2(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 12864U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(37, ng72);
    t2 = (t0 + 26484);
    t3 = *((char **)t2);
    t4 = ((((char*)(t3))) + 40U);
    t5 = *((char **)t4);
    t4 = (t0 + 17880);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t9, 0, 8);
    t10 = 7U;
    t11 = t10;
    t12 = (t5 + 4);
    t13 = *((unsigned int *)t5);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t12);
    t11 = (t11 & t14);
    t15 = (t9 + 4);
    t16 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t16 | t10);
    t17 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t17 | t11);
    xsi_driver_vfirst_trans(t4, 0, 2);
    t18 = (t0 + 17416);
    *((int *)t18) = 1;

LAB1:    return;
}

static void NetDecl_39_3(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 13112U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(39, ng72);
    t2 = (t0 + 26508);
    t3 = *((char **)t2);
    t4 = ((((char*)(t3))) + 40U);
    t5 = *((char **)t4);
    t4 = (t0 + 17944);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t9, 0, 8);
    t10 = 255U;
    t11 = t10;
    t12 = (t5 + 4);
    t13 = *((unsigned int *)t5);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t12);
    t11 = (t11 & t14);
    t15 = (t9 + 4);
    t16 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t16 | t10);
    t17 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t17 | t11);
    xsi_driver_vfirst_trans(t4, 0, 7U);
    t18 = (t0 + 17432);
    *((int *)t18) = 1;

LAB1:    return;
}

static void NetDecl_40_4(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 13360U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(40, ng72);
    t2 = (t0 + 26532);
    t3 = *((char **)t2);
    t4 = ((((char*)(t3))) + 40U);
    t5 = *((char **)t4);
    t4 = (t0 + 18008);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t9, 0, 8);
    t10 = 255U;
    t11 = t10;
    t12 = (t5 + 4);
    t13 = *((unsigned int *)t5);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t12);
    t11 = (t11 & t14);
    t15 = (t9 + 4);
    t16 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t16 | t10);
    t17 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t17 | t11);
    xsi_driver_vfirst_trans(t4, 0, 7U);
    t18 = (t0 + 17448);
    *((int *)t18) = 1;

LAB1:    return;
}

static void NetDecl_41_5(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 13608U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(41, ng72);
    t2 = (t0 + 26556);
    t3 = *((char **)t2);
    t4 = ((((char*)(t3))) + 40U);
    t5 = *((char **)t4);
    t4 = (t0 + 18072);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t9, 0, 8);
    t10 = 255U;
    t11 = t10;
    t12 = (t5 + 4);
    t13 = *((unsigned int *)t5);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t12);
    t11 = (t11 & t14);
    t15 = (t9 + 4);
    t16 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t16 | t10);
    t17 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t17 | t11);
    xsi_driver_vfirst_trans(t4, 0, 7U);
    t18 = (t0 + 17464);
    *((int *)t18) = 1;

LAB1:    return;
}

static void NetDecl_43_6(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 13856U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(43, ng72);
    t2 = (t0 + 26580);
    t3 = *((char **)t2);
    t4 = ((((char*)(t3))) + 40U);
    t5 = *((char **)t4);
    t4 = (t0 + 18136);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t9, 0, 8);
    t10 = 31U;
    t11 = t10;
    t12 = (t5 + 4);
    t13 = *((unsigned int *)t5);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t12);
    t11 = (t11 & t14);
    t15 = (t9 + 4);
    t16 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t16 | t10);
    t17 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t17 | t11);
    xsi_driver_vfirst_trans(t4, 0, 4U);
    t18 = (t0 + 17480);
    *((int *)t18) = 1;

LAB1:    return;
}

static void NetDecl_44_7(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 14104U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(44, ng72);
    t2 = (t0 + 26604);
    t3 = *((char **)t2);
    t4 = ((((char*)(t3))) + 40U);
    t5 = *((char **)t4);
    t4 = (t0 + 18200);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t9, 0, 8);
    t10 = 31U;
    t11 = t10;
    t12 = (t5 + 4);
    t13 = *((unsigned int *)t5);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t12);
    t11 = (t11 & t14);
    t15 = (t9 + 4);
    t16 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t16 | t10);
    t17 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t17 | t11);
    xsi_driver_vfirst_trans(t4, 0, 4U);
    t18 = (t0 + 17496);
    *((int *)t18) = 1;

LAB1:    return;
}

static void NetDecl_45_8(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 14352U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(45, ng72);
    t2 = (t0 + 26636);
    t3 = *((char **)t2);
    t4 = ((((char*)(t3))) + 40U);
    t5 = *((char **)t4);
    t4 = (t0 + 18264);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t9, 0, 8);
    t10 = 127U;
    t11 = t10;
    t12 = (t5 + 4);
    t13 = *((unsigned int *)t5);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t12);
    t11 = (t11 & t14);
    t15 = (t9 + 4);
    t16 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t16 | t10);
    t17 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t17 | t11);
    xsi_driver_vfirst_trans(t4, 0, 6U);
    t18 = (t0 + 17512);
    *((int *)t18) = 1;

LAB1:    return;
}

static void NetDecl_46_9(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 14600U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(46, ng72);
    t2 = (t0 + 26660);
    t3 = *((char **)t2);
    t4 = ((((char*)(t3))) + 40U);
    t5 = *((char **)t4);
    t4 = (t0 + 18328);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t9, 0, 8);
    t10 = 127U;
    t11 = t10;
    t12 = (t5 + 4);
    t13 = *((unsigned int *)t5);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t12);
    t11 = (t11 & t14);
    t15 = (t9 + 4);
    t16 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t16 | t10);
    t17 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t17 | t11);
    xsi_driver_vfirst_trans(t4, 0, 6U);
    t18 = (t0 + 17528);
    *((int *)t18) = 1;

LAB1:    return;
}

static void NetDecl_47_10(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 14848U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(47, ng72);
    t2 = (t0 + 26684);
    t3 = *((char **)t2);
    t4 = ((((char*)(t3))) + 40U);
    t5 = *((char **)t4);
    t4 = (t0 + 18392);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t9, 0, 8);
    t10 = 255U;
    t11 = t10;
    t12 = (t5 + 4);
    t13 = *((unsigned int *)t5);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t12);
    t11 = (t11 & t14);
    t15 = (t9 + 4);
    t16 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t16 | t10);
    t17 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t17 | t11);
    xsi_driver_vfirst_trans(t4, 0, 7U);
    t18 = (t0 + 17544);
    *((int *)t18) = 1;

LAB1:    return;
}

static void NetDecl_49_11(char *t0)
{
    char t3[8];
    char t7[8];
    char t21[8];
    char *t1;
    char *t2;
    char *t4;
    char *t5;
    char *t6;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;
    char *t15;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    char *t27;
    char *t28;
    char *t29;
    char *t30;
    char *t31;
    char *t32;
    char *t33;
    char *t34;
    char *t35;
    unsigned int t36;
    unsigned int t37;
    char *t38;
    unsigned int t39;
    unsigned int t40;
    char *t41;
    unsigned int t42;
    unsigned int t43;
    char *t44;

LAB0:    t1 = (t0 + 15096U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(49, ng72);
    t2 = (t0 + 26716);
    t4 = *((char **)t2);
    t5 = ((((char*)(t4))) + 56U);
    t6 = *((char **)t5);
    t8 = (t0 + 26748);
    t9 = *((char **)t8);
    t10 = ((((char*)(t9))) + 72U);
    t11 = *((char **)t10);
    t12 = (t0 + 26780);
    t13 = *((char **)t12);
    t14 = ((((char*)(t13))) + 64U);
    t15 = *((char **)t14);
    t16 = ((char*)((ng74)));
    xsi_vlog_generic_get_array_select_value(t7, 8, t6, t11, t15, 2, 1, t16, 32, 1);
    t17 = (t0 + 26812);
    t18 = *((char **)t17);
    t19 = ((((char*)(t18))) + 56U);
    t20 = *((char **)t19);
    t22 = (t0 + 26844);
    t23 = *((char **)t22);
    t24 = ((((char*)(t23))) + 72U);
    t25 = *((char **)t24);
    t26 = (t0 + 26876);
    t27 = *((char **)t26);
    t28 = ((((char*)(t27))) + 64U);
    t29 = *((char **)t28);
    t30 = ((char*)((ng75)));
    xsi_vlog_generic_get_array_select_value(t21, 8, t20, t25, t29, 2, 1, t30, 32, 1);
    xsi_vlogtype_concat(t3, 16, 16, 2U, t21, 8, t7, 8);
    t31 = (t0 + 18456);
    t32 = (t31 + 56U);
    t33 = *((char **)t32);
    t34 = (t33 + 56U);
    t35 = *((char **)t34);
    memset(t35, 0, 8);
    t36 = 127U;
    t37 = t36;
    t38 = (t3 + 4);
    t39 = *((unsigned int *)t3);
    t36 = (t36 & t39);
    t40 = *((unsigned int *)t38);
    t37 = (t37 & t40);
    t41 = (t35 + 4);
    t42 = *((unsigned int *)t35);
    *((unsigned int *)t35) = (t42 | t36);
    t43 = *((unsigned int *)t41);
    *((unsigned int *)t41) = (t43 | t37);
    xsi_driver_vfirst_trans(t31, 0, 6U);
    t44 = (t0 + 17560);
    *((int *)t44) = 1;

LAB1:    return;
}

static void NetDecl_51_12(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 15344U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(51, ng72);
    t2 = (t0 + 26908);
    t3 = *((char **)t2);
    t4 = ((((char*)(t3))) + 40U);
    t5 = *((char **)t4);
    t4 = (t0 + 18520);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t9, 0, 8);
    t10 = 4095U;
    t11 = t10;
    t12 = (t5 + 4);
    t13 = *((unsigned int *)t5);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t12);
    t11 = (t11 & t14);
    t15 = (t9 + 4);
    t16 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t16 | t10);
    t17 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t17 | t11);
    xsi_driver_vfirst_trans(t4, 0, 11U);
    t18 = (t0 + 17576);
    *((int *)t18) = 1;

LAB1:    return;
}

static void NetDecl_52_13(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;

LAB0:    t1 = (t0 + 15592U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(52, ng72);
    t2 = (t0 + 26940);
    t3 = *((char **)t2);
    t4 = ((((char*)(t3))) + 40U);
    t5 = *((char **)t4);
    t4 = (t0 + 18584);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    xsi_vlog_bit_copy(t9, 0, t5, 0, 62);
    xsi_driver_vfirst_trans(t4, 0, 61U);
    t10 = (t0 + 17592);
    *((int *)t10) = 1;

LAB1:    return;
}

static void NetDecl_53_14(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 15840U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(53, ng72);
    t2 = (t0 + 26980);
    t3 = *((char **)t2);
    t4 = ((((char*)(t3))) + 40U);
    t5 = *((char **)t4);
    t4 = (t0 + 18648);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t9, 0, 8);
    t10 = 524287U;
    t11 = t10;
    t12 = (t5 + 4);
    t13 = *((unsigned int *)t5);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t12);
    t11 = (t11 & t14);
    t15 = (t9 + 4);
    t16 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t16 | t10);
    t17 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t17 | t11);
    xsi_driver_vfirst_trans(t4, 0, 18U);
    t18 = (t0 + 17608);
    *((int *)t18) = 1;

LAB1:    return;
}

static void NetDecl_54_15(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 16088U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(54, ng72);
    t2 = (t0 + 27012);
    t3 = *((char **)t2);
    t4 = ((((char*)(t3))) + 40U);
    t5 = *((char **)t4);
    t4 = (t0 + 18712);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t9, 0, 8);
    t10 = 7U;
    t11 = t10;
    t12 = (t5 + 4);
    t13 = *((unsigned int *)t5);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t12);
    t11 = (t11 & t14);
    t15 = (t9 + 4);
    t16 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t16 | t10);
    t17 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t17 | t11);
    xsi_driver_vfirst_trans(t4, 0, 2U);
    t18 = (t0 + 17624);
    *((int *)t18) = 1;

LAB1:    return;
}

static void NetDecl_55_16(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    unsigned int t11;
    unsigned int t12;
    char *t13;
    unsigned int t14;
    unsigned int t15;
    char *t16;
    unsigned int t17;
    unsigned int t18;
    char *t19;

LAB0:    t1 = (t0 + 16336U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(55, ng72);
    t2 = (t0 + 27052);
    t3 = *((char **)t2);
    t4 = ((((char*)(t3))) + 56U);
    t5 = *((char **)t4);
    t6 = (t0 + 18776);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    memset(t10, 0, 8);
    t11 = 255U;
    t12 = t11;
    t13 = (t5 + 4);
    t14 = *((unsigned int *)t5);
    t11 = (t11 & t14);
    t15 = *((unsigned int *)t13);
    t12 = (t12 & t15);
    t16 = (t10 + 4);
    t17 = *((unsigned int *)t10);
    *((unsigned int *)t10) = (t17 | t11);
    t18 = *((unsigned int *)t16);
    *((unsigned int *)t16) = (t18 | t12);
    xsi_driver_vfirst_trans(t6, 0, 7U);
    t19 = (t0 + 17640);
    *((int *)t19) = 1;

LAB1:    return;
}

static void NetDecl_56_17(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;

LAB0:    t1 = (t0 + 16584U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(56, ng72);
    t2 = (t0 + 27084);
    t3 = *((char **)t2);
    t4 = ((((char*)(t3))) + 40U);
    t5 = *((char **)t4);
    t4 = (t0 + 18840);
    t6 = (t4 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t9, 0, 8);
    t10 = 1023U;
    t11 = t10;
    t12 = (t5 + 4);
    t13 = *((unsigned int *)t5);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t12);
    t11 = (t11 & t14);
    t15 = (t9 + 4);
    t16 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t16 | t10);
    t17 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t17 | t11);
    xsi_driver_vfirst_trans(t4, 0, 9U);
    t18 = (t0 + 17656);
    *((int *)t18) = 1;

LAB1:    return;
}

static void Initial_70_18(char *t0)
{
    char *t1;
    char *t2;

LAB0:    xsi_set_current_line(70, ng72);

LAB2:    xsi_set_current_line(71, ng72);
    xsi_vlogfile_write(1, 0, 0, ng76, 1, t0);
    xsi_set_current_line(72, ng72);
    t1 = ((char*)((ng77)));
    t2 = (t0 + 7128);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);
    xsi_set_current_line(73, ng72);
    t1 = ((char*)((ng77)));
    t2 = (t0 + 7288);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);
    xsi_set_current_line(74, ng72);
    t1 = ((char*)((ng77)));
    t2 = (t0 + 7448);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);
    xsi_set_current_line(75, ng72);
    t1 = ((char*)((ng77)));
    t2 = (t0 + 7608);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);
    xsi_set_current_line(76, ng72);
    t1 = ((char*)((ng77)));
    t2 = (t0 + 7768);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);
    xsi_set_current_line(78, ng72);
    t1 = ((char*)((ng78)));
    t2 = (t0 + 7928);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);
    xsi_set_current_line(79, ng72);
    t1 = ((char*)((ng79)));
    t2 = (t0 + 8088);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);
    xsi_set_current_line(80, ng72);
    t1 = ((char*)((ng79)));
    t2 = (t0 + 8248);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);
    xsi_set_current_line(81, ng72);
    t1 = ((char*)((ng79)));
    t2 = (t0 + 8408);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);
    xsi_set_current_line(82, ng72);
    t1 = ((char*)((ng80)));
    t2 = (t0 + 8888);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);
    xsi_set_current_line(83, ng72);
    t1 = ((char*)((ng77)));
    t2 = (t0 + 8568);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);
    xsi_set_current_line(84, ng72);
    t1 = ((char*)((ng81)));
    t2 = (t0 + 6808);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 1);

LAB1:    return;
}

static void Always_87_19(char *t0)
{
    char t26[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    int t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;
    char *t15;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t27;
    char *t28;
    char *t29;
    char *t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    unsigned int t44;
    unsigned int t45;
    unsigned int t46;
    unsigned int t47;
    char *t48;
    char *t49;
    char *t50;
    char *t51;

LAB0:    t1 = (t0 + 17080U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(87, ng72);
    t2 = (t0 + 17672);
    *((int *)t2) = 1;
    t3 = (t0 + 17112);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(87, ng72);

LAB5:    xsi_set_current_line(88, ng72);
    t4 = (t0 + 3528U);
    t5 = *((char **)t4);

LAB6:    t4 = ((char*)((ng81)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t4, 32);
    if (t6 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng1)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng3)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB11;

LAB12:    t2 = ((char*)((ng9)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB13;

LAB14:    t2 = ((char*)((ng10)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB15;

LAB16:
LAB18:
LAB17:    xsi_set_current_line(141, ng72);
    t2 = ((char*)((ng85)));
    t3 = (t0 + 6808);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);

LAB19:    xsi_set_current_line(143, ng72);
    t2 = (t0 + 3528U);
    t3 = *((char **)t2);
    t2 = (t0 + 6968);
    xsi_vlogvar_assign_value(t2, t3, 0, 0, 10);
    goto LAB2;

LAB7:    xsi_set_current_line(90, ng72);

LAB20:    xsi_set_current_line(92, ng72);
    t7 = ((char*)((ng82)));
    t8 = (t0 + 8408);
    xsi_vlogvar_assign_value(t8, t7, 0, 0, 32);
    xsi_set_current_line(93, ng72);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 8568);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 32);
    xsi_set_current_line(94, ng72);
    t2 = (t0 + 8408);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t7 = (t0 + 8568);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    t10 = (t0 + 16888);
    t11 = (t0 + 848);
    t12 = xsi_create_subprogram_invocation(t10, 0, t0, t11, 0, 0);
    t13 = (t0 + 9208);
    xsi_vlogvar_assign_value(t13, t4, 0, 0, 32);
    t14 = (t0 + 9368);
    xsi_vlogvar_assign_value(t14, t9, 0, 0, 32);

LAB21:    t15 = (t0 + 16984);
    t16 = *((char **)t15);
    t17 = (t16 + 80U);
    t18 = *((char **)t17);
    t19 = (t18 + 272U);
    t20 = *((char **)t19);
    t21 = (t20 + 0U);
    t22 = *((char **)t21);
    t6 = ((int  (*)(char *, char *))t22)(t0, t16);
    if (t6 != 0)
        goto LAB23;

LAB22:    t16 = (t0 + 16984);
    t23 = *((char **)t16);
    t16 = (t0 + 9048);
    t24 = (t16 + 56U);
    t25 = *((char **)t24);
    memcpy(t26, t25, 8);
    t27 = (t0 + 848);
    t28 = (t0 + 16888);
    t29 = 0;
    xsi_delete_subprogram_invocation(t27, t23, t0, t28, t29);
    t30 = (t0 + 6808);
    xsi_vlogvar_assign_value(t30, t26, 0, 0, 1);
    xsi_set_current_line(96, ng72);
    t2 = (t0 + 3688U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng4)));
    memset(t26, 0, 8);
    t4 = (t3 + 4);
    t7 = (t2 + 4);
    t31 = *((unsigned int *)t3);
    t32 = *((unsigned int *)t2);
    t33 = (t31 ^ t32);
    t34 = *((unsigned int *)t4);
    t35 = *((unsigned int *)t7);
    t36 = (t34 ^ t35);
    t37 = (t33 | t36);
    t38 = *((unsigned int *)t4);
    t39 = *((unsigned int *)t7);
    t40 = (t38 | t39);
    t41 = (~(t40));
    t42 = (t37 & t41);
    if (t42 != 0)
        goto LAB27;

LAB24:    if (t40 != 0)
        goto LAB26;

LAB25:    *((unsigned int *)t26) = 1;

LAB27:    t9 = (t26 + 4);
    t43 = *((unsigned int *)t9);
    t44 = (~(t43));
    t45 = *((unsigned int *)t26);
    t46 = (t45 & t44);
    t47 = (t46 != 0);
    if (t47 > 0)
        goto LAB28;

LAB29:
LAB30:    goto LAB19;

LAB9:    xsi_set_current_line(102, ng72);

LAB32:    xsi_set_current_line(104, ng72);
    t3 = ((char*)((ng2)));
    t4 = (t0 + 8088);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 32);
    xsi_set_current_line(105, ng72);
    t2 = ((char*)((ng82)));
    t3 = (t0 + 8248);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 32);
    xsi_set_current_line(106, ng72);
    t2 = (t0 + 8088);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t7 = (t0 + 8248);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    t10 = (t0 + 7448);
    t11 = (t10 + 56U);
    t12 = *((char **)t11);
    t13 = (t0 + 16888);
    t14 = (t0 + 1712);
    t15 = xsi_create_subprogram_invocation(t13, 0, t0, t14, 0, 0);
    t16 = (t0 + 10168);
    xsi_vlogvar_assign_value(t16, t4, 0, 0, 32);
    t17 = (t0 + 10328);
    xsi_vlogvar_assign_value(t17, t9, 0, 0, 32);
    t18 = (t0 + 10488);
    xsi_vlogvar_assign_value(t18, t12, 0, 0, 32);

LAB33:    t19 = (t0 + 16984);
    t20 = *((char **)t19);
    t21 = (t20 + 80U);
    t22 = *((char **)t21);
    t23 = (t22 + 272U);
    t24 = *((char **)t23);
    t25 = (t24 + 0U);
    t27 = *((char **)t25);
    t6 = ((int  (*)(char *, char *))t27)(t0, t20);
    if (t6 != 0)
        goto LAB35;

LAB34:    t20 = (t0 + 16984);
    t28 = *((char **)t20);
    t20 = (t0 + 10008);
    t29 = (t20 + 56U);
    t30 = *((char **)t29);
    memcpy(t26, t30, 8);
    t48 = (t0 + 1712);
    t49 = (t0 + 16888);
    t50 = 0;
    xsi_delete_subprogram_invocation(t48, t28, t0, t49, t50);
    t51 = (t0 + 6808);
    xsi_vlogvar_assign_value(t51, t26, 0, 0, 1);
    goto LAB19;

LAB11:    xsi_set_current_line(111, ng72);

LAB36:    xsi_set_current_line(113, ng72);
    t3 = ((char*)((ng2)));
    t4 = (t0 + 8888);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 32);
    xsi_set_current_line(114, ng72);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 8088);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 32);
    xsi_set_current_line(116, ng72);
    t2 = (t0 + 8088);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t7 = (t0 + 8888);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    t10 = (t0 + 16888);
    t11 = (t0 + 2144);
    t12 = xsi_create_subprogram_invocation(t10, 0, t0, t11, 0, 0);
    t13 = (t0 + 10808);
    xsi_vlogvar_assign_value(t13, t4, 0, 0, 32);
    t14 = (t0 + 10968);
    xsi_vlogvar_assign_value(t14, t9, 0, 0, 32);

LAB37:    t15 = (t0 + 16984);
    t16 = *((char **)t15);
    t17 = (t16 + 80U);
    t18 = *((char **)t17);
    t19 = (t18 + 272U);
    t20 = *((char **)t19);
    t21 = (t20 + 0U);
    t22 = *((char **)t21);
    t6 = ((int  (*)(char *, char *))t22)(t0, t16);
    if (t6 != 0)
        goto LAB39;

LAB38:    t16 = (t0 + 16984);
    t23 = *((char **)t16);
    t16 = (t0 + 10648);
    t24 = (t16 + 56U);
    t25 = *((char **)t24);
    memcpy(t26, t25, 8);
    t27 = (t0 + 2144);
    t28 = (t0 + 16888);
    t29 = 0;
    xsi_delete_subprogram_invocation(t27, t23, t0, t28, t29);
    t30 = (t0 + 6808);
    xsi_vlogvar_assign_value(t30, t26, 0, 0, 1);
    goto LAB19;

LAB13:    xsi_set_current_line(125, ng72);

LAB40:    xsi_set_current_line(126, ng72);
    t3 = ((char*)((ng83)));
    t4 = (t0 + 8888);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 32);
    xsi_set_current_line(127, ng72);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 8088);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 32);
    xsi_set_current_line(129, ng72);
    t2 = (t0 + 8088);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t7 = (t0 + 8888);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    t10 = (t0 + 16888);
    t11 = (t0 + 2576);
    t12 = xsi_create_subprogram_invocation(t10, 0, t0, t11, 0, 0);
    t13 = (t0 + 11288);
    xsi_vlogvar_assign_value(t13, t4, 0, 0, 32);
    t14 = (t0 + 11448);
    xsi_vlogvar_assign_value(t14, t9, 0, 0, 32);

LAB41:    t15 = (t0 + 16984);
    t16 = *((char **)t15);
    t17 = (t16 + 80U);
    t18 = *((char **)t17);
    t19 = (t18 + 272U);
    t20 = *((char **)t19);
    t21 = (t20 + 0U);
    t22 = *((char **)t21);
    t6 = ((int  (*)(char *, char *))t22)(t0, t16);
    if (t6 != 0)
        goto LAB43;

LAB42:    t16 = (t0 + 16984);
    t23 = *((char **)t16);
    t16 = (t0 + 11128);
    t24 = (t16 + 56U);
    t25 = *((char **)t24);
    memcpy(t26, t25, 8);
    t27 = (t0 + 2576);
    t28 = (t0 + 16888);
    t29 = 0;
    xsi_delete_subprogram_invocation(t27, t23, t0, t28, t29);
    t30 = (t0 + 6808);
    xsi_vlogvar_assign_value(t30, t26, 0, 0, 1);
    goto LAB19;

LAB15:    xsi_set_current_line(134, ng72);

LAB44:    xsi_set_current_line(135, ng72);
    t3 = ((char*)((ng84)));
    t4 = (t0 + 8408);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 32);
    xsi_set_current_line(136, ng72);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 8088);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 32);
    xsi_set_current_line(137, ng72);
    t2 = (t0 + 8088);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t7 = (t0 + 8408);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    t10 = (t0 + 16888);
    t11 = (t0 + 1280);
    t12 = xsi_create_subprogram_invocation(t10, 0, t0, t11, 0, 0);
    t13 = (t0 + 9688);
    xsi_vlogvar_assign_value(t13, t4, 0, 0, 32);
    t14 = (t0 + 9848);
    xsi_vlogvar_assign_value(t14, t9, 0, 0, 32);

LAB45:    t15 = (t0 + 16984);
    t16 = *((char **)t15);
    t17 = (t16 + 80U);
    t18 = *((char **)t17);
    t19 = (t18 + 272U);
    t20 = *((char **)t19);
    t21 = (t20 + 0U);
    t22 = *((char **)t21);
    t6 = ((int  (*)(char *, char *))t22)(t0, t16);
    if (t6 != 0)
        goto LAB47;

LAB46:    t16 = (t0 + 16984);
    t23 = *((char **)t16);
    t16 = (t0 + 9528);
    t24 = (t16 + 56U);
    t25 = *((char **)t24);
    memcpy(t26, t25, 8);
    t27 = (t0 + 1280);
    t28 = (t0 + 16888);
    t29 = 0;
    xsi_delete_subprogram_invocation(t27, t23, t0, t28, t29);
    t30 = (t0 + 6808);
    xsi_vlogvar_assign_value(t30, t26, 0, 0, 1);
    goto LAB19;

LAB23:    t15 = (t0 + 17080U);
    *((char **)t15) = &&LAB21;
    goto LAB1;

LAB26:    t8 = (t26 + 4);
    *((unsigned int *)t26) = 1;
    *((unsigned int *)t8) = 1;
    goto LAB27;

LAB28:    xsi_set_current_line(96, ng72);

LAB31:    xsi_set_current_line(97, ng72);
    t10 = (t0 + 8568);
    t11 = (t10 + 56U);
    t12 = *((char **)t11);
    t13 = (t0 + 7768);
    xsi_vlogvar_assign_value(t13, t12, 0, 0, 32);
    goto LAB30;

LAB35:    t19 = (t0 + 17080U);
    *((char **)t19) = &&LAB33;
    goto LAB1;

LAB39:    t15 = (t0 + 17080U);
    *((char **)t15) = &&LAB37;
    goto LAB1;

LAB43:    t15 = (t0 + 17080U);
    *((char **)t15) = &&LAB41;
    goto LAB1;

LAB47:    t15 = (t0 + 17080U);
    *((char **)t15) = &&LAB45;
    goto LAB1;

}


extern void work_m_00000000003655756831_2524751178_init()
{
	static char *pe[] = {(void *)Cont_20_0,(void *)Cont_36_1,(void *)Cont_37_2,(void *)NetDecl_39_3,(void *)NetDecl_40_4,(void *)NetDecl_41_5,(void *)NetDecl_43_6,(void *)NetDecl_44_7,(void *)NetDecl_45_8,(void *)NetDecl_46_9,(void *)NetDecl_47_10,(void *)NetDecl_49_11,(void *)NetDecl_51_12,(void *)NetDecl_52_13,(void *)NetDecl_53_14,(void *)NetDecl_54_15,(void *)NetDecl_55_16,(void *)NetDecl_56_17,(void *)Initial_70_18,(void *)Always_87_19};
	static char *se[] = {(void *)sp_TEST_LDI,(void *)sp_TEST_IN,(void *)sp_TEST_OUT,(void *)sp_TEST_SBI,(void *)sp_TEST_CBI};
	xsi_register_didat("work_m_00000000003655756831_2524751178", "isim/unitTestCpu_isim_beh.exe.sim/work/m_00000000003655756831_2524751178.didat");
	xsi_register_executes(pe);
	xsi_register_subprogram_executes(se);
}
