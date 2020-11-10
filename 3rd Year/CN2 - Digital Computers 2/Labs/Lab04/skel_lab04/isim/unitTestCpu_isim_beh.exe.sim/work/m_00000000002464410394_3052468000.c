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
static const char *ng0 = "C:/Users/student/Desktop/skel_lab04/control_unit.v";
static unsigned int ng1[] = {0U, 0U};
static unsigned int ng2[] = {65535U, 65535U};
static unsigned int ng3[] = {255U, 255U};
static int ng4[] = {0, 0};
static const char *ng5 = "\nPC => %3d";
static int ng6[] = {3, 0};
static int ng7[] = {24, 0};
static int ng8[] = {1, 0};
static int ng9[] = {25, 0};
static int ng10[] = {26, 0};
static int ng11[] = {5, 0};
static int ng12[] = {20, 0};
static unsigned int ng13[] = {191U, 0U};
static int ng14[] = {22, 0};
static int ng15[] = {23, 0};
static int ng16[] = {2, 0};
static unsigned int ng17[] = {15U, 15U};
static int ng18[] = {37, 0};
static int ng19[] = {38, 0};
static int ng20[] = {39, 0};
static int ng21[] = {46, 0};
static int ng22[] = {4, 0};
static int ng23[] = {50, 0};
static int ng24[] = {48, 0};
static int ng25[] = {6, 0};
static int ng26[] = {45, 0};
static int ng27[] = {7, 0};



static void Cont_131_0(char *t0)
{
    char t3[8];
    char t4[8];
    char t6[8];
    char t14[8];
    char t29[8];
    char t37[8];
    char t45[8];
    char t84[8];
    char t85[8];
    char t88[8];
    char t107[8];
    char t116[8];
    char *t1;
    char *t2;
    char *t5;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    char *t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    char *t27;
    char *t28;
    char *t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    char *t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    char *t44;
    unsigned int t46;
    unsigned int t47;
    unsigned int t48;
    char *t49;
    char *t50;
    char *t51;
    unsigned int t52;
    unsigned int t53;
    unsigned int t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    char *t59;
    char *t60;
    unsigned int t61;
    unsigned int t62;
    unsigned int t63;
    int t64;
    unsigned int t65;
    unsigned int t66;
    unsigned int t67;
    int t68;
    unsigned int t69;
    unsigned int t70;
    unsigned int t71;
    unsigned int t72;
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
    char *t86;
    char *t87;
    char *t89;
    unsigned int t90;
    unsigned int t91;
    unsigned int t92;
    unsigned int t93;
    unsigned int t94;
    unsigned int t95;
    char *t96;
    unsigned int t97;
    unsigned int t98;
    unsigned int t99;
    unsigned int t100;
    unsigned int t101;
    char *t102;
    char *t103;
    unsigned int t104;
    unsigned int t105;
    unsigned int t106;
    char *t108;
    char *t109;
    char *t110;
    char *t111;
    unsigned int t112;
    unsigned int t113;
    unsigned int t114;
    unsigned int t115;
    char *t117;
    char *t118;
    char *t119;
    char *t120;
    char *t121;
    char *t122;
    unsigned int t123;
    unsigned int t124;
    unsigned int t125;
    unsigned int t126;
    char *t127;
    char *t128;
    char *t129;
    char *t130;
    char *t131;
    char *t132;
    unsigned int t133;
    unsigned int t134;
    char *t135;
    unsigned int t136;
    unsigned int t137;
    char *t138;
    unsigned int t139;
    unsigned int t140;
    char *t141;

LAB0:    t1 = (t0 + 9448U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(131, ng0);
    t2 = (t0 + 5728U);
    t5 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t6 + 4);
    t7 = (t5 + 4);
    t8 = *((unsigned int *)t5);
    t9 = (t8 >> 6);
    t10 = (t9 & 1);
    *((unsigned int *)t6) = t10;
    t11 = *((unsigned int *)t7);
    t12 = (t11 >> 6);
    t13 = (t12 & 1);
    *((unsigned int *)t2) = t13;
    memset(t14, 0, 8);
    t15 = (t6 + 4);
    t16 = *((unsigned int *)t15);
    t17 = (~(t16));
    t18 = *((unsigned int *)t6);
    t19 = (t18 & t17);
    t20 = (t19 & 1U);
    if (t20 != 0)
        goto LAB4;

LAB5:    if (*((unsigned int *)t15) != 0)
        goto LAB6;

LAB7:    t22 = (t14 + 4);
    t23 = *((unsigned int *)t14);
    t24 = (!(t23));
    t25 = *((unsigned int *)t22);
    t26 = (t24 || t25);
    if (t26 > 0)
        goto LAB8;

LAB9:    memcpy(t45, t14, 8);

LAB10:    memset(t4, 0, 8);
    t73 = (t45 + 4);
    t74 = *((unsigned int *)t73);
    t75 = (~(t74));
    t76 = *((unsigned int *)t45);
    t77 = (t76 & t75);
    t78 = (t77 & 1U);
    if (t78 != 0)
        goto LAB18;

LAB19:    if (*((unsigned int *)t73) != 0)
        goto LAB20;

LAB21:    t80 = (t4 + 4);
    t81 = *((unsigned int *)t4);
    t82 = *((unsigned int *)t80);
    t83 = (t81 || t82);
    if (t83 > 0)
        goto LAB22;

LAB23:    t123 = *((unsigned int *)t4);
    t124 = (~(t123));
    t125 = *((unsigned int *)t80);
    t126 = (t124 || t125);
    if (t126 > 0)
        goto LAB24;

LAB25:    if (*((unsigned int *)t80) > 0)
        goto LAB26;

LAB27:    if (*((unsigned int *)t4) > 0)
        goto LAB28;

LAB29:    memcpy(t3, t127, 8);

LAB30:    t128 = (t0 + 12752);
    t129 = (t128 + 56U);
    t130 = *((char **)t129);
    t131 = (t130 + 56U);
    t132 = *((char **)t131);
    memset(t132, 0, 8);
    t133 = 65535U;
    t134 = t133;
    t135 = (t3 + 4);
    t136 = *((unsigned int *)t3);
    t133 = (t133 & t136);
    t137 = *((unsigned int *)t135);
    t134 = (t134 & t137);
    t138 = (t132 + 4);
    t139 = *((unsigned int *)t132);
    *((unsigned int *)t132) = (t139 | t133);
    t140 = *((unsigned int *)t138);
    *((unsigned int *)t138) = (t140 | t134);
    xsi_driver_vfirst_trans(t128, 0, 15);
    t141 = (t0 + 12496);
    *((int *)t141) = 1;

LAB1:    return;
LAB4:    *((unsigned int *)t14) = 1;
    goto LAB7;

LAB6:    t21 = (t14 + 4);
    *((unsigned int *)t14) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB7;

LAB8:    t27 = (t0 + 5728U);
    t28 = *((char **)t27);
    memset(t29, 0, 8);
    t27 = (t29 + 4);
    t30 = (t28 + 4);
    t31 = *((unsigned int *)t28);
    t32 = (t31 >> 9);
    t33 = (t32 & 1);
    *((unsigned int *)t29) = t33;
    t34 = *((unsigned int *)t30);
    t35 = (t34 >> 9);
    t36 = (t35 & 1);
    *((unsigned int *)t27) = t36;
    memset(t37, 0, 8);
    t38 = (t29 + 4);
    t39 = *((unsigned int *)t38);
    t40 = (~(t39));
    t41 = *((unsigned int *)t29);
    t42 = (t41 & t40);
    t43 = (t42 & 1U);
    if (t43 != 0)
        goto LAB11;

LAB12:    if (*((unsigned int *)t38) != 0)
        goto LAB13;

LAB14:    t46 = *((unsigned int *)t14);
    t47 = *((unsigned int *)t37);
    t48 = (t46 | t47);
    *((unsigned int *)t45) = t48;
    t49 = (t14 + 4);
    t50 = (t37 + 4);
    t51 = (t45 + 4);
    t52 = *((unsigned int *)t49);
    t53 = *((unsigned int *)t50);
    t54 = (t52 | t53);
    *((unsigned int *)t51) = t54;
    t55 = *((unsigned int *)t51);
    t56 = (t55 != 0);
    if (t56 == 1)
        goto LAB15;

LAB16:
LAB17:    goto LAB10;

LAB11:    *((unsigned int *)t37) = 1;
    goto LAB14;

LAB13:    t44 = (t37 + 4);
    *((unsigned int *)t37) = 1;
    *((unsigned int *)t44) = 1;
    goto LAB14;

LAB15:    t57 = *((unsigned int *)t45);
    t58 = *((unsigned int *)t51);
    *((unsigned int *)t45) = (t57 | t58);
    t59 = (t14 + 4);
    t60 = (t37 + 4);
    t61 = *((unsigned int *)t59);
    t62 = (~(t61));
    t63 = *((unsigned int *)t14);
    t64 = (t63 & t62);
    t65 = *((unsigned int *)t60);
    t66 = (~(t65));
    t67 = *((unsigned int *)t37);
    t68 = (t67 & t66);
    t69 = (~(t64));
    t70 = (~(t68));
    t71 = *((unsigned int *)t51);
    *((unsigned int *)t51) = (t71 & t69);
    t72 = *((unsigned int *)t51);
    *((unsigned int *)t51) = (t72 & t70);
    goto LAB17;

LAB18:    *((unsigned int *)t4) = 1;
    goto LAB21;

LAB20:    t79 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t79) = 1;
    goto LAB21;

