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
static const char *ng0 = "C:/Users/student/Desktop/lab07_skel/rom.v";
static int ng1[] = {0, 0};
static unsigned int ng2[] = {57392U, 0U};
static int ng3[] = {1, 0};
static unsigned int ng4[] = {47409U, 0U};
static int ng5[] = {2, 0};
static unsigned int ng6[] = {57408U, 0U};
static int ng7[] = {3, 0};
static unsigned int ng8[] = {47426U, 0U};
static int ng9[] = {4, 0};
static unsigned int ng10[] = {39447U, 0U};
static int ng11[] = {5, 0};
static unsigned int ng12[] = {39440U, 0U};
static int ng13[] = {6, 0};
static unsigned int ng14[] = {38935U, 0U};
static int ng15[] = {7, 0};
static unsigned int ng16[] = {38928U, 0U};
static int ng17[] = {8, 0};
static unsigned int ng18[] = {39446U, 0U};
static int ng19[] = {9, 0};
static unsigned int ng20[] = {39441U, 0U};
static int ng21[] = {10, 0};
static unsigned int ng22[] = {38934U, 0U};
static int ng23[] = {11, 0};
static unsigned int ng24[] = {38929U, 0U};
static int ng25[] = {12, 0};
static unsigned int ng26[] = {39445U, 0U};
static int ng27[] = {13, 0};
static unsigned int ng28[] = {39442U, 0U};
static int ng29[] = {14, 0};
static unsigned int ng30[] = {38933U, 0U};
static int ng31[] = {15, 0};
static unsigned int ng32[] = {38930U, 0U};
static int ng33[] = {16, 0};
static unsigned int ng34[] = {39444U, 0U};
static int ng35[] = {17, 0};
static unsigned int ng36[] = {39443U, 0U};
static int ng37[] = {18, 0};
static unsigned int ng38[] = {38932U, 0U};
static int ng39[] = {19, 0};
static unsigned int ng40[] = {38931U, 0U};
static int ng41[] = {20, 0};
static int ng42[] = {21, 0};
static int ng43[] = {22, 0};
static int ng44[] = {23, 0};
static int ng45[] = {24, 0};
static int ng46[] = {25, 0};
static int ng47[] = {26, 0};
static int ng48[] = {27, 0};
static int ng49[] = {28, 0};
static int ng50[] = {29, 0};
static int ng51[] = {30, 0};
static int ng52[] = {31, 0};
static int ng53[] = {32, 0};
static int ng54[] = {33, 0};
static unsigned int ng55[] = {0U, 0U};



