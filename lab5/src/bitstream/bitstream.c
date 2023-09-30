#include "bitstream.h"
#include <stdio.h>

int ReadBit(TBitStream* file) {
    if (file->Count == 8) {
		if (fread(&file->Buffer, sizeof(char), 1, file->Stream) != 1) {
			return EOF;
		}
		file->Count = 0;
	}
	int bit = (file->Buffer) & (1u << (7 - file->Count));
	++file->Count;
	return bit;
}

int WriteBit(TBitStream* file, const unsigned int bit) {
	if (file->Count == 8) {
	    if (fwrite(&file->Buffer, sizeof(char), 1, file->Stream) != 1) {
			return EOF;
		}
		file->Count = 0;
		file->Buffer = 0;
	}
	file->Buffer |= (bit != 0) <<  (7 - file->Count);
	++file->Count;
	return 0;
}


int CloseBitStream(TBitStream* file) {
	int isEror = 0;
	if (file->Stream) {
		if (file->Count != 0) {
			isEror = fwrite(&file->Buffer, sizeof(char), 1, file->Stream);
		}
		fclose(file->Stream);
	}
	file->Count = 0;
	file->Buffer = 0;
	return isEror;
}
