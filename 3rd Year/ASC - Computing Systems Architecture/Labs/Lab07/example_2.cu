#include <stdlib.h>
#include <stdio.h>

/**
 * This kernel computes the function f(x) = 2x + 1/(x + 1) for each
 * element in the given array.
 */
__global__ void vector_add(const float *a, float *b, const size_t n) {
  	// Compute the global element index this thread should process
  	unsigned int i = threadIdx.x + blockDim.x * blockIdx.x;

  	// Avoid accessing out of bounds elements
  	if (i < n) {
    	b[i] = 2.0 * a[i] + 1.0 / (a[i] + 1.0);
  	}
}


int main(void) {
  	// Declare variable to represent ~1M float values and
  	// computes the amount of bytes necessary to store them
  	const int num_elements = 1 << 16;
  	const int num_bytes = num_elements * sizeof(float);

  	// Declaring the 'host arrays': a host array is the classical
  	// array (static or dynamically allocated) we worked before.
  	float *host_array_a = 0;
	float *host_array_b = 0;
	
  	// Declaring the 'device array': this array is the equivalent
  	// of classical array from C, but specially designed for the GPU
  	// devices; we declare it in the same manner, but the allocation
  	// process is going to be different
  	float *device_array_a = 0;
	float *device_array_b = 0;

  	// Allocating the host array
  	host_array_a = (float *) malloc(num_bytes);
	host_array_b = (float *) malloc(num_bytes);

  	// Allocating the device's array; notice that we use a special
  	// function named cudaMalloc that takes the reference of the
  	// pointer declared above and the number of bytes.
  	cudaMalloc((void **) &device_array_a, num_bytes);
	cudaMalloc((void **) &device_array_b, num_bytes);

  	// If any memory allocation failed, report an error message
  	if (host_array_a == 0 || host_array_b == 0|| device_array_a == 0 || device_array_b == 0) {
    	printf("[HOST] Couldn't allocate memory\n");
    	return 1;
  	}

	// Initialize the host array by populating it with float values  
  	for (int i = 0; i < num_elements; ++i) {
    	host_array_a[i] = (float) i;
  	}

	// Copying the host array to the device memory space; notice the
	// parameters of the cudaMemcpy function; the function default
	// signature is cudaMemcpy(dest, src, bytes, flag) where
	// the flag specifies the transfer type.
	//
	// host -> device: cudaMemcpyHostToDevice
	// device -> host: cudaMemcpyDeviceToHost
	// device -> device: cudaMemcpyDeviceToDevice
	cudaMemcpy(device_array_a, host_array_a, num_bytes, cudaMemcpyHostToDevice);

	// Compute the parameters necessary to run the kernel: the number
	// of blocks and the number of threads per block; also, deal with
	// a possible partial final block
  	const size_t block_size = 256;
  	size_t blocks_no = num_elements / block_size;

	if (num_elements % block_size) 
		++blocks_no;

  	// Launch the kernel
  	vector_add<<<blocks_no, block_size>>>(device_array_a, device_array_b, num_elements);

  	// Copy the result back to the host memory space
  	cudaMemcpy(host_array_b, device_array_b, num_bytes, cudaMemcpyDeviceToHost);

	// Print out the first 10 results
	for (int i = 0; i < 10; ++i) {
		printf("Result %d: 2 * %1.1f + 1.0/(%1.1f + 1.0)= %1.3f\n", 
		i, host_array_a[i], host_array_a[i], host_array_b[i]);
	}

	// Deallocate memory
	free(host_array_a);
	free(host_array_b);
	cudaFree(device_array_a);
	cudaFree(device_array_b);
}

