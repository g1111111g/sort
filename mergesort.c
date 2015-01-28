#include<stdlib.h>
#include<stdio.h>
int a[8] = {8,7,6,5,4,3,2,1};
int b[8];

void MergeCompare(int sourceArr[], int tempArr[], int startIndex, int midIndex, int endIndex){	
	int i,j,k = 0,l = 0;
	for(i = startIndex,j = midIndex + 1; i <= midIndex && j <= endIndex;){
		if(sourceArr[i] <= sourceArr[j]){
			tempArr[k++] = sourceArr[i++];
		}else{
			tempArr[k++] = sourceArr[j++];
		}
	}
	if(i <= midIndex){
		for(; i <= midIndex; i++){
			tempArr[k++] = sourceArr[i];
		}
	}
	if(j <= endIndex){
		for(; j <= endIndex; j++){
			tempArr[k++] = sourceArr[j];
		}
	}
	for(k = 0, i = startIndex; i <= endIndex; i++, k++){
		sourceArr[i] = tempArr[k];
	}
	/*
	int i = startIndex;
	int j = midIndex + 1;
	int k = 0;
	while(i <= midIndex && j <= endIndex){
		if(sourceArr[i] <= sourceArr[j]){
			tempArr[k++] = sourceArr[i++];
		}else{
			tempArr[k++] = sourceArr[j++];
		}
	}
	while(i <= midIndex){
		tempArr[k++] = sourceArr[i++];
	}
	while(j <= endIndex){
		tempArr[k++] = sourceArr[j++];
	}
	for(k = 0,i = startIndex; i <= endIndex; i++,k++){
		sourceArr[i] = tempArr[k];
	}
	*/
}

void Merge(int sourceArr[], int tempArr[], int startIndex, int endIndex){
	int midIndex,i;
	if(startIndex < endIndex){	
		midIndex = (startIndex + endIndex)/2;
		Merge(sourceArr, tempArr, startIndex, midIndex);
		Merge(sourceArr, tempArr, midIndex + 1, endIndex);
		MergeCompare(sourceArr, tempArr, startIndex, midIndex, endIndex);
		for(i = 0; i < 8; i++){
			printf("%2d", a[i]);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]){
	int i;
	Merge(a, b, 0, 7);
	for(i = 0; i < 8; i++){
		printf("%2d", a[i]);
	}
	printf("\n");
	return 0;
}


