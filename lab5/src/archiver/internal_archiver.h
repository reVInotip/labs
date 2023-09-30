#pragma once
#include "../queue/queue.h"
#include "../tree/tree.h"
#include "../bitstream/bitstream.h"
#include <stdbool.h>
#include <stdio.h>

enum {
    SHIFT =  1,
    START =  0,
    BUF_SIZE =  8,
    ASCII_LENGTH = 256
};

typedef struct {
	unsigned int Height;
	unsigned long Code;
} TCode;

typedef struct {
	unsigned char Character;
	unsigned char Length;
} TBuffer;
