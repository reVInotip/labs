#include "dsu.h"
#include <stdlib.h>
#include <assert.h>

TDSU CreateDSU(unsigned int count) {
	unsigned int* tree = (unsigned int*)calloc(count, sizeof(int));
	assert(tree);
	TDSU dsu = {tree};
	return dsu;
}

void MakeSet(unsigned int value, TDSU dsu) {
	dsu.Tree[value] = value;
}

unsigned int Find(unsigned int value, TDSU dsu) {
	if (dsu.Tree[value] == value){
		return value;
	}
	return dsu.Tree[value] = Find(dsu.Tree[value], dsu);
}

void Unite(unsigned int firstValue, unsigned int secondValue, TDSU dsu) {
	unsigned int first = Find(/*value*/firstValue, /*dsu*/dsu);
	unsigned int second = Find(/*value*/secondValue, /*dsu*/dsu);
	srand(1256);
	if (rand() % 2 == 0) {
		dsu.Tree[first] = second;
	} else {
		dsu.Tree[second] = first;
	}
}

void DestroyDSU(TDSU dsu) {
	assert(dsu.Tree);
	free(dsu.Tree);
}
