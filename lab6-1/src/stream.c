#include <stdio.h>
#include <assert.h>
#include "stream.h"

TStream OpenStream(char* input, char* output) {
	TStream stream;
	stream.In = fopen(input, "r");
	stream.Out = fopen(output, "w");
	assert(stream.In != NULL);
	assert(stream.Out != NULL);
	return stream;
}

void CloseStream(TStream stream) {
	fclose(stream.In);
	fclose(stream.Out);
}

FILE* GetIn(TStream stream) {
	return stream.In;
}

FILE* GetOut(TStream stream) {
	return stream.Out;
}
