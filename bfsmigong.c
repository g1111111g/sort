/**
 * 
 * 广度优先搜索 A*
 * 迷宫寻路
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

#define MAX_QUEUE_SIZE 10

#define MAX_WIDTH 42
#define MAX_HEIGHT 40

int isfind = 0;

typedef struct node{
	int x;
	int y;
	struct node *next;
	struct node *parent;
}Node;

typedef struct queue{
	Node *head;
	Node *tail;
}Queue;

Node *queueList = NULL;

void initQueue(Queue *queue){
	queue->head = NULL;
	queue->tail = NULL;
}

int isempty(Queue *queue){
	return queue->tail == NULL;
}

Node *pop(Queue *queue){
	Node *node;
	node = queue->head;
	if(node != NULL){
		queue->head = node->next;
		if(queue->head == NULL){
			queue->tail = NULL;
		}
	}
	return node;
}

void push(Queue *queue, Node *node){
	node->next = NULL;
	if(queue->tail == NULL){
		queue->head = node;
		//node->parent = NULL;
	}else{
		queue->tail->next = node;
	}
	queue->tail = node;
}

Node *newNode(void){
	Node *node = NULL;
	if(queueList){
		node = queueList;
		queueList = node->next;
	}
	if(node == NULL){
		int i;
		node = (Node *)malloc(sizeof(Node) * MAX_QUEUE_SIZE);
		if(node == NULL){
			perror("malloc");
		}
		for(i = 2; i < MAX_QUEUE_SIZE; i++){
			node[i - 1].next = &node[i];
			node[i - 1].parent = &node[i - 2]; 
		}
		node[MAX_QUEUE_SIZE - 1].next = queueList;//环形链表
		queueList = &node[1];
	}
	return node;
}

void freeNode(Node *node){
	node->next = queueList;
	queueList = node;
}

int migong[MAX_WIDTH][MAX_HEIGHT] = 
	{
		{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,0},
		{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,1,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,1,0},
		{0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,0},


	};

char map[MAX_WIDTH][MAX_HEIGHT];
int visited[MAX_WIDTH][MAX_HEIGHT];
int direct[8][2] = {{1,0},{-1,0},{0,-1},{0,1},{1,1},{-1,-1},{1,-1},{-1,1}};
//int direct[4][2] = {{1,0},{-1,0},{0,-1},{0,1}};

void print(){
	int i,j;
	for(i = 0; i < MAX_WIDTH; i++){
		for(j = 0; j < MAX_HEIGHT; j++){
			printf("%3d",migong[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void printascii(){
	memset(map, '+', sizeof(map));
	int i,j;
	for(i = 0; i < MAX_WIDTH; i++){
		for(j = 0; j < MAX_HEIGHT; j++){
			if(migong[i][j] == 1){
				map[i][j] = '|';
			}
			if(migong[i][j] == 2){
				map[i][j] = '0';
			}
			printf("%3c",map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
int main(){
	/*
	Node *node1 = newNode();	
	node1->x = 1;
	node1->y = 1;

	Queue *queue = (Queue *)malloc(sizeof(Queue));
	push(queue, node1);
	Node *node2 = newNode();
	node2->x = 2;
	node2->y = 2;
	push(queue, node2);

	Node *getNode1 = pop(queue);
	Node *getNode2 = pop(queue);
	if(getNode2->parent != NULL){
		printf("%d %d\n", getNode2->parent->x, getNode2->parent->y);
	}else{
		fprintf(stderr,"queue is empty\n");
	}
	printf("%d\n", isempty(queue));
	*/
	Queue *queue = (Queue *)malloc(sizeof(Queue));
	if(!isempty(queue)){
		pop(queue);
	}
	Node *node = newNode();
	node->x = 0;
	node->y = 0;
	push(queue, node);
	int i;
	while(!isempty(queue)){
		Node *firstNode = pop(queue);
		if(firstNode->x == MAX_WIDTH - 1 && firstNode->y == MAX_HEIGHT - 1){
			printf("find it\n");
			migong[firstNode->x][firstNode->y] = 2;
			while(firstNode->parent != NULL){
				printf("%d %d\n", firstNode->parent->x, firstNode->parent->y);
				migong[firstNode->parent->x][firstNode->parent->y] = 2;
				firstNode = firstNode->parent;
			}
			print();
			printascii();
		}
		for(i = 0; i < 8; i++){
			Node *inNode = newNode();
			inNode->x = firstNode->x + direct[i][0];
			inNode->y = firstNode->y + direct[i][1];
			if(inNode->x >= 0 && 
				inNode->y >= 0 && 
					visited[inNode->x][inNode->y] == 0 && 
						migong[inNode->x][inNode->y] == 0 && 
							inNode->x < MAX_WIDTH && 
								inNode->y < MAX_HEIGHT){
				visited[inNode->x][inNode->y] = 1;
				inNode->parent = firstNode;
				push(queue, inNode);
			}
	//		free(inNode);
		}
	}
	free(queue);
	free(node);
	return 0;	
}
