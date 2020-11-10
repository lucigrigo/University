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
static const char *ng0 = "C:/Users/student/Desktop/skel_lab04/sram.v";
static int ng1[] = {0, 0};
static int ng2[] = {1, 0};
static unsigned int ng3[] = {0U, 255U};



static void Initial_18_0(char *t0)
{
    char t7[8];
    char t8[8];
    char t19[8];
    char t20[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t9;
    char *t10;
    char *t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    char *t17;
    char *t18;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    char *t27;
    char *t28;
    char *t29;
    char *t30;
    unsigned int t31;
    int t32;
    char *t33;
    unsigned int t34;
    int t35;
    int t36;
    unsigned int t37;
    unsigned int t38;
    int t39;
    int t40;

LAB0:    xsi_set_current_line(18, ng0);

LAB2:    xsi_set_current_line(19, ng0);
    xsi_set_current_line(19, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 2840);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 8);

LAB3:    t1 = (t0 + 2840);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = ((char*)((ng2)));
    t5 = (t0 + 608);
    t6 = *((char **)t5);
    memset(t7, 0, 8);
    xsi_vlog_unsigned_lshift(t7, 32, t4, 32, t6, 32);
    memset(t8, 0, 8);
    t5 = (t3 + 4);
    if (*((unsigned int *)t5) != 0)
        goto LAB5;

LAB4:    t9 = (t7 + 4);
    if (*((unsigned int *)t9) != 0)
        goto LAB5;

LAB8:    if (*((unsigned int *)t3) < *((unsigned int *)t7))
        goto LAB6;

LAB7:    t11 = (t8 + 4);
    t12 = *((unsigned int *)t11);
    t13 = (~(t12));
    t14 = *((unsigned int *)t8);
    t15 = (t14 & t13);
    t16 = (t15 != 0);
    if (t16 > 0)
        goto LAB9;

LAB10:
LAB1:    return;
LAB5:    t10 = (t8 + 4);
    *((unsigned int *)t8) = 1;
    *((unsigned int *)t10) = 1;
    goto LAB7;

LAB6:    *((unsigned int *)t8) = 1;
    goto LAB7;

LAB9:    xsi_set_current_line(19, ng0);

LAB11:    xsi_set_current_line(20, ng0);
    t17 = ((char*)((ng1)));
    t18 = (t0 + 2520);
    t21 = (t0 + 2520);
    t22 = (t21 + 72U);
    t23 = *((char **)t22);
    t24 = (t0 + 2520);
    t25 = (t24 + 64U);
    t26 = *((char **)t25);
    t27 = (t0 + 2840);
    t28 = (t27 + 56U);
    t29 = *((char **)t28);
    xsi_vlog_generic_convert_array_indices(t19, t20, t23, t26, 2, 1, t29, 8, 2);
    t30 = (t19 + 4);
    t31 = *((unsigned int *)t30);
    t32 = (!(t31));
    t33 = (t20 + 4);
    t34 = *((unsigned int *)t33);
    t35 = (!(t34));
    t36 = (t32 && t35);
    if (t36 == 1)
        goto LAB12;

LAB13:    xsi_set_current_line(19, ng0);
    t1 = (t0 + 2840);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = ((char*)((ng2)));
    memset(t7, 0, 8);
    xsi_vlog_unsigned_add(t7, 32, t3, 8, t4, 32);
    t5 = (t0 + 2840);
    xsi_vlogvar_assign_value(t5, t7, 0, 0, 8);
    goto LAB3;

LAB12:    t37 = *((unsigned int *)t19);
    t38 = *((unsigned int *)t20);
    t39 = (t37 - t38);
    t40 = (t39 + 1);
    xsi_vlogvar_wait_assign_value(t18, t17, 0, *((unsigned int *)t20), t40, 0LL);
    goto LAB13;

}

