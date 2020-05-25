#include <stdio.h>
#include <stdlib.h>
#define INF 9999														//�������� ������������� ��� ������ ������������(����� ���� � ��� ����������)

/*��������� �������*/
int** arrFromFile(char filename[], int *num);						//������������� ������� ���������� �� �����
void findMin(int **arr, int num, int *label, int *m_i, int *m_j);	//��� ������ ������������ �������� � �������
int** freeArr(int **arr, int num);									//������� ���������� ����������� ������ ��� �������
void Johnson(int **arr, int num);									//������� ������ ��������
void printArr(int **arr, int num);									//����� �������
void showGrant(int **arr,int *path, int num);						//����� ������� ������
void showTime(int **arr, int *path, int num);						//����� ������� ���������

int main(){
	int n;
	int **arr;
	arr = arrFromFile("file.txt", &n);
	if(arr == NULL){
		system("pause");
		return 0;
	}
	printArr(arr, n);													//������� ������ �� �����
	Johnson(arr, n);													//������ ������ ��������
	arr = freeArr(arr, n);
	system("pause");
	return 0;
}

int** arrFromFile(char filename[], int *num){
	int **arr;															//��������� ��������� ��� ����������� �������������� ������
	FILE *f;															//��������� �� ����
	f = fopen(filename, "r");											//��������� ���� ��� ������
	if(f == NULL) {														//���� ��������� ����� NULL, �� ����� ���, ������
		printf("error: file not found\n");
		return NULL;	
	}
	fscanf(f, "%d", num);												//��������� ���-�� ������� �� �����
	arr = (int**)malloc(sizeof(int*)*(*num));							//����������� ������ ��� ������
	int i=0;
	for(i=0;i<*num;i++){
		arr[i] = (int*)malloc(sizeof(int)*2);							//����������� ������ ��� 2 �������
		fscanf(f, "%d", &arr[i][0]);									//��������� �������� �� �����
		fscanf(f, "%d", &arr[i][1]);
	}
	fclose(f);															//��������� ����
	return arr;															//���������� ���������
}

void findMin(int **arr, int num, int *label, int *m_i, int *m_j){
	int i,j;
	int min = INF;														//����������� ������������ �������� �������� �������������(� ����� ������ 9999)
	for(i=0;i<num;i++){
		for(j=0;j<2;j++){
			if(arr[i][j] < min && *(label+i) == 0){						//���� ����� � ������� ������� ������ ��������� min � ��� �� ���������� ������ �������
				min = arr[i][j]; *m_i = i; *m_j = j;					//����������� ����� �������� min, ���������� ������� ������ � �������
			}
		}
	}
	if(min!=INF) *(label+*m_i) = 1;										//���� ����� ����� min, �� ��������, ��� �������� ������ �������
}

int** freeArr(int **arr, int num){
	int i;
	for(i=0;i<num;i++) free(arr[i]);									//������� �������
	free(arr);															//������� ������
	arr=NULL;															//��������
	return arr;															//����������
}

void Johnson(int **arr, int num){
	int i,j;
	int label[num];														//������ ����� ����(��� �������� min, ���������, ���� �� �� � �������, � ���� 1, �� ����, 0 -�� ����)
	int path[num];														//������ ����
	for(i=0;i<num;i++) label[i] = 0;									//�������� �������
	for(i=0;i<num;i++)path[i] = 0;
	int m_i=0,m_j=0,minidx=0, maxidx=num;								//m_i, m_j - ������� min ��������; minidx � maxidx ����� ��� ���������� ����
	for(i=0;i<num;i++){													
		findMin(arr, num, label, &m_i, &m_j);							//����� ������������
		if(m_j == 0){													//���� min ��������� � 1 ������...
			printf("detail %d = %d %d deleted on %d step(begin)\n", m_i+1, arr[m_i][0], arr[m_i][1], i+1);
			path[minidx] = m_i;											//...��������� � ������
			minidx++;													//����������� ������ ������ ���� �� 1
		}else{															//���� �� min �� 2 ������
			printf("detail %d = %d %d deleted on %d step(end)\n", m_i+1, arr[m_i][0], arr[m_i][1], i+1);
			path[maxidx-1] = m_i;										//�������� � �����
			maxidx--;													//��������� ������ ����� �� 1
		}
	}
	printf("\n");
	printf("path = ");
	for(i=0;i<num;i++) printf("%2d",path[i]+1);							//���������� ��������� ���� �� �����
	printf("\n");		
	showGrant(arr, path, num);											//������� ������ ������
	showTime(arr, path, num);											//������� ����� ���������
}

void printArr(int **arr, int num){
	int i;																//������ ������������ ����� �������
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
	printf("machine1: ");												//������� ��� 1 ������
	for(i=0;i<num;i++){													//������� ����, ����� ������ ���� ����
		for(j=0;j<arr[*(path+i)][0];j++){								//���� �������� �� ������� ���� �� ����������
			printf("%d", *(path+i)+1);									//������� �������� � 1 ������
		}
		printf(" ");
	}	
	printf("\n");
	printf("machine2: ");												//���� ����� ��� 2-��
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
	for(i=0;i<num;i++){													//������ ���������
		sum+=arr[*(path+i)][0];											//����������� �� ��������� ����
	}
	printf("Work Time = %d\n", sum);
}


