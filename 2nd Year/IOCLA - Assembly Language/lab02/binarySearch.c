#include <stdio.h>

int main() {

	int arr[5] = {2, 5, 8, 12, 25};
	int n;

	printf("Nr:");
	scanf("%d", &n);

	int low = 0;
	int high = 4;
	int mid;

check:	
	mid = low + (high - low)/2;

	if(n == arr[mid])
		goto found;
	
	if(low == high)
		goto notFound;

	if(n < arr[mid])
		goto left;

	if(n > arr[mid])
		goto right;

left:
	high = mid - 1;
	goto check;

right:
	low = mid + 1;
	goto check;

found:
	printf("A fost gasit.\n");
	goto end;

notFound:
	printf("Nu a fost gasit.\n");
	goto end;

end:
	return 0;

}



