#include <algorithm>
#include <array>
#include <chrono>
#include <errno.h>
#include <fstream>
#include <inttypes.h>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <random>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>

#include <cuda_runtime_api.h>
#include <cuda.h>

#include "gpu_hashtable.hpp"
#include "test_map.hpp"

using namespace std;
using namespace chrono;

GpuAllocator *glbGpuAllocator = nullptr;

GpuAllocator::GpuAllocator(long long int allocMax) {
	this->allocMax = allocMax;
	this->allocCurrent = 0;
}


/**
 * Wrapper _cudaMalloc
 * @return cudaMalloc allocation if within bounds/limits
 */
cudaError_t GpuAllocator::_cudaMalloc( void** devPtr, size_t size ) {

	if ( (this->allocCurrent + size) <= this->allocMax ) {
		cudaError_t rt = cudaMalloc(devPtr, size);
		this->allocCurrent += size;
		this->allocMap[ *devPtr ] = size;
		return rt;
	} else {
		DIE(true, "cudaMalloc would exceed allowed max alloc size" );
	}
}


/**
 * Wrapper _cudaMallocManaged
 * @return cudaMallocManaged allocation if within bounds/limits
 */
cudaError_t GpuAllocator::_cudaMallocManaged( void** devPtr, size_t size ) {

	if ( (this->allocCurrent + size) <= this->allocMax ) {
		cudaError_t rt = cudaMallocManaged(devPtr, size);
		this->allocCurrent += size;
		this->allocMap[ *devPtr ] = size;
		return rt;
	} else {
		DIE(true, "cudaMallocManaged would exceed allowed max alloc size" );
	}
}


/**
 * Wrapper _cudaFree
 * @return cudaFree allocation if ptr found (allocated via wrapper)
 */
cudaError_t GpuAllocator::_cudaFree( void* devPtr ) {

	if (this->allocMap.find(devPtr) == this->allocMap.end()) {
		return cudaErrorInvalidValue;
	} else {
		this->allocCurrent -= this->allocMap.find(devPtr)->second;
		this->allocMap.erase(devPtr);
		return cudaFree(devPtr);
	}
}


/**
 * Wrapper _used
 * @return current allocated memory via wrappers
 */
long long int GpuAllocator::_used( void ) {
	return this->allocCurrent;
}


void fillRandom(vector<int> &vecKeys, vector<int> &vecValues, int numEntries) {
	vecKeys.reserve(numEntries);
	vecValues.reserve(numEntries);
	
	int interval = (numeric_limits<int>::max() / numEntries) - 1;
	default_random_engine generator;
	uniform_int_distribution<int> distribution(1, interval);

	for(int i = 0; i < numEntries; i++) {
		vecKeys.push_back(interval * i + distribution(generator));
		vecValues.push_back(interval * i + distribution(generator));
	}
	
	random_shuffle(vecKeys.begin(), vecKeys.end());
	random_shuffle(vecValues.begin(), vecValues.end());
}


/**
 * Main description.
 * @param argv1 is total number of hash inserts/gets 
 * @param argv2 is number of sets, (total/nrsets) is a chunk
 * @param argv3 is min performance measured in M/sec for INSERT/GET
 * @return different than 0 means run has failed
 */
