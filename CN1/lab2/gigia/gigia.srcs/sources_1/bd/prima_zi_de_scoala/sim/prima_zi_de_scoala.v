//Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2019.2.1 (lin64) Build 2729669 Thu Dec  5 04:48:12 MST 2019
//Date        : Wed Feb 26 10:37:54 2020
//Host        : admin1-HP-ProDesk-600-G2-SFF running 64-bit Linux Mint 19.3 Tricia
//Command     : generate_target prima_zi_de_scoala.bd
//Design      : prima_zi_de_scoala
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "prima_zi_de_scoala,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=prima_zi_de_scoala,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=2,numReposBlks=2,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "prima_zi_de_scoala.hwdef" *) 
module prima_zi_de_scoala
   (a,
    b,
    carry_out,
    suma);
  input [0:0]a;
  input [0:0]b;
  output [0:0]carry_out;
  output [0:0]suma;

  wire [0:0]Op1_0_1;
  wire [0:0]Op2_0_1;
  wire [0:0]util_vector_logic_0_Res;
  wire [0:0]util_vector_logic_1_Res;

  assign Op1_0_1 = a[0];
  assign Op2_0_1 = b[0];
  assign carry_out[0] = util_vector_logic_1_Res;
  assign suma[0] = util_vector_logic_0_Res;
  prima_zi_de_scoala_util_vector_logic_1_0 si_1
       (.Op1(Op1_0_1),
        .Op2(Op2_0_1),
        .Res(util_vector_logic_1_Res));
  prima_zi_de_scoala_util_vector_logic_0_0 xor_0
       (.Op1(Op1_0_1),
        .Op2(Op2_0_1),
        .Res(util_vector_logic_0_Res));
endmodule
