#include <cstdlib>
#include <iostream>
#include "list.h"
using namespace std;

Queue::Queue(){
	front = rear = NULL; 
	cout<<"List version"<<endl;
	system("pause");
}

int Queue::EnQueue(int c, int d){
	if(Full()) return 0;
	element *temp = new element;
	temp->data.coef = c;
	temp->data.deg = d;
	temp->next = NULL;
	if(front == NULL){
		front = rear = temp;
	}else{
		rear->next = temp;
		rear = rear->next;
	}
	getchar();
	return 1;
}

int Queue::Full(){
	element *temp = new element;
	if(temp == NULL) return 1;
	delete temp;
	return 0;
}

DataType Queue::DeQueue(void){
	DataType temp = front->data;
	element *tmp = front;
	front = front->next;
	delete tmp;
	return temp;	
}

int Queue::Empty(){
	return front == NULL;
}

Queue::~Queue(){
   element * temp = front;
   while (front)
   {
         temp = front;
         front = front->next;
         delete temp;
   }
}
