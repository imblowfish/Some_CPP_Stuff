#include<cstring>
#include<iostream>
#include<fstream>
#include <windows.h>
#include<iostream>
#define POW 10

using namespace std;

struct node{
    bool end;
    node* son[POW];
};

class Forest{
    private:
        node *root[POW];
        node *addNode();
        node *getSon(node *t,char key);
        node *getTree(char *key);
        int connectSon(node *t, node *c,char key);
        void deleteTree(node *t);
    public:
        Forest();
        ~Forest();
        void insertNumber(char *key);
        int searchNumber(char *key);
};

Forest::Forest(){
    int i;
    for(i=0;i<POW;i++)
        root[i]=NULL;
    
}

Forest::~Forest(){
    int i;
    for(i=0;i<POW;i++)
        deleteTree(root[i]);
}

void Forest::insertNumber(char *key){
    node *son;
    node *cur = getTree(key);
    int i,l = strlen(key);
    for(i=1;i<l;i++){
        son = getSon(cur, key[i]);
        if(!son){
            son = addNode();
            connectSon(cur,son,key[i]);
        }
        cur = son;
    }
    cur->end=true;
    return;
}

node* Forest::addNode(){
    node *tmp = new node;
    tmp->end=false;
    int i;
    for(i=0;i<POW;i++)
        tmp->son[i]=NULL;
    return tmp;
}

int Forest::connectSon(node *t,node*c,char key){
    if(!t->son[key-'0']){
        t->son[key-'0']=c;
        return 1;
    }
    return 0;
}

node* Forest::getSon(node* t, char key){
    if(t->son[key-'0']){
        return t->son[key-'0'];
    }
    return NULL;
}

void Forest::deleteTree(node *t){
    if(!t)
        return;
    int i;
    for(i=0;i<POW;i++)
            deleteTree(t->son[i]);
    delete t;
    return;
}

node* Forest::getTree(char *key){
    if(root[*key-'0']){
        return root[*key-'0'];
    }
    root[*key-'0'] = addNode();
    return root[*key-'0'];
}

int Forest::searchNumber(char *key){
    node *cur;
    int l=strlen(key);
    for(cur=getTree(key);l>1;l--,key++){
        cur = getSon(cur,*(key+1));
        if(!cur)
            return 0;
    }
    return cur->end?1:0;
}

int main(int argv, char *argc[]){
    Forest forest;
    char buf[50];
    char number[5];
    ifstream f("file.txt");
    if (!f.is_open()){
        cout << "Error open file"<<endl;
        return 1;
    }
    while(!f.eof()) {
        f>>buf;
        forest.insertNumber(buf);
    }
            cout<<"Input number for find"<<endl;
            cin>>number;
            if(forest.searchNumber(number))
               cout<<"Find"<<endl;
            else
                cout<<"Not find"<<endl;
    return 0;
}

