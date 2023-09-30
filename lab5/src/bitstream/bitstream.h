#pragma once 
#include <stdio.h>

typedef struct {
    FILE* Stream;
    unsigned int Count;
    unsigned char Buffer;
} TBitStream;

int ReadBit(TBitStream* file);
int WriteBit(TBitStream* file, const unsigned int bit);
int CloseBitStream(TBitStream* file);
