//Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2019.2.1 (lin64) Build 2729669 Thu Dec  5 04:48:12 MST 2019
//Date        : Wed Mar  4 11:41:50 2020
//Host        : admin1-HP-ProDesk-600-G2-SFF running 64-bit Linux Mint 19.3 Tricia
//Command     : generate_target diszain_wrapper.bd
//Design      : diszain_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module diszain_wrapper
   (clk_0,
    cout,
    sum);
  input clk_0;
  output [0:0]cout;
  output [0:0]sum;

  wire clk_0;
  wire [0:0]cout;
  wire [0:0]sum;

  diszain diszain_i
       (.clk_0(clk_0),
        .cout(cout),
        .sum(sum));
endmodule
