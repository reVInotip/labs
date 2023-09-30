#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
  
void Swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
  
void Heapify(int* arr, int currentLength, int index) {
	int largest = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	if (left < currentLength && arr[left] > arr[largest]) {
		largest = left;
	}
	if (right < currentLength && arr[right] > arr[largest]) {
		largest = right;
	}
	if (largest != index) {
		Swap(/*a*/&arr[index], /*b*/&arr[largest]);
		Heapify(/*arr*/arr,
			/*currentLength*/currentLength,
			/*index*/largest);
	}
}
  
void BuildHeap(int* arr, const int length) {
	for (int i = length / 2 - 1; i >= 0; --i) {
    	Heapify(/*arr*/arr,
			/*currentLength*/length,
			/*index*/i);
	}
}

void HeapSort(int* arr, const int length) {
	BuildHeap(/*arr*/arr, /*length*/length);
	for (int i = length - 1; i >= 0; --i) {
		Swap(/*a*/&arr[0], /*b*/&arr[i]);
		Heapify(/*arr*/arr,
			/*currentLength*/i,
			/*index*/0);
	}
}
  
void PrintArray(int* arr, const int length) {
	for (int i = 0; i < length; ++i) {
		fprintf(stdout, "%d ", arr[i]);
	}
	fprintf(stdout, "\n");
}

int* CreateArray(int size) {
	int* temp = calloc(size, sizeof(int));
	assert(temp != NULL);
	return temp;
}

void DestroyArray(int* arr) {
	free(arr);
}

int main() {
	int length = 0;
	if (fscanf(stdin, "%d", &length) != 1) {
		printf("error in length input");
		return 0;
	}
	if (length == 0) {
		return 0;
	}
	int* arr = CreateArray(/*size*/length);
	for (int i = 0; i < length; ++i) {
		if (fscanf(stdin, "%d ", &arr[i]) != 1) {
			printf("error in array");
			DestroyArray(/*arr*/arr);
			return 0;
		}
	}
	HeapSort(/*arr*/arr, /*length*/length);
	PrintArray(/*arr*/arr, /*length*/length);
	DestroyArray(/*arr*/arr);
	return 0;
}
