// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.2.1 (lin64) Build 2729669 Thu Dec  5 04:48:12 MST 2019
// Date        : Wed Feb 26 11:13:37 2020
// Host        : admin1-HP-ProDesk-600-G2-SFF running 64-bit Linux Mint 19.3 Tricia
// Command     : write_verilog -force -mode synth_stub
//               /home/student1/fratele_lui_gigia/fratele_lui_gigia.srcs/sources_1/bd/diszain/ip/diszain_si_2_0/diszain_si_2_0_stub.v
// Design      : diszain_si_2_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "util_vector_logic_v2_0_1_util_vector_logic,Vivado 2019.2.1" *)
module diszain_si_2_0(Op1, Op2, Res)
/* synthesis syn_black_box black_box_pad_pin="Op1[0:0],Op2[0:0],Res[0:0]" */;
  input [0:0]Op1;
  input [0:0]Op2;
  output [0:0]Res;
endmodule
