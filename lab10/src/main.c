#include "points/points.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int countPoints = 0;
    if (scanf("%d", &countPoints) != 1) {
        printf("bad number of lines");
        return EXIT_SUCCESS;
    }
    if (countPoints < 0 || countPoints > POINTS_MAX) {
        printf("bad number of points");
        return EXIT_SUCCESS;
    }

    if (countPoints == 0) {
        return EXIT_SUCCESS;
    }

    TPointsArray points, answer;
    InitPointsArray(/*array*/&points, /*size*/(size_t)countPoints);
    InitPointsArray(/*array*/&answer, /*size*/(size_t)countPoints);
	
    int currentCount = 0;
    while (currentCount != countPoints) {
        int x = 0, y = 0;
        if (scanf("%d %d", &x, &y) != 2) {
            printf("bad number of lines");
            DestroyPointsArray(/*array*/&points);
            DestroyPointsArray(/*array*/&answer);
            return EXIT_SUCCESS;
        }
        TPoint currentPoint = { .X = x, .Y = y };
		
        Add(/*array*/&points, /*point*/currentPoint);

        ++currentCount;
    }
	
    AndrewMinConvexHull(/*ans*/&answer, /*points*/points);
	
    PrintPoints(/*array*/answer);	

    DestroyPointsArray(/*array*/&points);
    DestroyPointsArray(/*array*/&answer);

    return EXIT_SUCCESS;
}
