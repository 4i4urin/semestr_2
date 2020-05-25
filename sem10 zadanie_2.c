#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct city
{
	char* town;
	long int people;
};

int menu();
struct city* add(struct city*, int*);
char* input_str_consol(int*);
void list(struct city*, int);
long int num_from_str(char*);
void delite(struct city*, int*);
void shell_sort_struct(struct city*, int);
int bin_search(char**, char*, int);

int main(int argc, char const *argv[])
{
	int from_menu = menu();
	int num = 0;
	struct city* sp = calloc(1, sizeof(struct city));
	while(from_menu)
	{
		switch(from_menu)
		{
			case 1:
				sp = add(sp, &num);
				from_menu = menu();
			break;
			case 2: 
				delite(sp, &num);
				from_menu = menu();
			break;
			case 3:
				list(sp, num);
				from_menu = menu();
			break;
		}
	}
	return 0;
}

void delite(struct city* sp, int* num)
{
	printf("%d\n", *num);
	char** town_mass = calloc(*num, sizeof(char*));
	shell_sort_struct(sp, *num);
	for (int i = 0; i < *num; ++i)
		town_mass[i] = sp[i].town;
	for (int i = 0; i < *num; ++i)
		printf("%s\n", town_mass[i]);
	char* consol = input_str_consol(NULL);
	int del = bin_search(town_mass, consol, *num - 1);
	free(town_mass);
	printf("%d\n", del);
	if (del == -1)
	{
		printf("\nCity is burn\n");
		return;
	}
	free(consol);
	if (del != *num - 1)
		sp[del] = sp[*num - 1];
	else
		sp[del] = sp[*num -2];
	*num -= 1;
}

int bin_search(char** mas_str, char* x, int high)
{
	int low = 0;
	while (low <= high)
	{
		printf("In circle\n");
		int mid = (high + low) / 2;
		if (strcmp(mas_str[mid], x) == 1) //mas_str[mid] > x
			high = mid - 1;
		else if (strcmp(x, mas_str[mid]) == 1)// x > mas_str[mid]
			low = mid + 1;
		else 
			return mid;
	}
	return -1;
}

void shell_sort_struct(struct city* ptr_struct, int n)
{
	int gap, i, j;
	for (gap = n/2; gap > 0; gap /= 2)
	{
		for (i = gap; i < n; ++i)
		{//                                          prt_s[j] > ptr_s[j + gap]
			for (j = i - gap; j >= 0 && strcmp(ptr_struct[j].town, ptr_struct[j + gap].town) == 1; j -= gap)

			{
				struct city temp = ptr_struct[j];
				ptr_struct[j] = ptr_struct[j + gap];
				ptr_struct[j + gap] = temp;
			}
		}
	}
}

long int num_from_str(char* str)//вытаскивает из строки число
{
	long int res = 0;
	for (int i = 0; str[i] != '\0'; ++i)
	{
		res *= 10;
		if (str[i] <= '9' && str[i] >= '0')
			res = res + (str[i] - '0');
		else
		{
			printf("No such number\n");
			exit(401);
		}
	}
	return res;
}

void list(struct city* sp, int right)
{
	printf("%d\n", right);
	for (int i = 0; i < right; ++i)
		printf("%s %ld\n", sp[i].town, sp[i].people);
}

struct city* add(struct city* sp, int* num)
{
	(sp + *num)->town = input_str_consol(NULL);
	printf("%s\n", (sp + *num)->town);
	char* k = input_str_consol(NULL);
	printf("%s\n", k);
	(sp + *num)->people = num_from_str(k);
	*num += 1;
	sp = realloc(sp, (*num + 1) * sizeof(struct city));
	return sp;

}

char* input_str_consol(int* Eof)
{
	int i = 0, c;// \n и ; не считываются
	char* ptr_str = calloc(1, sizeof(char));
	while ((c = getchar()) != ' ' && c != '\n' && c != EOF)
	{
		*(ptr_str + i) = c;
		i += 1;
		ptr_str = realloc(ptr_str, (i + 1) * sizeof(char));
	}
	*(ptr_str + i) = '\0';
	if (c == EOF)
		*Eof = 0;
	return ptr_str;
}

int menu()
{
	int menu;
	while(1)
	{
		puts("Menu");
		puts("1 - add");
		puts("2 - delite");
		puts("3 - list");
		puts("0 - to quite");
		char c = getchar();
		switch(c)
		{
			case '1': menu = 1; break;
			case '2': menu = 2; break;
			case '3': menu = 3; break;
			case '0': menu = 0; break;
			default: puts("Unknow simbol"); while (c != '\n') c = getchar(); continue;
		}
		while (c != '\n') c = getchar();
		break;
	}
	
	return menu;
}
