struct num{
	int coef, deg;
};

typedef num DataType;

class Queue{
	
	struct element{
		DataType data;
		element *next;
	}*front,*rear;
	public:
		Queue();
		~Queue();
		int EnQueue(int c, int d);
		DataType DeQueue(void);
		int Full(void);
		int Empty(void);
};
