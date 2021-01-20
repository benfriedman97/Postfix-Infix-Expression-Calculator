#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

char *ScanLineStdin(char *dest, int dest_len);

int main(int argc, char *argv[])
{
	char infix[100], postfix[100], term[20], ch;
	int i, j, len;
	Status status;
	Item a;

	printf("Enter an infix expression: ");
	ScanLineStdin(infix, 100);	len = strlen(infix);
	STACK hStack = stackInitDefault(len);
	for (i = 0, j = 0; i < len; i++) {
		if (infix[i] == '+' || (infix[i] == '-' && !isdigit(infix[i + 1]) &&
			infix[i + 1] != '.') || infix[i] == '/' || infix[i] == '*' ||
			infix[i] == '$')
			stackPush(hStack, infix[i]);
		else if (infix[i] == '.' || infix[i] == '-' || isdigit(infix[i])) {
			while (infix[i] == '.' || infix[i] == '-' || isdigit(infix[i]))
				postfix[j++] = infix[i++];
			i--;
			postfix[j++] = ' ';
		}
		else if (infix[i] == ')') {
			a = stackGetTopItem(hStack, &status);
			postfix[j++] = (char)a;
			postfix[j++] = ' ';
			stackPop(hStack);
		}
	}
	while (!stackIsEmpty(hStack)) {
		a = stackGetTopItem(hStack, &status);
		postfix[j++] = (char)a;
		postfix[j++] = ' ';
		stackPop(hStack);
	}
	postfix[j] = '\0';

	printf("Infix expression: %s\n", infix);
	printf("Converted postfix expression: %s\n", postfix);

	stackDestroy(&hStack);
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
