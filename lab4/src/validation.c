#include <stdio.h>
#include "utilities.h"
#include "validation.h"
#define ERROR true
#define OK false

_Bool Validation(const char* arithmExpression, const int length) {
    char previousSymbol = '\0';
    int countOpenBracket = 0, countCloseBracket = 0, countDigits = 0;
    if (length == 0) {
        printf("syntax error");
        return ERROR;
    } else if (IsOperation(/*value*/arithmExpression[length - 2])) {
        printf("syntax error");
        return ERROR;
    }
    for (int i = 0; i < length - 1; ++i) {
        char symbol = arithmExpression[i];
        if (
            (!IsDigit(/*value*/symbol) && !IsOperation(/*value*/symbol)
             && symbol != '(' && symbol != ')') ||
            (IsDigit(/*value*/symbol) && previousSymbol == ')') ||
            (IsDigit(/*value*/previousSymbol) && symbol == '(') ||
            (IsOperation(/*value*/previousSymbol) && IsOperation(/*value*/symbol))
        ) {
            printf("syntax error");
            return ERROR;
        } else if (symbol == '(') {
            ++countOpenBracket;
        } else if (IsDigit(/*value*/symbol)) {
            ++countDigits;
        } else if (symbol == ')') {
            ++countCloseBracket;
            if (countCloseBracket > countOpenBracket) {
                printf("syntax error");
                return ERROR;
            }
        }
        previousSymbol = symbol;
    }
    if (countOpenBracket != countCloseBracket || countDigits == 0) {
        printf("syntax error");
        return ERROR;
    }
    return OK;
}
