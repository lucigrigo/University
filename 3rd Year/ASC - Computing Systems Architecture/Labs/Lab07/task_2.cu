#include <stdio.h>
#include <math.h>
#include "utils/utils.h"

// TODO 6: Write the code to add the two arrays element by element and 
// store the result in another array
__global__ void add_arrays(const float *a, const float *b, float *c, int N) {
	unsigned int i = threadIdx.x + blockDim.x * blockIdx.x;

	if (i < N)
		c[i] = a[i] + b[i];
}

int main(void) {
    cudaSetDevice(0);
    int N = 1 << 20;
	cudaError_t err;

    float *host_array_a = 0;
    float *host_array_b = 0;
    float *host_array_c = 0;

    float *device_array_a = 0;
    float *device_array_b = 0;
    float *device_array_c = 0;

    // TODO 1: Allocate the host's arrays
	
	host_array_a = (float *) malloc(N * sizeof(float));
	host_array_b = (float *) malloc(N * sizeof(float));
	host_array_c = (float *) malloc(N * sizeof(float));

    // TODO 2: Allocate the device's arrays
	
	err = cudaMalloc(&device_array_a, N * sizeof(float));
	DIE(err != cudaSuccess, "cudaMalloc err");
	err = cudaMalloc(&device_array_b, N * sizeof(float));
	DIE(err != cudaSuccess, "cudaMalloc err");
	err = cudaMalloc(&device_array_c, N * sizeof(float));
	DIE(err != cudaSuccess, "cudaMalloc err");

    // TODO 3: Check for allocation errors
	
	DIE(host_array_a == NULL || host_array_b == NULL || host_array_c == NULL, "malloc err");

    // TODO 4: Fill array with values; use fill_array_float to fill
    // host_array_a and fill_array_random to fill host_array_b. Each
    // function has the signature (float *a, int n), where n = number of elements.

	fill_array_float(host_array_a, N);
	fill_array_random(host_array_b, N);

    // TODO 5: Copy the host's arrays to device
	
	err = cudaMemcpy(device_array_a, host_array_a, N * sizeof(float), cudaMemcpyHostToDevice);
	DIE(err != cudaSuccess, "first cudamemcpy");

	err = cudaMemcpy(device_array_b, host_array_b, N * sizeof(float), cudaMemcpyHostToDevice);
	DIE(err != cudaSuccess, "second cudamemcpy");

    // TODO 6: Execute the kernel, calculating first the grid size
    // and the amount of threads in each block from the grid
    // Hint: For this execise the block_size can have any value lower than the
    //      API's maximum value (it's recommended to be close to the maximum
    //      value).
	const size_t block_size = 256;
	size_t no_blocks = N / block_size;

	if (N % block_size != 0)
		++no_blocks;

	add_arrays<<<no_blocks, block_size>>>(device_array_a, device_array_b, device_array_c, N);

    // TODO 7: Copy back the results and then uncomment the checking function

	err = cudaDeviceSynchronize();
	DIE(err != cudaSuccess, "cudadevicesynchronize err");

	err = cudaMemcpy(host_array_c, device_array_c, N * sizeof(float), cudaMemcpyDeviceToHost);
	DIE(err != cudaSuccess, "last cudaMemcpy err");

    check_task_2(host_array_a, host_array_b, host_array_c, N);

    // TODO 8: Free the memory
 
	free(host_array_a);
	free(host_array_b);
	free(host_array_c);
	
	err = cudaFree(device_array_a);
	DIE(err != cudaSuccess, "cudaFree err");
	err = cudaFree(device_array_b);
	DIE(err != cudaSuccess, "cudaFree err");
	err = cudaFree(device_array_c);
	DIE(err != cudaSuccess, "cudaFree err");

    return 0;
}
