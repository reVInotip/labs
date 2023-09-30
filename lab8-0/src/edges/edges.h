#pragma once

typedef struct TEdges {
	unsigned int EdgeLength;
	int EdgeStart;
	int EdgeEnd;
} TEdges;

TEdges* CreateEdges(const int count);
void DestroyEdges(TEdges* edges);
