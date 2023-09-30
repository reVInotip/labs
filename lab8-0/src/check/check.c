#include "check.h"
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

_Bool IsBadNumber(const char count) {
	if (count < 3) {
		printf("bad number of lines");
		return true;
	}
	return false;
}

_Bool IsBadVertex(const int start, const int end, const int count) {
	if ((start < 0 || start > count) || (end < 0 || end > count)) {
		printf("bad vertex");
		return true;
	}
	return false;
}

_Bool IsBadLength(const long int len) {
	if (len < 0 || len > INT_MAX) {
		printf("bad length");
		return true;
	}
	return false;
}

_Bool IsBadInput(const char count) {
	if (count < 2) {
		printf("bad input");
		return true;
	}
	return false;
}

_Bool IsBadCountVertices(const int count) {
	if (count < 0 || count > 5000) {
		printf("bad number of vertices");
		return true;
	}
	return false;
}

_Bool IsBadCountEdges(const int count, const int EDGES_MAX) {
	if (count < 0 || count > EDGES_MAX) {
		printf("bad number of edges");
		return true;
	}
	return false;
}

