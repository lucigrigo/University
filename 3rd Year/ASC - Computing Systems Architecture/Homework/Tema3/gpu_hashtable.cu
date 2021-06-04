/*
	ASC - Tema 3
	GPU Hashtable
	Grigore Lucian-Florin
	336CA
*/
#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <ctime>
#include <sstream>
#include <string>
#include "test_map.hpp"
#include "gpu_hashtable.hpp"

using namespace std;

// load factor boundaries
#define MAX_LOAD_FACTOR .75f
#define MIN_LOAD_FACTOR .55f

/*
Allocate CUDA memory only through glbGpuAllocator
cudaMalloc -> glbGpuAllocator->_cudaMalloc
cudaMallocManaged -> glbGpuAllocator->_cudaMallocManaged
cudaFree -> glbGpuAllocator->_cudaFree
*/

/**
* Hash function based on fnv-1a formulae.
*/
__device__ uint32_t
_hash(int key) {
	uint32_t hash = 2166136261;
    hash = hash ^ ((unsigned char *)(&key))[0];
    hash = hash * 16777619;
    hash = hash ^ ((unsigned char *)(&key))[1];
    hash = hash * 16777619;
    hash = hash ^ ((unsigned char *)(&key))[2];
    hash = hash * 16777619;
    hash = hash ^ ((unsigned char *)(&key))[3];
    hash = hash * 16777619;
    return hash;
}

// computes kernel params
void GpuHashTable::getDeviceParams(int noElems, int &noBlocks, int &noThreads) {
	cudaDeviceProp deviceProp;

	cudaGetDeviceProperties(&deviceProp, 0);
	cudaCheckError();

	noThreads = deviceProp.maxThreadsPerBlock;
	noBlocks = noElems / noThreads;

	if (noBlocks * noThreads != noElems)
		++noBlocks;
}

// returns current load factor
float GpuHashTable::computeLoadFactor() {
	return (float) size / capacity;
}

/**
 * Function constructor GpuHashTable
 * Performs init
 * Example on using wrapper allocators _cudaMalloc and _cudaFree
 */
GpuHashTable::GpuHashTable(int size):
	capacity(size), size(0) {
	int noBytes = capacity * sizeof(entry);
	glbGpuAllocator->_cudaMalloc((void **)&hashMap, noBytes);
	cudaCheckError();
	
	cudaMemset(hashMap, 0, noBytes);
	cudaCheckError();
}

/**
 * Function desctructor GpuHashTable
 */
GpuHashTable::~GpuHashTable() {
	glbGpuAllocator->_cudaFree(hashMap);
}

// GPU: copies one entry from old hashmap to a new one based on thread index
__global__ void
kernel_reshape(entry *newHashMap, int newCapacity, entry *oldHashMap, int oldCapacity) {
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if (idx >= oldCapacity)
		return;

	int key = oldHashMap[idx].key;
	if (key == 0)
		return;

	int value = oldHashMap[idx].value;
	uint32_t h = _hash(key) % newCapacity;

	// linear probing until a free spot is found
	do {
		if (atomicCAS(&newHashMap[h].key, 0, key) == 0) {
			newHashMap[h].value = value;
			
			return;
		}

		h = (h + 1) % newCapacity;
	} while(1);
}

/**
 * Function reshape
 * Performs resize of the hashtable based on load factor
 */
void GpuHashTable::reshape(int numBucketsReshape) {
	int noBytes = numBucketsReshape * sizeof(entry);

	entry *newHashMap;
	glbGpuAllocator->_cudaMalloc((void **)&newHashMap, noBytes);
	cudaCheckError();

	cudaMemset(newHashMap, 0, noBytes);
	cudaCheckError();

	int noBlocks;
	int noThreads;
	getDeviceParams(capacity, noBlocks, noThreads);

	kernel_reshape<<<noBlocks, noThreads>>>(newHashMap, numBucketsReshape, hashMap, capacity);

	cudaDeviceSynchronize();
	cudaCheckError();

	glbGpuAllocator->_cudaFree(hashMap);
	cudaCheckError();

	hashMap = newHashMap;
	capacity = numBucketsReshape;
}

