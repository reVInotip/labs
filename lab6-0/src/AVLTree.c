#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "AVLTree.h"

// static functions
static TAVLTree CreateLeaf(const int value, const unsigned char currentHeight, TAVLTree* mem) {
	assert(mem != NULL);
	assert(*mem != NULL);
	(*mem)->Number = value;
	(*mem)->Height = currentHeight;
	(*mem)->LeftTree = NULL;
	(*mem)->RightTree = NULL;
	return *mem;
}

static int DifferenceBeweenNodes(TAVLTree* AVLTree) {
	assert(AVLTree != NULL);
	assert(*AVLTree != NULL);
	return GetHeight(/*AVLTree*/&(*AVLTree)->LeftTree) - 
		GetHeight(/*AVLTree*/&(*AVLTree)->RightTree);
}

static void FixHeight(TAVLTree* AVLTree) {
	assert(AVLTree != NULL);
	assert(*AVLTree != NULL);
	unsigned char leftHeight = GetHeight(/*AVLTree*/&(*AVLTree)->LeftTree);
	unsigned char rightHeight = GetHeight(/*AVLTree*/&(*AVLTree)->RightTree);
	(*AVLTree)->Height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

static bool IsBalance(TAVLTree* AVLTree) {
	assert(AVLTree != NULL);
	char dif = DifferenceBeweenNodes(/*AVLTree*/AVLTree);
	if (dif == 1 || dif == 0 || dif == -1) {
		return true;
	}
	return false;
}

static TAVLTree RotateLeft(TAVLTree* AVLTree) {
	TAVLTree rightTree = (*AVLTree)->RightTree;
	(*AVLTree)->RightTree = rightTree->LeftTree;
	rightTree->LeftTree = *AVLTree;
	FixHeight(/*AVLTree*/AVLTree);
	FixHeight(/*AVLTree*/&rightTree);
	return rightTree;
}

static TAVLTree RotateRight(TAVLTree* AVLTree) {
	TAVLTree leftTree = (*AVLTree)->LeftTree;
	(*AVLTree)->LeftTree = leftTree->RightTree;
	leftTree->RightTree = *AVLTree;
	FixHeight(/*AVLTree*/AVLTree);
	FixHeight(/*AVLTree*/&leftTree);
	return leftTree;
}

static void BalanceAVLTree(TAVLTree* AVLTree) {
	assert(AVLTree != NULL);
	if (IsBalance(/*AVLTree*/AVLTree)) {
		FixHeight(/*AVLTree*/AVLTree);
		return;
	}
	if (DifferenceBeweenNodes(/*AVLTree*/AVLTree) > 0) {
		TAVLTree leftTree = (*AVLTree)->LeftTree;
		if (DifferenceBeweenNodes(/*AVLTree*/&leftTree) < 0) {
			(*AVLTree)->LeftTree = RotateLeft(/*AVLTree*/&leftTree);
		}
		*AVLTree = RotateRight(/*AVLTree*/AVLTree);
	} else {
		TAVLTree rightTree = (*AVLTree)->RightTree;
		if (DifferenceBeweenNodes(/*AVLTree*/&rightTree) > 0) {
			(*AVLTree)->RightTree = RotateRight(/*AVLTree*/&rightTree);
		}
		*AVLTree = RotateLeft(/*AVLTree*/AVLTree);
	}
}
// end static

TAVLTree CreateAVLTree(void) {
	return NULL;
}

unsigned char GetHeight(const TAVLTree* AVLTree) {
	assert(AVLTree != NULL);
	return (*AVLTree == NULL) ? 0 : (*AVLTree)->Height;
}

TAVLTree PushToAVLTree(const int data, TAVLTree* AVLTree, TAVLTree* memory) {
	assert(AVLTree != NULL);
	if (*AVLTree == NULL) {
		TAVLTree leaf = CreateLeaf(/*value*/data, /*currentHeight*/1, /*mem*/memory);
		return leaf;
	}
	if ((*AVLTree)->Number > data) {
		(*AVLTree)->LeftTree = PushToAVLTree(data, &(*AVLTree)->LeftTree, memory);
	} else {
		(*AVLTree)->RightTree = PushToAVLTree(data, &(*AVLTree)->RightTree, memory);
	}
	BalanceAVLTree(/*AVLTree*/AVLTree);
	return *AVLTree;
}
