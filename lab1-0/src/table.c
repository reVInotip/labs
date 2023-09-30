#include <stdbool.h>
#include "table.h"
table CreateTable(int baseValue) {
    table array;
    array.Len = 256;
    array.basicValue = baseValue;
    for (int i = 0; i < array.Len; ++i) {
        array.Data[i] = baseValue;
    }
    return array;
}

void PushPair(table* array, unsigned char first, int second) {
    array->Data[first] = second;
}

char GetElementByKey(const table* array, unsigned char key) {
    return array->Data[key];
}

_Bool IsPairInTable(const table* array, unsigned char key) {
    if (array->Data[key] == array->basicValue) {
        return false;
    }
    return true;
}
