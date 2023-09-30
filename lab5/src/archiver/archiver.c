#include "internal_archiver.h"

// static functions

static long AddBitToCode(long currentCode, unsigned long bit) {
	return (currentCode << 1) | bit;
}

static void GenerateCharactersCodes(TCode* codes, unsigned int currentHeight, long currentCode, const MysticalTree* tree) {
	if (!((*tree)->Left) && !((*tree)->Right)) {
		codes[(unsigned int)(*tree)->Data].Height = currentHeight;
		codes[(unsigned int)(*tree)->Data].Code = currentCode;
		currentHeight -= 1;
		currentCode >>= 1;
		return;
	}
	GenerateCharactersCodes(codes, currentHeight + 1, AddBitToCode(/*code*/currentCode, /*bit*/0ul), &(*tree)->Left);
	GenerateCharactersCodes(codes, currentHeight + 1, AddBitToCode(/*code*/currentCode, /*bit*/1ul), &(*tree)->Right);
	currentHeight -= 1;
	currentCode >>= 1;
}

static void WriteCharacterSequence(TBitStream* fileOut, TBitStream* fileIn, const MysticalTree* tree) {
	if (fseek(fileIn->Stream, SHIFT, START)) {
		return;
	}
	TCode codes[ASCII_LENGTH];
	GenerateCharactersCodes(/*codes*/codes, /*currentHeight*/0, /*currentCode*/0ul, /*tree*/tree);
	TBuffer buffer = {
		.Character = 0, 
		.Length = 0
	};
	while (true) {
		int bit = ReadBit(/*file*/fileIn);
		if (bit == EOF) {
			return;
		}
		buffer.Character |= (bit != 0) << (BUF_SIZE - (buffer.Length + 1));
		++buffer.Length;
		if (buffer.Length == BUF_SIZE) {
			unsigned long code = codes[(unsigned int)buffer.Character].Code;
			unsigned int height = codes[(unsigned int)buffer.Character].Height;
			for (unsigned int i = 1; i <= height; ++i) {
				if (WriteBit(/*file*/fileOut, /*bit*/code & (1ul << (height - i))) == EOF) {
					return;
				}
			}
			buffer.Character = 0;
			buffer.Length = 0;
		}
	}
	return;
}

static _Bool WriteCountBytes(TBitStream* outputFile, const unsigned int countBytes) {
	if (fwrite(&countBytes, sizeof(int), 1, outputFile->Stream) != 1) {
		return true;
	}
	return false;
}

static void WriteTree(TBitStream* file, const MysticalTree* tree) {
    if (!((*tree)->Left) && !((*tree)->Right)) {
		if (WriteBit(/*file*/file, /*bit*/0) == EOF) {
			return;
		}
		for (int i = 7; i >= 0; --i) {
			char symbol = (*tree)->Data;
			if (WriteBit(/*file*/file, /*bit*/symbol & (1u << i)) == EOF) {
				return;
			}
		}
		return;
	}
	if (WriteBit(/*file*/file, /*bit*/1) == EOF) {
		return;
	}
	WriteTree(/*file*/file, /*tree*/&(*tree)->Left);
	WriteTree(/*file*/file, /*tree*/&(*tree)->Right);
}

static void FillTreeFromQueue(MysticalQueue* queueOfSymbols, MysticalTree* tree) {
	while (!OneElementLeft(*queueOfSymbols)) {
		MysticalQueue firstElement = Get(/*queue*/queueOfSymbols);
		MysticalQueue secondElement = Get(/*queue*/queueOfSymbols);
		MysticalTree rightTree = GetTree(/*queue*/firstElement);
		MysticalTree leftTree = GetTree(/*queue*/secondElement);
		MysticalTree currentTree = MakeTree(/*right*/rightTree, /*left*/leftTree);
		int currentPriority = GetPriority(/*queue*/firstElement) + 
			GetPriority(/*queue*/secondElement);
		Put(/*queue*/queueOfSymbols, /*priority*/currentPriority, /*tree*/currentTree);
		DestroyQueue(/*queue*/&firstElement);
		DestroyQueue(/*queue*/&secondElement);
	}
	*tree = GetTree(/*queue*/*queueOfSymbols);
}

static unsigned int ReadBitsForEncode(int* data, TBitStream* inputFile) {
	unsigned int bytes = 0;
	if (!inputFile->Stream) {
		printf("File reading error\n");
		return 0;
	}
	TBuffer buffer = {
		.Character = 0,
		.Length = 0
	};
	while (true) {
		int bit = ReadBit(/*file*/inputFile);
		if (bit == EOF) {
			break;
		}
		buffer.Character |= (bit != 0) << (BUF_SIZE - (buffer.Length + 1));
		++buffer.Length;
		if (buffer.Length == 8) {
			++data[(unsigned int)buffer.Character];
			++bytes;
			buffer.Character = 0;
			buffer.Length = 0;
		}
	}
	return bytes;
}

static bool IsEmpty(const int* array, const size_t length) {
	for (size_t i = 0; i < length; ++i) {
		if (array[i] != 0) {
			return false;
		}
	}
	return true;
}

// end static

void Archiver(TBitStream* inputFile, TBitStream* outputFile) {
	int countSymbols[ASCII_LENGTH] = {0};
	unsigned int countBytes = ReadBitsForEncode(/*data*/countSymbols, /*inputFile*/inputFile);
	if (IsEmpty(/*array*/countSymbols, /*length*/ASCII_LENGTH)) {
		return;
	}
	MysticalQueue queueOfSymbols = CreateQueue();
	FillQueueFromArray(/*queue*/&queueOfSymbols, /*array*/countSymbols, /*length*/ASCII_LENGTH);
	MysticalTree binaryTree = CreateTree();
	FillTreeFromQueue(/*queueOfSymbols*/&queueOfSymbols, /*tree*/&binaryTree);
	if (WriteCountBytes(/*file*/outputFile, /*countBytes*/countBytes)) {
		return;
	}
	WriteTree(/*file*/outputFile, /*tree*/&binaryTree);
	if ((binaryTree->Left) && (binaryTree->Right)) {
		WriteCharacterSequence(/*fileOut*/outputFile, /*fileIn*/inputFile, /*tree*/&binaryTree);
	}
	DestroyTree(/*tree*/&binaryTree);
	DestroyQueue(/*queue*/&queueOfSymbols);
}
