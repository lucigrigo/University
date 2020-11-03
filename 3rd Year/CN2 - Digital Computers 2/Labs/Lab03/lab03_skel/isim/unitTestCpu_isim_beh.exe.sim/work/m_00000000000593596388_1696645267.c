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
static const char *ng0 = "C:/Users/student/Desktop/lab03_skel/rom.v";
static int ng1[] = {0, 0};
static unsigned int ng2[] = {57562U, 0U};
static int ng3[] = {1, 0};
static unsigned int ng4[] = {43226U, 0U};
static int ng5[] = {2, 0};
static unsigned int ng6[] = {57552U, 0U};
static int ng7[] = {3, 0};
static unsigned int ng8[] = {59594U, 0U};
static int ng9[] = {4, 0};
static unsigned int ng10[] = {33208U, 0U};
static int ng11[] = {5, 0};
static unsigned int ng12[] = {41162U, 0U};
static int ng13[] = {6, 0};
static unsigned int ng14[] = {12220U, 0U};
static unsigned int ng15[] = {0U, 0U};



static void Always_13_0(char *t0)
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

LAB2:    xsi_set_current_line(13, ng0);
    t2 = (t0 + 3528);
    *((int *)t2) = 1;
    t3 = (t0 + 2992);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(13, ng0);

LAB5:    xsi_set_current_line(14, ng0);
    t4 = (t0 + 1480U);
    t5 = *((char **)t4);

LAB6:    t4 = ((char*)((ng1)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t4, 32);
    if (t6 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng3)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng5)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB11;

LAB12:    t2 = ((char*)((ng7)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB13;

LAB14:    t2 = ((char*)((ng9)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng11)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB17;

LAB18:    t2 = ((char*)((ng13)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB19;

LAB20:
LAB22:
LAB21:    xsi_set_current_line(29, ng0);
    t2 = ((char*)((ng15)));
    t3 = (t0 + 2040);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 16);

LAB23:    goto LAB2;

LAB7:    xsi_set_current_line(16, ng0);
    t7 = ((char*)((ng2)));
    t8 = (t0 + 2040);
    xsi_vlogvar_assign_value(t8, t7, 0, 0, 16);
    goto LAB23;

LAB9:    xsi_set_current_line(18, ng0);
    t3 = ((char*)((ng4)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB23;

LAB11:    xsi_set_current_line(20, ng0);
    t3 = ((char*)((ng6)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB23;

LAB13:    xsi_set_current_line(22, ng0);
    t3 = ((char*)((ng8)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB23;

LAB15:    xsi_set_current_line(24, ng0);
    t3 = ((char*)((ng10)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB23;

LAB17:    xsi_set_current_line(26, ng0);
    t3 = ((char*)((ng12)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB23;

LAB19:    xsi_set_current_line(28, ng0);
    t3 = ((char*)((ng14)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB23;

}

static void Always_34_1(char *t0)
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

LAB2:    xsi_set_current_line(34, ng0);
    t2 = (t0 + 3544);
    *((int *)t2) = 1;
    t3 = (t0 + 3240);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(34, ng0);

LAB5:    xsi_set_current_line(35, ng0);
    t4 = (t0 + 2040);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = (t0 + 1880);
    xsi_vlogvar_wait_assign_value(t7, t6, 0, 0, 16, 0LL);
    goto LAB2;

}


extern void work_m_00000000000593596388_1696645267_init()
{
	static char *pe[] = {(void *)Always_13_0,(void *)Always_34_1};
	xsi_register_didat("work_m_00000000000593596388_1696645267", "isim/unitTestCpu_isim_beh.exe.sim/work/m_00000000000593596388_1696645267.didat");
	xsi_register_executes(pe);
}
