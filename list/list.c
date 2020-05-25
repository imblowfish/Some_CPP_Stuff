#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>

struct element
{
	char name[30];
	float price;
	int amount;
	int minAge;
	int maxAge;
};

typedef struct element DataType;

struct List
{
	DataType data;
	struct List *next;
};

typedef struct List *list;

list read_file(char *filename, list begin);
list add(list begin, DataType toy);
void write_file(char *filename, list begin);
void show(list);
DataType input_toy();
void edit(list);
void maxPrice(list begin);
void create_new(char *filename);
list delete_list(list begin);
list delete_record(list);
void print_record(list pos);
list add_in_file(list begin, DataType toy);
void findToy(list begin);
char create_file(char *filename);

int main(int argc, char *argv[]) 
{
	setlocale(LC_ALL, "Russian");
	char file[50];
	char menu;
	char yes;
	list toys = NULL;
	puts("Открыть файл:");
	gets(file);
	toys = read_file(file, toys);
	do
	{
		system("CLS");
		puts("1. Добавить игрушку");
		puts("2. Редактировать");
		puts("3. Показать содержимое файла");
		puts("4. Найти игрушку по заданному возрасту и цене");
		puts("5. Самая дорогая игрушка");
		puts("6. Удалить запись");
		puts("7. Удалить список");
		puts("8. Выход");
		menu=getchar();
		switch(menu)
		{
			case '1': toys = add(toys, input_toy()); break;
			case '2': edit(toys); break;
			case '3': show(toys); break;
			case '4': findToy(toys); break;
			case '5': maxPrice(toys); break;
			case '6': toys = delete_record(toys); break;
			case '7': if(toys == NULL)
					  {
					  	puts("Список пуст");
					  	system("pause");
						break;
					  }
					  puts("Удалить список?(y/n)");
					  do
					  {
					  	yes = getch();
					  }while(yes!='y' && yes!='Y' && yes!='n' && yes!='N');
					  if(yes == 'y' || yes == 'Y')
					  {
					  	toys = delete_list(toys);
					  	puts("Список удален");
					  	system("pause");
					  }
		}
	}while(menu!='8');
	write_file(file, toys);
	toys = delete_list(toys);
	system("pause");
	return 0;
	
}

void edit(list begin)
{
	int n, k = 1;
	char yes;
	system("CLS");
	if(begin == NULL)
	{
		puts("Список пуст");
		getch();
		return;
	}
	
	puts("Номер записи для редактирования?");
	scanf("%d", &n);
	
	if(n<1)
	{
		puts("Ошибка");
		system("pause");
		return;
	}
	while(begin->next && k < n)
	{
		begin = begin->next;
		k++;
	}
	if(begin == NULL)
	{
		puts("Ошибка");
		system("pause");
		return;
	}
	
	print_record(begin);
	puts("Редактировать?(y\\n)");
	do
		yes=getchar();
	while(yes!='y' && yes!= 'Y' && yes!='n' && yes!='N');
	if(yes=='y' || yes=='Y')
		begin->data = input_toy();
}

list delete_record(list begin)
{	
	int a, k = 1; 
	list temp, temp1; 
	if (begin == NULL) 
	{ 
		printf("Список пуст\n"); 
		system("pause"); 
		return begin; 
	} 
	printf("Номер записи для удаления?\n"); 
	scanf("%d", &a); 
	if (a<k) 
	{ 
		printf("Ошибка\n"); 
		system("pause"); 
		return begin; 
	} 
	if (a == k) 
	{ 
		temp = begin->next; 
		free(begin); 
		begin = temp; 
		return begin; 
	} 
	temp = begin; 
	while (temp&&k < a - 1) 
	{ 
		temp = temp->next; 
		k++; 
	} 
	if (temp == NULL || temp->next == NULL) 
	{ 
		printf("Элемент не существует\n"); 
		system("pause"); 
		return begin; 
	} 
	temp1 = temp->next; 
	temp->next = temp1->next; 
	free(temp1); 
	return begin; 
}

list delete_list(list begin)
{
	if(begin == NULL)
	{
		return;
	}
	list temp = begin;
	while(temp)
	{
		begin = temp->next;
		free(temp);
		temp = begin;		
	}
	return begin;
}

list add_in_file(list begin, DataType toy)
{
	list temp;
     if (begin == NULL) 
     {
        begin = (list) malloc (sizeof(struct List));
        temp = begin;
     }
     else
     {
        temp = begin;
        while (temp->next) temp = temp->next;
        temp->next = (list) malloc (sizeof(struct List));
        temp = temp->next;
     }
     temp->data = toy;
     temp->next = NULL;
     return begin;
}

