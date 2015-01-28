#include<stdio.h>
#include<stdlib.h>

void PrintIntArray(int *a, int size){
//	printf("%d\n", sizeof(a)); //print 8 because this is 64bit system
	int i;
	for(i = 0; i < size; i++){
		printf("%4u", a[i]);
	}
	printf("\n");
}
