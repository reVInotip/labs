#include <stdio.h>
#include <string.h>
#include "enter.h"

int EnterSample(unsigned char* sample, const int count) {
    if (fgets((char*)sample, count + 1, stdin) == NULL) {
        return 0;
    }
    int countReadingElements = strlen((char*)sample);
    sample[countReadingElements - 1] = '\0';
    return countReadingElements - 1;
}

int EnterBuffer(unsigned char* buffer, const int bufferLength) {
    int countReadingElements = fread(buffer, sizeof(unsigned char), bufferLength, stdin);
    if (countReadingElements == 0) {
        return '\0';
    }
    return buffer[countReadingElements - 1];
}
