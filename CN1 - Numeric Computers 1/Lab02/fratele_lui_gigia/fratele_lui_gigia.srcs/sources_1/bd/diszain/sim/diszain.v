//Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2019.2.1 (lin64) Build 2729669 Thu Dec  5 04:48:12 MST 2019
//Date        : Wed Mar  4 11:41:49 2020
//Host        : admin1-HP-ProDesk-600-G2-SFF running 64-bit Linux Mint 19.3 Tricia
//Command     : generate_target diszain.bd
//Design      : diszain
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "diszain,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=diszain,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=6,numReposBlks=6,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "diszain.hwdef" *) 
module diszain
   (clk_0,
    cout,
    sum);
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.CLK_0 CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.CLK_0, CLK_DOMAIN diszain_clk_0, FREQ_HZ 100000000, INSERT_VIP 0, PHASE 0.000" *) input clk_0;
  output [0:0]cout;
  output [0:0]sum;

  wire [0:0]Op1_0_1;
  wire [0:0]Op2_0_1;
  wire [0:0]Op2_1_1;
  wire clk_0_1;
  wire [0:0]si_1_Res;
  wire [0:0]si_2_Res;
  wire [0:0]si_3_Res;
  wire [0:0]xor_0_Res;
  wire [0:0]xor_1_Res;

  assign clk_0_1 = clk_0;
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
  diszain_vio_0_0 vio_0
       (.clk(clk_0_1),
        .probe_in0(xor_1_Res),
        .probe_in1(si_3_Res),
        .probe_out0(Op1_0_1),
        .probe_out1(Op2_0_1),
        .probe_out2(Op2_1_1));
  diszain_util_vector_logic_0_0 xor_0
       (.Op1(Op1_0_1),
        .Op2(Op2_0_1),
        .Res(xor_0_Res));
  diszain_xor_0_0 xor_1
       (.Op1(xor_0_Res),
        .Op2(Op2_1_1),
        .Res(xor_1_Res));
endmodule
