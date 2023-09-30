#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma once

typedef struct TRBTree* TRBTree;

TRBTree CreateRBTree(void);
TRBTree PushToRBTree(const int data, TRBTree* RBTree, TRBTree memory);
unsigned char GetBlackHeight(TRBTree RBTree);
void SetRootColor(TRBTree RBTree);
TRBTree CreateForest(const int length);
TRBTree NextTree(const TRBTree forest);
