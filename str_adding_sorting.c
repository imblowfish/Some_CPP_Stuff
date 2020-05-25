#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*��������� �������*/
int** arrToString(char **str, int num, char *str2);				//������������ ���������� ������ � ��������� ������ �����
int strcmp_my(char *str1, char *str2);							//���������� ������� ��������� �����
void printArr(int **arr, int num);								//����� �����
void sorting(char **arr, int num);								//���������� �� ��������(�� ������ ���� ����� ����� ������ �����������. ��������� ��������� O(n^2)

int main(){
	char **arr=NULL, str[50];
	int n=0,i=0;
	do{
		system("CLS");
		printArr(arr, n);								//�������, ���� ������ ���, �� ������ ������ �� �������
		printf("input strings:");					
		gets(str);										//��������� ������ � ����������
		if(str[0] != '\0') {							//���� ������ �� ������
			n++;										//����������� ����� �����
			arr = arrToString(arr, n, str);			//���������� ������ � ������
		}
	}while(str[0]!='\0');
	system("CLS");
	printf("before sorting\n");							
	printArr(arr, n);									//������� ������ �� ����������
	printf("after sotring\n");
	sorting(arr,n);										//���������
	printArr(arr, n);									//� �����
	if(arr!=NULL){										//������� ������
		for(i=0;i<n;i++)free(arr[i]);
		free(arr);
		arr=NULL;
	}
	system("pause");
	return 0;
}

int** arrToString(char **str, int num, char *str2){
	int i,j,k;
	char **savestr=NULL;										//��������� ��������� ��� ������ �������� ������� �����
	if(num != 1){
		savestr = (char**)malloc(sizeof(char*)*num-1);			//����������� ������ ��� ������
		if(savestr == NULL){									//��������� �������, ��� ������ ���� ���������������
			printf("memory error\n");
			system("pause");
			return NULL;
		}
		for(i=0;i<num-1;i++){									//����������� ������ ��� �������(�������)
			savestr[i] = (char*)malloc(sizeof(char)*(strlen(str[i])+1));
			if(savestr[i] == NULL){								//����� ��������
				for(j=0;j<i;j++)free(savestr[j]);				//���� �� ���� ��������������� ������, ������� ������ ��� ���������� ����������������� ��������
				free(savestr);
				savestr=NULL;
				printf("memory error\n");
				system("pause");
				return NULL;
			}
			strcpy(savestr[i],str[i]);							//�������� �������� �� ����� ������ � ������ ����������
		}
	}
	if(str!=NULL){												//���� � ������ ���� ��������
		for(i=0;i<num-1;i++) free(str[i]);						//����������� �������
		free(str);												//����������� ������
		str=NULL;												//��������
	}
	str = (char**)malloc(sizeof(char*)*num);					//����������� ������
	if(str == NULL){											//��������
		printf("memory error\n");
		system("pause");
		return NULL;
	}
	if(savestr!=NULL){											//���� ���� ������ � ������� ����������, ������������ ������ � ���� ������
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
		for(i=0;i<num-1;i++) free(savestr[i]);					//�����������
		free(savestr);
		savestr=NULL;
	}
	str[num-1] = (char*)malloc(sizeof(char)*(strlen(str2)+1));	//����������� ������ ��� ����� ������
	if(str[num-1] == NULL){											//��������
		for(i=0;i<num-1;i++)free(str[i]);
		free(str);
		str=NULL;
		printf("memory error\n");
		system("pause");
		return NULL;
	}
	strcpy(str[num-1], str2);									//����������
	return str;													//����������
}

int strcmp_my(char *str1, char *str2){
	int i,j;
	for(i=0;i<strlen(str1)+1,i<strlen(str2)+1;i++){				//����, ���� i ������ ����� ������ 1 � ����� ������ 2
		if(str1[i] > str2[i]) return 1;							//���� ������ ������ 1 > ������� ������ 2 ���������� 1(������ 1 ������ ������ 2)
		else if(str1[i] < str2[i]) return -1;					//��������
	}
	if(strlen(str1) == strlen(str2)) return 0;					//���� �� ����� ��� ������� �������, ���������� ����� �����, ���� �����, �� ��� �����
	else if(strlen(str1)>strlen(str2)) return 1;				//���� ������ 1 ������ ���������� 1
	else return -1;												//��������
}

void sorting(char **arr, int num){
	int i,j,k;
	for(i=0;i<num-1;i++){
		for(j=0;j<num-i-1;j++){									//�������� ����������
			if(strcmp_my(arr[j], arr[j+1])==1){					//���� �������� ������ ����������, ������ ��������� �� 1 ������
				char *save=(char*)malloc(sizeof(char)*(strlen(arr[j+1])+1));//��������� ������ ����� �������, �������������� ������� ������
				if(save==NULL){												//��������
					printf("memory error\n");
					return;
				}
				strcpy(save, arr[j+1]);										//�������� � ���������� ��������� �������
				free(arr[j+1]);												//�����������
				arr[j+1] = NULL;
				arr[j+1] = (char*)malloc(sizeof(char)*(strlen(arr[j])+1));	//����������� ������ ���������� �������� �������� ������ �������� ��������
				if(arr[j+1] == NULL){
					printf("memory error\n");
					return;
				}
				strcpy(arr[j+1],arr[j]);									//��������
				free(arr[j]);
				arr[j] = NULL;
				arr[j] = (char*)malloc(sizeof(char)*(strlen(save)+1));		//����������� ������ ��� ������� �������
				if(arr[j+1] == NULL){
					printf("memory error\n");
					return;
				}
				strcpy(arr[j], save);										//��������
				free(save);
				save=NULL;
			}
		}
	}																		//����������, ���� �� �������� �������� �������
}

void printArr(int **arr, int num){
	int i;
	if(arr == NULL) return;													//������ ����� �����
	printf("num|\tvalue\n");
	printf("--------------\n");
	for(i=0;i<num;i++) printf("%3d| %s\n",i+1,arr[i]);
	printf("--------------\n");
}