list add(list begin, DataType toy)
{
	int a, k = 1; 
	list temp,temp1; 
	if (begin == NULL) 
	{ 
		temp = begin; 
		begin = (list)malloc(sizeof(struct List)); 
		begin->data = toy; 
		begin->next = temp; 
		return begin; 
	} 
	printf("Под каким номером добавить запись?\n"); 
	scanf("%d", &a); 
	if (a<k) 
	{ 
		printf("Ошибка\n"); 
		system("pause"); 
		return begin; 
	} 
	if (a == k) 
	{ 
		temp = begin; 
		begin = (list)malloc(sizeof(struct List)); 
		begin->data = toy; 
		begin->next = temp; 
		return begin; 
	} 
	temp = begin; 
	while (temp && k < (a - 1) && a != 1) 
	{ 
		temp = temp->next; 
		k++; 
	} 
	if (temp == NULL) 
	{ 
		printf("Ошибка\n"); 
		system("pause"); 
		return begin; 
	} 
	if (temp->next == NULL) 
	{ 
		temp->next = (list)malloc(sizeof(struct List)); 
		temp = temp->next; 
		temp->data = toy; 
		temp->next = NULL; 
		return begin; 
	} 
	temp1 = temp->next; 
	temp->next = (list)malloc(sizeof(struct List)); 
	temp = temp->next; 
	temp->data = toy; 
	temp->next = temp1; 
	return begin; 
}


void maxPrice(list begin)
{
	int maxPrice = 0;
	list save;
	char* find;
	while(begin)
	{
		find = strstr(begin->data.name, "constructor");
		if(begin->data.price > maxPrice && find)
		{
			maxPrice = begin->data.price;
			save = begin;
		}
		begin = begin->next;
		find=NULL;
	}
	if(save != NULL)print_record(save);
	else printf("Конструктор не найден\n");
	system("pause");
}

void findToy(list begin)
{
	int age;
	float price;
	puts("Введите возраст ребенка");
	scanf("%d", &age);
	puts("Введите максимальную сумму покупки");
	scanf("%f", &price);
	
	while(begin->next)
	{
		if(age >= begin->data.minAge && age <= begin->data.maxAge && begin->data.price <= price) print_record(begin);
		begin = begin->next;
	}
	getch();
}

void print_record(list pos)
{
	printf("Название : %s\n Цена : %.2f\n Количество : %.2d\n Мин Возраст : %d Макс Возраст : %d\n", pos->data.name, pos->data.price, pos->data.amount, pos->data.minAge, pos->data.maxAge);
}

DataType input_toy(void)
{
	DataType toy;
	puts("Название игрушки");
	scanf("%s", &toy.name);
	puts("Цена игрушки");
	scanf("%f", &toy.price);
	puts("Количество игрушек");
	scanf("%d",&toy.amount);
	puts("Минимальный возраст для игрушки");
	scanf("%d", &toy.minAge);
	puts("Максимальный возраст для игрушки");
	scanf("%d", &toy.maxAge);
	return toy;
}

char create_file(char *filename)
{
	FILE *f;
	puts("Создание нового файла");
	system("pause");
	if((f=fopen(filename,"ab"))==NULL)
	{
		perror("Ошибка открытия файла");	 
		system("pause");
		return NULL;
	}
	else
		return NULL;
	fclose(f);
	return filename;
}

list read_file(char *filename, list begin)
{
	FILE *f;
	DataType toy;
	char yes;
	if((f=fopen(filename, "rb"))==NULL)
	{
		perror("Ошибка открытия файла");
		system("pause");
		filename = create_file(filename);
	}
	if(filename != NULL)
	{
		while(fread(&toy, sizeof(toy),1,f))
		begin = add_in_file(begin, toy);
		fclose(f);
		return begin;
	}
}

void show(list begin)
{
	int k = 0;
	system("CLS");
	if(begin == NULL)
	{
		puts("Список пуст");
		system("pause");
		return;
	}
	puts("|  N |  Название  |   Цена   | Количество | Мин Возраст |  Макс Возраст |");
	puts("-------------------------------------------------------------------------");
	while(begin)
	{
		printf("|%3d |%11s |%9.2f |%11d |%12d |%14d |\n", ++k, begin->data.name,
											   begin->data.price,
										   	   begin->data.amount,
											   begin->data.minAge, begin->data.maxAge);
		begin = begin->next;
	}
	puts("-------------------------------------------------------------------------");
	system("pause");
}

void write_file(char *filename, list begin)
{
	FILE *f;
	if((f=fopen(filename,"wb")) == NULL)
	{
		perror("Ошибка сохранения файла");
		system("pause");
		return;
	}
	while(begin)
	{
		fwrite(&begin->data, sizeof(DataType),1,f);
		begin = begin->next;
	}
}

