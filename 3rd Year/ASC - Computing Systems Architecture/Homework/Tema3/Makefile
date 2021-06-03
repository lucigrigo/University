all: gpu_hashtable

gpu_hashtable: gpu_hashtable.cu test_map.cpp gpu_hashtable.hpp
	nvcc -O2 -g -std=c++11 test_map.cpp gpu_hashtable.cu -o gpu_hashtable

clean:
	rm -f gpu_hashtable
