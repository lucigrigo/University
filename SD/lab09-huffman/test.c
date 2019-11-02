#include <stdio.h>

#include "huffman.h"

#define ASSERT(cond, msg) if (!(cond)) { failed(msg); exit(0); }
void passed(char* s) {
    printf("Testul %s a fost trecut cu succes!\t\t \n", s);
}

void failed(char* s) {
    printf("Testul %s NU a fost trecut!\n", s);
}


void runTest(char *text, char *testName) {
    int textSize = strlen(text);

    int freqs[256];
    computeFreqs(text, textSize, freqs);

    int numNodes = 0;
    HuffmanNode *nodes = makeTree(freqs, &numNodes);

    char *compressed = compress(text, textSize, nodes, numNodes);
    char *decompressed = decompress(compressed, strlen(compressed), nodes, numNodes);

    ASSERT(strcmp(text, compressed) != 0, testName);
    ASSERT(strcmp(text, decompressed) == 0, testName);
}

int main() {
    runTest("ababab", "Regular-01");
    runTest("hello world", "Regular-02");
    runTest("ana are mere", "Regular-03");
    runTest("ala bala portocala", "Regular-04");
    runTest("this is an example of a huffman tree", "Regular-05");
    passed("Regular");

    runTest("aaaaaaaa", "Single-01");
    runTest("a", "Single-02");
    passed("Single");

    runTest("", "Empty-01");
    passed("Empty");

    return 0;
}

