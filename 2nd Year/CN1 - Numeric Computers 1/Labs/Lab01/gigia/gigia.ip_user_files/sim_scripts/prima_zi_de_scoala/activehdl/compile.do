vlib work
vlib activehdl

vlib activehdl/util_vector_logic_v2_0_1
vlib activehdl/xil_defaultlib

vmap util_vector_logic_v2_0_1 activehdl/util_vector_logic_v2_0_1
vmap xil_defaultlib activehdl/xil_defaultlib

vlog -work util_vector_logic_v2_0_1  -v2k5 \
"../../../../gigia.srcs/sources_1/bd/prima_zi_de_scoala/ipshared/2137/hdl/util_vector_logic_v2_0_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 \
"../../../bd/prima_zi_de_scoala/ip/prima_zi_de_scoala_util_vector_logic_0_0/sim/prima_zi_de_scoala_util_vector_logic_0_0.v" \
"../../../bd/prima_zi_de_scoala/ip/prima_zi_de_scoala_util_vector_logic_1_0/sim/prima_zi_de_scoala_util_vector_logic_1_0.v" \
"../../../bd/prima_zi_de_scoala/sim/prima_zi_de_scoala.v" \

vlog -work xil_defaultlib \
"glbl.v"

