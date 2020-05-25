#include <iostream>
#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#include <cmath>
using namespace std;

void print(int **el, int n, int vol);			//вывод введенных значений
void printVal(int val, int p);					//вывод перевод в двоичную системы счисления
void printAllCombin(int p, int n);				//вывод всех комбинаций из n элементов(их 2^n)

int main(){
	int n, p,**el, vol, best=-1, 				/*n - число эл-от, p-2^n, el-массив элементов с ценами и весами, vol - объем рюкзака, best - лучшая комбинация*/
		i, j, bc=0, sumw=999, sumc=0;			/*bc - лучшая цена, sumw - сумма весов, sumc - сумма цен*/
	printf("input num of elements\n");
	scanf("%d", &n);
	printf("input vol of knap\n");
	scanf("%d", &vol);
	p=2<<(n-1);									//возводим 2 в степень n
	el = (int**)malloc(sizeof(int*)*n);	
	for(i=0;i<n;i=-~i) {						//-~i битовый аналог i++
		el[i] = (int*)malloc(sizeof(int)*2);
		printf("input weight of element %d=",i+1);
		scanf("%d",&el[i][0]);
		printf("input cost of element %d=", i+1);
		scanf("%d",&el[i][1]);
		printf("\n");
	}
	system("CLS");
	print(el, n, vol);							//выводим всю введенную информацию
	for(i=0;i<p;i=-~i){
		for(j=0;j<n;j=-~j){
			if(i & (1<<j)) {					//проверка j-го бита в i - равен ли он единице
				sumw+=el[j][0]; sumc+=el[j][1]; //если равен, записыаем значения из элемента j в суммы
			}	
		}
		if(sumw<=vol && sumc>bc) {				//если сумма весов меньше макс веса рюкака(объема) и сумма цен больше лучшей цены
			bc = sumc; 							//записываем цену
			best=i;								//записываем комбинацию в виде десятичного числа, потом переведем
		}
		sumw = 0;	
		sumc = 0;	
	}
	printf("ALL COMBINATION\n");				//выводим все комбинации из n элементов(можно закомментировать, если слишком много не поместятся)
	printAllCombin(p, n);						
	if((best^(-1)) == 0) printf("can't find best\n");//битовая операция сравнения чисел, если не нашли решения(b == -1), то выводим, что решения нет
	else {
		printf("best combination\n");  printVal(best,n);//иначе выводим лучшую комбинацию в виде двоичного числа
		printf("\nbest const = %d\n",bc);				//и лучшую цену
	}
	for(i=0;i<n;i++) free(el[i]);						//освобождаем память
	free(el);
	system("pause");
	return 0;
}

void print(int **el, int n, int vol){
	system("CLS");
	printf("| num | weight | cost |\n");
	printf("-----------------------\n");
	for(int i=0;i<n;i++)printf("|%5d|%8d|%6d|\n", i+1, el[i][0], el[i][1]);
	printf("-----------------------\n");
	printf("numOfEl = %d\nvolOfKnap=%d\n",n,vol);
}

void printVal(int val, int p){
	int j;
	for(j=p;j>0;j=~-j) printf("|%d|",j);
	printf("\n");
	for(j=p;j>0;j=~-j) printf("|%d|",(val >> (j-1)) & 1);		//(val >> (j-1)) & 1) значение j-го бита в val(справа налево)	
	printf("\n");
}

void printAllCombin(int p, int n){
	int i;
	for(i = 0; i < p; i++) {
		printVal(i, n);
		printf("\n");	
	}
}

