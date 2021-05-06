#include <stdio.h>
#include <math.h>
#include "utils/utils.h"

#define BUF_2M		(2 * 1024 * 1024)
#define BUF_32M		(32 * 1024 * 1024)

int main(void) {
    cudaSetDevice(0);

    int *host_array_a = 0;
    int *host_array_b = 0;

    int *device_array_a = 0;
    int *device_array_b = 0;
    int *device_array_c = 0;

    // TODO 1: Allocate the host's arrays with the specified number of elements:
    // host_array_a => 32M
    // host_array_b => 32M
	host_array_a = (int *) malloc(BUF_32M * sizeof(int));
	host_array_b = (int *) malloc(BUF_32M * sizeof(int));

    // TODO 2: Allocate the device's arrays with the specified number of elements:
    // device_array_a => 32M
    // device_array_b => 32M
    // device_array_c => 2M
	cudaMalloc(&device_array_a, BUF_32M * sizeof(float));
	cudaMalloc(&device_array_b, BUF_32M * sizeof(float));
	cudaMalloc(&device_array_c, BUF_2M * sizeof(float));

    // Check for allocation errors
    if (host_array_a == 0 || host_array_b == 0 || 
        device_array_a == 0 || device_array_b == 0 || 
        device_array_c == 0) {
        printf("[*] Error!\n");
        return 1;
    }

    for (int i = 0; i < BUF_32M; ++i) {
        host_array_a[i] = i % 32;
        host_array_b[i] = i % 2;
    }

    printf("Before swap:\n");
    printf("a[i]\tb[i]\n");
    for (int i = 0; i < 10; ++i) {
        printf("%d\t%d\n", host_array_a[i], host_array_b[i]);
    }

    // TODO 3: Copy from host to device

	cudaError_t err = cudaMemcpy(device_array_a, host_array_a, BUF_32M * sizeof(int), cudaMemcpyHostToDevice);
	DIE(err != cudaSuccess, "1st cudamemcpy");

	err = cudaMemcpy(device_array_b, host_array_b, BUF_32M * sizeof(int), cudaMemcpyHostToDevice);
	DIE(err != cudaSuccess, "2nd cudamemcpy");

    // TODO 4: Swap the buffers (BUF_2M values each iteration)
    // Hint 1: device_array_c should be used as a temporary buffer
    // Hint 2: cudaMemcpy

	for (int i = 0; i != BUF_32M; i += BUF_2M) {
		err = cudaMemcpy(device_array_c, device_array_b + i,
						BUF_2M * sizeof(int),
						cudaMemcpyDeviceToDevice);
		DIE(err != cudaSuccess, "1st for cudamemcpy");

		err = cudaMemcpy(device_array_b + i, device_array_a + i,
						BUF_2M * sizeof(int),
						cudaMemcpyDeviceToDevice);
		DIE(err != cudaSuccess, "2nd for cudamemcpy");

		err = cudaMemcpy(device_array_a + i, device_array_c,
						BUF_2M * sizeof(int),
						cudaMemcpyDeviceToDevice);
		DIE(err != cudaSuccess, "3rd for cudamemcpy");
	}

    // TODO 5: Copy from device to host

	err = cudaMemcpy(host_array_a, device_array_a,
					BUF_2M * sizeof(int), cudaMemcpyDeviceToHost);
	DIE(err != cudaSuccess, "first cudamemcpy after");

	err = cudaMemcpy(host_array_b, device_array_b,
					BUF_2M * sizeof(int), cudaMemcpyDeviceToHost);
	DIE(err != cudaSuccess, "second cudamemcpy after");

    printf("\nAfter swap:\n");
    printf("a[i]\tb[i]\n");
    for (int i = 0; i < 10; ++i) {
        printf("%d\t%d\n", host_array_a[i], host_array_b[i]);
    }

    // TODO 6: Free the memory

	free(host_array_a);
	free(host_array_b);

	err = cudaFree(device_array_a);
	DIE(err != cudaSuccess, "first cudafree");

	err = cudaFree(device_array_b);
	DIE(err != cudaSuccess, "second cudafree");

	err = cudaFree(device_array_c);
	DIE(err != cudaSuccess, "third cudafree");

    return 0;
}
