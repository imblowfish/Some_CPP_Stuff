#include <iostream>
#include <cstdlib>



#define LIST
#ifdef LIST
#include "list.cpp"
#else
#include "arr.cpp"
#endif

using namespace std;

DataType findDiff(DataType x);

DataType findDiff(DataType x){
	if(x.deg == 0)
		x.deg-=1;
	if(x.deg!=0){
		x.coef*=x.deg;
		x.deg-=1;
	}
	return x;
}


int main(int argc, char** argv) {
	Queue q;
	DataType el;
	int n,i,c,d;
	cout<<"How many numbers you want to enter?"<<endl;
	cin>>n;
	for(i=0;i<n;i++){
		do{
			cout<<"Coefficient "<<i+1<<" element = ";
			cin>>c;
			cout<<"Degree "<<i+1<<" element = ";
			cin>>d;
		}while(d<0);
		q.EnQueue(c,d);
	}
	cout<<"p(x) = ";
	while(!(q.Empty())){
			el = findDiff(q.DeQueue());
			if(el.deg==0)
				cout<<el.coef<<"+";
			else if(el.deg < 0)
				cout<<"0+"; 
			else
				cout<<el.coef<<"x^"<<el.deg<<"+";
	}
	cout<<"0"<<endl;
	system("pause");
	return EXIT_SUCCESS;
}


