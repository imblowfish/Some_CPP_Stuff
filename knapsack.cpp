#include <iostream>
#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#include <cmath>
using namespace std;

void print(int **el, int n, int vol);			//����� ��������� ��������
void printVal(int val, int p);					//����� ������� � �������� ������� ���������
void printAllCombin(int p, int n);				//����� ���� ���������� �� n ���������(�� 2^n)

int main(){
	int n, p,**el, vol, best=-1, 				/*n - ����� ��-��, p-2^n, el-������ ��������� � ������ � ������, vol - ����� �������, best - ������ ����������*/
		i, j, bc=0, sumw=999, sumc=0;			/*bc - ������ ����, sumw - ����� �����, sumc - ����� ���*/
	printf("input num of elements\n");
	scanf("%d", &n);
	printf("input vol of knap\n");
	scanf("%d", &vol);
	p=2<<(n-1);									//�������� 2 � ������� n
	el = (int**)malloc(sizeof(int*)*n);	
	for(i=0;i<n;i=-~i) {						//-~i ������� ������ i++
		el[i] = (int*)malloc(sizeof(int)*2);
		printf("input weight of element %d=",i+1);
		scanf("%d",&el[i][0]);
		printf("input cost of element %d=", i+1);
		scanf("%d",&el[i][1]);
		printf("\n");
	}
	system("CLS");
	print(el, n, vol);							//������� ��� ��������� ����������
	for(i=0;i<p;i=-~i){
		for(j=0;j<n;j=-~j){
			if(i & (1<<j)) {					//�������� j-�� ���� � i - ����� �� �� �������
				sumw+=el[j][0]; sumc+=el[j][1]; //���� �����, ��������� �������� �� �������� j � �����
			}	
		}
		if(sumw<=vol && sumc>bc) {				//���� ����� ����� ������ ���� ���� ������(������) � ����� ��� ������ ������ ����
			bc = sumc; 							//���������� ����
			best=i;								//���������� ���������� � ���� ����������� �����, ����� ���������
		}
		sumw = 0;	
		sumc = 0;	
	}
	printf("ALL COMBINATION\n");				//������� ��� ���������� �� n ���������(����� ����������������, ���� ������� ����� �� ����������)
	printAllCombin(p, n);						
	if((best^(-1)) == 0) printf("can't find best\n");//������� �������� ��������� �����, ���� �� ����� �������(b == -1), �� �������, ��� ������� ���
	else {
		printf("best combination\n");  printVal(best,n);//����� ������� ������ ���������� � ���� ��������� �����
		printf("\nbest const = %d\n",bc);				//� ������ ����
	}
	for(i=0;i<n;i++) free(el[i]);						//����������� ������
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
	for(j=p;j>0;j=~-j) printf("|%d|",(val >> (j-1)) & 1);		//(val >> (j-1)) & 1) �������� j-�� ���� � val(������ ������)	
	printf("\n");
}

void printAllCombin(int p, int n){
	int i;
	for(i = 0; i < p; i++) {
		printVal(i, n);
		printf("\n");	
	}
}

