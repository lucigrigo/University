#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) (a) < (b) ? (a) : (b)

typedef char *Key;
typedef int Value;
typedef long (*HashFunction)(Key, long);

typedef struct Element
{
  Key key;
  Value value;
  struct Element *next;
} Element;

typedef struct HashTable
{
  Element **elements;
  long size;
  HashFunction hashFunction;
} HashTable;

void initHashTable(HashTable **h, long size, HashFunction f)
{
  *h = (HashTable *)malloc(sizeof(HashTable));
  (*h)->size = size;
  (*h)->hashFunction = f;
  (*h)->elements = (Element **)malloc(size * sizeof(Element *));
}

int exists(HashTable *hashTable, Key key)
{
  int found = 0, i;
  for (i = 0; i < hashTable->size; i++)
  {
    Element *elementPtr = hashTable->elements[i];
    while (elementPtr != NULL)
    {
      if (strcmp(elementPtr->key, key) == 0)
        found = 1;
      elementPtr = elementPtr->next;
    }
  }
  return found;
}

Value get(HashTable *hashTable, Key key)
{
  int i;
  for (i = 0; i < hashTable->size; i++)
  {
    Element *elementPtr = hashTable->elements[i];
    while (elementPtr != NULL)
    {
      if (strcmp(elementPtr->key, key) == 0)
        return elementPtr->value;
      elementPtr = elementPtr->next;
    }
  }
  return (Value)-1;
}

void put(HashTable *hashTable, Key key, Value value)
{
  Element *elementPtr = hashTable->elements[hashTable->hashFunction(key, hashTable->size)];
  while (elementPtr != NULL)
  {
    if (strcmp(elementPtr->key, key) == 0)
    {
      elementPtr->value = value;
      return;
    }
    elementPtr = elementPtr->next;
  }
  Element *newElement = (Element *)malloc(sizeof(Element));
  newElement->key = (char *)malloc(strlen(key));
  strcpy(newElement->key, key);
  newElement->value = value;
  newElement->next = hashTable->elements[hashTable->hashFunction(key, hashTable->size)];
  hashTable->elements[hashTable->hashFunction(key, hashTable->size)] = newElement;
}

void deleteKey(HashTable *hashTable, Key key)
{
  int i;
  for (i = 0; i < hashTable->size; i++)
  {
    Element *elementPtr = hashTable->elements[i];
    if (strcmp(elementPtr->key, key) == 0)
    {
      hashTable->elements[i] = elementPtr->next;
      free(elementPtr->key);
      free(elementPtr);
      return;
    }
    else
    {
      Element *prevPtr = elementPtr;
      elementPtr = elementPtr->next;
      while (elementPtr != NULL)
      {
        if (strcmp(elementPtr->key, key) == 0)
        {
          prevPtr->next = elementPtr->next;
          free(elementPtr->key);
          free(elementPtr);
          return;
        }
        prevPtr = elementPtr;
        elementPtr = elementPtr->next;
      }
    }
  }
}

void print(HashTable *hashTable)
{
  int i;
  for (i = 0; i < hashTable->size; i++)
  {
    Element *elementPtr = hashTable->elements[i];
    if (elementPtr != NULL)
      printf("%d:\n", i);
    while (elementPtr != NULL)
    {
      printf("  %s : %d\n", elementPtr->key,
             elementPtr->value);
      elementPtr = elementPtr->next;
    }
  }
}

void freeHashTable(HashTable *hashTable)
{
  int i;
  for (i = 0; i < hashTable->size; i++)
  {
    if (hashTable->elements[i] != NULL)
    {
      Element *aux1 = hashTable->elements[i], *aux2;
      while (aux1 != NULL)
      {
        aux2 = aux1->next;
        free(aux1->key);
        free(aux1);
        aux1 = aux2;
      }
    }
  }
  free(hashTable);
}

long hash1(Key word, long size)
{
  long h = 0;
  int i;
  for (i = 0; i < (strlen(word) - 1); i++)
  {
    h = h * 17 + word[i];
  }
  return h % size;
}

int main(int argc, char *argv[])
{
  HashTable *hashTable, *secondHashTable;
  FILE *f1, *f2;
  char word[256], delim[5] = " \n";
  long hashSize, common;

  hashSize = atoi(argv[1]);
  f1 = fopen(argv[2], "r");
  f2 = fopen(argv[3], "r");

  initHashTable(&hashTable, hashSize, &hash1);
  initHashTable(&secondHashTable, hashSize, &hash1);

  // Cerinta 3

  while (fgets(word, 256, f1))
  {
    char *token = strtok(word, delim);
    while (token != NULL)
    {
      if (exists(hashTable, token))
      {
        int newValue = get(hashTable, token) + 1;
        put(hashTable, token, newValue);
      }
      else
      {
        put(hashTable, token, 1);
      }
      token = strtok(NULL, delim);
    }
  }
  print(hashTable);

  // Cerinta 4

  while (fgets(word, 256, f2))
  {
    char *token = strtok(word, delim);
    while (token != NULL)
    {
      if (exists(secondHashTable, token))
      {
        int newValue = get(secondHashTable, token) + 1;
        put(secondHashTable, token, newValue);
      }
      else
      {
        put(secondHashTable, token, 1);
      }
      token = strtok(NULL, delim);
    }
  }
  int i;
  for (i = 0; i < secondHashTable->size; i++)
  {
    Element *elementPtr = secondHashTable->elements[i];
    while (elementPtr != NULL)
    {
      if (exists(hashTable, elementPtr->key))
      {
        common += min(get(hashTable, elementPtr->key),
                      elementPtr->value);
      }
      elementPtr = elementPtr->next;
    }
  }

  printf("Common words: %ld\n", common);

  fclose(f1);
  fclose(f2);
  return 0;
}
