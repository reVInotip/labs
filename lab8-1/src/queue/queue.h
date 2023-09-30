#include "../graph/graph.h"
#pragma once

typedef struct THeap THeap;

typedef struct TQueue {
	THeap* Heap;
	short* Indexes;
	int HeapSize;
} TQueue;

TQueue CreateQueue(const int size);
void DecreaseKey(TQueue* queue, const unsigned int newKey, const TEdge edge);
TEdge Get(TQueue* queue);
void DestroyQueue(TQueue* queue);
