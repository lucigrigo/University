#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_INPUT_LEN 256

typedef int Item;
#include "Queue.h"

void printArray(int *arr, int len)
{
	for (int i = 0; i < len; i++)
		printf("%d ", arr[i]);
}

int arrayMaximum(const int *arr, int len)
{
	int max = arr[0];
	for (int i = 1; i < len; i++)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}

int getNumberOfDigits(int num)
{
	int digits = 0;
	while (num)
	{
		num = num / 10;
		digits++;
	}
	return digits;
}

void convertToIntArray(Queue **src, int *dest)
{
	int i, length = 0;
	for (i = 0; i < 10; i++)
	{
		QueueNode *ptr = src[i]->front;
		while (ptr != NULL)
		{
			dest[length++] = ptr->elem;
			ptr = ptr->next;
			dequeue(src[i]);
		}
	}
}

void splitIntoQs(int *src, int len, Queue **dest, int digitMark)
{
	int comp = pow(10, digitMark), i = 0;
	while (i < len)
	{
		int desc = src[i] / (comp / 10);
		int copy = (desc % 10);
		enqueue(dest[copy], src[i]);
		i++;
	}
}

void radixSort(int *arr, int len)
{
	// 🐶
	Queue **q = (Queue **)malloc(10 * sizeof(Queue *));
	int i;
	for (i = 0; i < 10; i++)
	{
		q[i] = createQueue();
	}

	int maxDigitNumber = 1;
	for (i = 0; i < len; i++)
	{
		int maxDigit = 1, maxImp = 10, rez = (arr[i] / maxImp);
		while (rez > 0)
		{
			maxDigit = maxDigit + 1;
			maxImp = maxImp * 10;
			rez = (arr[i] / maxImp);
		}
		if (maxDigit > maxDigitNumber)
		{
			maxDigitNumber = maxDigit;
		}
	}

	int a = 1;
	while (a <= maxDigitNumber)
	{
		splitIntoQs(arr, len, q, a);
		convertToIntArray(q, arr);
		a++;
	}

	for (i = 0; i < 10; i++)
	{
		destroyQueue(q[i]);
	}
	free(q);
}

int main(void)
{

	int len;
	char fileBuffer[MAX_INPUT_LEN];
	FILE *inputFile = fopen("input-radix-sort.csv", "r");
	if (inputFile == NULL)
		return 1;

	int capacity = MAX_INPUT_LEN;
	int *arr = (int *)malloc(capacity * sizeof(int));

	int count = 0;
	while (fgets(fileBuffer, MAX_INPUT_LEN, inputFile) != NULL)
	{
		fileBuffer[strcspn(fileBuffer, "\r\n")] = 0;
		len = strlen(fileBuffer);
		if (len == 0)
			break;

		char *token = strtok(fileBuffer, ",\n");
		if (token == NULL)
			return 1;
		len = 0;
		arr[len++] = atoi(token);
		while (token != NULL)
		{
			if (len == capacity)
			{
				capacity <<= 1;
				arr = realloc(arr, capacity * sizeof(int));
			}

			token = strtok(NULL, ",\r\n");
			if (token != NULL)
				arr[len++] = atoi(token);
		}

		count++;
		printf("Input array %d:\t", count);
		printArray(arr, len);
		printf("\n");
		radixSort(arr, len);
		printf("Sorted array %d:\t", count);
		printArray(arr, len);
		printf("\n");
		printf("\n");
	}

	free(arr);
	fclose(inputFile);
	return 0;
}