LAB22:    t86 = (t0 + 5728U);
    t87 = *((char **)t86);
    memset(t88, 0, 8);
    t86 = (t88 + 4);
    t89 = (t87 + 4);
    t90 = *((unsigned int *)t87);
    t91 = (t90 >> 12);
    t92 = (t91 & 1);
    *((unsigned int *)t88) = t92;
    t93 = *((unsigned int *)t89);
    t94 = (t93 >> 12);
    t95 = (t94 & 1);
    *((unsigned int *)t86) = t95;
    memset(t85, 0, 8);
    t96 = (t88 + 4);
    t97 = *((unsigned int *)t96);
    t98 = (~(t97));
    t99 = *((unsigned int *)t88);
    t100 = (t99 & t98);
    t101 = (t100 & 1U);
    if (t101 != 0)
        goto LAB31;

LAB32:    if (*((unsigned int *)t96) != 0)
        goto LAB33;

LAB34:    t103 = (t85 + 4);
    t104 = *((unsigned int *)t85);
    t105 = *((unsigned int *)t103);
    t106 = (t104 || t105);
    if (t106 > 0)
        goto LAB35;

LAB36:    t112 = *((unsigned int *)t85);
    t113 = (~(t112));
    t114 = *((unsigned int *)t103);
    t115 = (t113 || t114);
    if (t115 > 0)
        goto LAB37;

LAB38:    if (*((unsigned int *)t103) > 0)
        goto LAB39;

LAB40:    if (*((unsigned int *)t85) > 0)
        goto LAB41;

LAB42:    memcpy(t84, t116, 8);

LAB43:    goto LAB23;

LAB24:    t127 = ((char*)((ng2)));
    goto LAB25;

LAB26:    xsi_vlog_unsigned_bit_combine(t3, 16, t84, 16, t127, 16);
    goto LAB30;

LAB28:    memcpy(t3, t84, 8);
    goto LAB30;

LAB31:    *((unsigned int *)t85) = 1;
    goto LAB34;

LAB33:    t102 = (t85 + 4);
    *((unsigned int *)t85) = 1;
    *((unsigned int *)t102) = 1;
    goto LAB34;

LAB35:    t108 = (t0 + 8368);
    t109 = (t108 + 56U);
    t110 = *((char **)t109);
    t111 = ((char*)((ng1)));
    xsi_vlogtype_concat(t107, 16, 16, 2U, t111, 8, t110, 8);
    goto LAB36;

