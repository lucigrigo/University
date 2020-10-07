vlib modelsim_lib/work
vlib modelsim_lib/msim

vlib modelsim_lib/msim/util_vector_logic_v2_0_1
vlib modelsim_lib/msim/xil_defaultlib

vmap util_vector_logic_v2_0_1 modelsim_lib/msim/util_vector_logic_v2_0_1
vmap xil_defaultlib modelsim_lib/msim/xil_defaultlib

vlog -work util_vector_logic_v2_0_1 -64 -incr \
"../../../../gigia.srcs/sources_1/bd/prima_zi_de_scoala/ipshared/2137/hdl/util_vector_logic_v2_0_vl_rfs.v" \

vlog -work xil_defaultlib -64 -incr \
"../../../bd/prima_zi_de_scoala/ip/prima_zi_de_scoala_util_vector_logic_0_0/sim/prima_zi_de_scoala_util_vector_logic_0_0.v" \
"../../../bd/prima_zi_de_scoala/ip/prima_zi_de_scoala_util_vector_logic_1_0/sim/prima_zi_de_scoala_util_vector_logic_1_0.v" \
"../../../bd/prima_zi_de_scoala/sim/prima_zi_de_scoala.v" \

vlog -work xil_defaultlib \
"glbl.v"

