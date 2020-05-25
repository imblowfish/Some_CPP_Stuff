#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Прототипы функций*/
int** arrToString(char **str, int num, char *str2);				//динамическое добавление строки в двумерный массив строк
int strcmp_my(char *str1, char *str2);							//реализация функции сравнения строк
void printArr(int **arr, int num);								//вывод строк
void sorting(char **arr, int num);								//сортировка по алфавиту(за основу была взята самая легкая пузырьковая. сложность алгоритма O(n^2)

int main(){
	char **arr=NULL, str[50];
	int n=0,i=0;
	do{
		system("CLS");
		printArr(arr, n);								//выводим, если ничего нет, то просто выйдет из функции
		printf("input strings:");					
		gets(str);										//считываем строку с клавиатуры
		if(str[0] != '\0') {							//если строка не пустая
			n++;										//увеличиваем число строк
			arr = arrToString(arr, n, str);			//записываем строку в массив
		}
	}while(str[0]!='\0');
	system("CLS");
	printf("before sorting\n");							
	printArr(arr, n);									//выводим строки до сортировки
	printf("after sotring\n");
	sorting(arr,n);										//сортируем
	printArr(arr, n);									//и после
	if(arr!=NULL){										//очистка памяти
		for(i=0;i<n;i++)free(arr[i]);
		free(arr);
		arr=NULL;
	}
	system("pause");
	return 0;
}

int** arrToString(char **str, int num, char *str2){
	int i,j,k;
	char **savestr=NULL;										//двумерный указатель для записи значения массива строк
	if(num != 1){
		savestr = (char**)malloc(sizeof(char*)*num-1);			//резервируем память под строку
		if(savestr == NULL){									//выполняем провеку, что память была зарезервирована
			printf("memory error\n");
			system("pause");
			return NULL;
		}
		for(i=0;i<num-1;i++){									//резервируем память под столбцы(символы)
			savestr[i] = (char*)malloc(sizeof(char)*(strlen(str[i])+1));
			if(savestr[i] == NULL){								//снова проверка
				for(j=0;j<i;j++)free(savestr[j]);				//если не была зарезервирована память, очищаем память под предыдущие зарезервированные элементы
				free(savestr);
				savestr=NULL;
				printf("memory error\n");
				system("pause");
				return NULL;
			}
			strcpy(savestr[i],str[i]);							//копируем значение из нашей строки в строку сохранения
		}
	}
	if(str!=NULL){												//если в строке есть значения
		for(i=0;i<num-1;i++) free(str[i]);						//освобождаем столбцы
		free(str);												//освобождаем строки
		str=NULL;												//обнуляем
	}
	str = (char**)malloc(sizeof(char*)*num);					//резервируем память
	if(str == NULL){											//проверка
		printf("memory error\n");
		system("pause");
		return NULL;
	}
	if(savestr!=NULL){											//если есть запись в массиве сохранения, переписываем оттуда в нашу строку
		for(i=0;i<num-1;i++) {				
			str[i] = (char*)malloc(sizeof(char)*(strlen(savestr[i])+1));
			if(str[i] == NULL){
				for(j=0;j<i;j++) free(str[j]);
				free(str);
				str=NULL;
				for(i=0;i<num-1;i++) free(savestr[i]);
				printf("memory error\n");
				system("pause");
				return NULL;
			}
			strcpy(str[i],savestr[i]);
		}
		for(i=0;i<num-1;i++) free(savestr[i]);					//освобождаем
		free(savestr);
		savestr=NULL;
	}
	str[num-1] = (char*)malloc(sizeof(char)*(strlen(str2)+1));	//резервируем память под новую строку
	if(str[num-1] == NULL){											//проверка
		for(i=0;i<num-1;i++)free(str[i]);
		free(str);
		str=NULL;
		printf("memory error\n");
		system("pause");
		return NULL;
	}
	strcpy(str[num-1], str2);									//записываем
	return str;													//возвращаем
}

int strcmp_my(char *str1, char *str2){
	int i,j;
	for(i=0;i<strlen(str1)+1,i<strlen(str2)+1;i++){				//идем, пока i меньше длины строки 1 и длины строки 2
		if(str1[i] > str2[i]) return 1;							//если символ строки 1 > символа строки 2 возвращаем 1(строка 1 больше строки 2)
		else if(str1[i] < str2[i]) return -1;					//наоборот
	}
	if(strlen(str1) == strlen(str2)) return 0;					//если до этого все символы совпали, сравниваем длину строк, если схожи, то они равны
	else if(strlen(str1)>strlen(str2)) return 1;				//если строка 1 больше возвращаем 1
	else return -1;												//наоборот
}

void sorting(char **arr, int num){
	int i,j,k;
	for(i=0;i<num-1;i++){
		for(j=0;j<num-i-1;j++){									//начинаем сортировку
			if(strcmp_my(arr[j], arr[j+1])==1){					//если нынешний больше следующего, должны перенести на 1 вперед
				char *save=(char*)malloc(sizeof(char)*(strlen(arr[j+1])+1));//сохраняем строку перед заменой, предварительно выделив память
				if(save==NULL){												//проверка
					printf("memory error\n");
					return;
				}
				strcpy(save, arr[j+1]);										//копируем в сохранение следующий элемент
				free(arr[j+1]);												//освобождаем
				arr[j+1] = NULL;
				arr[j+1] = (char*)malloc(sizeof(char)*(strlen(arr[j])+1));	//резервируем память следующему элементу размером равную текущему элементу
				if(arr[j+1] == NULL){
					printf("memory error\n");
					return;
				}
				strcpy(arr[j+1],arr[j]);									//копируем
				free(arr[j]);
				arr[j] = NULL;
				arr[j] = (char*)malloc(sizeof(char)*(strlen(save)+1));		//резервируем память под текущий элемент
				if(arr[j+1] == NULL){
					printf("memory error\n");
					return;
				}
				strcpy(arr[j], save);										//копируем
				free(save);
				save=NULL;
			}
		}
	}																		//продолжаем, пока не закончим проверку массива
}

void printArr(int **arr, int num){
	int i;
	if(arr == NULL) return;													//просто вывод строк
	printf("num|\tvalue\n");
	printf("--------------\n");
	for(i=0;i<num;i++) printf("%3d| %s\n",i+1,arr[i]);
	printf("--------------\n");
}


