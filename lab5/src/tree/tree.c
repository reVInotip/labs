#include "tree.h"
#include <stdlib.h>
#include <assert.h>

MysticalTree CreateTree() {
	return NULL;
}

MysticalTree MakeLeaf(const unsigned char symbol) {
	MysticalTree leaf = malloc(sizeof(struct MysticalTree));
	assert(leaf != NULL);
	leaf->Data = symbol;
	leaf->Left = NULL;
	leaf->Right = NULL;
	return leaf;
}

MysticalTree MakeTree(const MysticalTree rightTree, const MysticalTree leftTree) {
	assert(rightTree != NULL);
	assert(leftTree != NULL);
	MysticalTree currentTree = MakeLeaf(/*symbol*/'\0');
	currentTree->Left = leftTree;
	currentTree->Right = rightTree;
	return currentTree;
}

void DestroyTree(MysticalTree* tree) {
	assert(tree != NULL);
	if (*tree == NULL) {
		return;
	}
	DestroyTree(&((*tree)->Left));
	DestroyTree(&((*tree)->Right));
	free(*tree);
	*tree = NULL;
}