static void Always_24_1(char *t0)
{
    char t20[8];
    char t21[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    char *t11;
    char *t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    char *t18;
    char *t19;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    char *t27;
    char *t28;
    char *t29;
    unsigned int t30;
    int t31;
    char *t32;
    unsigned int t33;
    int t34;
    int t35;
    unsigned int t36;
    unsigned int t37;
    int t38;
    int t39;

LAB0:    t1 = (t0 + 4008U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(24, ng0);
    t2 = (t0 + 4576);
    *((int *)t2) = 1;
    t3 = (t0 + 4040);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(25, ng0);

LAB5:    xsi_set_current_line(26, ng0);
    t4 = (t0 + 1640U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:
LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(26, ng0);

LAB9:    xsi_set_current_line(27, ng0);
    t11 = (t0 + 1800U);
    t12 = *((char **)t11);
    t11 = (t12 + 4);
    t13 = *((unsigned int *)t11);
    t14 = (~(t13));
    t15 = *((unsigned int *)t12);
    t16 = (t15 & t14);
    t17 = (t16 != 0);
    if (t17 > 0)
        goto LAB10;

LAB11:    xsi_set_current_line(29, ng0);

LAB16:    xsi_set_current_line(30, ng0);
    t2 = (t0 + 1960U);
    t3 = *((char **)t2);
    t2 = (t0 + 2680);
    xsi_vlogvar_wait_assign_value(t2, t3, 0, 0, 7, 0LL);

LAB12:    goto LAB8;

LAB10:    xsi_set_current_line(27, ng0);

LAB13:    xsi_set_current_line(28, ng0);
    t18 = (t0 + 2120U);
    t19 = *((char **)t18);
    t18 = (t0 + 2520);
    t22 = (t0 + 2520);
    t23 = (t22 + 72U);
    t24 = *((char **)t23);
    t25 = (t0 + 2520);
    t26 = (t25 + 64U);
    t27 = *((char **)t26);
    t28 = (t0 + 1960U);
    t29 = *((char **)t28);
    xsi_vlog_generic_convert_array_indices(t20, t21, t24, t27, 2, 1, t29, 7, 2);
    t28 = (t20 + 4);
    t30 = *((unsigned int *)t28);
    t31 = (!(t30));
    t32 = (t21 + 4);
    t33 = *((unsigned int *)t32);
    t34 = (!(t33));
    t35 = (t31 && t34);
    if (t35 == 1)
        goto LAB14;

LAB15:    goto LAB12;

LAB14:    t36 = *((unsigned int *)t20);
    t37 = *((unsigned int *)t21);
    t38 = (t36 - t37);
    t39 = (t38 + 1);
    xsi_vlogvar_wait_assign_value(t18, t19, 0, *((unsigned int *)t21), t39, 0LL);
    goto LAB15;

}

static void Cont_35_2(char *t0)
{
    char t3[8];
    char t4[8];
    char t6[8];
    char t19[8];
    char t26[8];
    char t58[8];
    char t70[8];
    char t79[8];
    char t87[8];
    char t133[8];
    char *t1;
    char *t2;
    char *t5;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    char *t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    char *t17;
    char *t18;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    char *t25;
    unsigned int t27;
    unsigned int t28;
    unsigned int t29;
    char *t30;
    char *t31;
    char *t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    char *t40;
    char *t41;
    unsigned int t42;
    unsigned int t43;
    unsigned int t44;
    unsigned int t45;
    unsigned int t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    int t50;
    int t51;
    unsigned int t52;
    unsigned int t53;
    unsigned int t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    char *t59;
    unsigned int t60;
    unsigned int t61;
    unsigned int t62;
    unsigned int t63;
    unsigned int t64;
    char *t65;
    char *t66;
    unsigned int t67;
    unsigned int t68;
    unsigned int t69;
    char *t71;
    char *t72;
    unsigned int t73;
    unsigned int t74;
    unsigned int t75;
    unsigned int t76;
    unsigned int t77;
    char *t78;
    char *t80;
    unsigned int t81;
    unsigned int t82;
    unsigned int t83;
    unsigned int t84;
    unsigned int t85;
    char *t86;
    unsigned int t88;
    unsigned int t89;
    unsigned int t90;
    char *t91;
    char *t92;
    char *t93;
    unsigned int t94;
    unsigned int t95;
    unsigned int t96;
    unsigned int t97;
    unsigned int t98;
    unsigned int t99;
    unsigned int t100;
    char *t101;
    char *t102;
    unsigned int t103;
    unsigned int t104;
    unsigned int t105;
    unsigned int t106;
    unsigned int t107;
    unsigned int t108;
    unsigned int t109;
    unsigned int t110;
    int t111;
    int t112;
    unsigned int t113;
    unsigned int t114;
    unsigned int t115;
    unsigned int t116;
    unsigned int t117;
    unsigned int t118;
    char *t119;
    unsigned int t120;
    unsigned int t121;
    unsigned int t122;
    unsigned int t123;
    unsigned int t124;
    char *t125;
    char *t126;
    unsigned int t127;
    unsigned int t128;
    unsigned int t129;
    char *t130;
    char *t131;
    char *t132;
    char *t134;
    char *t135;
    char *t136;
    char *t137;
    char *t138;
    char *t139;
    char *t140;
    char *t141;
    char *t142;
    unsigned int t143;
    unsigned int t144;
    unsigned int t145;
    unsigned int t146;
    char *t147;
    char *t148;
    char *t149;
    char *t150;
    char *t151;
    char *t152;
    unsigned int t153;
    unsigned int t154;
    char *t155;
    unsigned int t156;
    unsigned int t157;
    char *t158;
    unsigned int t159;
    unsigned int t160;
    char *t161;

LAB0:    t1 = (t0 + 4256U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(35, ng0);
    t2 = (t0 + 1640U);
    t5 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t5 + 4);
    t7 = *((unsigned int *)t2);
    t8 = (~(t7));
    t9 = *((unsigned int *)t5);
    t10 = (t9 & t8);
    t11 = (t10 & 1U);
    if (t11 != 0)
        goto LAB4;

LAB5:    if (*((unsigned int *)t2) != 0)
        goto LAB6;

LAB7:    t13 = (t6 + 4);
    t14 = *((unsigned int *)t6);
    t15 = *((unsigned int *)t13);
    t16 = (t14 || t15);
    if (t16 > 0)
        goto LAB8;

LAB9:    memcpy(t26, t6, 8);

LAB10:    memset(t58, 0, 8);
    t59 = (t26 + 4);
    t60 = *((unsigned int *)t59);
    t61 = (~(t60));
    t62 = *((unsigned int *)t26);
    t63 = (t62 & t61);
    t64 = (t63 & 1U);
    if (t64 != 0)
        goto LAB18;

LAB19:    if (*((unsigned int *)t59) != 0)
        goto LAB20;

LAB21:    t66 = (t58 + 4);
    t67 = *((unsigned int *)t58);
    t68 = *((unsigned int *)t66);
    t69 = (t67 || t68);
    if (t69 > 0)
        goto LAB22;

LAB23:    memcpy(t87, t58, 8);

LAB24:    memset(t4, 0, 8);
    t119 = (t87 + 4);
    t120 = *((unsigned int *)t119);
    t121 = (~(t120));
    t122 = *((unsigned int *)t87);
    t123 = (t122 & t121);
    t124 = (t123 & 1U);
    if (t124 != 0)
        goto LAB36;

LAB37:    if (*((unsigned int *)t119) != 0)
        goto LAB38;

LAB39:    t126 = (t4 + 4);
    t127 = *((unsigned int *)t4);
    t128 = *((unsigned int *)t126);
    t129 = (t127 || t128);
    if (t129 > 0)
        goto LAB40;

LAB41:    t143 = *((unsigned int *)t4);
    t144 = (~(t143));
    t145 = *((unsigned int *)t126);
    t146 = (t144 || t145);
    if (t146 > 0)
        goto LAB42;

LAB43:    if (*((unsigned int *)t126) > 0)
        goto LAB44;

LAB45:    if (*((unsigned int *)t4) > 0)
        goto LAB46;

LAB47:    memcpy(t3, t147, 8);

LAB48:    t148 = (t0 + 4672);
    t149 = (t148 + 56U);
    t150 = *((char **)t149);
    t151 = (t150 + 56U);
    t152 = *((char **)t151);
    memset(t152, 0, 8);
    t153 = 255U;
    t154 = t153;
    t155 = (t3 + 4);
    t156 = *((unsigned int *)t3);
    t153 = (t153 & t156);
    t157 = *((unsigned int *)t155);
    t154 = (t154 & t157);
    t158 = (t152 + 4);
    t159 = *((unsigned int *)t152);
    *((unsigned int *)t152) = (t159 | t153);
    t160 = *((unsigned int *)t158);
    *((unsigned int *)t158) = (t160 | t154);
    xsi_driver_vfirst_trans(t148, 0, 7);
    t161 = (t0 + 4592);
    *((int *)t161) = 1;

LAB1:    return;
LAB4:    *((unsigned int *)t6) = 1;
    goto LAB7;

LAB6:    t12 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t12) = 1;
    goto LAB7;

LAB8:    t17 = (t0 + 1480U);
    t18 = *((char **)t17);
    memset(t19, 0, 8);
    t17 = (t18 + 4);
    t20 = *((unsigned int *)t17);
    t21 = (~(t20));
    t22 = *((unsigned int *)t18);
    t23 = (t22 & t21);
    t24 = (t23 & 1U);
    if (t24 != 0)
        goto LAB11;

LAB12:    if (*((unsigned int *)t17) != 0)
        goto LAB13;

LAB14:    t27 = *((unsigned int *)t6);
    t28 = *((unsigned int *)t19);
    t29 = (t27 & t28);
    *((unsigned int *)t26) = t29;
    t30 = (t6 + 4);
    t31 = (t19 + 4);
    t32 = (t26 + 4);
    t33 = *((unsigned int *)t30);
    t34 = *((unsigned int *)t31);
    t35 = (t33 | t34);
    *((unsigned int *)t32) = t35;
    t36 = *((unsigned int *)t32);
    t37 = (t36 != 0);
    if (t37 == 1)
        goto LAB15;

LAB16:
LAB17:    goto LAB10;

LAB11:    *((unsigned int *)t19) = 1;
    goto LAB14;

LAB13:    t25 = (t19 + 4);
    *((unsigned int *)t19) = 1;
    *((unsigned int *)t25) = 1;
    goto LAB14;

LAB15:    t38 = *((unsigned int *)t26);
    t39 = *((unsigned int *)t32);
    *((unsigned int *)t26) = (t38 | t39);
    t40 = (t6 + 4);
    t41 = (t19 + 4);
    t42 = *((unsigned int *)t6);
    t43 = (~(t42));
    t44 = *((unsigned int *)t40);
    t45 = (~(t44));
    t46 = *((unsigned int *)t19);
    t47 = (~(t46));
    t48 = *((unsigned int *)t41);
    t49 = (~(t48));
    t50 = (t43 & t45);
    t51 = (t47 & t49);
    t52 = (~(t50));
    t53 = (~(t51));
    t54 = *((unsigned int *)t32);
    *((unsigned int *)t32) = (t54 & t52);
    t55 = *((unsigned int *)t32);
    *((unsigned int *)t32) = (t55 & t53);
    t56 = *((unsigned int *)t26);
    *((unsigned int *)t26) = (t56 & t52);
    t57 = *((unsigned int *)t26);
    *((unsigned int *)t26) = (t57 & t53);
    goto LAB17;

LAB18:    *((unsigned int *)t58) = 1;
    goto LAB21;

LAB20:    t65 = (t58 + 4);
    *((unsigned int *)t58) = 1;
    *((unsigned int *)t65) = 1;
    goto LAB21;

LAB22:    t71 = (t0 + 1800U);
    t72 = *((char **)t71);
    memset(t70, 0, 8);
    t71 = (t72 + 4);
    t73 = *((unsigned int *)t71);
    t74 = (~(t73));
    t75 = *((unsigned int *)t72);
    t76 = (t75 & t74);
    t77 = (t76 & 1U);
    if (t77 != 0)
        goto LAB28;

LAB26:    if (*((unsigned int *)t71) == 0)
        goto LAB25;

LAB27:    t78 = (t70 + 4);
    *((unsigned int *)t70) = 1;
    *((unsigned int *)t78) = 1;

LAB28:    memset(t79, 0, 8);
    t80 = (t70 + 4);
    t81 = *((unsigned int *)t80);
    t82 = (~(t81));
    t83 = *((unsigned int *)t70);
    t84 = (t83 & t82);
    t85 = (t84 & 1U);
    if (t85 != 0)
        goto LAB29;

LAB30:    if (*((unsigned int *)t80) != 0)
        goto LAB31;

LAB32:    t88 = *((unsigned int *)t58);
    t89 = *((unsigned int *)t79);
    t90 = (t88 & t89);
    *((unsigned int *)t87) = t90;
    t91 = (t58 + 4);
    t92 = (t79 + 4);
    t93 = (t87 + 4);
    t94 = *((unsigned int *)t91);
    t95 = *((unsigned int *)t92);
    t96 = (t94 | t95);
    *((unsigned int *)t93) = t96;
    t97 = *((unsigned int *)t93);
    t98 = (t97 != 0);
    if (t98 == 1)
        goto LAB33;

LAB34:
LAB35:    goto LAB24;

LAB25:    *((unsigned int *)t70) = 1;
    goto LAB28;

LAB29:    *((unsigned int *)t79) = 1;
    goto LAB32;

LAB31:    t86 = (t79 + 4);
    *((unsigned int *)t79) = 1;
    *((unsigned int *)t86) = 1;
    goto LAB32;

LAB33:    t99 = *((unsigned int *)t87);
    t100 = *((unsigned int *)t93);
    *((unsigned int *)t87) = (t99 | t100);
    t101 = (t58 + 4);
    t102 = (t79 + 4);
    t103 = *((unsigned int *)t58);
    t104 = (~(t103));
    t105 = *((unsigned int *)t101);
    t106 = (~(t105));
    t107 = *((unsigned int *)t79);
    t108 = (~(t107));
    t109 = *((unsigned int *)t102);
    t110 = (~(t109));
    t111 = (t104 & t106);
    t112 = (t108 & t110);
    t113 = (~(t111));
    t114 = (~(t112));
    t115 = *((unsigned int *)t93);
    *((unsigned int *)t93) = (t115 & t113);
    t116 = *((unsigned int *)t93);
    *((unsigned int *)t93) = (t116 & t114);
    t117 = *((unsigned int *)t87);
    *((unsigned int *)t87) = (t117 & t113);
    t118 = *((unsigned int *)t87);
    *((unsigned int *)t87) = (t118 & t114);
    goto LAB35;

LAB36:    *((unsigned int *)t4) = 1;
    goto LAB39;

LAB38:    t125 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t125) = 1;
    goto LAB39;

LAB40:    t130 = (t0 + 2520);
    t131 = (t130 + 56U);
    t132 = *((char **)t131);
    t134 = (t0 + 2520);
    t135 = (t134 + 72U);
    t136 = *((char **)t135);
    t137 = (t0 + 2520);
    t138 = (t137 + 64U);
    t139 = *((char **)t138);
    t140 = (t0 + 2680);
    t141 = (t140 + 56U);
    t142 = *((char **)t141);
    xsi_vlog_generic_get_array_select_value(t133, 8, t132, t136, t139, 2, 1, t142, 7, 2);
    goto LAB41;

LAB42:    t147 = ((char*)((ng3)));
    goto LAB43;

LAB44:    xsi_vlog_unsigned_bit_combine(t3, 8, t133, 8, t147, 8);
    goto LAB48;

LAB46:    memcpy(t3, t133, 8);
    goto LAB48;

}


extern void work_m_00000000000173021144_1835084805_init()
{
	static char *pe[] = {(void *)Initial_18_0,(void *)Always_24_1,(void *)Cont_35_2};
	xsi_register_didat("work_m_00000000000173021144_1835084805", "isim/unitTestCpu_isim_beh.exe.sim/work/m_00000000000173021144_1835084805.didat");
	xsi_register_executes(pe);
}
