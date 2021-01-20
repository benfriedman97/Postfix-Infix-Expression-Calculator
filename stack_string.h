#ifndef STACK_STRING_H
#define STACK_STRING_H

#include "status.h"

typedef void* STACK_STRING;

STACK_STRING stackstringInitDefault(int capacity, int len);
Status stackstringPush(STACK_STRING hStack_string, char *str, int len);
Status stackstringPop(STACK_STRING hStack_string);
Boolean stackstringIsEmpty(STACK_STRING hStack_string);
char* stackstringGetTopItem(STACK_STRING hStack_string);
void stackstringDestroy(STACK_STRING *phStack_string);

#endif
