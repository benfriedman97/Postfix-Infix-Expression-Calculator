#ifndef STACK_H
#define STACK_H

#include "status.h"
#define EMTPY_CODE 99

typedef void* STACK;
typedef double Item;

STACK stackInitDefault(int capacity);
Status stackPush(STACK hStack, Item item);
Status stackPop(STACK hStack);
Boolean stackIsEmpty(STACK hStack);
Item stackGetTopItem(STACK hStack, Status *pStatus);
void stackDestroy(STACK *phStack);

#endif
