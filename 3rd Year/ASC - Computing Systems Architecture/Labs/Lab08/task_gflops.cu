#include <stdio.h>
#include "utils/utils.h"

__global__ void kernel_gflops(float* a, float* b, int N) {
	int row = threadIdx.y;
	int col = threadIdx.x;
	int idx = row * N + col;

	// ~TODO~
	// Execute at least two floating point operations (e.g. +, -, *, /)
	// on the value from array a at index idx and
	// store the result in array b at index idx. 
	// NOTE: Do not change value directly in array a.
	b[idx] = a[idx] * 3.f + 5.f - 4.f * 1.75f - a[idx] * 0.65f + 2.f * a[idx] / 1.2f;
}

int main(void) {
    int nDevices;

    // Get the number of CUDA-capable GPU(s)
    cudaGetDeviceCount(&nDevices);
    cudaSetDevice(0);

    float *device_a = 0;
    float *device_b = 0;
    float *host_a = 0;
    float *host_b = 0;

    int N = 4096;
    int size = N * N;

    // Arrays a and b are of size N * N
    host_a = (float *) malloc(size * sizeof(float));
    host_b = (float *) malloc(size * sizeof(float));
    cudaMalloc((void **) &device_a, size * sizeof(float));
    cudaMalloc((void **) &device_b, size * sizeof(float));

    if (host_a == 0 || host_b == 0 || device_a == 0 || device_b == 0) {
        printf("[HOST] Couldn't allocate memory\n");
    	return 1;
    }

    // Populate array a randomly
    fill_array_random(host_a, size);
    cudaMemcpy(device_a, host_a, size * sizeof(float), cudaMemcpyHostToDevice);

    cudaEvent_t start, stop;

    // ~TODO~
    // Create two cuda events (start and stop)
    // by using the cudaEventCreate function.
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

    cudaEventRecord(start);
    kernel_gflops<<<size / 256, 256>>> (device_a, device_b, N);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float ms = 0;
    cudaEventElapsedTime(&ms, start, stop);
    float seconds = ms / pow((float) 10, 3);

    // ~TODO~
    // Set num_ops to the number of floating point operations
    // done in the kernel multiplied with the size of the matrix.
    long num_ops = 9 * size;

    float gflops = (float) num_ops / seconds / 1e+9;
    printf("GFLOPS: %.3f\n", gflops);
    // GFLOPS = 170.205

    free(host_a);
    free(host_b);
    cudaFree(device_a);
    cudaFree(device_b);
    
    return 0;
}