// GPU: inserts into hashmap one entry from the given arrays based on thread index
__global__ void
kernel_insert(entry *hashMap, int *keys, int *values, int noKeys, int capacity, int *noUpdates) {
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if (idx >= noKeys)
		return;

	int key = keys[idx];
	int value = values[idx];
	uint32_t h = _hash(key) % capacity;
	int prevKey = 0;

	// linear probing until a free spot is found or an update is done
	do {
		prevKey = atomicCAS(&hashMap[h].key, 0, key);

		if (prevKey == 0 || prevKey == key) {
			hashMap[h].value = value;

			if (prevKey == key)
				atomicAdd(noUpdates, 1);

			return;
		}

		h = (h + 1) % capacity;
	} while(1);
}

/**
 * Function insertBatch
 * Inserts a batch of key:value, using GPU and wrapper allocators
 */
bool GpuHashTable::insertBatch(int *keys, int* values, int numKeys) {
	int noBytes = numKeys * sizeof(int);
	int *deviceKeys;
	int *deviceValues;
	int *noUpdates;

	glbGpuAllocator->_cudaMalloc((void **)&deviceKeys, noBytes);
	cudaCheckError();

	glbGpuAllocator->_cudaMalloc((void **)&deviceValues, noBytes);
	cudaCheckError();

	glbGpuAllocator->_cudaMallocManaged((void **)&noUpdates, sizeof(int));
	cudaCheckError();
	*noUpdates = 0;

	cudaMemcpy(deviceKeys, keys, noBytes, cudaMemcpyHostToDevice);
	cudaCheckError();

	cudaMemcpy(deviceValues, values, noBytes, cudaMemcpyHostToDevice);
	cudaCheckError();

	if ((size + numKeys) / (float) capacity >= MAX_LOAD_FACTOR)
		reshape((size + numKeys) / MIN_LOAD_FACTOR);

	int noBlocks;
	int noThreads;
	getDeviceParams(numKeys, noBlocks, noThreads);

	kernel_insert<<<noBlocks, noThreads>>>(hashMap, deviceKeys, deviceValues, numKeys, capacity, noUpdates);
	
	cudaDeviceSynchronize();
	cudaCheckError();

	size = size + numKeys - *noUpdates;

	glbGpuAllocator->_cudaFree(deviceKeys);
	cudaCheckError();

	glbGpuAllocator->_cudaFree(deviceValues);
	cudaCheckError();

	glbGpuAllocator->_cudaFree(noUpdates);
	cudaCheckError();

	return true;
}

// GPU: returns one value corresponding to one given key based on the thread index
__global__ void
kernel_get(entry *hashMap, int *deviceKeys, int noKeys, int capacity, int *values) {
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if (idx >= noKeys)
		return;

	int key = deviceKeys[idx];
	uint32_t h = _hash(key) % capacity;

	// linear probing until the key is found
	do {
		if (key == hashMap[h].key) {
			values[idx] = hashMap[h].value;
			return;
		}

		h = (h + 1) % capacity;
	} while(1);
}

/**
 * Function getBatch
 * Gets a batch of key:value, using GPU
 */
int* GpuHashTable::getBatch(int* keys, int numKeys) {
	int *values;
	int *deviceKeys;
	int noBytes = numKeys * sizeof(int);

	glbGpuAllocator->_cudaMalloc((void **)&deviceKeys, noBytes);
	cudaCheckError();

	cudaMemcpy(deviceKeys, keys, noBytes, cudaMemcpyHostToDevice);
	cudaCheckError();

	glbGpuAllocator->_cudaMallocManaged((void **)&values, noBytes);
	cudaCheckError();

	int noBlocks;
	int noThreads;
	getDeviceParams(numKeys, noBlocks, noThreads);

	kernel_get<<<noBlocks, noThreads>>>(hashMap, deviceKeys, numKeys, capacity, values);

	cudaDeviceSynchronize();
	cudaCheckError();

	glbGpuAllocator->_cudaFree(deviceKeys);
	cudaCheckError();

	// return RAM allocated values to not overflow VRAM wrapper - glbGpuAllocator
	int *hostValues = (int *) malloc(noBytes);
	cudaMemcpy(hostValues, values, noBytes, cudaMemcpyDeviceToHost);
	cudaCheckError();

	glbGpuAllocator->_cudaFree(values);
	cudaCheckError();

	return hostValues;
}
