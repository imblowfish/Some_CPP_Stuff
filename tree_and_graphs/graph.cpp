#include<iostream>
#include <fstream>
using namespace std;

class Element{
	public:
	int to;
	int wt;
	Element *next;
	Element(int to, int wt=0, Element*next = NULL):to(to),wt(wt),next(next){}
};

class List{
		Element *first, *last, *get;
		int count;
	public:
		List(){
			first = last = NULL;
			count = 0;
		}
		void add(int to, int wt){
			Element *newElement = new Element(to,wt);
			if(last){
				last->next = newElement;
				last = last->next;
			} 
			else{
				first = newElement;
				get = newElement;
				last = newElement;
			}
			count++;
		}
		Element* getElement(){
			if(!first)
				return NULL;
			if(!get)
				get = first;
			Element *temp = get;
			get = get->next;
			return temp;
		}
		int getCount(){
			return count;
		}
		~List(){
			Element *tmp = first, *del;
			while(tmp!=NULL){
				del = tmp;
				tmp = tmp->next;
				delete del;
			}
		}
};

class GraphList{
	private:
		List *graph;
		int vertexNumber;
		int INF=999;
	public:
		int min(int a, int b){
			if(a<b)
				return a;
			else
				return b;
		}
		GraphList(int n);
		int AddArc(int from, int to, int wt);
		int FindDiam();
		~GraphList();
};

GraphList::GraphList(int n):vertexNumber(n){
	graph = new List[vertexNumber];
}

GraphList::~GraphList(){
	delete [] graph;
}

int GraphList::AddArc(int from, int to, int wt){
	if(from<0 || from>=vertexNumber || to<0 || to>=vertexNumber)
		return 0;
	graph[from].add(to,wt);
	return 1;
}

int GraphList::FindDiam(){
	int P[vertexNumber][vertexNumber];
	Element *tmp;
	int i,j,k,d = 0;
	
	for(i=0;i<vertexNumber;i++){
		for(j=0;j<vertexNumber;j++)
			P[i][j] = INF;
	}
	
	for(i=0;i<vertexNumber;i++){
		for(j=0;j<graph[i].getCount();j++){
			tmp = graph[i].getElement();
			P[i][i] = 0;
			P[i][tmp->to] = tmp->wt;
		}
	}
	
	for(k=0; k<vertexNumber; k++)
		for(i=0; i<vertexNumber; i++)
			for(j=0; j<vertexNumber; j++){ 
				if(P[i][k]<INF && P[k][j]<INF)	
					P[i][j]=min(P[i][j],P[i][k]+P[k][j]);
			}
		
	for(i=0; i<vertexNumber; ++i)
		for(j=0; j<vertexNumber; ++j){
			if(P[i][j] == INF){
				return d = INF;
			}
			if(d<P[i][j]&& P[i][j]!=INF) 
				d=P[i][j];
		}		
	return d; 
}

int main(void){ 
	int i,j,buf;
	int size;
	ifstream f("file.txt");
	if(!f.is_open()){
		cout<<"Error open file..."<<endl;
		return 0;
	}
	f>>size;
	GraphList g(size);
	for(i=0;i<size;i++)
		for(j=0;j<size;j++){
			f>>buf;
			if(buf){
				g.AddArc(i,j,buf);
			}
		}
	cout<<"Diameter = "<<g.FindDiam()<<endl;
	system("pause");
	return 0;
}
