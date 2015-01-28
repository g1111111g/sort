#include<stdlib.h>
#include<stdio.h>

void Qsort(int a[], int numsize);
int main(int argc, char* argv[]){
	int a[] = {4,7,1,8,2,6,5,9,3,0};
	int size = sizeof(a)/sizeof(int);
	Qsort(a, size);
	//printf("%d\n", sizeof(short));
	PrintIntArray(a, &size);	
	return 0;
}

void Qsort(int a[], int numsize){
	int i = 0;
	int j = numsize - 1;
	int val = a[0];
	if(numsize > 1){
		while(i < j){
			for(;j>i;j--){
				if(a[j] < val){
					a[i++] = a[j];
					break;
				}
			}

			for(;i<j;i++){
				if(a[i] > val){
					a[j--] = a[i];
					break;
				}
			}
		}
		a[i] = val;
		Qsort(a, i);
		Qsort(a+i+1, numsize-i-1);
	}
}


