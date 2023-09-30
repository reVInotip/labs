#include <stdbool.h>
#include "utilities.h"

_Bool IsDigit(int value) {
    if (value <= '9' && value >= '0') {
        return true;
    }
    return false;
}

_Bool IsOperation(char value) {
    if (value == '+' || value == '-' || value == '*' || value == '/') {
        return true;
    }
    return false;
}

