#include <iostream>

#define DATA_ELEM   75
#define DB_ELEM     20
#define DB_SIZE    100

using namespace std;

struct Data {
	unsigned int d1;
	unsigned int d2;
};

union Item {
    Data data;
    unsigned long long int raw;
};

// TODO, changes only in kernel_write
// database has empty(0) and non-empty(!=0) positions, around DB_ELEM/DB_SIZE occupied
// change the kernel so each thread writes dataToAdd in an empty spot in database
// reordoring of data is permitted
// (0 1 0 1 0 ) => (t1:2, t2:3) => (2 1 1 3 0)
__global__ void kernel_write(unsigned long long int *data,
                             unsigned long long int *database,
                             int dbElemNum) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    long long unsigned dataToAdd = data[idx];
	long long unsigned oldData = 0l;

    if(dataToAdd == 0) {
        return;
    }

    // logic using atomicExch to place elements in empty slots, no barriers
    // TODO
	while((oldData = atomicExch(database + idx, dataToAdd))) {
		atomicExch(database + idx, oldData);
		idx = (idx + 1) % dbElemNum;
	}
}

// do not modify validateDB and main
//
void validateDB(unsigned long long int *database, int dbSize, int expNZElem) {

    bool isValid = true;
    int numNZElem = 0;

    for(int i = 0; i < DB_SIZE; i++) {

        Item item;
        item.raw = database[i];

        if(item.raw != 0) {
            numNZElem++;
        }

        cout << item.data.d1 << "-" << item.data.d2;
        if(item.data.d1 != item.data.d2) {
            cout << " ERR, ";
            isValid = false;
        } else {
            cout << " OK, ";
        }
    }

    if (!isValid) {
        cout << endl << "INVALID, corrupt writes" << endl;
    } else if (expNZElem != numNZElem) {
        cout << endl << "INVALID, expected database elements "
            << expNZElem << " but got " << numNZElem << endl;
    } else {
        cout << endl << "VALID" << endl;
    }
}

int main(void) {

    long long unsigned *data = 0;
    cudaMallocManaged(&data, DATA_ELEM * sizeof(unsigned long long int));
    if (data == 0) {
        cout << "[HOST] Couldn't allocate memory\n";
        return 1;
    }

    // data to introduce into db
    for(int i = 0; i < DATA_ELEM; i++) {
        Item item;
        item.data.d1 = i + 1;
        item.data.d2 = i + 1;
        data[i] = item.raw;
    }

    long long unsigned *database = 0;
    cudaMallocManaged(&database, DB_SIZE * sizeof(unsigned long long int));
    if (data == 0) {
        cout << "[HOST] Couldn't allocate memory\n";
        return 1;
    }

    // current db is 25% full, 75% empty
    for(int i = 0; i < DB_SIZE; i++) {
        if(i % (DB_SIZE / DB_ELEM) == 0) {
            Item item;
            item.data.d1 = 1111;
            item.data.d2 = 1111;
            database[i] = item.raw;
        }
    }

    kernel_write<<<DATA_ELEM, 1>>> (data, database, DB_SIZE);
	cudaDeviceSynchronize();

    validateDB(database, DB_SIZE, (DB_ELEM + DATA_ELEM));

    cudaFree(data);
    cudaFree(database);
    return 0;
}
