#pragma once

typedef struct TStream {
	FILE* In;
	FILE* Out;
} TStream;

TStream OpenStream(char* input, char* output);
void CloseStream(TStream stream);
FILE* GetIn(TStream stream);
FILE* GetOut(TStream stream);
