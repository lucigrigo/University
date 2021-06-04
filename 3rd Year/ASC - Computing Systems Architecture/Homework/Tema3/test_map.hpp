#include <unordered_map>

using namespace std;

#define MB_1	(1024 * 1024)

#define	KEY_INVALID		0
#define DIE(assertion, call_description) \
	do {	\
		if (assertion) {	\
		fprintf(stderr, "(%s, %d): ",	\
		__FILE__, __LINE__);	\
		perror(call_description);	\
		exit(errno);	\
	}	\
} while (0)

class GpuAllocator
{
    long long int allocMax;
    long long int allocCurrent;

	std::unordered_map<void*, int> allocMap;

public:
    GpuAllocator(long long int allocMax);

    cudaError_t _cudaMalloc( void** devPtr, size_t size );
	cudaError_t _cudaMallocManaged( void** devPtr, size_t size );
    cudaError_t _cudaFree( void* devPtr );

    float _loadFactor( void );
    long long int _used( void );
};

extern GpuAllocator *glbGpuAllocator;