LAB37:    t117 = (t0 + 7568);
    t118 = (t117 + 56U);
    t119 = *((char **)t118);
    t120 = (t0 + 7408);
    t121 = (t120 + 56U);
    t122 = *((char **)t121);
    xsi_vlogtype_concat(t116, 16, 16, 2U, t122, 8, t119, 8);
    goto LAB38;

LAB39:    xsi_vlog_unsigned_bit_combine(t84, 16, t107, 16, t116, 16);
    goto LAB43;

LAB41:    memcpy(t84, t107, 8);
    goto LAB43;

}

static void Cont_136_1(char *t0)
{
    char t3[8];
    char t4[8];
    char t6[8];
    char *t1;
    char *t2;
    char *t5;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    char *t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    char *t20;
    char *t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    char *t25;
    char *t26;
    char *t27;
    unsigned int t28;
    unsigned int t29;
    unsigned int t30;
    unsigned int t31;
    char *t32;
    char *t33;
    char *t34;
    char *t35;
    char *t36;
    char *t37;
    unsigned int t38;
    unsigned int t39;
    char *t40;
    unsigned int t41;
    unsigned int t42;
    char *t43;
    unsigned int t44;
    unsigned int t45;
    char *t46;

LAB0:    t1 = (t0 + 9696U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(136, ng0);
    t2 = (t0 + 5408U);
    t5 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t6 + 4);
    t7 = (t5 + 4);
    t8 = *((unsigned int *)t5);
    t9 = (t8 >> 1);
    t10 = (t9 & 1);
    *((unsigned int *)t6) = t10;
    t11 = *((unsigned int *)t7);
    t12 = (t11 >> 1);
    t13 = (t12 & 1);
    *((unsigned int *)t2) = t13;
    memset(t4, 0, 8);
    t14 = (t6 + 4);
    t15 = *((unsigned int *)t14);
    t16 = (~(t15));
    t17 = *((unsigned int *)t6);
    t18 = (t17 & t16);
    t19 = (t18 & 1U);
    if (t19 != 0)
        goto LAB4;

LAB5:    if (*((unsigned int *)t14) != 0)
        goto LAB6;

LAB7:    t21 = (t4 + 4);
    t22 = *((unsigned int *)t4);
    t23 = *((unsigned int *)t21);
    t24 = (t22 || t23);
    if (t24 > 0)
        goto LAB8;

LAB9:    t28 = *((unsigned int *)t4);
    t29 = (~(t28));
    t30 = *((unsigned int *)t21);
    t31 = (t29 || t30);
    if (t31 > 0)
        goto LAB10;

LAB11:    if (*((unsigned int *)t21) > 0)
        goto LAB12;

LAB13:    if (*((unsigned int *)t4) > 0)
        goto LAB14;

LAB15:    memcpy(t3, t32, 8);

LAB16:    t33 = (t0 + 12816);
    t34 = (t33 + 56U);
    t35 = *((char **)t34);
    t36 = (t35 + 56U);
    t37 = *((char **)t36);
    memset(t37, 0, 8);
    t38 = 255U;
    t39 = t38;
    t40 = (t3 + 4);
    t41 = *((unsigned int *)t3);
    t38 = (t38 & t41);
    t42 = *((unsigned int *)t40);
    t39 = (t39 & t42);
    t43 = (t37 + 4);
    t44 = *((unsigned int *)t37);
    *((unsigned int *)t37) = (t44 | t38);
    t45 = *((unsigned int *)t43);
    *((unsigned int *)t43) = (t45 | t39);
    xsi_driver_vfirst_trans(t33, 0, 7);
    t46 = (t0 + 12512);
    *((int *)t46) = 1;

LAB1:    return;
LAB4:    *((unsigned int *)t4) = 1;
    goto LAB7;

LAB6:    t20 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t20) = 1;
    goto LAB7;

LAB8:    t25 = (t0 + 7408);
    t26 = (t25 + 56U);
    t27 = *((char **)t26);
    goto LAB9;

LAB10:    t32 = ((char*)((ng3)));
    goto LAB11;

LAB12:    xsi_vlog_unsigned_bit_combine(t3, 8, t27, 8, t32, 8);
    goto LAB16;

LAB14:    memcpy(t3, t27, 8);
    goto LAB16;

}

static void Always_142_2(char *t0)
{
    char t13[8];
    char t32[8];
    char t38[8];
    char t65[8];
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
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    char *t26;
    char *t27;
    int t28;
    char *t29;
    char *t30;
    char *t31;
    char *t33;
    char *t34;
    char *t35;
    char *t36;
    char *t37;
    char *t39;
    char *t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    unsigned int t44;
    unsigned int t45;
    unsigned int t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    unsigned int t52;
    char *t53;
    char *t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    unsigned int t59;
    char *t60;
    char *t61;
    char *t62;
    char *t63;
    char *t64;

LAB0:    t1 = (t0 + 9944U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(142, ng0);
    t2 = (t0 + 12528);
    *((int *)t2) = 1;
    t3 = (t0 + 9976);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(142, ng0);

LAB5:    xsi_set_current_line(143, ng0);
    t4 = (t0 + 1888U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(146, ng0);
    t2 = (t0 + 2208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng6)));
    memset(t13, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t2);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB13;

LAB10:    if (t18 != 0)
        goto LAB12;

LAB11:    *((unsigned int *)t13) = 1;

LAB13:    t12 = (t13 + 4);
    t21 = *((unsigned int *)t12);
    t22 = (~(t21));
    t23 = *((unsigned int *)t13);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB14;

LAB15:    xsi_set_current_line(177, ng0);
    t2 = (t0 + 2208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng11)));
    memset(t13, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t2);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB53;

LAB50:    if (t18 != 0)
        goto LAB52;

LAB51:    *((unsigned int *)t13) = 1;

LAB53:    t12 = (t13 + 4);
    t21 = *((unsigned int *)t12);
    t22 = (~(t21));
    t23 = *((unsigned int *)t13);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB54;

LAB55:
LAB56:
LAB16:
LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(143, ng0);

