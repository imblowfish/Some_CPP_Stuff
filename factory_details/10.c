#include <stdio.h>
#include <stdlib.h>
#define INF 9999														//значение бесконечности для поиска минимального(чтобы было с чем сравнивать)

/*Прототипы функций*/
int** arrFromFile(char filename[], int *num);						//инициализация матрицы значениями из файла
void findMin(int **arr, int num, int *label, int *m_i, int *m_j);	//для поиска минимального элемента в матрице
int** freeArr(int **arr, int num);									//очистка выделенной динамически памяти под матрицу
void Johnson(int **arr, int num);									//решение задачи Джонсона
void printArr(int **arr, int num);									//вывод матрицы
void showGrant(int **arr,int *path, int num);						//вывод графика Гранта
void showTime(int **arr, int *path, int num);						//вывод времени отработки

int main(){
	int n;
	int **arr;
	arr = arrFromFile("file.txt", &n);
	if(arr == NULL){
		system("pause");
		return 0;
	}
	printArr(arr, n);													//выводим массив на экран
	Johnson(arr, n);													//решаем задачу Джонсона
	arr = freeArr(arr, n);
	system("pause");
	return 0;
}

int** arrFromFile(char filename[], int *num){
	int **arr;															//двумерный указатель для дальнейшего резервирования памяти
	FILE *f;															//указатель на файл
	f = fopen(filename, "r");											//открываем файл для чтения
	if(f == NULL) {														//если указатель равен NULL, то файла нет, ошибка
		printf("error: file not found\n");
		return NULL;	
	}
	fscanf(f, "%d", num);												//считываем кол-во деталей из файла
	arr = (int**)malloc(sizeof(int*)*(*num));							//резервируем память под строки
	int i=0;
	for(i=0;i<*num;i++){
		arr[i] = (int*)malloc(sizeof(int)*2);							//резервируем память под 2 столбца
		fscanf(f, "%d", &arr[i][0]);									//считываем значения из файла
		fscanf(f, "%d", &arr[i][1]);
	}
	fclose(f);															//закрываем файл
	return arr;															//возвращаем указатель
}

void findMin(int **arr, int num, int *label, int *m_i, int *m_j){
	int i,j;
	int min = INF;														//присваиваем минимальному элементу значение бесконечности(в нашем случае 9999)
	for(i=0;i<num;i++){
		for(j=0;j<2;j++){
			if(arr[i][j] < min && *(label+i) == 0){						//если нашли в матрице элемент меньше нынешнего min и еще не записывали данную вершину
				min = arr[i][j]; *m_i = i; *m_j = j;					//присваиваем новое значение min, запоминаем индексы строки и столбца
			}
		}
	}
	if(min!=INF) *(label+*m_i) = 1;										//если нашли новый min, то отмечаем, что посетили данную вершину
}

int** freeArr(int **arr, int num){
	int i;
	for(i=0;i<num;i++) free(arr[i]);									//очищаем столбцы
	free(arr);															//очищаем строки
	arr=NULL;															//обнуляем
	return arr;															//возвращаем
}

void Johnson(int **arr, int num){
	int i,j;
	int label[num];														//массив меток пути(при проверке min, сверяемся, были ли мы в вершине, и если 1, то были, 0 -не были)
	int path[num];														//массив пути
	for(i=0;i<num;i++) label[i] = 0;									//обнуляем массивы
	for(i=0;i<num;i++)path[i] = 0;
	int m_i=0,m_j=0,minidx=0, maxidx=num;								//m_i, m_j - индексы min элемента; minidx и maxidx нужны для заполнения пути
	for(i=0;i<num;i++){													
		findMin(arr, num, label, &m_i, &m_j);							//поиск минимального
		if(m_j == 0){													//если min находится в 1 станке...
			printf("detail %d = %d %d deleted on %d step(begin)\n", m_i+1, arr[m_i][0], arr[m_i][1], i+1);
			path[minidx] = m_i;											//...добавляем в начало
			minidx++;													//увеличиваем индекс начала пути на 1
		}else{															//если же min на 2 станке
			printf("detail %d = %d %d deleted on %d step(end)\n", m_i+1, arr[m_i][0], arr[m_i][1], i+1);
			path[maxidx-1] = m_i;										//помещаем в конец
			maxidx--;													//уменьшаем индекс конца на 1
		}
	}
	printf("\n");
	printf("path = ");
	for(i=0;i<num;i++) printf("%2d",path[i]+1);							//отображаем найденный путь на экран
	printf("\n");		
	showGrant(arr, path, num);											//выводим график Гранта
	showTime(arr, path, num);											//выводим время отработки
}

void printArr(int **arr, int num){
	int i;																//просто красивенький вывод матрицы
	printf("-------------------------------------------------\n");
	printf("|\tdetail num|\tmachine1|\tmachine2|\n");
	printf("-------------------------------------------------\n");
	for(i=0;i<num;i++){
		printf("|\t%10d|\t%8d|\t%8d|\n", i+1, arr[i][0], arr[i][1]);
	}
	printf("-------------------------------------------------\n");
}

void showGrant(int **arr,int *path, int num){
	int i,j;											
	printf("machine1: ");												//выводим для 1 станка
	for(i=0;i<num;i++){													//внешний цикл, чтобы обойти весь путь
		for(j=0;j<arr[*(path+i)][0];j++){								//пока значение по индексу пути не достигнуто
			printf("%d", *(path+i)+1);									//Выводим значение с 1 станка
		}
		printf(" ");
	}	
	printf("\n");
	printf("machine2: ");												//тоже самое для 2-го
	for(i=0;i<num;i++){
		for(j=0;j<arr[*(path+i)][1];j++){
			printf("%d", *(path+i)+1);
		}
		printf(" ");
	}	
	printf("\n");
}

void showTime(int **arr, int *path, int num){
	int i;
	int sum=0;
	for(i=0;i<num;i++){													//просто суммируем
		sum+=arr[*(path+i)][0];											//перемещаясь по значениям пути
	}
	printf("Work Time = %d\n", sum);
}


