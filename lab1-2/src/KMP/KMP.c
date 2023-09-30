#include "KMP.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// static functions

static int* CreateShiftTable(const size_t size) {
    int* table = (int*)calloc(size, sizeof(int));
    assert(table);

    return table;
}

static void DestroyShiftTable(int* shiftTable) {
    free(shiftTable);
}

static void PrefixFunction(int* shiftTable, const TString sample) {
    for (int i = 1; i < sample.Length; ++i){
        int j = shiftTable[i - 1];
        while (j > 0 && sample.Text[i] != sample.Text[j]) {
            j = shiftTable[j - 1];
        }

        if (sample.Text[i] == sample.Text[j]) {
            ++j;
        }

        shiftTable[i] = j;
    }
}

static bool ShiftBuffer(TString* buffer, int sampleLength, int shift) {
    if (buffer->Begin + sampleLength + shift > buffer->Length) {
        int shiftedBufferSize = buffer->Length - buffer->Begin - shift;
        for (int i = 0; i < shiftedBufferSize; ++i) {
            buffer->Text[i] = buffer->Text[buffer->Begin + shift + i];
        }
		
        int currentBufferSize = fread(buffer->Text + shiftedBufferSize, sizeof(char),
            MAX_BUFFER_LENGTH - shiftedBufferSize, stdin);
        buffer->Length = shiftedBufferSize + currentBufferSize;
        buffer->Begin = 0;
        return (buffer->Length > sampleLength);
    }

    buffer->Begin += shift;
    return true;
}

static void PrintShiftTable(int* shiftTable, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        printf("%d ", shiftTable[i]);
    }
}

// end static

void InitString(TString* string, const size_t size) {
    unsigned char* text = (unsigned char*)calloc(size, sizeof(unsigned char));
    assert(text);

    string->Begin = 0;
    string->Length = 0;
    string->Text = text;
}

void KMPMatcher(TString sample, TString text) {
    int* shiftTable = CreateShiftTable(/*size*/MAX_SAMPLE_LENGTH);
    PrefixFunction(/*shiftTable*/shiftTable, /*sample*/sample);
    PrintShiftTable(/*shiftTable*/shiftTable, /*length*/sample.Length);

    if (text.Length < sample.Length) {
        DestroyShiftTable(/*shiftTable*/shiftTable);
        return;
    }

    int position = 1;

    while (true) {
        // find all equal elemtns in sample and current buffer
        int countEqualSymbols = 0;
        while (countEqualSymbols < sample.Length &&
               sample.Text[countEqualSymbols] == text.Text[text.Begin + countEqualSymbols]) {
            ++countEqualSymbols;
        }
		
        // calculate shift
        int shift = 1;
        if (countEqualSymbols != 0) {
            shift = countEqualSymbols - shiftTable[countEqualSymbols - 1];
            printf("%d %d ", position, countEqualSymbols);
        }
		
        position += shift;
        if (!ShiftBuffer(/*buffer*/&text, /*sampleLength*/sample.Length, /*shift*/shift)) {
            break;
        }
    }

    DestroyShiftTable(/*shiftTable*/shiftTable);
}

void DestroyString(TString* string) {
    free(string->Text);
    string->Length = 0;
    string->Begin = 0;
}