LAB9:    xsi_set_current_line(144, ng0);
    t11 = ((char*)((ng4)));
    t12 = (t0 + 7088);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 10, 0LL);
    xsi_set_current_line(145, ng0);
    t2 = ((char*)((ng4)));
    xsi_vlogfile_write(1, 0, 0, ng5, 2, t0, (char)119, t2, 32);
    goto LAB8;

LAB12:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB13;

LAB14:    xsi_set_current_line(146, ng0);

LAB17:    xsi_set_current_line(147, ng0);
    t26 = (t0 + 5568U);
    t27 = *((char **)t26);

LAB18:    t26 = ((char*)((ng7)));
    t28 = xsi_vlog_unsigned_case_compare(t27, 8, t26, 32);
    if (t28 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng9)));
    t28 = xsi_vlog_unsigned_case_compare(t27, 8, t2, 32);
    if (t28 == 1)
        goto LAB21;

LAB22:    t2 = ((char*)((ng10)));
    t28 = xsi_vlog_unsigned_case_compare(t27, 8, t2, 32);
    if (t28 == 1)
        goto LAB23;

LAB24:
LAB26:
LAB25:    xsi_set_current_line(172, ng0);

LAB49:    xsi_set_current_line(173, ng0);
    t2 = (t0 + 7088);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 8528);
    xsi_vlogvar_wait_assign_value(t5, t4, 0, 0, 10, 0LL);

LAB27:    goto LAB16;

LAB19:    xsi_set_current_line(151, ng0);

LAB28:    xsi_set_current_line(152, ng0);
    t29 = (t0 + 8208);
    t30 = (t29 + 56U);
    t31 = *((char **)t30);
    t33 = (t0 + 8208);
    t34 = (t33 + 72U);
    t35 = *((char **)t34);
    t36 = (t0 + 6368U);
    t37 = *((char **)t36);
    xsi_vlog_generic_get_index_select_value(t32, 32, t31, t35, 2, t37, 3, 2);
    t36 = ((char*)((ng8)));
    memset(t38, 0, 8);
    t39 = (t32 + 4);
    t40 = (t36 + 4);
    t41 = *((unsigned int *)t32);
    t42 = *((unsigned int *)t36);
    t43 = (t41 ^ t42);
    t44 = *((unsigned int *)t39);
    t45 = *((unsigned int *)t40);
    t46 = (t44 ^ t45);
    t47 = (t43 | t46);
    t48 = *((unsigned int *)t39);
    t49 = *((unsigned int *)t40);
    t50 = (t48 | t49);
    t51 = (~(t50));
    t52 = (t47 & t51);
    if (t52 != 0)
        goto LAB32;

LAB29:    if (t50 != 0)
        goto LAB31;

LAB30:    *((unsigned int *)t38) = 1;

LAB32:    t54 = (t38 + 4);
    t55 = *((unsigned int *)t54);
    t56 = (~(t55));
    t57 = *((unsigned int *)t38);
    t58 = (t57 & t56);
    t59 = (t58 != 0);
    if (t59 > 0)
        goto LAB33;

LAB34:    xsi_set_current_line(154, ng0);

LAB37:    xsi_set_current_line(155, ng0);
    t2 = (t0 + 7088);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 8528);
    xsi_vlogvar_wait_assign_value(t5, t4, 0, 0, 10, 0LL);

LAB35:    goto LAB27;

LAB21:    xsi_set_current_line(159, ng0);

LAB38:    xsi_set_current_line(160, ng0);
    t3 = (t0 + 8208);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t11 = (t0 + 8208);
    t12 = (t11 + 72U);
    t26 = *((char **)t12);
    t29 = (t0 + 6368U);
    t30 = *((char **)t29);
    xsi_vlog_generic_get_index_select_value(t13, 32, t5, t26, 2, t30, 3, 2);
    t29 = ((char*)((ng4)));
    memset(t32, 0, 8);
    t31 = (t13 + 4);
    t33 = (t29 + 4);
    t6 = *((unsigned int *)t13);
    t7 = *((unsigned int *)t29);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t31);
    t10 = *((unsigned int *)t33);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t31);
    t17 = *((unsigned int *)t33);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB42;

LAB39:    if (t18 != 0)
        goto LAB41;

LAB40:    *((unsigned int *)t32) = 1;

LAB42:    t35 = (t32 + 4);
    t21 = *((unsigned int *)t35);
    t22 = (~(t21));
    t23 = *((unsigned int *)t32);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB43;

LAB44:    xsi_set_current_line(162, ng0);

LAB47:    xsi_set_current_line(163, ng0);
    t2 = (t0 + 7088);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 8528);
    xsi_vlogvar_wait_assign_value(t5, t4, 0, 0, 10, 0LL);

LAB45:    goto LAB27;

LAB23:    xsi_set_current_line(167, ng0);

LAB48:    xsi_set_current_line(168, ng0);
    t3 = (t0 + 7088);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t11 = (t0 + 6208U);
    t12 = *((char **)t11);
    memset(t13, 0, 8);
    xsi_vlog_unsigned_add(t13, 12, t5, 10, t12, 12);
    t11 = (t0 + 8528);
    xsi_vlogvar_wait_assign_value(t11, t13, 0, 0, 10, 0LL);
    goto LAB27;

LAB31:    t53 = (t38 + 4);
    *((unsigned int *)t38) = 1;
    *((unsigned int *)t53) = 1;
    goto LAB32;

LAB33:    xsi_set_current_line(152, ng0);

LAB36:    xsi_set_current_line(153, ng0);
    t60 = (t0 + 7088);
    t61 = (t60 + 56U);
    t62 = *((char **)t61);
    t63 = (t0 + 6208U);
    t64 = *((char **)t63);
    memset(t65, 0, 8);
    xsi_vlog_unsigned_add(t65, 12, t62, 10, t64, 12);
    t63 = (t0 + 8528);
    xsi_vlogvar_wait_assign_value(t63, t65, 0, 0, 10, 0LL);
    goto LAB35;

LAB41:    t34 = (t32 + 4);
    *((unsigned int *)t32) = 1;
    *((unsigned int *)t34) = 1;
    goto LAB42;

