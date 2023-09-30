#include "KMP/KMP.h"
#include <stdio.h>
#include <stdlib.h>

void EnterSample(TString* string) {
    unsigned char symbol = '\0';
    int countSymbols = 0;
    while (fread(&symbol, sizeof(char), 1, stdin)) {
        if (countSymbols > MAX_SAMPLE_LENGTH) {
            printf("bad sample length");
            return;
        } else if (symbol == '\n' || symbol == '\0') {
            return;
        }
		
        ++countSymbols;
        string->Text[countSymbols - 1] = symbol;
        string->Length = countSymbols;
    }
}

void EnterText(TString* string, const size_t count) {
    string->Length = fread(string->Text, sizeof(char), count, stdin);
    string->Begin = 0;
}

int main(void)	{
    TString sample, text;
    InitString(/*string*/&sample, /*size*/MAX_SAMPLE_LENGTH);
    InitString(/*string*/&text, /*size*/MAX_BUFFER_LENGTH);

    EnterSample(/*string*/&sample);
    EnterText(/*string*/&text, /*count*/MAX_BUFFER_LENGTH);

    KMPMatcher(/*sample*/sample, /*text*/text);
	
    DestroyString(/*string*/&sample);
    DestroyString(/*string*/&text);

    return EXIT_SUCCESS;
}
