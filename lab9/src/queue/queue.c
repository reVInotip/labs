#include "../graph/graph.h"
#include "queue.h"
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#define Swap(type, a, b)\
do {\
    type tmp = a;\
    a = b;\
    b = tmp;\
} while(0)

// static functions

static void ShiftUp(TQueue* queue, int index) {
	if (index == 0) {
		return;
	}
	TEdge* heap = queue->Heap;
	short* indexes = queue->Indexes;
	while (heap[index].MinPath < heap[(index - 1) / 2].MinPath) {
		Swap(/*type*/short,
			/*a*/indexes[heap[index].Vertex],
			/*b*/indexes[heap[(index - 1) / 2].Vertex]);
		Swap(/*type*/TEdge, /*a*/heap[index], /*b*/heap[(index - 1) / 2]);
		index = (index - 1) / 2;
	}
}

static void SiftDown(TQueue* queue, int index) {
	TEdge* heap = queue->Heap;
	short* indexes = queue->Indexes;
	while (2 * index + 1 < queue->HeapSize) {
		int leftHeap = 2 * index + 1;
		int rightHeap = 2 * index + 2;
		int j = leftHeap;
		if ((rightHeap < queue->HeapSize) && (heap[rightHeap].MinPath < heap[leftHeap].MinPath)) {
			j = rightHeap;
		}
		if (heap[index].MinPath <= heap[j].MinPath) {
			break;
		}
		Swap(/*type*/short, /*a*/indexes[heap[index].Vertex], /*b*/indexes[heap[j].Vertex]);
		Swap(/*type*/TEdge, /*a*/heap[index], /*b*/heap[j]);
		index = j;
	}
}

static void Put(TQueue* queue, const TEdge edge) {
	assert(queue);
	TEdge* heap = queue->Heap;
	short* indexes = queue->Indexes;
	++queue->HeapSize;
	heap[queue->HeapSize - 1] = edge;
	indexes[queue->HeapSize - 1] = queue->HeapSize - 1;
	ShiftUp(/*queue*/queue, /*indexInHeap*/queue->HeapSize - 1);
}

// end static

TQueue CreateQueue(const int size) {
	TEdge* heap = (TEdge*)calloc(size, sizeof(TEdge));
	assert(heap);
	short* indexes = (short*)calloc(size, sizeof(short));
	assert(indexes);

	TQueue queue = {
		.Heap = heap,
		.Indexes = indexes,
		.HeapSize = 0
	};

	for (int i = 0; i < size; ++i) {
		TEdge currentEdge = { .MinPath = LLONG_MAX, .Parent = SHRT_MAX, .Vertex = i };
		Put(/*queue*/&queue, /*edge*/currentEdge);
	}
	return queue;
}

void DecreaseKey(TQueue* queue, const long long pathToParent, const TEdge edge) {
	assert(queue);
	int i = (queue->Indexes)[edge.Vertex];
	if (i == SHRT_MAX) {
		return;
	}
	if ((queue->Heap[i]).MinPath > pathToParent + edge.MinPath) {
		(queue->Heap[i]).MinPath = pathToParent + edge.MinPath;
		(queue->Heap[i]).Parent = edge.Parent;
		ShiftUp(/*queue*/queue, /*index*/i);
	}
}


TEdge Get(TQueue* queue) {
	assert(queue);
	TEdge* heap = queue->Heap;
	short* indexes = queue->Indexes;
	TEdge min = heap[0];
	int minVertex = (int)(heap[0]).Vertex;
	int maxVertex = (int)(heap[queue->HeapSize - 1]).Vertex;
	indexes[maxVertex] = indexes[minVertex];
	indexes[minVertex] = SHRT_MAX;
	heap[0] = heap[queue->HeapSize - 1];
	--queue->HeapSize;
	SiftDown(/*queue*/queue, /*index*/0);
	return min;
}

void DestroyQueue(TQueue* queue) {
	assert(queue);
	queue->HeapSize = 0;
	free(queue->Heap);
	free(queue->Indexes);
}
