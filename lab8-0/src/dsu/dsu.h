#pragma once

typedef struct TDSU {
	unsigned int* Tree;
} TDSU;

TDSU CreateDSU(unsigned int count);
void MakeSet(unsigned int value, TDSU dsu);
unsigned int Find(unsigned int value, TDSU dsu);
void Unite(unsigned int firstValue, unsigned int secondValue, TDSU dsu);
void DestroyDSU(TDSU dsu);
