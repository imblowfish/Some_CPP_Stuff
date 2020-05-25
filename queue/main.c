#include <stdio.h>
#include "Queue.c"

int main(int argc, char *argv[]) {
	int n=1;
	qArr q=NULL;
	char str[50];
	do{
		printf("%3d\t",n);
		gets(str);
		printf("\n");
		q = addToQueue(q, str, n++);
	}while(str[0]!='\0');
	ShowQArr(q);
	q = freeQArr(q);
	system("pause");
	return 0;
}
