#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <mem.h>
#include <time.h>

int8_t min_max_elements(int32_t *arr, uint32_t size, int32_t *min, int32_t *max)
{
	int64_t count = size;
	if (!arr || size < 2 || !min || !max)
		return (0);
	while (count--)
	{
		if (*min > *arr)
			*min = *arr;
		else if (*max < *arr)
			*max = *arr;
		++arr;
	}
	if (size > (*max - *min + 1))
		return (1);
	else
		return (0);
}

void	sorting_by_counting(int32_t *arr, uint32_t size, int32_t min, int32_t max)
{
	int32_t *buff = NULL;
	uint32_t buff_size = 0;
	int32_t i = 0;
	int32_t j = 0;

	buff_size = (max - min) > 0 ? (uint32_t)(max - min) : 0;
	if  (!arr || !buff_size || !(buff = (int32_t*)malloc(sizeof(int32_t) * buff_size)))
		return;
	memset(buff, 0, sizeof(int32_t) * buff_size);
	while (i < size)
		buff[*(arr + i++) - min] += 1;
	i = 0;
	while (i < size)
	{
		if (*(buff + j) == 0)
			++j;
		else
		{
			*(arr + i++) = (j + min);
			*(buff + j) -= 1;
		}
	}
	free(buff);
}

int main(void)
{

	int32_t arr[] = {9,5,7,6,4,8,10,-3,4,6,5,7,7,9,10,3,3,8,10,4,7,12,9,6,10,9,5,6,7,8,4,22,9,3,11};

	uint32_t size = sizeof(arr)/sizeof(int32_t);
	int32_t min = *arr;
	int32_t max = *arr;
	double time = 0;

	if (!min_max_elements(arr, size, &min, &max))
	{
		printf("Something goes wrong or you need to use another array\n"
		 "check the length of the array and the range of numbers;\n");
		return (0);
	}

	clock_t start_time = clock();
	sorting_by_counting(arr, size, min, max);
	time = clock() - start_time;

	for (uint32_t i = 0; i < size; ++i) {
		printf("%d", arr[i]);
		if (i + 1 < size)
			printf(", ");
	}
	printf(";\n");
	printf("time = %f\n", time / CLOCKS_PER_SEC);
	return (0);
}
