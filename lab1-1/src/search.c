#include <stdio.h>
#include "buffer.h"
#include "enter.h"
#include "search.h"
#define HASH_CONST 3

void Hash(
    const unsigned char* sample,
    const unsigned char* buffer,
    const int length,
    long int* bufferHash,
    long int* sampleHash
) {
    *sampleHash = sample[length - 1] % HASH_CONST;
    *bufferHash = buffer[length - 1] % HASH_CONST;
    for (int i = length - 2; i >= 0; --i) {
        *bufferHash = (*bufferHash * HASH_CONST) + (buffer[i] % HASH_CONST);
        *sampleHash = (*sampleHash * HASH_CONST) + (sample[i] % HASH_CONST);
    }
}

void StringComparison(
    const int length,
    const unsigned char* buffer,
    const unsigned char* sample,
    const int symbolIndex,
    const int currentIndex
) {
    for (int i = 0; i < length; ++i) {
        printf("%d ", symbolIndex + i);
        if (buffer[(currentIndex + i) % length] != sample[i]) {
            return;
        }
    }
}

void BinaryPow(long int* number, int degree) {
    long int pow = HASH_CONST;
    while (degree > 0) {
        if ((degree & 1) == 1) {
            *number *= pow;
            --degree;
        }
        pow *= pow;
        degree >>= 1;
    }
}

void Search(const unsigned char* sample, const int length) {
    unsigned char* buffer = CreateBuffer(/*bufferLength*/length);
    int nextChar = EnterBuffer(/*buffer*/buffer, /*bufferLength*/length);
    long int maxDegree = 1, sampleHash = 0, bufferHash = 0;

    Hash(/*sample*/sample, /*buffer*/buffer, /*length*/length,
        /*bufferHash*/&bufferHash, /*sampleHash*/&sampleHash);
    printf("%ld ", sampleHash);

    BinaryPow(/*number*/&maxDegree, /*degree*/length - 1);

    int symbolIndex = 1, currentIndex = 0;
    while (nextChar != '\0') {
        if (bufferHash == sampleHash) {
            StringComparison(/*length*/length, /*buffer*/buffer,
                    /*sample*/sample, /*symbolIndex*/symbolIndex,
                     /*currentIndex*/currentIndex);
        }
                
        nextChar = fgetc(stdin);
        if (nextChar == EOF) {
            break;
        }

        bufferHash = ((bufferHash - (buffer[currentIndex] % HASH_CONST)) / HASH_CONST) +
                ((nextChar % HASH_CONST) * maxDegree);
        buffer[currentIndex] = nextChar;
        currentIndex = (currentIndex + 1) % length;
        ++symbolIndex;
    }
    DestroyBuffer(/*buffer*/buffer);
}