LAB43:    xsi_set_current_line(160, ng0);

LAB46:    xsi_set_current_line(161, ng0);
    t36 = (t0 + 7088);
    t37 = (t36 + 56U);
    t39 = *((char **)t37);
    t40 = (t0 + 6208U);
    t53 = *((char **)t40);
    memset(t38, 0, 8);
    xsi_vlog_unsigned_add(t38, 12, t39, 10, t53, 12);
    t40 = (t0 + 8528);
    xsi_vlogvar_wait_assign_value(t40, t38, 0, 0, 10, 0LL);
    goto LAB45;

LAB52:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB53;

LAB54:    xsi_set_current_line(178, ng0);

LAB57:    xsi_set_current_line(179, ng0);
    t26 = (t0 + 8528);
    t29 = (t26 + 56U);
    t30 = *((char **)t29);
    t31 = ((char*)((ng8)));
    memset(t32, 0, 8);
    xsi_vlog_unsigned_add(t32, 32, t30, 10, t31, 32);
    t33 = (t0 + 7088);
    xsi_vlogvar_wait_assign_value(t33, t32, 0, 0, 10, 0LL);
    xsi_set_current_line(180, ng0);
    t2 = (t0 + 7088);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng12)));
    memset(t13, 0, 8);
    t11 = (t4 + 4);
    if (*((unsigned int *)t11) != 0)
        goto LAB59;

LAB58:    t12 = (t5 + 4);
    if (*((unsigned int *)t12) != 0)
        goto LAB59;

LAB62:    if (*((unsigned int *)t4) < *((unsigned int *)t5))
        goto LAB60;

LAB61:    t29 = (t13 + 4);
    t6 = *((unsigned int *)t29);
    t7 = (~(t6));
    t8 = *((unsigned int *)t13);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB63;

LAB64:
LAB65:    goto LAB56;

LAB59:    t26 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t26) = 1;
    goto LAB61;

LAB60:    *((unsigned int *)t13) = 1;
    goto LAB61;

LAB63:    xsi_set_current_line(180, ng0);

LAB66:    xsi_set_current_line(181, ng0);
    t30 = (t0 + 8528);
    t31 = (t30 + 56U);
    t33 = *((char **)t31);
    t34 = ((char*)((ng8)));
    memset(t32, 0, 8);
    xsi_vlog_unsigned_add(t32, 32, t33, 10, t34, 32);
    xsi_vlogfile_write(1, 0, 0, ng5, 2, t0, (char)118, t32, 32);
    goto LAB65;

}

static void Cont_186_3(char *t0)
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

LAB0:    t1 = (t0 + 10192U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(186, ng0);
    t2 = (t0 + 8208);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 12880);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memset(t9, 0, 8);
    t10 = 255U;
    t11 = t10;
    t12 = (t4 + 4);
    t13 = *((unsigned int *)t4);
    t10 = (t10 & t13);
    t14 = *((unsigned int *)t12);
    t11 = (t11 & t14);
    t15 = (t9 + 4);
    t16 = *((unsigned int *)t9);
    *((unsigned int *)t9) = (t16 | t10);
    t17 = *((unsigned int *)t15);
    *((unsigned int *)t15) = (t17 | t11);
    xsi_driver_vfirst_trans(t5, 0, 7);
    t18 = (t0 + 12544);
    *((int *)t18) = 1;

LAB1:    return;
}

