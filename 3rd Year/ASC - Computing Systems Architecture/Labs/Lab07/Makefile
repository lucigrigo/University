COMPILER=nvcc
LIBS=-lm

build: example_1 example_2 task_1 task_2 task_3

example_1: example_1.cu
	$(COMPILER) $^ -o $@ $(LIBS)

example_2: example_2.cu
	$(COMPILER) $^ -o $@ $(LIBS)

task_1: task_1.cu
	$(COMPILER) $^ -o $@ $(LIBS)

task_2: task_2.cu
	$(COMPILER) $^ -o $@ $(LIBS)

task_3: task_3.cu
	$(COMPILER) $^ -o $@ $(LIBS)

clean:
	rm -rf example_1
	rm -rf example_2
	rm -rf task_1
	rm -rf task_2
	rm -rf task_3
	rm -rf *.o
