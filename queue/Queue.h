struct node{
	char *val;
	struct node *next;
};
typedef struct node Node;

struct queue{
	Node *head;
	Node *tail;
};
typedef struct queue *Queue;

Queue Push(Queue q, char *val);
char* Pop(Queue q);
void Show(Queue q);
Queue Init(Queue q);
Queue Clear(Queue q);

struct qarr{
	Queue oddQ;																		//очередь для нечетных
	Queue evenQ;																	//очередь для четных 
};
typedef struct qarr *qArr;


qArr addToQueue(qArr q, char *val, int n);
qArr freeQArr(qArr q);
void ShowQArr(qArr q);


