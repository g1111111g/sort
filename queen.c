#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#define MAX 4 
int queen[MAX], sum = 0;
int num[] = {1,2,3,4};
int count = 0;
void show(){
	int i;
	for(i = 0; i < MAX; i++){
		printf("(%d %d)", i, queen[i]);
	//	printf("(%d)", num[queen[i]]);
	}
	printf("\n");
	sum++;
}

int checkCanPutQueen(int n){/*检查当前竖排和对角线是否能放皇后*/
	int i;
	for(i = 0; i < n; i++){
		if(queen[i] == queen[n] || abs(queen[i] - queen[n]) == (n - i)){
			return 1;/*不能放*/
		}
	}
	return 0;/*可以放*/
}

void put(int n){/*尝试在x坐标为n时放置皇后*/
	int i;
	for(i = 0; i < MAX; i++){
		queen[n] = i;/*n值为x坐标 queen[n]值为y坐标*/
		if(!checkCanPutQueen(n)){
			printf("[%d %d]\n", n, i);
			if(n == MAX - 1){
				show();
			}else{
				printf("resursion\n");
				put(n + 1);
				printf("back up\n");
			}
		}else{
			printf("<<<%d %d>>>\n", n, i);
		}
	}

	count++;
}
int main(int argv, char *args[]){
	int a = clock();
	put(0);
	int b = clock();
	printf("run time:%d\n",b-a);
	printf("%d\n",sum);
	return 0;
}
