#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

int isfind = 0;

struct statck{
	int x;
	int y;
}s[100];
int stackpos = 0;
int migong[][10] = 
	{
		{0,1,0,0,0,0,0,0,1,0},
		{0,1,0,1,0,0,1,0,1,0},
		{0,1,0,1,0,0,1,0,1,0},
		{0,1,0,1,1,0,1,0,1,0},
		{0,1,0,0,1,0,1,0,0,0},
		{0,1,0,0,1,0,1,0,0,0},
		{0,1,0,0,1,1,1,0,1,0},
		{0,1,0,0,0,0,0,0,1,0},
		{0,1,1,1,1,1,1,0,1,0},
		{0,0,0,0,0,0,0,0,1,0},
	};

int MAX_Y = sizeof(migong)/sizeof(migong[0]);
int MAX_X = sizeof(migong[0])/sizeof(int);

void print(){
	int i,j;
	for(i = 0; i < MAX_Y; i++){
		for(j = 0; j < MAX_X; j++){
			printf("%3d",migong[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void printStack(){
	int i,j,sx,sy;
	for(i = 0; i < MAX_Y; i++){
		for(j = 0; j < MAX_X; j++){
			if(migong[i][j]==3){
				migong[i][j] = 0;
			}
		}
	}
	sx = s[0].x;
	sy = s[0].y;
	for(i = 0; i < stackpos; i++){
		printf("(%d %d)", s[i].x, s[i].y);
		if(s[i].x > sx){
			printf("下");
		}else if(s[i].x < sx){
			printf("上");
		}else if(s[i].y > sy){
			printf("右");
		}else{
			printf("左");
		}
		sx = s[i].x;
		sy = s[i].y;
		migong[s[i].x][s[i].y] = 2;
	}
	printf("\n");
	print();
}

/**
 */
int checkCanGo(int x,int y){
	if(x < 0 || y < 0 || x >= MAX_X || y >= MAX_Y || migong[x][y] == 1 || migong[x][y] == 3){
		return 0;
	}
	return 1;
}

void find(int i,int j){
	int a,x,y;
	if(isfind){
		return;
	}
	for(a = 0; a < 4; a++){
		if(a == 0){
			x = i;
			y = j + 1;
		}else if(a == 1){
			x = i - 1;
			y = j;		
		}else if(a == 2){
			x = i;
			y = j - 1;
		}else if(a == 3){
			x = i + 1;
			y = j;	
		}
		if(checkCanGo(x, y)){
			migong[x][y] = 1;
			s[stackpos].x = x;
			s[stackpos].y = y;
			stackpos++;
			if(x == 9 && y == 9){
				isfind = 1;
				printStack();
				return;
			}else{
				find(x, y);	
				migong[x][y] = 3; //着色说明已经走过并且此路不通
				stackpos--;
			}
		}
	}
}

int main(){
	find(0, 0);
	return 0;	
}
