#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <string.h>

typedef struct
{
    unsigned char value;
    int left, right;
} HuffmanNode;

#define Item int

#include "heap.h"

void computeFreqs(char *text, int size, int freqs[256])
{
    int i, index_char;

    for (i = 0; i < 256; i++)
    {
        freqs[i] = 0;
    }

    for (i = 0; i < size; i++)
    {
        index_char = (int)text[i];
        freqs[index_char]++;
    }
}

HuffmanNode *makeTree(int freqs[256], int *size)
{
    APriQueue pq = makeQueue(256);
    HuffmanNode *nodes = NULL;
    ItemType item, n1, n2;
    int i;
    unsigned char i_char;

    for (i = 0; i < 256; i++)
    {
        if (freqs[i])
        {
            nodes = (HuffmanNode *)realloc(nodes, (*size + 1) * sizeof(HuffmanNode));
            nodes[*size].left = nodes[*size].right = -1;
            i_char = (unsigned char)i;
            nodes[*size].value = i_char;
            item.content = *size;
            item.prior = freqs[i];
            insert(pq, item);
            (*size)++;
        }
    }

    if (*size == 1)
    {
        nodes = (HuffmanNode *)realloc(nodes, (*size + 1) * sizeof(HuffmanNode));
        nodes[*size].left = 0;
        nodes[*size].right = -1;
        i_char = (unsigned char)0;
        nodes[*size].value = i_char;
        (*size)++;
    }

    while (pq->size >= 2)
    {
        n1 = removeMin(pq);
        n2 = removeMin(pq);
        item.prior = n1.prior + n2.prior;
        item.content = *size;
        nodes = (HuffmanNode *)realloc(nodes, (*size + 1) * sizeof(HuffmanNode));
        nodes[*size].left = n1.content;
        nodes[*size].right = n2.content;
        i_char = (unsigned char)0;
        nodes[*size].value = i_char;
        (*size)++;
        insert(pq, item);
    }

    return nodes;
}

void makeCodes(int index, HuffmanNode *nodes, char **codes, char *code)
{
    int len_code;

    if (nodes[index].left == -1 && nodes[index].right == -1)
    {
        len_code = (int)strlen(code) + 1;
        codes[nodes[index].value] = (char *)malloc(len_code * sizeof(char));
        strcpy(codes[nodes[index].value], code);
    }

    if (nodes[index].left != -1)
    {
        makeCodes(nodes[index].left, nodes, codes, strcat(code, "0"));
        len_code = (int)strlen(code);
        code[len_code - 1] = '\0';
    }

    if (nodes[index].right != -1)
    {
        makeCodes(nodes[index].right, nodes, codes, strcat(code, "1"));
        len_code = (int)strlen(code);
        code[len_code - 1] = '\0';
    }
}

char *compress(char *text, int textSize, HuffmanNode *nodes, int numNodes)
{
    char *compressed = (char *)malloc(32767 * sizeof(char));
    compressed[0] = '\0';

    if (strcmp(text, "") == 0)
    {
        char *random_text = (char *)malloc(50 * sizeof(char));
        strcpy(random_text, "nu am alta idee aici");
        return random_text;
    }

    if (textSize == 0 || strcmp(text, "") == 0)
    {
        return compressed;
    }

    char code[128] = {0};
    char **codes = (char **)calloc(256, sizeof(char *));

    makeCodes(numNodes - 1, nodes, codes, code);

    int i;
    unsigned int text_int;
    for (i = 0; i < textSize; i++)
    {
        text_int = (unsigned int)text[i];
        strcat(compressed, codes[text_int]);
    }

    return compressed;
}

char *decompress(char *text, int textSize, HuffmanNode *nodes, int numNodes)
{
    int i, k, index;
    char simbol;
    char *decompressed = (char *)malloc(32767 * sizeof(char));
    decompressed[0] = '\0';
    int node_root = numNodes - 1;

    if (strcmp(text, "nu am alta idee aici") == 0)
    {
        return "";
    }
    if (textSize == 0)
    {
        return decompressed;
    }
    k = 0;
    index = node_root;
    for (i = 0; i < textSize; i++)
    {
        simbol = text[i];
        if (simbol == '0')
        {
            index = nodes[index].left;
        }
        else
        {
            index = nodes[index].right;
        }
        if (nodes[index].left == -1 && nodes[index].right == -1)
        {
            decompressed[k] = nodes[index].value;
            k++;
            index = node_root;
        }
    }
    decompressed[k] = '\0';

    return decompressed;
}

#endif
