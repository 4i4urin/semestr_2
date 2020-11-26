//random quick sort

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SWAP(a, b) int temp = a; a = b; b = temp;
#define N 3000000000
#define LONG_ARR 100

void quick_sort(int*, int, int);
void out(int*, int);
void counting_sort(int*, int, int);


int main(int argc, char const *argv[])
{
	int num[LONG_ARR], i;
	srand(time(NULL));
	for (int i = 0; i < LONG_ARR; ++i)
		num[i] = rand() % N;
	printf("Input array\n");
	out(num, LONG_ARR);
	printf("WAT kind of sort do you want to use?\n");
	printf("c -> counting_sort\n");
	printf("q -> quick_sort_random\n");
	char c = getchar();
	printf("\n");
	if (c == 'q') 
		quick_sort(num, 0, LONG_ARR - 1);
	else if (c == 'c')
		counting_sort(num, N, LONG_ARR);
	else 
	{
		printf("Unknown simbol\n");
		return 333;
	}
	printf("Output array\n");
	out(num, LONG_ARR);
	printf("num[0] = %d\n", num[0]);
	printf("num[LONG_ARR] = %d\n", num[LONG_ARR - 1]);
	return 0;
}


void counting_sort(int* arr, int k, int n)
{
	int* count_arr;
	count_arr = malloc(k * sizeof(int));
	for (int i = 0; i < k; ++i)
		count_arr[i] = 0;
	for (int i = 0; i < n; ++i)
		count_arr[arr[i]] += 1;
	int b = 0;
	for (int j = 0; j < k; ++j)
	{
		for (int i = 0; i < count_arr[j]; ++i)
		{
			arr[b] = j;
			b += 1;
		}
	}
	free(count_arr);
}


void quick_sort(int* arr, int left, int right)
{
	int i, j, p, y;
	srand(time(NULL));
	i = left; j = right;
	y = left + rand() % (right - left);
	p = arr[y];
	do 
	{
		while ((arr[i] < p) && (i < right)) i++;
		while ((arr[j] > p) && (j > left)) j--;
		if (i <= j)
		{
			SWAP(arr[i], arr[j]);
			i++; j--;
		}
	} while (i <= j);
	if (left < j) quick_sort(arr, left, j);
	if (right > i) quick_sort(arr, i, right);
}

void out(int* arr, int max)
{
	if (max > 500)
		printf("Too much print\n");
	else 
	{
		for (int i = 0; i < max; i++)
		{
			printf("%d ", arr[i]);
			if ((i % 10) == 0 && i != 0)
				printf("\n");
		}
		printf("\n");
		printf("\n");
	}
}
