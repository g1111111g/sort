#include<stdio.h>
#include<stdlib.h>

#define MAX 8

int queen[MAX];
int count;

int checkCanPutQueen(int n){
	int i;
	for(i = 0; i < n; i++){
		if(queen[i] == queen[n]
			|| abs(queen[i] - queen[n]) == (n - i)){
			return 1;
		}
	}
	return 0;
}

void putQueen(int n){
	int i;
	for(i = 0; i < MAX; i++){
		queen[n] = i;
		if(!checkCanPutQueen(n)){
			if(n == MAX - 1){
				count++;
			}else{
				putQueen(n + 1);
			}
		}
	}
}

int main(int argv, char *args[]){
	putQueen(0);
	printf("%d\n", count);
	return 0;
}