int main(int argc, char **argv)
{
	clock_t begin;
	double elapsedTime;
	
	int numKeys = 0;
	int numChunks = 0;
	int minSpeed = 100;
	vector<int> vecKeys;
	vector<int> vecValues;
	int *valuesGot = NULL;
	
	DIE(argc != 4, 
		"ERR, args num, call ./bin test_numKeys test_numChunks hash_speed");
	
	numKeys = stoll(argv[1]);
	DIE((numKeys < 1) || (numKeys >= numeric_limits<int>::max()),
		"ERR, numKeys should be greater or equal to 1 and less than maxint");
	
	numChunks = stoll(argv[2]);
	DIE((numChunks < 1) || (numChunks >= numKeys), 
		"ERR, numChunks should be greater or equal to 1");

	minSpeed = stoll(argv[3]);
	DIE((minSpeed < 0) || (minSpeed >= 500), 
		"ERR, minSpeed should be between 0 and 500");

	float loadFactorMin = 0.5f;
	float loadFactorMax = 1.0f;

	float speedGet = 0.f;
	float speedInsert = 0.f;
	
	fillRandom(vecKeys, vecValues, numKeys);
	
	glbGpuAllocator = new GpuAllocator(numKeys * sizeof(int) * 2 * 4);

	GpuHashTable gHashTable(1);
	
	int inserted = 0;
	int chunkSize = numKeys / numChunks;
	gHashTable.reshape(chunkSize);
	
	// perform INSERT and test performance
	for(int chunkStart = 0; chunkStart < numKeys; chunkStart += chunkSize) {
		
		int *keysStart = &vecKeys[chunkStart];
		int *valuesStart = &vecValues[chunkStart];
		
		auto start = high_resolution_clock::now();

		// INSERT stage
		gHashTable.insertBatch(keysStart, valuesStart, chunkSize);
		inserted += chunkSize;

		auto stop = high_resolution_clock::now();
		elapsedTime = duration_cast<microseconds>(stop - start).count();

		float speed = chunkSize / elapsedTime;
		float hashLoadFactor = (float) inserted * sizeof(int) * 2.f / glbGpuAllocator->_used();

		cout << setw(20) << left << "HASH_BATCH_INSERT"
		<< setw(24) << left << "count: " + to_string(chunkSize)
		<< setw(24) << left << "speed: " + to_string( (int)speed ) + "M/sec"
		<< setw(24) << left 
		<< "loadfactor: " + to_string( (int)(hashLoadFactor * 100.f) ) + "%" << endl;

		// check load factor
		DIE( loadFactorMin > hashLoadFactor, "loadFactorMin > hashLoadFactor");
		DIE( loadFactorMax < hashLoadFactor, "loadFactorMax < hashLoadFactor");

		speedInsert += speed;
	}
	
	// perform INSERT for update validation
	int chunkSizeUpdate = min(64, numKeys);
	for(int chunkStart = 0; chunkStart < chunkSizeUpdate; chunkStart++) {
		vecValues[chunkStart] += 1111111 + chunkStart;
	}

	gHashTable.insertBatch(&vecKeys[0], &vecValues[0], chunkSizeUpdate);
	
	// perform GET and test performance
	for(int chunkStart = 0; chunkStart < numKeys; chunkStart += chunkSize) {
		
		int *keysStart = &vecKeys[chunkStart];

		auto start = high_resolution_clock::now();

		// GET stage
		valuesGot = gHashTable.getBatch(keysStart, chunkSize);

		auto stop = high_resolution_clock::now();
		elapsedTime = duration_cast<microseconds>(stop - start).count();

		float speed = chunkSize / elapsedTime;
		float hashLoadFactor = (float) inserted * sizeof(int) * 2.f / glbGpuAllocator->_used();

		cout << setw(20) << left << "HASH_BATCH_GET"
		<< setw(24) << left << "count: " + to_string(chunkSize)
		<< setw(24) << left << "speed: " + to_string( (int)speed ) + "M/sec"
		<< setw(24) << left 
		<< "loadfactor: " + to_string( (int)(hashLoadFactor * 100.f) ) + "%" << endl;

		// check load factor
		DIE( loadFactorMin > hashLoadFactor, "loadFactorMin > hashLoadFactor" );
		DIE( loadFactorMax < hashLoadFactor, "loadFactorMax < hashLoadFactor" );
		DIE( valuesGot == NULL, "ERR, ptr valuesCheck cannot be NULL" );

		speedGet += speed;
		
		int mistmatches = 0;
		for(int i = 0; i < chunkSize; i++) {
			if(vecValues[chunkStart + i] != valuesGot[i]) {
				mistmatches++;
				if(mistmatches < 32) {
					cout << "Expected " << vecValues[chunkStart + i]
					<< ", but got " << valuesGot[i] << " for key:" << keysStart[i] << endl;
				}
			}
		}
		
		if(mistmatches > 0) {
			cout << "ERR, mistmatches: " << mistmatches << " / " << numKeys << endl;
			exit(1);
		}
	}

	float avgSpeedInsert = speedInsert / numChunks;
	float avgSpeedGet = speedGet / numChunks;

	cout << "----------------------------------------------" << endl;
	cout << setw(24) << left << "AVG_INSERT: " + to_string( (int)avgSpeedInsert ) + " M/sec,"
		<< setw(24) << left<< "AVG_GET: " + to_string( (int)avgSpeedGet ) + " M/sec,"
		<< setw(24) << left<< "MIN_SPEED_REQ: " +  to_string(minSpeed) + " M/sec" << endl;

	DIE( minSpeed > avgSpeedGet, "minSpeed > avgSpeedGet" );
	DIE( minSpeed > avgSpeedInsert, "minSpeed > avgSpeedInsert" );

	cout << endl;

	return 0;
}

