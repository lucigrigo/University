onbreak {quit -f}
onerror {quit -f}

vsim -t 1ps -lib xil_defaultlib prima_zi_de_scoala_opt

do {wave.do}

view wave
view structure
view signals

do {prima_zi_de_scoala.udo}

run -all

quit -force
