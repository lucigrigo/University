/*
	ASC - Tema 3
	GPU Hashtable
	Grigore Lucian-Florin
	336CA
*/
#ifndef _HASHCPU_
#define _HASHCPU_

#include <vector>

using namespace std;

#define cudaCheckError() { \
	cudaError_t e=cudaGetLastError(); \
	if(e!=cudaSuccess) { \
		cout << "Cuda failure " << __FILE__ << ", " << __LINE__ << ", " << cudaGetErrorString(e); \
		exit(0); \
	 }\
}

// structure that stores <key, values> associations
struct entry {
	int key;
	int value;
};

/**
 * Class GpuHashTable to implement functions
 */
class GpuHashTable
{
private:
	entry *hashMap; // array of entries
	int size; // current size of hashmap
	int capacity; // maximum size of hashmap

	void getDeviceParams(int, int &, int &);

	float computeLoadFactor();
public:
	GpuHashTable(int size);
	void reshape(int sizeReshape);

	bool insertBatch(int *keys, int* values, int numKeys);
	int* getBatch(int* key, int numItems);
	
	~GpuHashTable();
};

#endif

