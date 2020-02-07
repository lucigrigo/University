#include <stdio.h>

int main() {

	int arr[] = {2, 7, 8, 3};
	int max = arr[0];
	int i = 0;
	int length = 4;

check:
	
	if(max < arr[i])
		max = arr[i];

	i++;

	if(i == length)
		goto end;

	goto check;

end:
	printf("Max este: %d\n", max);
	return 0;


}
