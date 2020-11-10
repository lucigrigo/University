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
static const char *ng0 = "C:/Users/student/Desktop/skel_lab04/cpu.v";
static const char *ng1 = "Start cpu ...";
static const char *ng2 = "Legend:";
static const char *ng3 = "OPERATION OP1, OP2 - STAGE: OK <=> PASS";
static const char *ng4 = "OPERATION OP1, OP2 - STAGE: FAILED => EXPECTED_VALUE VS COMPUED_VALUE <=> FAIL";



static void Initial_41_0(char *t0)
{

LAB0:    xsi_set_current_line(42, ng0);

LAB2:    xsi_set_current_line(43, ng0);
    xsi_vlogfile_write(1, 0, 0, ng1, 1, t0);
    xsi_set_current_line(44, ng0);
    xsi_vlogfile_write(1, 0, 0, ng2, 1, t0);
    xsi_set_current_line(45, ng0);
    xsi_vlogfile_write(1, 0, 0, ng3, 1, t0);
    xsi_set_current_line(46, ng0);
    xsi_vlogfile_write(1, 0, 0, ng4, 1, t0);

LAB1:    return;
}


extern void work_m_00000000000260405604_1200043877_init()
{
	static char *pe[] = {(void *)Initial_41_0};
	xsi_register_didat("work_m_00000000000260405604_1200043877", "isim/unitTestCpu_isim_beh.exe.sim/work/m_00000000000260405604_1200043877.didat");
	xsi_register_executes(pe);
}
