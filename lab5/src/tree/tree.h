#pragma once

typedef struct MysticalTree {
	struct MysticalTree* Left;
	struct MysticalTree* Right;
	unsigned char Data;
}* MysticalTree;

MysticalTree CreateTree();
MysticalTree MakeLeaf(const unsigned char symbol);
MysticalTree MakeTree(const MysticalTree right, const MysticalTree left);
void DestroyTree(MysticalTree* tree);