static void Always_12_0(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    int t6;
    char *t7;
    char *t8;

LAB0:    t1 = (t0 + 2960U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(12, ng0);
    t2 = (t0 + 3528);
    *((int *)t2) = 1;
    t3 = (t0 + 2992);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(12, ng0);

LAB5:    xsi_set_current_line(13, ng0);
    t4 = (t0 + 1480U);
    t5 = *((char **)t4);

LAB6:    t4 = ((char*)((ng1)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t4, 32);
    if (t6 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng3)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng5)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB11;

LAB12:    t2 = ((char*)((ng7)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB13;

LAB14:    t2 = ((char*)((ng9)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng11)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB17;

LAB18:    t2 = ((char*)((ng13)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng15)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB21;

LAB22:    t2 = ((char*)((ng17)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB23;

LAB24:    t2 = ((char*)((ng19)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB25;

LAB26:    t2 = ((char*)((ng21)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB27;

LAB28:    t2 = ((char*)((ng23)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB29;

LAB30:    t2 = ((char*)((ng25)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB31;

LAB32:    t2 = ((char*)((ng27)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB33;

LAB34:    t2 = ((char*)((ng29)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB35;

LAB36:    t2 = ((char*)((ng31)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB37;

LAB38:    t2 = ((char*)((ng33)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB39;

LAB40:    t2 = ((char*)((ng35)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB41;

LAB42:    t2 = ((char*)((ng37)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB43;

LAB44:    t2 = ((char*)((ng39)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB45;

LAB46:    t2 = ((char*)((ng41)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB47;

LAB48:    t2 = ((char*)((ng42)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB49;

LAB50:    t2 = ((char*)((ng43)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB51;

LAB52:    t2 = ((char*)((ng44)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB53;

LAB54:    t2 = ((char*)((ng45)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB55;

LAB56:    t2 = ((char*)((ng46)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB57;

LAB58:    t2 = ((char*)((ng47)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB59;

LAB60:    t2 = ((char*)((ng48)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB61;

LAB62:    t2 = ((char*)((ng49)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB63;

LAB64:    t2 = ((char*)((ng50)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB65;

LAB66:    t2 = ((char*)((ng51)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB67;

LAB68:    t2 = ((char*)((ng52)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB69;

LAB70:    t2 = ((char*)((ng53)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB71;

LAB72:    t2 = ((char*)((ng54)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 8, t2, 32);
    if (t6 == 1)
        goto LAB73;

LAB74:
LAB76:
LAB75:    xsi_set_current_line(106, ng0);
    t2 = ((char*)((ng55)));
    t3 = (t0 + 2040);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 16);

LAB77:    goto LAB2;

LAB7:    xsi_set_current_line(39, ng0);
    t7 = ((char*)((ng2)));
    t8 = (t0 + 2040);
    xsi_vlogvar_assign_value(t8, t7, 0, 0, 16);
    goto LAB77;

LAB9:    xsi_set_current_line(41, ng0);
    t3 = ((char*)((ng4)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB11:    xsi_set_current_line(43, ng0);
    t3 = ((char*)((ng6)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB13:    xsi_set_current_line(45, ng0);
    t3 = ((char*)((ng8)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB15:    xsi_set_current_line(47, ng0);
    t3 = ((char*)((ng10)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB17:    xsi_set_current_line(49, ng0);
    t3 = ((char*)((ng12)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB19:    xsi_set_current_line(51, ng0);
    t3 = ((char*)((ng14)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB21:    xsi_set_current_line(53, ng0);
    t3 = ((char*)((ng16)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB23:    xsi_set_current_line(55, ng0);
    t3 = ((char*)((ng18)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB25:    xsi_set_current_line(57, ng0);
    t3 = ((char*)((ng20)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB27:    xsi_set_current_line(59, ng0);
    t3 = ((char*)((ng22)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB29:    xsi_set_current_line(61, ng0);
    t3 = ((char*)((ng24)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB31:    xsi_set_current_line(63, ng0);
    t3 = ((char*)((ng26)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB33:    xsi_set_current_line(65, ng0);
    t3 = ((char*)((ng28)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB35:    xsi_set_current_line(67, ng0);
    t3 = ((char*)((ng30)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB37:    xsi_set_current_line(69, ng0);
    t3 = ((char*)((ng32)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB39:    xsi_set_current_line(71, ng0);
    t3 = ((char*)((ng34)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB41:    xsi_set_current_line(73, ng0);
    t3 = ((char*)((ng36)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB43:    xsi_set_current_line(75, ng0);
    t3 = ((char*)((ng38)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB45:    xsi_set_current_line(77, ng0);
    t3 = ((char*)((ng40)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB47:    xsi_set_current_line(79, ng0);
    t3 = ((char*)((ng34)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB49:    xsi_set_current_line(81, ng0);
    t3 = ((char*)((ng36)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB51:    xsi_set_current_line(83, ng0);
    t3 = ((char*)((ng38)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB53:    xsi_set_current_line(85, ng0);
    t3 = ((char*)((ng40)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB55:    xsi_set_current_line(87, ng0);
    t3 = ((char*)((ng26)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB57:    xsi_set_current_line(89, ng0);
    t3 = ((char*)((ng28)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB59:    xsi_set_current_line(91, ng0);
    t3 = ((char*)((ng30)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB61:    xsi_set_current_line(93, ng0);
    t3 = ((char*)((ng32)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB63:    xsi_set_current_line(95, ng0);
    t3 = ((char*)((ng18)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB65:    xsi_set_current_line(97, ng0);
    t3 = ((char*)((ng20)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB67:    xsi_set_current_line(99, ng0);
    t3 = ((char*)((ng22)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB69:    xsi_set_current_line(101, ng0);
    t3 = ((char*)((ng24)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB71:    xsi_set_current_line(103, ng0);
    t3 = ((char*)((ng10)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

LAB73:    xsi_set_current_line(105, ng0);
    t3 = ((char*)((ng12)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB77;

}

static void Always_111_1(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;

LAB0:    t1 = (t0 + 3208U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(111, ng0);
    t2 = (t0 + 3544);
    *((int *)t2) = 1;
    t3 = (t0 + 3240);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(111, ng0);

LAB5:    xsi_set_current_line(112, ng0);
    t4 = (t0 + 2040);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = (t0 + 1880);
    xsi_vlogvar_wait_assign_value(t7, t6, 0, 0, 16, 0LL);
    goto LAB2;

}


extern void work_m_00000000000593596388_2220189930_init()
{
	static char *pe[] = {(void *)Always_12_0,(void *)Always_111_1};
	xsi_register_didat("work_m_00000000000593596388_2220189930", "isim/rom_isim_beh.exe.sim/work/m_00000000000593596388_2220189930.didat");
	xsi_register_executes(pe);
}
