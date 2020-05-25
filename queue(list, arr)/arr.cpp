#include "arr.h"
#include <iostream>
using namespace std;

Queue::Queue(){
	front=0; 
	rear=MAXLENGTH-1;
	cout<<"Array version"<<endl;
	system("pause");
}

int Queue::Empty(void){
	return (rear+1)%MAXLENGTH == front;
}

int Queue::Full(void){
	return (rear+2)%MAXLENGTH == front;
}

int Queue::EnQueue(int c, int d){
	if(Full()) return 0;
	rear = (rear+1)%MAXLENGTH;
	data[rear].coef = c;
	data[rear].deg = d;
	return 1;
}

DataType Queue::DeQueue(void){
	int temp = front;
	front = (front+1)%MAXLENGTH;
	return data[temp];
}