static void Always_188_4(char *t0)
{
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

LAB0:    t1 = (t0 + 10440U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(188, ng0);
    t2 = (t0 + 12560);
    *((int *)t2) = 1;
    t3 = (t0 + 10472);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(189, ng0);
    t4 = (t0 + 1888U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB5;

LAB6:    xsi_set_current_line(192, ng0);
    t2 = (t0 + 4288U);
    t3 = *((char **)t2);
    t2 = (t0 + 8208);
    xsi_vlogvar_wait_assign_value(t2, t3, 0, 0, 8, 0LL);

LAB7:    goto LAB2;

LAB5:    xsi_set_current_line(190, ng0);
    t11 = ((char*)((ng4)));
    t12 = (t0 + 8208);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 8, 0LL);
    goto LAB7;

}

static void Always_195_5(char *t0)
{
    char t13[8];
    char t22[8];
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
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    char *t20;
    char *t21;
    char *t23;

LAB0:    t1 = (t0 + 10688U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(195, ng0);
    t2 = (t0 + 12576);
    *((int *)t2) = 1;
    t3 = (t0 + 10720);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(195, ng0);

LAB5:    xsi_set_current_line(196, ng0);
    t4 = (t0 + 1888U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(198, ng0);

LAB9:    xsi_set_current_line(208, ng0);
    t2 = (t0 + 5408U);
    t3 = *((char **)t2);
    memset(t13, 0, 8);
    t2 = (t13 + 4);
    t4 = (t3 + 4);
    t6 = *((unsigned int *)t3);
    t7 = (t6 >> 6);
    t8 = (t7 & 1);
    *((unsigned int *)t13) = t8;
    t9 = *((unsigned int *)t4);
    t10 = (t9 >> 6);
    t14 = (t10 & 1);
    *((unsigned int *)t2) = t14;
    t5 = (t13 + 4);
    t15 = *((unsigned int *)t5);
    t16 = (~(t15));
    t17 = *((unsigned int *)t13);
    t18 = (t17 & t16);
    t19 = (t18 != 0);
    if (t19 > 0)
        goto LAB10;

LAB11:
LAB12:    xsi_set_current_line(211, ng0);
    t2 = (t0 + 5408U);
    t3 = *((char **)t2);
    memset(t13, 0, 8);
    t2 = (t13 + 4);
    t4 = (t3 + 4);
    t6 = *((unsigned int *)t3);
    t7 = (t6 >> 7);
    t8 = (t7 & 1);
    *((unsigned int *)t13) = t8;
    t9 = *((unsigned int *)t4);
    t10 = (t9 >> 7);
    t14 = (t10 & 1);
    *((unsigned int *)t2) = t14;
    t5 = (t13 + 4);
    t15 = *((unsigned int *)t5);
    t16 = (~(t15));
    t17 = *((unsigned int *)t13);
    t18 = (t17 & t16);
    t19 = (t18 != 0);
    if (t19 > 0)
        goto LAB14;

LAB15:
LAB16:
LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(197, ng0);
    t11 = ((char*)((ng13)));
    t12 = (t0 + 8368);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 8, 0LL);
    goto LAB8;

LAB10:    xsi_set_current_line(208, ng0);

LAB13:    xsi_set_current_line(209, ng0);
    t11 = (t0 + 8368);
    t12 = (t11 + 56U);
    t20 = *((char **)t12);
    t21 = ((char*)((ng8)));
    memset(t22, 0, 8);
    xsi_vlog_unsigned_minus(t22, 32, t20, 8, t21, 32);
    t23 = (t0 + 8368);
    xsi_vlogvar_wait_assign_value(t23, t22, 0, 0, 8, 0LL);
    goto LAB12;

LAB14:    xsi_set_current_line(211, ng0);

LAB17:    xsi_set_current_line(212, ng0);
    t11 = (t0 + 8368);
    t12 = (t11 + 56U);
    t20 = *((char **)t12);
    t21 = ((char*)((ng8)));
    memset(t22, 0, 8);
    xsi_vlog_unsigned_add(t22, 32, t20, 8, t21, 32);
    t23 = (t0 + 8368);
    xsi_vlogvar_wait_assign_value(t23, t22, 0, 0, 8, 0LL);
    goto LAB16;

}

static void Always_217_6(char *t0)
{
    char t13[8];
    char t28[8];
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
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    char *t20;
    char *t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    char *t29;
    unsigned int t30;
    unsigned int t31;
    unsigned int t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    char *t36;

LAB0:    t1 = (t0 + 10936U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(217, ng0);
    t2 = (t0 + 12592);
    *((int *)t2) = 1;
    t3 = (t0 + 10968);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(217, ng0);

LAB5:    xsi_set_current_line(221, ng0);
    t4 = (t0 + 1888U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB6;

LAB7:    xsi_set_current_line(223, ng0);
    t2 = (t0 + 5728U);
    t3 = *((char **)t2);
    memset(t13, 0, 8);
    t2 = (t13 + 4);
    t4 = (t3 + 4);
    t6 = *((unsigned int *)t3);
    t7 = (t6 >> 3);
    t8 = (t7 & 1);
    *((unsigned int *)t13) = t8;
    t9 = *((unsigned int *)t4);
    t10 = (t9 >> 3);
    t14 = (t10 & 1);
    *((unsigned int *)t2) = t14;
    t5 = (t13 + 4);
    t15 = *((unsigned int *)t5);
    t16 = (~(t15));
    t17 = *((unsigned int *)t13);
    t18 = (t17 & t16);
    t19 = (t18 != 0);
    if (t19 > 0)
        goto LAB9;

LAB10:    xsi_set_current_line(225, ng0);
    t2 = (t0 + 5408U);
    t3 = *((char **)t2);
    memset(t13, 0, 8);
    t2 = (t13 + 4);
    t4 = (t3 + 4);
    t6 = *((unsigned int *)t3);
    t7 = (t6 >> 0);
    t8 = (t7 & 1);
    *((unsigned int *)t13) = t8;
    t9 = *((unsigned int *)t4);
    t10 = (t9 >> 0);
    t14 = (t10 & 1);
    *((unsigned int *)t2) = t14;
    t5 = (t13 + 4);
    t15 = *((unsigned int *)t5);
    t16 = (~(t15));
    t17 = *((unsigned int *)t13);
    t18 = (t17 & t16);
    t19 = (t18 != 0);
    if (t19 > 0)
        goto LAB12;

LAB13:    xsi_set_current_line(227, ng0);
    t2 = (t0 + 5568U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng14)));
    memset(t13, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t2);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t22 = (t15 & t19);
    if (t22 != 0)
        goto LAB18;

LAB15:    if (t18 != 0)
        goto LAB17;

LAB16:    *((unsigned int *)t13) = 1;

LAB18:    t12 = (t13 + 4);
    t23 = *((unsigned int *)t12);
    t24 = (~(t23));
    t25 = *((unsigned int *)t13);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB19;

LAB20:    xsi_set_current_line(229, ng0);
    t2 = (t0 + 5568U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng15)));
    memset(t13, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t2);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t22 = (t15 & t19);
    if (t22 != 0)
        goto LAB25;

LAB22:    if (t18 != 0)
        goto LAB24;

LAB23:    *((unsigned int *)t13) = 1;

LAB25:    t12 = (t13 + 4);
    t23 = *((unsigned int *)t12);
    t24 = (~(t23));
    t25 = *((unsigned int *)t13);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB26;

LAB27:
LAB28:
LAB21:
LAB14:
LAB11:
LAB8:    goto LAB2;

LAB6:    xsi_set_current_line(222, ng0);
    t11 = ((char*)((ng1)));
    t12 = (t0 + 8048);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 8, 0LL);
    goto LAB8;

LAB9:    xsi_set_current_line(224, ng0);
    t11 = (t0 + 7888);
    t12 = (t11 + 56U);
    t20 = *((char **)t12);
    t21 = (t0 + 8048);
    xsi_vlogvar_wait_assign_value(t21, t20, 0, 0, 8, 0LL);
    goto LAB11;

LAB12:    xsi_set_current_line(226, ng0);
    t11 = (t0 + 4768U);
    t12 = *((char **)t11);
    t11 = (t0 + 8048);
    xsi_vlogvar_wait_assign_value(t11, t12, 0, 0, 8, 0LL);
    goto LAB14;

LAB17:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB18;

