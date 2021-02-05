int printLevel;
int N;
int P;

void* threadFunction(void *var);
void getArgs(int argc, char **argv);
void printPartial();
void printAll();
void print();
void startThreads();
void displayVector(int *v, int N);
int * allocVector(int N);
