#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#define N1 180
#define N2 500
#define N3 1000
#define N4 5000
//было 1800 5000 10000 50000
using namespace std;

typedef int(*FuncAdress) (int *,int);

int Bubble(int *arr, int n);
int Shake(int *arr, int n);
int RecQSort(int *arr, int n);
int NonRecQSort(int *arr, int n);
void FillArray1(int *arr, int n); 
void FillArray2(int *arr, int n); 
void Randomize(int *arr, int n); 
void Copy(int *arr, int *arr1, int n);

int main(){
    FuncAdress mas[] = {Bubble, Shake, RecQSort, NonRecQSort};
    int b, number [12];
    int *a,*a1,j,i=0;
    a = new int[N4];
    a1 = new int[N4];
    FillArray1(a1,N4);
    Randomize(a1,N4);
    if (a == NULL) cout << "Error"<<endl;
    while (i<4){
        for (j=0;j<4;j++){
            b = j==0? N1: j==1? N2: j==2? N3:N4;
            
            FillArray1(a,b);
           	number[j*3]=mas[i](a,b);
           	
            FillArray2(a,b);
            number[j*3+1]=mas[i](a,b);
            
			Copy(a, a1, b);
            number[j*3+2]=mas[i](a,b);
            
		}
        printf("%s",i==0?"----------------BubbleSort-----------------\n":i==1?"-----------------ShakerSort----------------\n"
        :i==2?"-----------------RecQSort------------------\n":"--------------NonRecQSort------------------\n");
        cout << "         Randomize      Unsorted     Sorted\n";
        for (j=0;j<12;){
       	 	printf("N%i:     %10d    %10d %10d\n",j/3,number[j++], number[j++],number[j++]);
        }
        cout << endl;
        i++;
	}
	free(a);
    return 0;
    system("pause");
}

void FillArray1(int *arr, int n){
    int i, j=n;
    for (i=0;i<n;i++) arr[i]= j--;
}

void FillArray2(int *arr, int n){
    int i;
    for (i=0;i<n;i++) arr[i] = i;
}

void Randomize(int *arr, int n){
	int i,save;
    int r;
    srand(time(0));
    for(i=0;i<n;i++){
    	do{
    		r = rand()%n-1;
    		r*=r;
		}while(r>=n || r<0);
		save = arr[i];
		arr[i] = arr[r];
		arr[r] = save;
	}
}

void Copy(int *arr, int *arr1, int n){
	int i;
	for(i=0;i<n;i++){
		arr[i] = arr1[i];
	}
}

int Bubble(int *arr, int n){
	int i, j, save, equals=0;
	for(i=0;i<n;i++){
		for(j=0;j<n-1;j++){
			if(arr[j]<arr[j+1]){
				save = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = save;
				equals++;
			}
		}
	}
	return equals;
}

int Shake(int *arr, int n){
	int equals = 0;
	int j, k = n-1, left = 1, right = n-1, x;
	do{
		for(j=right; j>=left;j--)
			if(arr[j-1]<arr[j]){
				x = arr[j-1];
				arr[j-1] = arr[j];
				arr[j] = x;
				equals++;
				k = j;
			}
			left = k+1;
		for(j=left;j<=right;j++)
			if(arr[j-1]<arr[j]){
				x = arr[j-1];
				arr[j-1] = arr[j];
				arr[j] = x;
				equals++;
				k = j;
			}
			right = k-1;
	}while(left<right);
	return equals;
}

int RecQSort(int *arr, int n){
	int equals=0;
	int x, w, i, j;
    x = arr[n/2];
	i=0; j=n-1;
	do{
		while (arr[i]>x) i++;
		while (x>arr[j]) j--;
		if (i<=j){
			if(i!=j){
				++equals;
				w = arr[i]; 
				arr[i] = arr[j]; 
				arr[j] = w;
			}
			i++; j--;
		}
	}while (i<j);
	if (j>0)
		equals+=RecQSort(arr, j+1);
	if (i<n-1)
		equals+=RecQSort(arr+i, n-i);
	return equals;
}

int NonRecQSort(int *arr, int n){
	int equals = 0;
	const int M=20;
	int i, j, left, right, s, x, w;
	struct {int left, right;} stack[M];
	s = 0;
	stack[0].left = 0; 
	stack[0].right = n-1;
	do{
		left = stack[s].left;
		right = stack[s].right;
		s--;
		do{
			i = left;
			j = right;
			x = arr[(left+right)/2];
			do{
				while (arr[i]>x) i++;
				while (x>arr[j]) j--;
				if (i<=j){
					if(i!=j){
						equals++;
						w = arr[i];
						arr[i] = arr[j];
						arr[j] = w;		
					}
					i++; j--;
				}
			}while (i<j);
			if (i<right){
				s++;
				stack[s].left = i;
				stack[s].right = right;
			}
			right = j;
		}while (left<right);
	}while (s>-1);
	return equals;
}
