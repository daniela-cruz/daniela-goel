#include <stdio.h>
#define MY_SIZEOF(type) (char *)(&type + 1) - (char *)(&type)

int main()
{
	int arr[10];
	
	
	printf("%ld", MY_SIZEOF(arr));
	return 0;
}
