#include<stdio.h>
#include<stdlib.h>
#include "tool.h"

struct A{
	int a;
	int b;
	int c[5];
}aa[2];
int main(int argc,char *argv[]){
	int i;
	int a[] = {1,2,3,4};
	PrintIntArray(a, 4);	
	printf("%d\n", argc);
	for(i = 0; i < argc; i++){
		printf("%s %d\n", argv[i], sizeof(struct A));
	}
	exit(0);
}
