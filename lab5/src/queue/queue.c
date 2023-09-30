#include "queue.h"
#include "../tree/tree.h"
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

MysticalQueue CreateQueue() {
	return NULL;
}

void FillQueueFromArray(MysticalQueue* queue, const int* array, const size_t length) {
	assert(queue != NULL);
	for (int i = 0; i < (int)length; ++i) {
		if (array[i] == 0) {
			continue;
		}
		MysticalTree currentTree = MakeLeaf(/*symbol*/(char)i);
		Put(/*queue*/queue, /*priority*/array[i], /*tree*/currentTree);
	}
}

void Put(MysticalQueue* queue, const int priority, const MysticalTree tree) {
	assert(queue != NULL);
	MysticalQueue currentQueue = (MysticalQueue)malloc(sizeof(struct MysticalQueue));
	assert(currentQueue != NULL);
	currentQueue->Priority = priority;
	currentQueue->Tree = tree;
	if (*queue == NULL) {
		currentQueue->Parent = NULL;
		currentQueue->Child = NULL;
		*queue = currentQueue;
	} else {
		MysticalQueue currentPtr = *queue;
		MysticalQueue lastPtr = currentPtr->Parent;
		while (currentPtr != NULL) {
			if (currentPtr->Priority >= priority) {
				break;
			}
			lastPtr = currentPtr;
			currentPtr = currentPtr->Child;
		}
		if (currentPtr == NULL) {
			lastPtr->Child = currentQueue;
			currentQueue->Parent = lastPtr;
			currentQueue->Child = CreateQueue();
		} else if (lastPtr == NULL) {
			currentPtr->Parent = currentQueue;
			currentQueue->Parent = CreateQueue();
			currentQueue->Child = currentPtr;
			*queue = currentQueue;
		} else {
			currentQueue->Child = currentPtr;
			currentQueue->Parent = lastPtr;
			lastPtr->Child = currentQueue;
			currentPtr->Parent = currentQueue;
		}
	}
}

MysticalQueue Get(MysticalQueue* queue) {
	assert(queue != NULL);
	if (*queue == NULL) {
		return NULL;
	}
	MysticalQueue currentQueue = *queue;
	*queue = (*queue)->Child;
	if (*queue != NULL) {
		(*queue)->Parent = NULL;
	}
	currentQueue->Child = NULL;
	return currentQueue;
}

int GetPriority(const MysticalQueue queue) {
	assert(queue != NULL);
	return queue->Priority;
}

MysticalTree GetTree(const MysticalQueue queue) {
	assert(queue != NULL);
	return queue->Tree;
}

bool OneElementLeft(const MysticalQueue queue) {
	return (queue->Child == NULL);
}

void DestroyQueue(MysticalQueue* queue) {
	assert(queue != NULL);
	while (*queue != NULL) {
		MysticalQueue currentQueue = *queue;
		*queue = (*queue)->Child;
		free(currentQueue);
	}
}
