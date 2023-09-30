#pragma once
#include <stdlib.h>

enum {
    MAX_SAMPLE_LENGTH = 16,
    MAX_BUFFER_LENGTH = 512
};

typedef struct TString{
    int Begin, Length;
    unsigned char* Text;
} TString;

void InitString(TString* string, const size_t size);
void KMPMatcher(TString sample, TString text);
void DestroyString(TString* string);
