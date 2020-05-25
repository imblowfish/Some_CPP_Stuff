#define MAXLENGTH 100
struct num{
	int coef;
	int deg;
};

typedef num DataType;

class Queue{
	int front, rear;
	DataType data[MAXLENGTH];
public:
	Queue();
	int Empty(void);
	int Full(void);
	int EnQueue(int c, int d);
	DataType DeQueue(void);
};
