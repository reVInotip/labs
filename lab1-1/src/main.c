#include "search.h"
#include "enter.h"
#define MAX_SIZE 34

int main(void) {
    unsigned char sample[MAX_SIZE];
    int length = EnterSample(/*sample*/sample, /*count*/MAX_SIZE/2);
    if (length == 0) {
        return 0;
    }
    Search(/*sample*/sample, /*length*/length);
    return 0;
}