LAB19:    xsi_set_current_line(228, ng0);
    t20 = (t0 + 6208U);
    t21 = *((char **)t20);
    memset(t28, 0, 8);
    t20 = (t28 + 4);
    t29 = (t21 + 4);
    t30 = *((unsigned int *)t21);
    t31 = (t30 >> 0);
    *((unsigned int *)t28) = t31;
    t32 = *((unsigned int *)t29);
    t33 = (t32 >> 0);
    *((unsigned int *)t20) = t33;
    t34 = *((unsigned int *)t28);
    *((unsigned int *)t28) = (t34 & 255U);
    t35 = *((unsigned int *)t20);
    *((unsigned int *)t20) = (t35 & 255U);
    t36 = (t0 + 8048);
    xsi_vlogvar_wait_assign_value(t36, t28, 0, 0, 8, 0LL);
    goto LAB21;

LAB24:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB25;

LAB26:    xsi_set_current_line(230, ng0);
    t20 = (t0 + 7408);
    t21 = (t20 + 56U);
    t29 = *((char **)t21);
    t36 = (t0 + 8048);
    xsi_vlogvar_wait_assign_value(t36, t29, 0, 0, 8, 0LL);
    goto LAB28;

}

static void Always_234_7(char *t0)
{
    char t13[8];
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
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    char *t26;
    char *t27;

LAB0:    t1 = (t0 + 11184U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(234, ng0);
    t2 = (t0 + 12608);
    *((int *)t2) = 1;
    t3 = (t0 + 11216);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(235, ng0);
    t4 = (t0 + 1888U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB5;

LAB6:    xsi_set_current_line(237, ng0);
    t2 = (t0 + 2208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng8)));
    memset(t13, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t2);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB11;

LAB8:    if (t18 != 0)
        goto LAB10;

LAB9:    *((unsigned int *)t13) = 1;

LAB11:    t12 = (t13 + 4);
    t21 = *((unsigned int *)t12);
    t22 = (~(t21));
    t23 = *((unsigned int *)t13);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB12;

LAB13:
LAB14:
LAB7:    goto LAB2;

LAB5:    xsi_set_current_line(236, ng0);
    t11 = ((char*)((ng4)));
    t12 = (t0 + 7728);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 16, 0LL);
    goto LAB7;

LAB10:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB11;

LAB12:    xsi_set_current_line(238, ng0);
    t26 = (t0 + 2048U);
    t27 = *((char **)t26);
    t26 = (t0 + 7728);
    xsi_vlogvar_wait_assign_value(t26, t27, 0, 0, 16, 0LL);
    goto LAB14;

}

static void Always_241_8(char *t0)
{
    char t13[8];
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
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    char *t26;
    char *t27;

LAB0:    t1 = (t0 + 11432U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(241, ng0);
    t2 = (t0 + 12624);
    *((int *)t2) = 1;
    t3 = (t0 + 11464);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(242, ng0);
    t4 = (t0 + 1888U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB5;

LAB6:    xsi_set_current_line(244, ng0);
    t2 = (t0 + 2208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng6)));
    memset(t13, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t2);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB11;

LAB8:    if (t18 != 0)
        goto LAB10;

LAB9:    *((unsigned int *)t13) = 1;

LAB11:    t12 = (t13 + 4);
    t21 = *((unsigned int *)t12);
    t22 = (~(t21));
    t23 = *((unsigned int *)t13);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB12;

LAB13:
LAB14:
LAB7:    goto LAB2;

LAB5:    xsi_set_current_line(243, ng0);
    t11 = ((char*)((ng4)));
    t12 = (t0 + 7888);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 8, 0LL);
    goto LAB7;

LAB10:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB11;

LAB12:    xsi_set_current_line(245, ng0);
    t26 = (t0 + 4448U);
    t27 = *((char **)t26);
    t26 = (t0 + 7888);
    xsi_vlogvar_wait_assign_value(t26, t27, 0, 0, 8, 0LL);
    goto LAB14;

}

static void Always_248_9(char *t0)
{
    char t13[8];
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
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    char *t26;
    char *t27;

LAB0:    t1 = (t0 + 11680U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(248, ng0);
    t2 = (t0 + 12640);
    *((int *)t2) = 1;
    t3 = (t0 + 11712);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(249, ng0);
    t4 = (t0 + 1888U);
    t5 = *((char **)t4);
    t4 = (t5 + 4);
    t6 = *((unsigned int *)t4);
    t7 = (~(t6));
    t8 = *((unsigned int *)t5);
    t9 = (t8 & t7);
    t10 = (t9 != 0);
    if (t10 > 0)
        goto LAB5;

LAB6:    xsi_set_current_line(252, ng0);
    t2 = (t0 + 2208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng16)));
    memset(t13, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t6 = *((unsigned int *)t3);
    t7 = *((unsigned int *)t2);
    t8 = (t6 ^ t7);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t14 = (t9 ^ t10);
    t15 = (t8 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB12;

LAB9:    if (t18 != 0)
        goto LAB11;

LAB10:    *((unsigned int *)t13) = 1;

LAB12:    t12 = (t13 + 4);
    t21 = *((unsigned int *)t12);
    t22 = (~(t21));
    t23 = *((unsigned int *)t13);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB13;

LAB14:
LAB15:
LAB7:    goto LAB2;

LAB5:    xsi_set_current_line(249, ng0);

LAB8:    xsi_set_current_line(250, ng0);
    t11 = ((char*)((ng4)));
    t12 = (t0 + 7568);
    xsi_vlogvar_wait_assign_value(t12, t11, 0, 0, 8, 0LL);
    xsi_set_current_line(251, ng0);
    t2 = ((char*)((ng4)));
    t3 = (t0 + 7408);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 8, 0LL);
    goto LAB7;

LAB11:    t11 = (t13 + 4);
    *((unsigned int *)t13) = 1;
    *((unsigned int *)t11) = 1;
    goto LAB12;

LAB13:    xsi_set_current_line(252, ng0);

LAB16:    xsi_set_current_line(253, ng0);
    t26 = (t0 + 2848U);
    t27 = *((char **)t26);
    t26 = (t0 + 7568);
    xsi_vlogvar_wait_assign_value(t26, t27, 0, 0, 8, 0LL);
    xsi_set_current_line(254, ng0);
    t2 = (t0 + 2688U);
    t3 = *((char **)t2);
    t2 = (t0 + 7408);
    xsi_vlogvar_wait_assign_value(t2, t3, 0, 0, 8, 0LL);
    goto LAB15;

}

