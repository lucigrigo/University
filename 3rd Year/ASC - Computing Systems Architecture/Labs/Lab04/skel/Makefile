CFLAGS  = -std=c99 -g -Wall -O3
LDLIBS  = -lm
OBJS    = task1a task1b task1c task2 task3 task4 task5

all : $(OBJS)

plots : plot_l1 plot_l2 plot_line

l1_size.out : task4
	./run_l1_size.sh > l1_size.out

plot_l1 : l1_size.out
	gnuplot -persist -e "set xlabel 'Size (bytes)'; set ylabel 'Performance (ops/sec)'; plot 'l1_size.out' using 1:4 title 'L1 cache size' with lines"

l2_size.out : task4
	./run_l2_size.sh > l2_size.out

plot_l2 : l2_size.out
	gnuplot -persist -e "set xlabel 'Size (bytes)'; set ylabel 'Performance (ops/sec)'; plot 'l2_size.out' using 1:4 title 'L2 cache size' with lines"

line_size.out : task5
	./run_line_size.sh > line_size.out

plot_line : line_size.out
	gnuplot -persist -e "set xlabel 'Step (bytes)'; set ylabel 'Average time (sec/ops)'; plot 'line_size.out' using 1:4 title 'Cache line size'"

clean :
	rm -f $(OBJS) l1_size.out l2_size.out line_size.out

.PHONY: all plot_l1 plot_l2 plot_line plots clean
