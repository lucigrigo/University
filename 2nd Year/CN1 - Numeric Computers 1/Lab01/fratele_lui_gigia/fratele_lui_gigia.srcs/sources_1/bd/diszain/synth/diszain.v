//Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2019.2.1 (lin64) Build 2729669 Thu Dec  5 04:48:12 MST 2019
//Date        : Wed Feb 26 11:12:39 2020
//Host        : admin1-HP-ProDesk-600-G2-SFF running 64-bit Linux Mint 19.3 Tricia
//Command     : generate_target diszain.bd
//Design      : diszain
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "diszain,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=diszain,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=5,numReposBlks=5,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "diszain.hwdef" *) 
module diszain
   (a,
    b,
    cin,
    cout,
    sum);
  input [0:0]a;
  input [0:0]b;
  input [0:0]cin;
  output [0:0]cout;
  output [0:0]sum;

  wire [0:0]Op1_0_1;
  wire [0:0]Op2_0_1;
  wire [0:0]Op2_1_1;
  wire [0:0]si_1_Res;
  wire [0:0]si_2_Res;
  wire [0:0]si_3_Res;
  wire [0:0]xor_0_Res;
  wire [0:0]xor_1_Res;

  assign Op1_0_1 = a[0];
  assign Op2_0_1 = b[0];
  assign Op2_1_1 = cin[0];
  assign cout[0] = si_3_Res;
  assign sum[0] = xor_1_Res;
  diszain_util_vector_logic_0_1 si_1
       (.Op1(Op1_0_1),
        .Op2(Op2_0_1),
        .Res(si_1_Res));
  diszain_si_1_0 si_2
       (.Op1(xor_0_Res),
        .Op2(Op2_1_1),
        .Res(si_2_Res));
  diszain_si_2_0 si_3
       (.Op1(si_1_Res),
        .Op2(si_2_Res),
        .Res(si_3_Res));
  diszain_util_vector_logic_0_0 xor_0
       (.Op1(Op1_0_1),
        .Op2(Op2_0_1),
        .Res(xor_0_Res));
  diszain_xor_0_0 xor_1
       (.Op1(xor_0_Res),
        .Op2(Op2_1_1),
        .Res(xor_1_Res));
endmodule
