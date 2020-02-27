//Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2019.2.1 (lin64) Build 2729669 Thu Dec  5 04:48:12 MST 2019
//Date        : Wed Feb 26 11:12:39 2020
//Host        : admin1-HP-ProDesk-600-G2-SFF running 64-bit Linux Mint 19.3 Tricia
//Command     : generate_target diszain_wrapper.bd
//Design      : diszain_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module diszain_wrapper
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

  wire [0:0]a;
  wire [0:0]b;
  wire [0:0]cin;
  wire [0:0]cout;
  wire [0:0]sum;

  diszain diszain_i
       (.a(a),
        .b(b),
        .cin(cin),
        .cout(cout),
        .sum(sum));
endmodule
