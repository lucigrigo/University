// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.2.1 (lin64) Build 2729669 Thu Dec  5 04:48:12 MST 2019
// Date        : Wed Mar  4 11:42:58 2020
// Host        : admin1-HP-ProDesk-600-G2-SFF running 64-bit Linux Mint 19.3 Tricia
// Command     : write_verilog -force -mode synth_stub
//               /home/student1/Downloads/lab2/fratele_lui_gigia/fratele_lui_gigia.srcs/sources_1/bd/diszain/ip/diszain_vio_0_0/diszain_vio_0_0_stub.v
// Design      : diszain_vio_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "vio,Vivado 2019.2.1" *)
module diszain_vio_0_0(clk, probe_in0, probe_in1, probe_out0, 
  probe_out1, probe_out2)
/* synthesis syn_black_box black_box_pad_pin="clk,probe_in0[0:0],probe_in1[0:0],probe_out0[0:0],probe_out1[0:0],probe_out2[0:0]" */;
  input clk;
  input [0:0]probe_in0;
  input [0:0]probe_in1;
  output [0:0]probe_out0;
  output [0:0]probe_out1;
  output [0:0]probe_out2;
endmodule
