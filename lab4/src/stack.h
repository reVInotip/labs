#pragma once
typedef struct Stack {
	int value;
	struct Stack* next;
}* Stack;

Stack Create();
void Push(Stack* values, int data);
int Pop(Stack* values);
void Destroy(Stack* values);
int GetTop(Stack values);
_Bool IsEmpty(Stack values); 
