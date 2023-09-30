#pragma once

typedef struct TStack {
    short* Array;
    int Index;
    int Size;
} TStack;

TStack CreateStack(const int size);
void Push(TStack* stack, const short value);
void PrintStack(TStack stack);
void DestroyStack(TStack* stack);
