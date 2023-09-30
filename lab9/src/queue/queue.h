#pragma once
#include "../graph/graph.h"

typedef struct TQueue {
	TEdge* Heap;
	short* Indexes;
	int HeapSize;
} TQueue;

TQueue CreateQueue(const int size);
void DecreaseKey(TQueue* queue, const long long pathToParent, const TEdge edge);
TEdge Get(TQueue* queue);
void DestroyQueue(TQueue* queue);
