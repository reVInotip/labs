#pragma once
#include <stdbool.h>

typedef struct T_BNode {
    int* Values;
    struct T_BNode** Children;
    int CountValues;
    bool IsLeaf;
} T_BNode;

typedef struct T_BTree {
    int Rank, Height;
    T_BNode* Root;
} T_BTree;

T_BNode* CreateNode(const int rank);
void Insert(T_BTree* tree, const int value);
void DestroyTree(T_BNode* root);
