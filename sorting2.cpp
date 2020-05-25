#include <stdio.h>
#include <string.h>
#define MAX 512

void NaturalMergingSort(char nameFile[]);

char EndRange(FILE *f);

int main(void){ 
	char filename[] = "file.txt";
	NaturalMergingSort(filename);
	return 0; 
}

void NaturalMergingSort(char filename[]){ 
	char a1[MAX], a2[MAX];
	int s1, s2,mark;
	FILE *f,*f1, *f2;
	char file1, file2;	
	s1 = s2 = 1;
	while (s1 > 0 && s2 > 0){ 
		mark = 1;
		s1 = 0;
		s2 = 0;
		f=fopen(filename, "r");
		f1=fopen("sort1.txt", "w");
		f2=fopen("sort2.txt", "w");
		fgets(a1, MAX, f);
		fprintf(f1, "%s", a1);
		fgets(a2, MAX, f);
		do{ 
			if (strcmp(a2, a1) < 0){
				switch (mark){ 
					case 1: fprintf(f1, "'\n");
						    mark = 2;
							s1++;
							break;
					case 2:
							fprintf(f2, "'\n");
							mark = 1;
							s2++;
							break; 
					} 
			}
			if (mark == 1){ 
				fprintf(f1, "%s", a2);
				s1++;
			}else{
				fprintf(f2, "%s", a2);
				s2++; 
			}
			strcpy(a1, a2); 
		}while (fgets(a2, MAX, f) != NULL);
		if (s2 > 0 && mark == 2)
			fprintf(f2, "'\n");
		if (s1 > 0 && mark == 1)
			fprintf(f1, "'\n");
		fclose(f2);
		fclose(f1);
		fclose(f);
		f=fopen(filename, "w");
		f1=fopen("sort1.txt", "r");
		f2=fopen("sort2.txt", "r");
		if(!feof(f1))
			fgets(a1, MAX, f1);
		if (!feof(f2))
			fgets(a2, MAX, f2);
		while (!feof(f1) && !feof(f2)){ 
			file1 = file2 = 0;
			while (!file1 && !file2){ 
				if (strcmp(a1, a2) <= 0){ 
					fprintf(f, "%s", a1);
					file1 = EndRange(f1);
					fgets(a1, MAX, f1);
				}else{ 
					fprintf(f, "%s", a2);
					file2 = EndRange(f2);
					fgets(a2, MAX, f2); 
				} 
			}
			while (!file1){
				fprintf(f, "%s", a1);
				file1 = EndRange(f1);
				fgets(a1, MAX, f1); 
			}
			while (!file2){ 
				fprintf(f, "%s", a2);
				file2 = EndRange(f2);
				fgets(a2, MAX, f2); 
			} 
		}
		file1 = file2 = 0;
		while (!file1 && !feof(f1)){ 
			fprintf(f, "%s", a1);
			file1 = EndRange(f1);
			fgets(a1, MAX, f1); 
		}
		while (!file2 && !feof(f2)){ 
			fprintf(f, "%s", a2);
			file2 = EndRange(f2);
			fgets(a2, MAX, f2);}
			fclose(f2);
			fclose(f1);
			fclose(f); 
		}
		remove("sort1.txt");
		remove("sort2.txt"); 
}

char EndRange(FILE *f){
	int pos = ftell(f);
	int tmp;
	tmp = fgetc(f);
	if (tmp != '\''){ 
		fseek(f, pos, SEEK_SET);
		return 0; 
	}else{ 
		fseek(f, 2, SEEK_CUR);
		return 1; 
	} 
}
