Compilare: make
Rulare:
#./useAllCPU N M PRINT_LEVEL THREADS
./useAllCPU 1000000 1000000 0 `nproc`


# ./addTwoVectors N PRINT_LEVEL THREADS
time ./addTwoVectors 30000 0 1
time ./addTwoVectors 30000 0 2
time ./addTwoVectors 30000 0 4