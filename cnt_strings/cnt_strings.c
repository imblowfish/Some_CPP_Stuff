#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Прототипы функций*/
struct node{
	char *word;
	int count;
	struct node *left;
	struct node *right;
};

typedef struct node *Node;

struct tree{
	Node root;
};

typedef struct tree Tree;

Node addToTree(Node p, char *val){
	int check;
	if(p == NULL){
		p = (Node)malloc(sizeof(struct node));
		if(p==NULL){
			printf("error add node\n");
			system("pause");
			exit(1);
		}
		p->word = (char*)malloc(sizeof(char)*(strlen(val)+1));
		if(p->word == NULL){
			printf("error add word\n");
			system("pause");
			exit(1);
		}
		strcpy(p->word, val);
		p->count = 0;
		p->count++;
		p->left = p->right = NULL;
	}else if(check = strcmp(p->word, val) == 0) p->count++;
	else if(check < 0) p->left = addToTree(p->left, val);
	else p->right = addToTree(p->right, val);
	return p;
}

Node freeTree(Node p){
	if(p!=NULL){
		freeTree(p->left);
		freeTree(p->right);
		free(p);
		return NULL;
	}
	return NULL;
}

void printTree(Node p){
	if(p!=NULL){
		printTree(p->left);	
		printf("%s count=%d\n",p->word,p->count);
		printTree(p->right);
	}
}

Tree* treeCreate(){
	Tree *tree = (Tree*)malloc(sizeof(Tree));
	if(tree == NULL) return NULL;
	tree->root = NULL;
	return tree;
}

int main(){
	Tree *tree;
	tree = treeCreate();
	char str[50];
	FILE *f;
	f = fopen("file.txt", "r");
	if(f==NULL){
		printf("error open file\n");
		system("pause");
		return 0;
	}
	while(!feof(f)){
		fscanf(f, "%s", str);
		tree->root = addToTree(tree->root, str);
	}
	printTree(tree->root);
	tree->root = freeTree(tree->root);
	system("pause");
	return 0;
}


