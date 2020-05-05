#include <stdio.h>

int main() {

	int i, j, temp;
	int arr[] = {2, 1, 5, 0, 4};
	int arrSize = 5;
	
	i = 0;

startFor:
	if (i >= (arrSize - 1)) goto endFor;

	j = 0;

startMiddleFor:
	if (j >= arrSize - 1 - i) goto endMiddleFor;

	if (arr[j] > arr[j+1])
    {
        temp = arr[j+1];
        arr[j+1] = arr[j];
        arr[j] = temp;
    }

    j++;
    goto startMiddleFor;
endMiddleFor:

    ++i;
    goto startFor;
endFor:;

	for(i = 0; i < arrSize; i++)
		printf("%d, ", arr[i]);

	return 0;

}

