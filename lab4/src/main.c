#include "read.h"
#include "calculator.h"
#define MAX_LENGTH 1001

int main(void) {
    char arithmExpression[MAX_LENGTH];
    int length = ReadArithmExpression(/*arithmExpression*/arithmExpression);
    Calculator(/*arithmExpression*/arithmExpression, /*length*/length);
    return 0;
}
