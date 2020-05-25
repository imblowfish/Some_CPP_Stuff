#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "Queue.h"

Queue Push(Queue q, char *val){
	if(q->head == NULL){
		q->head = (Node*) malloc (sizeof(Node));
		q->head->val = (char*)malloc(sizeof(char)*(strlen(val)+1));
		strcpy(q->head->val, val);
		q->tail = q->head;
		q->head->next = NULL;
	}else{
		q->tail->next = (Node*) malloc (sizeof(Node));
		q->tail->next->val = (char*)malloc(sizeof(char)*(strlen(val)+1));
		strcpy(q->tail->next->val, val);
		q->tail = q->tail->next;
		q->tail->next = NULL;
	}
	return q;
}

char* Pop(Queue q){
	if(q->head!=NULL){
		char *save = q->head->val;
		Node* temp=q->head;
		q->head = q->head->next;
		free(temp);
		return save;
	}else{
		printf("Queue is empty\n");
		return NULL;
	}
	
}

void Show(Queue q){
	if(!q->head) {
		printf("Queue is empty\n");
		return;
	}
	Node* temp;
	temp = q->head;
	while(q->head){
		printf("%s\n",q->head->val);
		q->head = q->head->next;
	}	
	q->head = temp;
	return;
}

Queue Init(Queue q){
	q = (Queue*)malloc(sizeof(Queue));
	q->head = q->tail = NULL;
	return q;
}

Queue Clear(Queue q){
	if(!q->head) {
		printf("Queue is empty\n");
		return;
	}
	if(!q->head->next) free(q->head);
	else{
		while(q->head){
			Node* temp = q->head;
			q->head = q->head->next;
			free(temp);
		}
	}
	free(q);
	q = NULL;
	return q;
}

qArr addToQueue(qArr q, char *val, int n){
	if(!q){
		q = (qArr*)malloc(sizeof(qArr));
		q->evenQ = Init(q->evenQ);
		q->oddQ = Init(q->oddQ);	
	}
	if(n%2==0) q->evenQ = Push(q->evenQ, val);
	else q->oddQ = Push(q->oddQ, val);
}

qArr freeQArr(qArr q){
	q->evenQ = Clear(q->evenQ);
	q->oddQ = Clear(q->oddQ);
	free(q);
	return q;
}

void ShowQArr(qArr q){
	printf("-----------\n");
	printf("even queue:\n");
	printf("-----------\n");
	Show(q->evenQ);
	printf("-----------\n");
	printf("odd queue:\n");
	printf("-----------\n");
	Show(q->oddQ);
	printf("-----------\n");
}
