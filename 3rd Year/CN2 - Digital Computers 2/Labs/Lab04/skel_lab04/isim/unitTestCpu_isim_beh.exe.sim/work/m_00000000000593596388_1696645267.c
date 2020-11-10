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
static const char *ng0 = "C:/Users/student/Desktop/skel_lab04/rom.v";
static int ng1[] = {0, 0};
static unsigned int ng2[] = {57349U, 0U};
static int ng3[] = {1, 0};
static unsigned int ng4[] = {57375U, 0U};
static int ng5[] = {2, 0};
static unsigned int ng6[] = {37647U, 0U};
static int ng7[] = {3, 0};
static unsigned int ng8[] = {37663U, 0U};
static int ng9[] = {4, 0};
static unsigned int ng10[] = {12256U, 0U};
static int ng11[] = {5, 0};
static unsigned int ng12[] = {7137U, 0U};
static int ng13[] = {6, 0};
static unsigned int ng14[] = {61481U, 0U};
static int ng15[] = {7, 0};
static unsigned int ng16[] = {61458U, 0U};
static int ng17[] = {8, 0};
static unsigned int ng18[] = {6913U, 0U};
static int ng19[] = {9, 0};
static unsigned int ng20[] = {53242U, 0U};
static int ng21[] = {10, 0};
static unsigned int ng22[] = {6928U, 0U};
static int ng23[] = {11, 0};
static unsigned int ng24[] = {53240U, 0U};
static int ng25[] = {12, 0};
static int ng26[] = {13, 0};
static unsigned int ng27[] = {37199U, 0U};
static int ng28[] = {14, 0};
static unsigned int ng29[] = {37215U, 0U};
static int ng30[] = {15, 0};
static unsigned int ng31[] = {37231U, 0U};
static int ng32[] = {16, 0};
static unsigned int ng33[] = {57393U, 0U};
static int ng34[] = {17, 0};
static unsigned int ng35[] = {57418U, 0U};
static int ng36[] = {18, 0};
static unsigned int ng37[] = {57425U, 0U};
static int ng38[] = {19, 0};
static unsigned int ng39[] = {37727U, 0U};
static int ng40[] = {20, 0};
static int ng41[] = {21, 0};
static int ng42[] = {22, 0};
static int ng43[] = {23, 0};
static unsigned int ng44[] = {3941U, 0U};
static int ng45[] = {24, 0};
static int ng46[] = {25, 0};
static unsigned int ng47[] = {37743U, 0U};
static int ng48[] = {26, 0};
static unsigned int ng49[] = {6979U, 0U};
static int ng50[] = {27, 0};
static unsigned int ng51[] = {61449U, 0U};
static int ng52[] = {28, 0};
static int ng53[] = {29, 0};
static int ng54[] = {30, 0};
static unsigned int ng55[] = {0U, 0U};



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

