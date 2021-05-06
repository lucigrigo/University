#include <stdio.h>

__global__ void kernel_example(int value) {
	/**
	 * This is a kernel; a kernel is a piece of code that
	 * will be executed by each thread from each block in
	 * the GPU device.
	 */
	printf("[GPU] Hello from the GPU!\n");
	printf("[GPU] The value is %d\n", value);
}

int main(void) {
	/**
	 * Here, we declare and/or initialize different values or we
	 * can call different functions (as in every C/C++ program);
	 * In our case, here we also initialize the buffers, copy
	 * local data to the device buffers, etc (you'll see more about
	 * this in the following exercises).
	 */
	int nDevices;
	printf("[HOST] Hello from the host!\n");

	/**
	 * Get the number of compute-capable devices. See more info 
	 * about this function in the Cuda Toolkit Documentation.
	 */
	cudaGetDeviceCount(&nDevices);
	printf("[HOST] You have %d CUDA-capable GPU(s)\n", nDevices);

	/** 
	 * Launching the above kernel with a single block, each block
	 * with a single thread. The syncrhonize and the checking functions
	 * assures that everything works as expected.
	 */
	kernel_example<<<1,1>>>(25);
	cudaDeviceSynchronize();

	/**
	 * Here we can also deallocate the allocated memory for the device
	 */
  	return 0;
}

