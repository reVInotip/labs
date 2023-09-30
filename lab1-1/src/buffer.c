#include <stdlib.h>
#include <assert.h>
#include "buffer.h"

unsigned char* CreateBuffer(int bufferLength) {
    unsigned char* ptr = malloc(sizeof(unsigned char) * bufferLength);
    assert(ptr != NULL);
    return ptr;
}

void DestroyBuffer(unsigned char* buffer) {
    free(buffer);
}