LAB20:    t2 = ((char*)((ng15)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB21;

LAB22:    t2 = ((char*)((ng17)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB23;

LAB24:    t2 = ((char*)((ng19)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB25;

LAB26:    t2 = ((char*)((ng21)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB27;

LAB28:    t2 = ((char*)((ng23)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB29;

LAB30:    t2 = ((char*)((ng25)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB31;

LAB32:    t2 = ((char*)((ng26)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB33;

LAB34:    t2 = ((char*)((ng28)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB35;

LAB36:    t2 = ((char*)((ng30)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB37;

LAB38:    t2 = ((char*)((ng32)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB39;

LAB40:    t2 = ((char*)((ng34)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB41;

LAB42:    t2 = ((char*)((ng36)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB43;

LAB44:    t2 = ((char*)((ng38)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB45;

LAB46:    t2 = ((char*)((ng40)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB47;

LAB48:    t2 = ((char*)((ng41)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB49;

LAB50:    t2 = ((char*)((ng42)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB51;

LAB52:    t2 = ((char*)((ng43)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB53;

LAB54:    t2 = ((char*)((ng45)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB55;

LAB56:    t2 = ((char*)((ng46)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB57;

LAB58:    t2 = ((char*)((ng48)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB59;

LAB60:    t2 = ((char*)((ng50)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB61;

LAB62:    t2 = ((char*)((ng52)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB63;

LAB64:    t2 = ((char*)((ng53)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB65;

LAB66:    t2 = ((char*)((ng54)));
    t6 = xsi_vlog_unsigned_case_compare(t5, 10, t2, 32);
    if (t6 == 1)
        goto LAB67;

LAB68:
LAB70:
LAB69:    xsi_set_current_line(104, ng0);
    t2 = ((char*)((ng55)));
    t3 = (t0 + 2040);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 16);

LAB71:    goto LAB2;

LAB7:    xsi_set_current_line(26, ng0);
    t7 = ((char*)((ng2)));
    t8 = (t0 + 2040);
    xsi_vlogvar_assign_value(t8, t7, 0, 0, 16);
    goto LAB71;

LAB9:    xsi_set_current_line(29, ng0);
    t3 = ((char*)((ng4)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB11:    xsi_set_current_line(32, ng0);
    t3 = ((char*)((ng6)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB13:    xsi_set_current_line(35, ng0);
    t3 = ((char*)((ng8)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB15:    xsi_set_current_line(38, ng0);
    t3 = ((char*)((ng10)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB17:    xsi_set_current_line(41, ng0);
    t3 = ((char*)((ng12)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB19:    xsi_set_current_line(44, ng0);
    t3 = ((char*)((ng14)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB21:    xsi_set_current_line(47, ng0);
    t3 = ((char*)((ng16)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB23:    xsi_set_current_line(50, ng0);
    t3 = ((char*)((ng18)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB25:    xsi_set_current_line(53, ng0);
    t3 = ((char*)((ng20)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB27:    xsi_set_current_line(56, ng0);
    t3 = ((char*)((ng22)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB29:    xsi_set_current_line(59, ng0);
    t3 = ((char*)((ng24)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB31:    xsi_set_current_line(62, ng0);
    t3 = ((char*)((ng6)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB33:    xsi_set_current_line(65, ng0);
    t3 = ((char*)((ng27)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB35:    xsi_set_current_line(68, ng0);
    t3 = ((char*)((ng29)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB37:    xsi_set_current_line(71, ng0);
    t3 = ((char*)((ng31)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB39:    xsi_set_current_line(74, ng0);
    t3 = ((char*)((ng33)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB41:    xsi_set_current_line(76, ng0);
    t3 = ((char*)((ng35)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB43:    xsi_set_current_line(78, ng0);
    t3 = ((char*)((ng37)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB45:    xsi_set_current_line(80, ng0);
    t3 = ((char*)((ng39)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB47:    xsi_set_current_line(82, ng0);
    t3 = ((char*)((ng39)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB49:    xsi_set_current_line(84, ng0);
    t3 = ((char*)((ng29)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB51:    xsi_set_current_line(86, ng0);
    t3 = ((char*)((ng31)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB53:    xsi_set_current_line(88, ng0);
    t3 = ((char*)((ng44)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB55:    xsi_set_current_line(90, ng0);
    t3 = ((char*)((ng39)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB57:    xsi_set_current_line(92, ng0);
    t3 = ((char*)((ng47)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB59:    xsi_set_current_line(94, ng0);
    t3 = ((char*)((ng49)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB61:    xsi_set_current_line(96, ng0);
    t3 = ((char*)((ng51)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB63:    xsi_set_current_line(98, ng0);
    t3 = ((char*)((ng24)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB65:    xsi_set_current_line(100, ng0);
    t3 = ((char*)((ng29)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

LAB67:    xsi_set_current_line(102, ng0);
    t3 = ((char*)((ng31)));
    t4 = (t0 + 2040);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 16);
    goto LAB71;

}

static void Always_109_1(char *t0)
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

LAB2:    xsi_set_current_line(109, ng0);
    t2 = (t0 + 3544);
    *((int *)t2) = 1;
    t3 = (t0 + 3240);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(109, ng0);

LAB5:    xsi_set_current_line(110, ng0);
    t4 = (t0 + 2040);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    t7 = (t0 + 1880);
    xsi_vlogvar_wait_assign_value(t7, t6, 0, 0, 16, 0LL);
    goto LAB2;

}


extern void work_m_00000000000593596388_1696645267_init()
{
	static char *pe[] = {(void *)Always_13_0,(void *)Always_109_1};
	xsi_register_didat("work_m_00000000000593596388_1696645267", "isim/unitTestCpu_isim_beh.exe.sim/work/m_00000000000593596388_1696645267.didat");
	xsi_register_executes(pe);
}
