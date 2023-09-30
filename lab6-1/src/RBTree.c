#include "RBTree.h"

struct TRBTree {
	struct TRBTree* LeftTree;
	struct TRBTree* RightTree;
    int Number;
	unsigned char Color;
};

// static functions
static TRBTree CreateLeaf(const int value, TRBTree mem) {
	assert(mem);
	mem->Number = value;
	mem->Color = 'r';
	mem->LeftTree = NULL;
	mem->RightTree = NULL;
	return mem;
}

static TRBTree RotateLeft(TRBTree RBTree) {
	TRBTree rightTree = RBTree->RightTree;
	rightTree->Color = RBTree->Color;
	RBTree->Color = 'r';
	RBTree->RightTree = rightTree->LeftTree;
	rightTree->LeftTree = RBTree;
	return rightTree;
}

static TRBTree RotateRight(TRBTree RBTree) {
	TRBTree leftTree = RBTree->LeftTree;
	leftTree->Color = RBTree->Color;
	RBTree->Color = 'r';
	RBTree->LeftTree = leftTree->RightTree;
	leftTree->RightTree = RBTree;
	return leftTree;
}

static bool NodeIsRed(TRBTree RBTree) {
	if (!RBTree) {
		return false;
	}
	return RBTree->Color == 'r';
}

static void BalanceRBTree(TRBTree* RBTree) {
	// Left Case
	if (NodeIsRed(/*RBTree*/(*RBTree)->LeftTree)) {
		if (NodeIsRed(/*RBTree*/(*RBTree)->RightTree)) {
			if (
				NodeIsRed(/*RBTree*/((*RBTree)->LeftTree)->LeftTree) ||
				NodeIsRed(/*RBTree*/((*RBTree)->LeftTree)->RightTree)
			) {
				((*RBTree)->LeftTree)->Color = 'b';
				((*RBTree)->RightTree)->Color = 'b';
				(*RBTree)->Color = 'r';
			}
		} else {
			if (NodeIsRed(/*RBTree*/((*RBTree)->LeftTree)->RightTree)) {
				(*RBTree)->LeftTree = RotateLeft(/*RBTree*/(*RBTree)->LeftTree);
			}
			*RBTree = RotateRight(/*RBTree*/*RBTree);
		}
	}
	// Right Case
	if (NodeIsRed(/*RBTree*/(*RBTree)->RightTree)) {
		if (NodeIsRed((*RBTree)->LeftTree)) {
			if (
				NodeIsRed(/*RBTree*/((*RBTree)->RightTree)->LeftTree) ||
				NodeIsRed(/*RBTree*/((*RBTree)->RightTree)->RightTree)
			) {
				((*RBTree)->RightTree)->Color = 'b';
				((*RBTree)->LeftTree)->Color = 'b';
				(*RBTree)->Color = 'r';
			}
		} else {
			if (NodeIsRed(/*RBTree*/((*RBTree)->RightTree)->LeftTree)) {
				(*RBTree)->RightTree = RotateRight(/*RBTree*/(*RBTree)->RightTree);
			}
			*RBTree = RotateLeft(/*RBTree*/*RBTree);
		}
	}
}
// end static

TRBTree CreateRBTree(void) {
	return NULL;
}

TRBTree PushToRBTree(const int data, TRBTree* RBTree, TRBTree memory) {
	assert(RBTree);
	if (!*RBTree) {
		TRBTree leaf = CreateLeaf(/*value*/data, /*mem*/memory);
		return leaf;
	}
	if ((*RBTree)->Number > data) {
		(*RBTree)->LeftTree = PushToRBTree(data, &(*RBTree)->LeftTree, memory);
	} else {
		(*RBTree)->RightTree = PushToRBTree(data, &(*RBTree)->RightTree, memory);
	}
	BalanceRBTree(/*RBTree*/RBTree);
	return *RBTree;
}

void SetRootColor(TRBTree RBTree) {
	if (!RBTree) {
		return;
	}
	RBTree->Color = 'b';
}

TRBTree CreateForest(const int length) {
	TRBTree currentForest = (TRBTree)malloc(sizeof(struct TRBTree) * length);
	assert(currentForest);
	return currentForest;
}

TRBTree NextTree(const TRBTree forest) {
	return forest + 1;
}

unsigned char GetBlackHeight(TRBTree RBTree) {
	if (!RBTree) {
		return 0;
	}
	unsigned blackHeight = 1;
	while (RBTree) {
		blackHeight += RBTree->Color == 'b' ? 1 : 0;
		RBTree = RBTree->LeftTree;
	}
	return blackHeight;
}
