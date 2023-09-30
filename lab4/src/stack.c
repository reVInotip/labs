#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "stack.h"

Stack Create() {
	Stack ptr = malloc(sizeof(struct Stack));
	assert(ptr != NULL);
	ptr->value = '\0';
	ptr->next = NULL;
	return ptr;
}

void Push(Stack* values, int data) {
	Stack newOperation = malloc(sizeof(**values));
	assert(newOperation != NULL);
	newOperation->value = data;
	newOperation->next = *values;
	*values = newOperation;
}

int Pop(Stack* values) {
	if (IsEmpty(/*values*/*values)) {
		return 0;
	}
	int data = (*values)->value;
	Stack next = (*values)->next;
	free(*values);
	*values = next;
	return data;
}

void Destroy(Stack* values) {
	while (*values != NULL) {
		Stack next = (*values)->next;
		free(*values);
		*values = next;
	}
}

int GetTop(Stack values) {
	return values->value;
}

_Bool IsEmpty(Stack values) {
	if (values->value == '\0' && values->next == NULL) {
		return true;
	}
	return false;
}
