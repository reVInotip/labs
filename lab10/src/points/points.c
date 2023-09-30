#include "points.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// static functions

static int Compare(const void* i, const void* j) {
	const TPoint* a = (const TPoint*)i;
	const TPoint* b = (const TPoint*)j;
	if (a->X == b->X) {
		if (a->Y > b->Y) {
			return 1;
		} else if (a->Y < b->Y) {
			return -1;
		}
		return 0;
	} else if (a->X > b->X) {
		return 1;
	}
	return -1;
}

static double Rotate(const TPoint a, const TPoint b, const TPoint c) {
	double aX = a.X / 2.0l, aY = a.Y / 2.0l;
	double bX = b.X / 2.0l, bY = b.Y / 2.0l;
	double cX = c.X / 2.0l, cY = c.Y / 2.0l;
	
	// this is pseudoscalar poduct
	return aX*(bY - cY) + bX*(cY - aY) + cX*(aY - bY);
}

static TPoint Get(TPointsArray array, const size_t index) {
	return array.Points[index];
}

// end static

void InitPointsArray(TPointsArray* array, const size_t size) {
	TPoint* points = (TPoint*)calloc(size, sizeof(TPoint));
	assert(points);
	
	array->Points = points;
	array->Size = 0;
	array->MaxSize = size;
}

void Add(TPointsArray* array, const TPoint point) {
	if (array->Size < array->MaxSize) {
		array->Points[array->Size] = point;
		++array->Size;
	}
}

void Delete(TPointsArray* array) {
	--array->Size;
}

void DestroyPointsArray(TPointsArray* array) {
	free(array->Points);
	array->Size = 0;
	array->MaxSize = 0;
}

void PrintPoints(TPointsArray array) {
	for (size_t i = 0; i < array.Size; ++i) {
		TPoint point = Get(/*array*/array, /*index*/i);
		printf("%d %d\n", point.X, point.Y);
	}
}

void AndrewMinConvexHull(TPointsArray* ans, const TPointsArray points) {
	TPointsArray up, down;
	InitPointsArray(/*array*/&up, /*size*/points.Size);
	InitPointsArray(/*array*/&down, /*size*/points.Size);

	qsort(points.Points, points.Size, sizeof(TPoint), Compare);

	Add(/*array*/&up, /*point*/Get(/*array*/points, /*index*/0ul));
	Add(/*array*/&down, /*point*/Get(/*array*/points, /*index*/0ul));
	TPoint pointMin = Get(/*array*/points, /*index*/0ul);
	TPoint pointMax = Get(/*array*/points, /*index*/points.Size - 1);
	
	for (size_t i = 1; i < points.Size; ++i) {
		if (i == points.Size - 1 ||
			Rotate(/*a*/pointMin, /*b*/Get(/*array*/points, /*index*/i), /*c*/pointMax) < 0.0l) {
			while (up.Size >= 2 &&
				Rotate(/*a*/Get(/*array*/up, /*index*/up.Size - 2),
						/*b*/Get(/*array*/up, /*index*/up.Size - 1),
						/*c*/Get(/*array*/points, /*index*/i)) >= 0.0l) {
				Delete(/*array*/&up);
			}
			Add(/*array*/&up, /*point*/Get(/*array*/points, /*index*/i));
		}

		if (i == points.Size - 1 ||
			Rotate(/*a*/pointMin, /*b*/Get(/*array*/points, /*index*/i), /*c*/pointMax) > 0.0l) {
			while (down.Size >= 2 &&
				Rotate(/*a*/Get(/*array*/down, /*index*/down.Size - 2),
						/*b*/Get(/*array*/down, /*index*/down.Size - 1),
						/*c*/Get(/*array*/points, /*index*/i)) <= 0.0l) {
				Delete(/*array*/&down);
			}
			Add(/*array*/&down, /*point*/Get(/*array*/points, /*index*/i));
		}
	}

	
	for (size_t i = 0; i < up.Size; ++i) {
		Add(/*array*/ans, /*point*/Get(/*array*/up, /*index*/i));
	}
	for (size_t i = 1; i < down.Size - 1; ++i) {
		Add(/*array*/ans, /*point*/Get(/*array*/down, /*index*/i));
	}
	
	DestroyPointsArray(/*array*/&up);
	DestroyPointsArray(/*array*/&down);
}
