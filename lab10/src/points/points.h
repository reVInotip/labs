#pragma once
#include <stdlib.h>

enum { POINTS_MAX = 100000 };

typedef struct TPoint {
	int X, Y;
} TPoint;

typedef struct TPointsArray {
	TPoint* Points;
	size_t Size, MaxSize;
} TPointsArray;

void InitPointsArray(TPointsArray* array, const size_t size);
void Add(TPointsArray* array, const TPoint point);
void PrintPoints(TPointsArray array);
void DestroyPointsArray(TPointsArray* array);
void AndrewMinConvexHull(TPointsArray* ans, const TPointsArray points);
