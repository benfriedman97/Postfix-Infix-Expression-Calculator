#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "stack.h"

char *ScanLineStdin(char *dest, int dest_len);

int main(int argc, char *argv[])
{
	char postfix[100], term[20], ch;
	int i, len, j, pow_10;
	double n;;
	Item a, b;
	Status status;

	printf("Enter a postfix expression: ");
	ScanLineStdin(postfix, 100);
	len = strlen(postfix);
	STACK hStack = stackInitDefault(len);

	for (i = 0, j = 0; i < len; i++, j = 0) {
		//addition/subtraction/multiplication/division
		if (postfix[i] == '+' || (postfix[i] == '-' && !isdigit(postfix[i+1]) &&
			postfix[i+1] != '.') || postfix[i] == '/' || postfix[i] == '*') {
			b = stackGetTopItem(hStack, &status);
			stackPop(hStack);
			a = stackGetTopItem(hStack, &status);
			stackPop(hStack);
			if (postfix[i] == '+')
				stackPush(hStack, a + b);
			else if (postfix[i] == '-')
				stackPush(hStack, a - b);
			else if (postfix[i] == '/')
				stackPush(hStack, a / b);
			else
				stackPush(hStack, a * b);
		}
		//square root
		else if (postfix[i] == '$') {
			a = stackGetTopItem(hStack, &status);
			stackPop(hStack);
			if (a < 0) {
				printf("Cannot take square root of a negative\n");
				break;
			}
			stackPush(hStack, sqrt(a));
		}
		/*Negative/positive, decimal starting with '.', negative decimal starting
		with '-.'*/
		else if (postfix[i] == '.' || postfix[i] == '-' || isdigit(postfix[i])) {
			j = 0;
			while (postfix[i] == '.' || postfix[i] == '-' || isdigit(postfix[i]))
				term[j++] = postfix[i++];
			i--;
			term[j] = '\0';
			sscanf(term, "%lf", &n);
			stackPush(hStack, n);
		}
	}
	printf("The result of \"%s is %f\"\n", postfix,
		stackGetTopItem(hStack, &status));
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
