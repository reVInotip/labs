#include <stdio.h>
#include "read.h"
#define MAX_LENGTH 1001

int ReadArithmExpression(char* arithmExpression) {
    int countReadingElements = fread(arithmExpression, sizeof(char), MAX_LENGTH, stdin);
    if (countReadingElements - 1 == 0) {
        return 0;
    }
    arithmExpression[countReadingElements - 1] = '\0';
    return countReadingElements;
}
