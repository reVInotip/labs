#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "table.h"
#define MAX_SIZE 17

void CreateShiftTable(const char *sample, const int length, table *shifts) {
        int shiftForLetter = 0;
        for (int i = length - 2; i >= 0; --i) {
                ++shiftForLetter;
                if (IsPairInTable(/*array*/shifts, /*key*/sample[i])) {
                        continue;
                }
                PushPair(/*array*/shifts, /*first*/sample[i], /*second*/shiftForLetter);
        }
        if (!IsPairInTable(/*array*/shifts, /*key*/sample[length - 1])) {
                PushPair(/*array*/shifts, /*first*/sample[length - 1], length);
        }
}

int FindSampleInText(const char *sample, const char *buffer, const int length, int index) {
        int k = 0, currentIndex = 0;
        bool isStart = index == length - 1;
        for (int i = length - 1; i >= 0; --i) {
                if (isStart) {
                        isStart = false;
                }
                else {
                        printf(" ");
                }
                printf("%d", index - k + 1);
                if (sample[i] != buffer[i]) {
                        currentIndex = i;
                        break;
                }
                k = i == 0 ? k : k + 1;
        }
        return currentIndex + k;
}

void RemovePrefix(char *buffer, int count, int lenBuffer) {
        int j = 0;
        for (int i = count; i < lenBuffer; ++i) {
                buffer[j] = buffer[i];
                ++j;
        }
}

int main(void) {
        char sample[MAX_SIZE];
        int k = 0;
        while (scanf("%c", &sample[k]) == 1) {
                if (sample[k] == '\n') {
                        sample[k] = '\0';
                        break;
                }
                ++k;
                if (k == MAX_SIZE) {
                        return 0;
                }
        }
        const int sampleLength = strlen(sample);
        table shifts = CreateTable(/*baseValue*/sampleLength);
        CreateShiftTable(/*string*/sample,
                        /*length*/sampleLength,
                        /*shifts*/&shifts);
        char buffer[sampleLength];
        int countElementsForReading = sampleLength, index = sampleLength - 1;
        while (true) {
                const int currentTextLength = fread(&buffer[sampleLength - countElementsForReading],
                                sizeof(unsigned char), countElementsForReading, stdin);
                if (currentTextLength < countElementsForReading) {
                        return 0;
                }
                int indexForShift = FindSampleInText(/*sample*/sample,
                                /*buffer*/buffer,
                                /*length*/sampleLength,
                                /*index*/index);
                countElementsForReading = GetElementByKey(/*array*/&shifts,
                                /*key*/buffer[indexForShift]);
                //отрицательных значений здесь быть не может
                RemovePrefix(/*buffer*/buffer,
                                /*count*/countElementsForReading,
                                /*lenBuffer*/sampleLength);
                index = countElementsForReading + index;
        }
        return 0;
}

