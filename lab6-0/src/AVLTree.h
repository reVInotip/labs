#pragma once

typedef struct TAVLTree{
	int Number;
	unsigned char Height;
	struct TAVLTree* LeftTree;
	struct TAVLTree* RightTree;
}* TAVLTree;

TAVLTree CreateAVLTree(void);
TAVLTree PushToAVLTree(const int data, TAVLTree* AVLTree, TAVLTree* memory);
unsigned char GetHeight(const TAVLTree* AVLTree);
