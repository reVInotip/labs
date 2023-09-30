#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int* CreateArray(int size) {
	int* arr = calloc(size, sizeof(int));
	assert(arr != NULL);
	return arr;
}

void Swap (int* first, int* second) {
	int t = *first;
	*first = *second;
	*second = t;
}

int Partition(int* array, int low, int high) {
	int p = array[(low + high) / 2], i = low, j = high;
	while (i <= j) {
		while (array[i] < p) {
			++i;
		}
		while (array[j] > p) {
			--j;
		}
		if (i >= j) {
			break;
		}
		Swap(/*first*/&array[i],
			/*second*/&array[j]);
		++i; --j;
	}
	return j;
}

void QuickSort(int* array, int low, int high) {
	if (low < high) {
		int partitionIndex = Partition(/*array*/array,
				/*low*/low,
				/*high*/high);
		QuickSort(array, low, partitionIndex);
		QuickSort(array, partitionIndex + 1, high);
	}
}

void PrintArray(int* array, int length) {
	for (int i = 0; i < length; ++i) {
		fprintf(stdout, "%d ", array[i]);
	}
	fprintf(stdout, "\n");
}

void Destroy(int* array) {
	free(array);
}

int main(void) {
	int length = 0;
	if (fscanf(stdin, "%d", &length) != 1) {
		return 0;
	}
	if (length == 0) {
		return 0;
	}
	int* array = CreateArray(/*size*/length);
	for (int i = 0; i < length; ++i) {
		if (fscanf(stdin, "%d", &array[i]) != 1) {
			Destroy(/*array*/array);
			return 0;
		}
	}
	QuickSort(/*array*/array,
			/*low*/0,
			/*high*/length - 1);
	PrintArray(/*array*/array,
			/*size*/length);
	Destroy(/*array*/array);
    return 0;
}
