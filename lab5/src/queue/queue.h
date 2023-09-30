#pragma once
#include "../tree/tree.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct MysticalQueue {
	struct MysticalTree* Tree;
	struct MysticalQueue* Child;
	struct MysticalQueue* Parent;
	int Priority;
}* MysticalQueue;

MysticalQueue CreateQueue();
void FillQueueFromArray(MysticalQueue* queue, const int* array, const size_t length);
void Put(MysticalQueue* queue, const int priority, const MysticalTree tree);
MysticalQueue Get(MysticalQueue* queue);
int GetPriority(const MysticalQueue queue);
MysticalTree GetTree(const MysticalQueue queue);
bool OneElementLeft(const MysticalQueue queue);
void DestroyQueue(MysticalQueue* queue);
