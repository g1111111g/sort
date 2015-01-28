#include<stdlib.h>
#include<stdio.h>

void move(int n, char a, char b, char c);
int main(int argc, char* argv[]){
	int n;
	printf("please input num:\n");
	while(scanf("%d", &n)){
		move(n, 'a', 'b', 'c');
	}
	return 0;
}

void move(int n, char a, char b, char c){
	if(n == 1){
		printf("%c->%c\n", a, c);
	}else{
		move(n - 1, a, c, b);
		printf("%c->%c\n", a, c);
		move(n - 1, b, a, c);
	}
}
