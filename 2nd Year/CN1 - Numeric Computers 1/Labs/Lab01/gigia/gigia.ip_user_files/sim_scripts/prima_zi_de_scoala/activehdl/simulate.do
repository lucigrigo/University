onbreak {quit -force}
onerror {quit -force}

asim -t 1ps +access +r +m+prima_zi_de_scoala -L util_vector_logic_v2_0_1 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip -O5 xil_defaultlib.prima_zi_de_scoala xil_defaultlib.glbl

do {wave.do}

view wave
view structure

do {prima_zi_de_scoala.udo}

run -all

endsim

quit -force
