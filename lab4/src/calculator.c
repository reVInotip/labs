#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "stack.h"
#include "utilities.h"
#include "validation.h"
#include "calculator.h"
#define MAX_LENGTH 1001
#define PLUS -1 // +
#define MINUS -2 // -
#define MULTIPLY -3 // *
#define DIVIDE -4 // /
// я хитро воспользовался тем, что у нас нет унарной операции взятия противоположного
// с целью избежать совпадения например кода + и числа 43 при расчётах;)

int GetPriority(char operation) {
    if (operation == '+' || operation == '-') {
        return 1;
    } else if (operation == '*' || operation == '/') {
        return 2;
    }
    // ожидаемый случай возвращения нуля - символ конца строки
    // когда он вернётся нужно будет выгрузить все элементы из стека 
    return 0;
}

void AddDigit(int* array, int digit, int* size) {
    array[(*size) - 1] = digit;
    ++(*size);
}

int ReplaceOperation(const char operation) {
    switch (operation) {
        case '+':
            return PLUS;
        case '-':
            return MINUS;
        case '*':
            return MULTIPLY;
        case '/':
            return DIVIDE;
    }
    return 0;
}

int TraslateToPolishEntry(const char* arithmExpression, const int length, int* newArithmExpression) {
    int currentSize = 1, digit = 0;
    char operation = '\0';
    Stack operations = Create();
    for (int i = 0; i < length; ++i) {
        if (IsDigit(/*value*/arithmExpression[i])) {
            digit *= 10;
            digit += arithmExpression[i] - '0';
        } else if (arithmExpression[i] == '(') {
            Push(/*values*/&operations, /*data*/'(');
        } else if (arithmExpression[i] == ')') {
            AddDigit(/*array*/newArithmExpression, /*digit*/digit, /*size*/&currentSize);
            digit = -1;
            while (GetTop(/*values*/operations) != '(' && !IsEmpty(/*values*/operations)) {
                operation = Pop(/*values*/&operations);
                newArithmExpression[currentSize - 1] = ReplaceOperation(/*operation*/operation);
                ++currentSize;
            }
            Pop(/*values*/&operations);
        } else {
            if (digit != -1) {
                AddDigit(/*array*/newArithmExpression, /*digit*/digit, /*size*/&currentSize);
            }
            digit = 0;
            int priority = GetPriority(/*operation*/arithmExpression[i]);
            char symbol = GetTop(/*values*/operations);
            while (!IsEmpty(/*values*/operations) && (GetPriority(/*operation*/symbol) >= priority)) {
                operation = Pop(/*values*/&operations);
                newArithmExpression[currentSize - 1] = ReplaceOperation(/*operation*/operation);
                symbol = GetTop(/*values*/operations);
                ++currentSize;
            }
            Push(/*values*/&operations, /*data*/arithmExpression[i]);
        } 
    }
    Destroy(/*values*/&operations);
    return currentSize - 1;
}

int MakeOperation(const int first, const int second, const char operation) {
    switch (operation) {
        case PLUS:
            return first + second;
        case MINUS:
            return first - second;
        case MULTIPLY:
            return first * second;
        case DIVIDE:
            return first / second;
    }
    return 0;
}

void Calculate(const int* postfixArithmExpression, const int size) {
    Stack digits = Create();
    for (int i = 0; i < size; ++i) {
        if (postfixArithmExpression[i] > PLUS) {
            Push(/*values*/&digits, /*data*/postfixArithmExpression[i]);
        } else {
            int second = Pop(/*values*/&digits);
            int first = Pop(/*values*/&digits);
            char operation = postfixArithmExpression[i];
            if (operation == DIVIDE && second == 0) {
                printf("division by zero");
                Destroy(/*values*/&digits);
                return;
            }
            int res = MakeOperation(/*first*/first, /*second*/second, /*operation*/operation);
            Push(/*values*/&digits, /*data*/res);
        }
    }
    int answer = Pop(/*values*/&digits);
    Destroy(/*values*/&digits);
    printf("%d", answer);
}

void Calculator(const char* arithmExpression, const int length) {
    bool isInvalid = Validation(/*arithmExpression*/arithmExpression, /*length*/length);
    if (isInvalid) {
        return;
    }
    int postfixArithmExpression[MAX_LENGTH];
    int size = TraslateToPolishEntry(/*arithmExpression*/arithmExpression,
                                    /*length*/length,
			            /*newArithmExpression*/postfixArithmExpression);
    Calculate(/*postfixArithmExpression*/postfixArithmExpression, /*size*/size);
}
