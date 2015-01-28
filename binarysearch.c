#include<stdio.h>
#include<stdlib.h>

void binarySearch(int a[], int low, int heigh, int key);
int main(int argc, char *argv[]){
	
	int a[9] = {1,2,3,4,5,6,7,8,9};
	binarySearch(a, 0, sizeof(a)/sizeof(int) - 1, 1);
	binarySearch(a, 0, sizeof(a)/sizeof(int) - 1, 2);
	binarySearch(a, 0, sizeof(a)/sizeof(int) - 1, 3);
	binarySearch(a, 0, sizeof(a)/sizeof(int) - 1, 4);
	binarySearch(a, 0, sizeof(a)/sizeof(int) - 1, 5);
	binarySearch(a, 0, sizeof(a)/sizeof(int) - 1, 6);
	binarySearch(a, 0, sizeof(a)/sizeof(int) - 1, 7);
	binarySearch(a, 0, sizeof(a)/sizeof(int) - 1, 8);
	binarySearch(a, 0, sizeof(a)/sizeof(int) - 1, 9);
	binarySearch(a, 0, sizeof(a)/sizeof(int) - 1, 10);
	return 0;
}

void binarySearch(int a[], int low, int heigh, int key){
	int mid;
	if(low > heigh){
		printf("not find:%d\n", key);
		return;
	}
	mid = (low + heigh)/2;
	if(a[mid] == key){
		printf("you find it:%d\n", key);
		return;
	}
	if(a[mid] > key){
		binarySearch(a, low, mid - 1, key);
	}else{
		binarySearch(a, mid + 1, heigh, key);
	}
}