static void Cont_257_10(char *t0)
{
    char t4[8];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    unsigned int t25;
    unsigned int t26;
    char *t27;
    unsigned int t28;
    unsigned int t29;
    char *t30;
    unsigned int t31;
    unsigned int t32;
    char *t33;

LAB0:    t1 = (t0 + 11928U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(257, ng0);
    t2 = (t0 + 2208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng6)));
    memset(t4, 0, 8);
    t5 = (t3 + 4);
    t6 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t5);
    t11 = *((unsigned int *)t6);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t5);
    t15 = *((unsigned int *)t6);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB7;

LAB4:    if (t16 != 0)
        goto LAB6;

LAB5:    *((unsigned int *)t4) = 1;

LAB7:    t20 = (t0 + 12944);
    t21 = (t20 + 56U);
    t22 = *((char **)t21);
    t23 = (t22 + 56U);
    t24 = *((char **)t23);
    memset(t24, 0, 8);
    t25 = 1U;
    t26 = t25;
    t27 = (t4 + 4);
    t28 = *((unsigned int *)t4);
    t25 = (t25 & t28);
    t29 = *((unsigned int *)t27);
    t26 = (t26 & t29);
    t30 = (t24 + 4);
    t31 = *((unsigned int *)t24);
    *((unsigned int *)t24) = (t31 | t25);
    t32 = *((unsigned int *)t30);
    *((unsigned int *)t30) = (t32 | t26);
    xsi_driver_vfirst_trans(t20, 0, 0);
    t33 = (t0 + 12656);
    *((int *)t33) = 1;

LAB1:    return;
LAB6:    t19 = (t4 + 4);
    *((unsigned int *)t4) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB7;

}

static void Always_261_11(char *t0)
{
    char t6[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    char *t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    char *t28;
    char *t29;
    int t30;

LAB0:    t1 = (t0 + 12176U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(261, ng0);
    t2 = (t0 + 12672);
    *((int *)t2) = 1;
    t3 = (t0 + 12208);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(261, ng0);

LAB5:    xsi_set_current_line(262, ng0);
    t4 = (t0 + 3968U);
    t5 = *((char **)t4);
    t4 = ((char*)((ng4)));
    memset(t6, 0, 8);
    t7 = (t5 + 4);
    t8 = (t4 + 4);
    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t4);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t7);
    t13 = *((unsigned int *)t8);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB9;

LAB6:    if (t18 != 0)
        goto LAB8;

LAB7:    *((unsigned int *)t6) = 1;

LAB9:    t22 = (t6 + 4);
    t23 = *((unsigned int *)t22);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB10;

LAB11:    xsi_set_current_line(264, ng0);

LAB13:    xsi_set_current_line(265, ng0);
    t2 = (t0 + 5568U);
    t3 = *((char **)t2);

LAB14:    t2 = ((char*)((ng18)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 8, t2, 32);
    if (t30 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng19)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 8, t2, 32);
    if (t30 == 1)
        goto LAB17;

LAB18:    t2 = ((char*)((ng20)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 8, t2, 32);
    if (t30 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng21)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 8, t2, 32);
    if (t30 == 1)
        goto LAB21;

LAB22:    t2 = ((char*)((ng23)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 8, t2, 32);
    if (t30 == 1)
        goto LAB23;

LAB24:    t2 = ((char*)((ng24)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 8, t2, 32);
    if (t30 == 1)
        goto LAB25;

LAB26:    t2 = ((char*)((ng26)));
    t30 = xsi_vlog_unsigned_case_compare(t3, 8, t2, 32);
    if (t30 == 1)
        goto LAB27;

LAB28:
LAB30:
LAB29:    xsi_set_current_line(281, ng0);
    t2 = ((char*)((ng4)));
    t4 = (t0 + 7248);
    xsi_vlogvar_assign_value(t4, t2, 0, 0, 4);

LAB31:
LAB12:    goto LAB2;

LAB8:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(263, ng0);
    t28 = ((char*)((ng17)));
    t29 = (t0 + 7248);
    xsi_vlogvar_assign_value(t29, t28, 0, 0, 4);
    goto LAB12;

LAB15:    xsi_set_current_line(267, ng0);
    t4 = ((char*)((ng8)));
    t5 = (t0 + 7248);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 4);
    goto LAB31;

LAB17:    xsi_set_current_line(269, ng0);
    t4 = ((char*)((ng16)));
    t5 = (t0 + 7248);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 4);
    goto LAB31;

LAB19:    xsi_set_current_line(271, ng0);
    t4 = ((char*)((ng6)));
    t5 = (t0 + 7248);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 4);
    goto LAB31;

LAB21:    xsi_set_current_line(273, ng0);
    t4 = ((char*)((ng22)));
    t5 = (t0 + 7248);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 4);
    goto LAB31;

LAB23:    xsi_set_current_line(275, ng0);
    t4 = ((char*)((ng11)));
    t5 = (t0 + 7248);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 4);
    goto LAB31;

LAB25:    xsi_set_current_line(277, ng0);
    t4 = ((char*)((ng25)));
    t5 = (t0 + 7248);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 4);
    goto LAB31;

LAB27:    xsi_set_current_line(279, ng0);
    t4 = ((char*)((ng27)));
    t5 = (t0 + 7248);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 4);
    goto LAB31;

}


extern void work_m_00000000002464410394_3052468000_init()
{
	static char *pe[] = {(void *)Cont_131_0,(void *)Cont_136_1,(void *)Always_142_2,(void *)Cont_186_3,(void *)Always_188_4,(void *)Always_195_5,(void *)Always_217_6,(void *)Always_234_7,(void *)Always_241_8,(void *)Always_248_9,(void *)Cont_257_10,(void *)Always_261_11};
	xsi_register_didat("work_m_00000000002464410394_3052468000", "isim/unitTestCpu_isim_beh.exe.sim/work/m_00000000002464410394_3052468000.didat");
	xsi_register_executes(pe);
}
