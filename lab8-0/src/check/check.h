#pragma once
#include <stdbool.h>

_Bool IsBadNumber(const char count);
_Bool IsBadVertex(const int start, const int end, const int count);
_Bool IsBadLength(const long int len);
_Bool IsBadInput(const char count);
_Bool IsBadCountVertices(const int count);
_Bool IsBadCountEdges(const int count, const int EDGES_MAX);
