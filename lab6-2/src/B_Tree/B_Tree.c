#include "B_Tree.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

// static functions

static void CreateChildren(T_BNode* node, const int rank) {
    node->IsLeaf = false;
    node->Children = calloc(2 * rank, sizeof(T_BNode*));
    assert(node->Children);
}

static bool IsFull(T_BNode* node, const int rank) {
    return node->CountValues == 2 * rank - 1;
}

static int BinarySearch(T_BNode* node, const int value) {
    int left = 0, right = node->CountValues - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (value <= node->Values[mid]) {
            right = mid - 1;
        }
        if (value >= node->Values[mid]) {
            left = mid + 1;
        }
    }
    return right + 1;
}

static void MoveValueArrays(T_BNode *old, T_BNode *new, int indexOld, int indexNew) {
    int moveIndex = new->CountValues - indexNew;
    memmove(new->Values + indexNew, old->Values + indexOld, moveIndex * sizeof(int));
    if (!old->IsLeaf) {
        memmove(new->Children + indexNew, old->Children + indexOld, (moveIndex + 1) * sizeof(T_BNode*));
    }
}

static void Separation(T_BNode* parent, const int treeRank, const int moveIndex) {
    T_BNode* old = parent->Children[moveIndex];
    T_BNode* new = CreateNode(/*rank*/treeRank);

    if (!old->IsLeaf) {
        CreateChildren(/*node*/new, /*rank*/treeRank);
    }

    new->CountValues = treeRank - 1;
    MoveValueArrays(/*old*/old, /*new*/new, /*indexOld*/treeRank, /*indexNew*/0);
    old->CountValues = treeRank - 1;
    ++parent->CountValues;

    MoveValueArrays(/*old*/parent, /*new*/parent, /*indexOld*/moveIndex, /*indexNew*/moveIndex + 1);
    parent->Values[moveIndex] = old->Values[treeRank - 1];
    parent->Children[moveIndex + 1] = new;
}

static void InsertInNotFullNode(T_BNode* node, const int rank, const int value) {
    if (node->IsLeaf) {
        int index = BinarySearch(/*node*/node, /*value*/value);
        ++node->CountValues;
        MoveValueArrays(/*old*/node, /*new*/node, /*indexOld*/index, /*indexNew*/index + 1);
        node->Values[index] = value;
    } else {
        int childIndex = BinarySearch(/*node*/node, /*value*/value);
        if (IsFull(/*node*/node->Children[childIndex], /*rank*/rank)) {
            Separation(/*parent*/node, /*treeRank*/rank, /*moveIndex*/childIndex);
        }
        int newIndex = BinarySearch(/*node*/node, /*value*/value);
        InsertInNotFullNode(node->Children[newIndex], rank, value);
    }
}

// end static

T_BNode* CreateNode(const int rank) {
    T_BNode *node = malloc(sizeof(T_BNode));
    assert(node);

    node->CountValues = 0;
    node->IsLeaf = true;

    node->Values = calloc(2 * rank - 1, sizeof(int));
    assert(node->Values);

    node->Children = NULL;
    return node;
}

void Insert(T_BTree* tree, const int value) {
    if (IsFull(/*node*/tree->Root, /*rank*/tree->Rank)) {
        T_BNode *newRoot = CreateNode(/*rank*/tree->Rank);
        CreateChildren(/*node*/newRoot, /*rank*/tree->Rank);
        newRoot->Children[0] = tree->Root;
        Separation(/*parent*/newRoot, /*treeRank*/tree->Rank, /*moveIndex*/0);
        tree->Root = newRoot;
        ++tree->Height;
    }
    InsertInNotFullNode(/*node*/tree->Root, /*rank*/tree->Rank, /*value*/value);
}

void DestroyTree(T_BNode* root) {
    free(root->Values);
    if (root->IsLeaf) {
        free(root);
        return;
    } else {
        for (int i = 0; i <= root->CountValues; ++i) {
            DestroyTree(root->Children[i]);
        }
    }
    free(root->Children);
    free(root);
}
