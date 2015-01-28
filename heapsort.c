#include<stdio.h>
#include<stdlib.h>

void print(int a[], int len){
	int i;
	for(i = 0; i < len; i++){
		printf("%2d", a[i]);
	}
	printf("\n");

}

void HeapAdjust(int a[], int s, int length){
	int tmp = a[s];
	int child = 2*s+1; /*child为调整位置的左节点*/
	while(child < length){
		if(child+1 < length && a[child] < a[child+1]){
			++child;
		}
		if(a[s] < a[child]){
			a[s] = a[child];
			s = child;
			child = 2*s+1;
		}else{
			break;
		}
		a[s] = tmp;
	}
}

void HeapBuild(int a[], int length){
	int i;
	for(i = (length - 1)/2; i >= 0; i--){/*从最后一个有孩子节点的位置开始调整堆*/
		HeapAdjust(a, i, length);
		print(a, length);
	}
	printf("\n");
}

void HeapSort(int a[], int length){
	int i,temp;
	HeapBuild(a, length);
	for(i = length - 1; i > 0; i--){
		temp = a[0];
		a[0] = a[i];
		a[i] = temp;
		HeapAdjust(a, 0, i);
		print(a, length);
	}
	printf("\n");
}

int main(int argc, char *argv[]){
	int i;
	int a[] = {1,5,3,2,4,6,7,8,0};
	HeapSort(a, 9);
	print(a, 9);	
	return 0;
}
