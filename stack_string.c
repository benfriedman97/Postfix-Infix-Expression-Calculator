#include <stdlib.h>
#include <string.h>
#include "stack_string.h"

#define SIZE 30

typedef struct stack_string {
	int size;
	int capacity;
	char **stack;
} Stack_string;

STACK_STRING stackstringInitDefault(int capacity, int len)
{
	int i, j;
	Stack_string *pStack = (Stack_string*)malloc(sizeof(Stack_string));
	if (pStack != NULL) {
		pStack->stack = (char**)malloc(sizeof(char*) * capacity);
		if (pStack->stack == NULL) {
			free(pStack);
			return NULL;
		}
		for (i = 0; i < capacity; i++) {
			pStack->stack[i] = (char*)malloc(sizeof(char) * (len + 1));
			if (pStack->stack[i] == NULL) {
				for (j = i - 1; j >= 0; j--)
					free(pStack->stack[j]);
				free(pStack->stack);
				free(pStack);
				return NULL;
			}
		}
		pStack->capacity = capacity;
		pStack->size = 0;
	}
	return (STACK_STRING)pStack;
}


Status stackstringPush(STACK_STRING hStack_string, char *str, int len)
{
	char **temp;
	int i, j;
	Stack_string *pStack = (Stack_string*)hStack_string;

	if (pStack->size >= pStack->capacity) {
		temp = (char**)malloc(sizeof(char*) * pStack->size);
		if (temp == NULL)
			return FAILURE;
		for (i = 0; i < pStack->size; i++) {
			temp[i] = (char*)malloc(sizeof(char) * (len + 1));
			if (temp[i] == NULL) {
				for (j = i - 1; j >= 0; j--)
					free(temp[j]);
				free(temp);
				return FAILURE;
			}
		}
		for (i = 0; i < pStack->size; i++)
			strcpy(temp[i], pStack->stack[i]);
		for (i = 0; i < pStack->size; i++)
			free(pStack->stack[i]);
		free(pStack->stack);

		pStack->stack = (char**)malloc(sizeof(char*) * pStack->capacity * 2);
		if (pStack->stack == NULL) {
			pStack->stack = temp;
			return FAILURE;
		}
		for (i = 0; i < pStack->capacity * 2; i++) {
			pStack->stack[i] = (char*)malloc(sizeof(char) * (len + 1));
			if (pStack->stack[i] == NULL) {
				for (j = i - 1; j >= 0; j--)
					free(pStack->stack[j]);
				free(pStack->stack);
				pStack->stack = temp;
			}
		}
		for (i = 0; i < pStack->size; i++)
			strcpy(pStack->stack[i], temp[i]);
		for (i = 0; i < pStack->size; i++)
			free(temp[i]);
		free(temp);
		pStack->capacity *= 2;
	}

	strcpy(pStack->stack[pStack->size++], str);
	return SUCCESS;
}

Status stackstringPop(STACK_STRING hStack_string)
{
	if (stackstringIsEmpty(hStack_string))
		return FAILURE;
	Stack_string *pStack = (Stack_string*)hStack_string;
	pStack->size--;
	return SUCCESS;
}


Boolean stackstringIsEmpty(STACK_STRING hStack_string)
{
	Stack_string* pStack = (Stack_string*)hStack_string;
	if (pStack->size <= 0)
		return TRUE;
	return FALSE;
}

char* stackstringGetTopItem(STACK_STRING hStack_string)
{
	if (stackstringIsEmpty(hStack_string))
		return NULL;

	Stack_string *pStack = (Stack_string*)hStack_string;
	return pStack->stack[pStack->size - 1];
}


void stackstringDestroy(STACK_STRING *phStack_string)
{
	Stack_string *pStack = (Stack_string*)*phStack_string;
	int i;
	for (i = 0; i < pStack->capacity; i++)
		free(pStack->stack[i]);
	free(pStack->stack);
	free(pStack);
	*phStack_string = NULL;
}
