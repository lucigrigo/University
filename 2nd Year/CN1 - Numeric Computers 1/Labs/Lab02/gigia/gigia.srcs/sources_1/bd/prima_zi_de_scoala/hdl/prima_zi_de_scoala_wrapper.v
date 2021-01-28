//Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2019.2.1 (lin64) Build 2729669 Thu Dec  5 04:48:12 MST 2019
//Date        : Wed Feb 26 10:37:54 2020
//Host        : admin1-HP-ProDesk-600-G2-SFF running 64-bit Linux Mint 19.3 Tricia
//Command     : generate_target prima_zi_de_scoala_wrapper.bd
//Design      : prima_zi_de_scoala_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module prima_zi_de_scoala_wrapper
   (a,
    b,
    carry_out,
    suma);
  input [0:0]a;
  input [0:0]b;
  output [0:0]carry_out;
  output [0:0]suma;

  wire [0:0]a;
  wire [0:0]b;
  wire [0:0]carry_out;
  wire [0:0]suma;

  prima_zi_de_scoala prima_zi_de_scoala_i
       (.a(a),
        .b(b),
        .carry_out(carry_out),
        .suma(suma));
endmodule
