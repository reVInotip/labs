#include "../queue/queue.h"
#include "../tree/tree.h"
#include "../bitstream/bitstream.h"
#include "unarchiver.h"
#include <stdio.h>

// static functions

static unsigned char ReadCharacter(TBitStream* file) {
	unsigned char character = 0;
	for (char i = 7; i >= 0; --i) {
		int bit = ReadBit(/*file*/file);
		if (bit == EOF) {
			return 0;
		}
		character |= (bit != 0) << i;
	}
	return character;
}

static MysticalTree ReadEncodingTree(TBitStream* inputFile) {
	if (inputFile->Stream == NULL) {
		printf("File reading error");
		return NULL;
	}
	int bit = ReadBit(/*file*/inputFile);
	if (bit == EOF) {
		return NULL;
	} else if (bit == 0) {
		unsigned char character = ReadCharacter(/*file*/inputFile);
		return MakeLeaf(/*symbol*/character);
	}
	MysticalTree left = ReadEncodingTree(inputFile);
	MysticalTree right = ReadEncodingTree(inputFile);
	return MakeTree(/*rightTree*/right, /*leftTree*/left);
}

static void WriteBitsForDecode(TBitStream* fileIn, TBitStream* fileOut, MysticalTree encodingTree, unsigned int count) {
	if (fileOut->Stream == NULL) {
		printf("File writing error");
		return;
	}
	if (!(encodingTree->Left) && !(encodingTree->Right)) {
		for (unsigned int i = 0; i < count; ++i) {
			if (fwrite(&(encodingTree->Data), sizeof(char), 1, fileOut->Stream) != 1) {
				break;
			}
		}
		return;
	}
	MysticalTree copy = encodingTree;
	unsigned int currentCount = 0;
	while(true) {
		if (currentCount == count) {
			break;
		}
		int bit = ReadBit(/*file*/fileIn);
		if (!(copy->Left) && !(copy->Right)) {
			unsigned char character = copy->Data;
			if (fwrite(&character, sizeof(char), 1, fileOut->Stream) != 1) {
				break;
			}
			copy = encodingTree;
			++currentCount;
		}
		if (bit == EOF) {
			continue;
		} else if (bit == 0) {
			copy = copy->Left ? copy->Left : copy;
		} else {
			copy = copy->Right ? copy->Right : copy;
		}
	}
}

// end static

void Unarchiver(TBitStream* inputFile, TBitStream* outputFile) {
	unsigned int countCharatersInOrginalFile = 0;
	if (fread(&countCharatersInOrginalFile, sizeof(int), 1, inputFile->Stream) != 1) {
		return;
	}
	MysticalTree encodingTree = ReadEncodingTree(/*inputFile*/inputFile);
	if (!encodingTree) {
		return;
	}
	WriteBitsForDecode(/*fileIn*/inputFile,
			/*fileOut*/outputFile,
			/*encodingTree*/encodingTree, 
			/*count*/countCharatersInOrginalFile);
	DestroyTree(/*tree*/&encodingTree);
}
