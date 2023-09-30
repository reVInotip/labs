#include "B_Tree/B_Tree.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    int treePow = 0, countValues = 0, value = 0;

    if (scanf("%d %d", &treePow, &countValues) != 2) {
        printf("error in input\n");
        return EXIT_FAILURE;
    }

    T_BNode* root = CreateNode(/*rank*/treePow);
    T_BTree BTree = { .Rank = treePow, .Height = 0, .Root = root };

    for (int i = 0; i < countValues; ++i) {
        if (scanf("%d", &value) != 1) {
            DestroyTree(/*root*/BTree.Root);
            return EXIT_FAILURE;
        }

        Insert(/*tree*/&BTree, /*value*/value);
    }

    printf("%d\n", BTree.Height + (int)(countValues != 0));

    DestroyTree(/*root*/BTree.Root);

    return EXIT_SUCCESS;
}
