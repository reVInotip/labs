#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include "queue.h"
#include "../graph/graph.h"
#define Swap(type, a, b)\
do {\
	type tmp = a;\
	a = b; b = tmp;\
} while(0)

struct THeap {
	unsigned int MinPath;
	TEdge Edge;
};

// static

static void ShiftUp(TQueue* queue, int index) {
	if (index == 0) return;
	THeap* heap = queue->Heap;
	short* indexes = queue->Indexes;
	while (heap[index].MinPath < heap[(index - 1) / 2].MinPath) {
		Swap(/*type*/short,
			/*a*/indexes[(heap[index].Edge).Vertex],
			/*b*/indexes[(heap[(index - 1) / 2].Edge).Vertex]);
		Swap(/*type*/THeap, /*a*/heap[index], /*b*/heap[(index - 1) / 2]);
		index = (index - 1) / 2;
	}
}

static void SiftDown(TQueue* queue, int index) {
	THeap* heap = queue->Heap;
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
		Swap(/*type*/short, /*a*/indexes[(heap[index].Edge).Vertex], /*b*/indexes[(heap[j].Edge).Vertex]);
		Swap(/*type*/THeap, /*a*/heap[index], /*b*/heap[j]);
		index = j;
	}
}

static void Put(TQueue* queue, const unsigned int key, const TEdge edge) {
	assert(queue);
	THeap* heap = queue->Heap;
	short* indexes = queue->Indexes;
	++queue->HeapSize;
	heap[queue->HeapSize - 1].MinPath = key;
	heap[queue->HeapSize - 1].Edge = edge;
	indexes[queue->HeapSize - 1] = queue->HeapSize - 1;
	ShiftUp(/*queue*/queue, /*indexInHeap*/queue->HeapSize - 1);
}

// end static

TQueue CreateQueue(const int size) {
	THeap* heap = (THeap*)calloc(size, sizeof(THeap));
	assert(heap);
	short* indexes = (short*)calloc(size, sizeof(short));
	assert(indexes);

	TQueue queue = {
		.Heap = heap,
		.Indexes = indexes,
		.HeapSize = 0
	};

	for (int i = 0; i < size; ++i) {
		TEdge currentEdge = { .Parent = SHRT_MAX, .Vertex = i };
		Put(/*queue*/&queue, /*key*/UINT_MAX, /*edge*/currentEdge);
	}
	return queue;
}

void DecreaseKey(TQueue* queue, const unsigned int newKey, const TEdge edge) {
	assert(queue);
	int i = (queue->Indexes)[edge.Vertex];
	if (newKey < (queue->Heap)[i].MinPath) {
		(queue->Heap)[i].MinPath = newKey;
		((queue->Heap)[i].Edge).Parent = edge.Parent;
		ShiftUp(/*queue*/queue, /*index*/i);
	}
}


TEdge Get(TQueue* queue) {
	assert(queue);
	THeap* heap = queue->Heap;
	short* indexes = queue->Indexes;
	TEdge min = heap[0].Edge;
	int minVertex = (int)((heap[0]).Edge).Vertex;
	int maxVertex = (int)((heap[queue->HeapSize - 1]).Edge).Vertex;
	indexes[maxVertex] = indexes[minVertex];
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
