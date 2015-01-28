/**
 * 
 * 广度优先搜索 A*
 * 迷宫寻路
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#define MAX_QUEUE_SIZE 10
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

int migong[][10] = 
	{
		{0,0,0,0,0,0,0,0,1,0},
		{0,0,0,0,0,0,1,0,1,0},
		{0,0,0,0,0,0,1,0,1,0},
		{0,0,0,0,0,0,1,0,1,0},
		{0,0,0,0,0,0,1,1,0,0},
		{0,0,0,0,0,0,1,0,0,0},
		{0,1,0,0,0,0,1,0,0,0},
		{0,1,0,0,0,0,1,0,0,0},
		{0,1,0,0,0,1,0,0,0,0},
		{0,1,0,1,0,0,0,0,1,0},
	};
int visited[10][10];
int direct[8][2] = {{1,0},{-1,0},{0,-1},{0,1}};

void print(){
	int i,j;
	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			printf("%3d",migong[i][j]);
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
		if(firstNode->x == 9 && firstNode->y == 9){
			printf("find it\n");
			while(firstNode->parent != NULL){
				printf("%d %d\n", firstNode->parent->x, firstNode->parent->y);
				migong[firstNode->parent->x][firstNode->parent->y] = 2;
				firstNode = firstNode->parent;
			}
			print();
		}
		for(i = 0; i < 4; i++){
			Node *inNode = newNode();
			inNode->x = firstNode->x + direct[i][0];
			inNode->y = firstNode->y + direct[i][1];
			if(inNode->x >= 0 && 
				inNode->y >= 0 && 
					visited[inNode->x][inNode->y] == 0 && 
						migong[inNode->x][inNode->y] == 0){
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
