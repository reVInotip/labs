#include <stdlib.h>
#include <stdio.h>
#include "AVLTree.h"
#include "stream.h"

unsigned char FillAVLTree(TAVLTree* AVLTree, TStream currentStream) {
	int countTops = 0;
	if (!fscanf(GetIn(/*stream*/currentStream), "%d\n", &countTops)) {
		printf("bad input");
		return EXIT_SUCCESS;
	}
	TAVLTree forest = (TAVLTree)malloc(sizeof(struct TAVLTree) * countTops);
	TAVLTree oldForest = forest;
	while (countTops != 0) {
		int value = 0;
		if (!fscanf(GetIn(/*stream*/currentStream), "%d ", &value)) {
			break;
		}
		*AVLTree = PushToAVLTree(/*data*/value, /*AVLTree*/AVLTree, /*memory*/&forest);
		++forest;
		--countTops;
	}
	unsigned char height = GetHeight(/*AVLTree*/AVLTree);
	free(oldForest);
	return height;
}

int main(void) {
	TStream stream = OpenStream(/*input*/"in.txt", /*output*/"out.txt");
	TAVLTree AVLTree = CreateAVLTree();
	unsigned char height = FillAVLTree(/*AVLTree*/&AVLTree, /*currentStream*/stream);
	fprintf(GetOut(/*stream*/stream), "%d", height);
	CloseStream(/*stream*/stream);
    return EXIT_SUCCESS;
}
