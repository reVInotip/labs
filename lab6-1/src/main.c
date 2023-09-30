#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "RBTree.h"
#include "stream.h"

unsigned char FillRBTree(TRBTree* RBTree, TStream currentStream) {
	int countTops = 0;
	if (!fscanf(GetIn(/*stream*/currentStream), "%d\n", &countTops)) {
		printf("bad input");
		return EXIT_SUCCESS;
	}
	TRBTree forest = CreateForest(/*length*/countTops);
	TRBTree oldForest = forest;
	while (countTops != 0) {
		int value = 0;
		if (!fscanf(GetIn(/*stream*/currentStream), "%d ", &value)) {
			break;
		}
		*RBTree = PushToRBTree(/*data*/value, /*RBTree*/RBTree, /*memory*/forest);
		forest = NextTree(/*forest*/forest);
		--countTops;
	}
	SetRootColor(/*RBTree*/*RBTree);
	unsigned char blackHeight = GetBlackHeight(/*RBTree*/*RBTree);
	free(oldForest);
	return blackHeight;
}

int main(void) {
	TStream stream = OpenStream(/*input*/"in.txt", /*output*/"out.txt");
	TRBTree RBTree = CreateRBTree();
	unsigned char height = FillRBTree(/*RBTree*/&RBTree, /*currentStream*/stream);
	fprintf(GetOut(/*stream*/stream), "%d", height);
	CloseStream(/*stream*/stream);
    return EXIT_SUCCESS;
}
