#!/bin/bash -f
# ****************************************************************************
# Vivado (TM) v2019.2.1 (64-bit)
#
# Filename    : simulate.sh
# Simulator   : Xilinx Vivado Simulator
# Description : Script for simulating the design by launching the simulator
#
# Generated by Vivado on Wed Feb 26 10:38:08 EET 2020
# SW Build 2729669 on Thu Dec  5 04:48:12 MST 2019
#
# Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
#
# usage: simulate.sh
#
# ****************************************************************************
set -Eeuo pipefail
echo "xsim prima_zi_de_scoala_wrapper_behav -key {Behavioral:sim_1:Functional:prima_zi_de_scoala_wrapper} -tclbatch prima_zi_de_scoala_wrapper.tcl -protoinst "protoinst_files/prima_zi_de_scoala.protoinst" -log simulate.log"
xsim prima_zi_de_scoala_wrapper_behav -key {Behavioral:sim_1:Functional:prima_zi_de_scoala_wrapper} -tclbatch prima_zi_de_scoala_wrapper.tcl -protoinst "protoinst_files/prima_zi_de_scoala.protoinst" -log simulate.log

