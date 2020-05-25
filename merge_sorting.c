#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Прототипы функций*/
void insert(int *arr, int min, int max);										//сортировка вставками
void merge(int *arr, int n, int min, int max);									//рекурсивная функция сортировки слиянием
void printArr(int *arr, int n);													//вывод массива
char checkArr(int *arr, int n);													//проверка правильности сортировки

int main(){
	int *arr, n,i;
	printf("please, input num of elements\n");
	scanf("%d", &n);
	system("CLS");
	srand(time(NULL));
	arr = (int*)malloc(sizeof(int)*n);
	for(i=0;i<n;i++) arr[i] = rand()%100;
	printf("--------------\n");
	printf("before sorting\n");
	printf("--------------\n");
	printArr(arr, n);
	merge(arr, n, 0, n-1);
	printf("--------------\n");
	printf("after sorting\n");
	printf("--------------\n");
	printArr(arr, n);
	printf("--------------\n");
	if(checkArr(arr,n) == 0) printf("!!!error sorting!!!\n");
	else printf("***right sorting***\n");
	system("pause");
	return 0;
}

void insert(int *arr, int min, int max){
	int save;
	int i,j;
	for(i=min;i<=max;i++){
		save = arr[i];
		for(j=i-1;j>=0 && arr[j] > save;j--){
			arr[j+1] = arr[j];
		}
		arr[j+1] = save;
	}	
}

void merge(int *arr, int n, int min, int max){
	if(max-min<5) {
		insert(arr,min,max);
		return;
	}
	if(max <= min) return;
	int middle = min + (max-min)/2;
	merge(arr, n, min, middle);
	merge(arr, n, middle+1,max);
	int i,j,k;
	int *buf = (int*)malloc(sizeof(int)*n);
	//for(i=0;i<n;i++) buf[i] = a[i];
	for(i=min;i<=max;i++) buf[i] = arr[i];		
	i=min, j = middle+1;
	for(k=min;k<=max;k++){
		if(i>middle){
			arr[k] = buf[j];
			j++;
		}else if(j>max){
			arr[k] = buf[i];
			i++;
		}else if(buf[j]<buf[i]){
			arr[k] = buf[j];
			j++;
		}else{
			arr[k] = buf[i];
			i++;
		}
	}
}

void printArr(int *arr, int n){
	int i;
	for(i=0;i<n;i++) printf("%4d", arr[i]);
	printf("\n");
}

char checkArr(int *arr, int n){
	int i;
	for(i=0;i<n-1;i++) if(arr[i]>arr[i+1]) return 0;
	return 1;
}

