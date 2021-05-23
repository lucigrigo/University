#include <iostream>

#define INDEX_NUM   3

#define INDEX_SUM   0
#define INDEX_MAX   1
#define INDEX_MIN   2

#define NUM_MAX         1024

#define ITEMS_NUM       (1024 * 1024)
#define BLOCK_SIZE      256

using namespace std;

// TODO-1 => ./task_no_atomic
// 1 thread does all compute, no atomic/sync
// thread.0 of block.0 computes everything
__global__ void kernel_no_atomics(int *data, int *results) {
	if (threadIdx.x != 0 || blockIdx.x != 0)
		return;

	for (int i = 0; i < ITEMS_NUM; ++i) {
		results[INDEX_SUM] += data[i];

		results[INDEX_MAX] = (data[i] > results[INDEX_MAX]) ? data[i] : results[INDEX_MAX];

		results[INDEX_MIN] = (data[i] < results[INDEX_MIN]) ? data[i] : results[INDEX_MIN];
	}
}

// TODO-2 => ./task_partial_atomic
// ITEMS_NUM / 256 threads, ITEMS_NUM / 256 * 3 atomic calls
// thread.0 of each block does partial compute, than uses atomics to compute
__global__ void kernel_partial_atomics(int *data, int *results) {
	if (threadIdx.x != 0)
		return;

	int start = blockIdx.x * BLOCK_SIZE;
	int localRes[INDEX_NUM] = {0};
	localRes[INDEX_MIN] = NUM_MAX;

	for (int i = 0; i < BLOCK_SIZE; ++i) {
		localRes[INDEX_SUM] += data[start + i];

		localRes[INDEX_MIN] = (data[start + i] < localRes[INDEX_MIN]) ? data[start + i] : localRes[INDEX_MIN];

		localRes[INDEX_MAX] = (data[start + i] > localRes[INDEX_MAX]) ? data[start + i] : localRes[INDEX_MAX];
	}

	atomicAdd(results + INDEX_SUM, localRes[INDEX_SUM]);
	atomicMax(results + INDEX_MAX, localRes[INDEX_MAX]);
	atomicMin(results + INDEX_MIN, localRes[INDEX_MIN]);
}

// TODO-3 => ./task_full_atomic
// ITEMS_NUM threads do compute, ITEMS_NUM * 3 atomic calls
// all threads to atomics to compute
__global__ void kernel_full_atomics(int *data, int *results) {
	int idx = blockIdx.x * blockDim.x + threadIdx.x;

	atomicAdd(results + INDEX_SUM, data[idx]);
	atomicMax(results + INDEX_MAX, data[idx]);
	atomicMin(results + INDEX_MIN, data[idx]);
}

int main(void) {
    int expResults[INDEX_NUM];
    
    int *data = NULL;
    cudaMallocManaged(&data, ITEMS_NUM * sizeof(int));
    if (data == 0) {
        cout << "[HOST] Couldn't allocate memory\n";
        return 1;
    }
    
    // generate data and expected result
    expResults[INDEX_SUM] = 0;
    expResults[INDEX_MAX] = 0;
    expResults[INDEX_MIN] = NUM_MAX;
    
    for(int i = 0; i < ITEMS_NUM; i++) {
        // each generated number is lower than NUM_MAX as value
        data[i] = rand() % NUM_MAX;
        
        expResults[INDEX_SUM] += data[i];
        
        expResults[INDEX_MAX] = (data[i] > expResults[INDEX_MAX]) ?
            data[i] : expResults[INDEX_MAX];
        
        expResults[INDEX_MIN] = (data[i] < expResults[INDEX_MIN]) ?
            data[i] : expResults[INDEX_MIN];
    }
    
    int *results = NULL;
    cudaMallocManaged(&results, INDEX_NUM * sizeof(int));
    if (results == 0) {
        cout << "[HOST] Couldn't allocate memory\n";
    	return 1;
    }
   
    // compute 10 times the results
    for(int i = 0; i < 10; i++) {
        
        // init
        results[INDEX_SUM] = 0;
        results[INDEX_MAX] = 0;
        results[INDEX_MIN] = NUM_MAX;
        
#ifdef NO_ATOMIC
        kernel_no_atomics<<< 1 , 1 >>> (data, results);
        cudaDeviceSynchronize();
#endif

#ifdef PARTIAL_ATOMIC
        kernel_partial_atomics<<< ITEMS_NUM / 256 , 1 >>> (data, results);
        cudaDeviceSynchronize();
#endif

#ifdef FULL_ATOMIC
        kernel_full_atomics<<< ITEMS_NUM / 256 , 256 >>> (data, results);
        cudaDeviceSynchronize();
#endif
    }
    
    cout << "SUM: " << results[INDEX_SUM] << endl;
    if(results[INDEX_SUM] != expResults[INDEX_SUM]) {
        cout << "Failed, SUM should be " << expResults[INDEX_SUM] << endl;
    }
    
    cout << "MAX: " << results[INDEX_MAX] << endl;
    if(results[INDEX_MAX] != expResults[INDEX_MAX]) {
        cout << "Failed, MAX should be " << expResults[INDEX_MAX] << endl;
    }
    
    cout << "MIN: " << results[INDEX_MIN] << endl;
    if(results[INDEX_MIN] != expResults[INDEX_MIN]) {
        cout << "Failed, MIN should be " << expResults[INDEX_MIN] << endl;
    }
    
    cudaFree(results);
    return 0;
}
