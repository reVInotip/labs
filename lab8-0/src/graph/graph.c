#include "graph.h"
#include "../dsu/dsu.h"
#include "../edges/edges.h"
#include <stdbool.h>

_Bool GraphIsConnected(TGraph graph, TDSU dsu) {
	int count = 0;
	for (int i = 0; i < graph.CountEdges; ++i) {
		int u = (graph.Edges)[i].EdgeStart;
		int v = (graph.Edges)[i].EdgeEnd;
		unsigned int setForU = Find(/*value*/u, /*dsu*/dsu);
		unsigned int setForV = Find(/*value*/v, /*dsu*/dsu);
		if (setForU != setForV) {
			++count;
			Unite(/*firstValue*/u, /*secondValue*/v, /*dsu*/dsu);
		}
	}
	return count == graph.CountVertices - 1;
}
