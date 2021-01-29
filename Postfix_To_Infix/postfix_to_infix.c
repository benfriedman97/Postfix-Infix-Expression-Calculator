/* Algorithm
- if a character is an operand, push it to the stack
- if a character is an operator, pop operand from the stack, say its s1. Pop
  operator from the stack, say its s2. Perform s2 operator s1 and push it to
  the stack as a stromg/
- If there is only one string in the stack, that value is the desired infix string
- NOTE***: the stack must be a stack of strings*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <vld.h>
#include "stack_string.h"

#define STR_SIZE 100

char *ScanLineStdin(char *dest, int dest_len);

int main(int argc, char *argv[])
{
	char postfix[50], operand[30], a[30], b[30], expression[50], operator[2];
	int i, len, j;

	printf("Enter postfix expression: ");
	ScanLineStdin(postfix, 50);
	len = strlen(postfix);
	STACK_STRING hStack = stackstringInitDefault(10, STR_SIZE);
	for (i = 0; i < len; i++) {
		//operand
		if ((postfix[i] == '-' && (postfix[i + 1] == '.' || isdigit(postfix[i + 1]))) ||
			postfix[i] == '.' || isdigit(postfix[i])) {
			j = 0;
			while ((postfix[i] == '-' && (postfix[i + 1] == '.' || isdigit(postfix[i + 1]))) ||
				postfix[i] == '.' || isdigit(postfix[i]))
				operand[j++] = postfix[i++];
			i--;
			operand[j] = '\0';
			stackstringPush(hStack, operand, STR_SIZE);
		}
		//operator
		else if (postfix[i] == '-' || postfix[i] == '+' || postfix[i] == '/' ||
			postfix[i] == '*') {
			strcpy(b, stackstringGetTopItem(hStack));
			stackstringPop(hStack);
			strcpy(a, stackstringGetTopItem(hStack));
			stackstringPop(hStack);
			strcpy(expression, "(");
			strcat(expression, a);
			operator[0] = postfix[i]; operator[1] = '\0';
			strcat(expression, " ");
			strcat(expression, operator);
			strcat(expression, " ");
			strcat(expression, b);
			strcat(expression, ")");
			stackstringPush(hStack, expression, STR_SIZE);
		}
		else if (postfix[i] == '$') {
			strcpy(a, stackstringGetTopItem(hStack));
			stackstringPop(hStack);
			strcpy(expression, "(");
			strcat(expression, "$");
			strcat(expression, a);
			strcat(expression, ")");
			stackstringPush(hStack, expression, STR_SIZE);
		}
	}
	printf("%s", stackstringGetTopItem(hStack));
	stackstringDestroy(&hStack);
	return 0;
}

char *ScanLineStdin(char *dest, int dest_len) {
	int i, ch;

	//Clears any \n characters
	ch = getchar();
	while (ch == '\n') {
		ch = getchar();
	}
	dest[0] = ch;
	//Gets next line on character at a time
	i = 1;
	for (ch = getchar(); ch != '\n' && ch != EOF && i < dest_len - 1; ch = getchar())
		dest[i++] = ch;
	dest[i] = '\0';
	//discards any characters that remain on input line
	while (ch != '\n' && ch != EOF)
		ch = getchar();
	return dest;
}
