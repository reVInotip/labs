#include "stack.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

TStack CreateStack(const int size) {
    short* array = (short*)calloc(size, sizeof(short));
    assert(array);

    TStack stack = { .Array = array, .Index = size - 1, .Size = size };
	
    return stack;
}

void Push(TStack* stack, const short value) {
    if (stack->Index >= 0) {
        (stack->Array)[stack->Index] = value;
        --stack->Index;
    }
}

void PrintStack(TStack stack) {
    for (int i = 0; i < stack.Size; ++i) {
        printf("%d ", (stack.Array)[i] + 1);
    }
}

void DestroyStack(TStack* stack) {
    free(stack->Array);
    stack->Size = 0;
    stack->Index = 0;
}
