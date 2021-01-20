#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "stack.h"

char *ScanLineStdin(char *dest, int dest_len);
char* InfixToPostfix(char *infix, char *postfix);
double evaluatePostfix(char *postfix);

int main(int argc, char *argv[])
{
	
	char infix[100], postfix[100];

	printf("Enter an infix expression: ");
	ScanLineStdin(infix, 100);
	InfixToPostfix(infix, postfix);
	printf("Infix expression: %s\n", infix);
	printf("Converted to postfix: %s\n", postfix);
	printf("Result: %f", evaluatePostfix(postfix));

	return 0;
}

/*
Algorithm:
- if a number is encountered, write it to output.
- if a left parentheses is encountered, ignore it.
- if an operator is encountered, push it onto the stack.
- if a right parentheses is encountered, write the operator at the top
  of the stack to output
So, only a stack of operators is needed since all numbers automatically get
written to the string
*/
char* InfixToPostfix(char *infix, char *postfix)
{
	STACK hStack_operators = stackInitDefault(10);

	char term[20];
	int i, j, len = strlen(infix);
	Status status;
	char a;
	
	for (i = 0, j = 0; i < len; i++) {
		//operator
		if (infix[i] == '+' || (infix[i] == '-' && !isdigit(infix[i + 1]) &&
			infix[i + 1] != '.') || infix[i] == '/' || infix[i] == '*' ||
			infix[i] == '$')
			stackPush(hStack_operators, infix[i]);
		//operand
		else if (infix[i] == '.' || infix[i] == '-' || isdigit(infix[i])) {
			while (infix[i] == '.' || infix[i] == '-' || isdigit(infix[i]))
				postfix[j++] = infix[i++];
			i--;
			postfix[j++] = ' ';
		}
		//right parenthese
		else if (infix[i] == ')') {
			a = (char)stackGetTopItem(hStack_operators, &status);
			postfix[j++] = a;
			postfix[j++] = ' ';
			stackPop(hStack_operators);
		}
	}
	while (!stackIsEmpty(hStack_operators)) {
		a = (char)stackGetTopItem(hStack_operators, &status);
		postfix[j++] = a;
		postfix[j++] = ' ';
		stackPop(hStack_operators);
	}
	postfix[j] = '\0';
	return postfix;

	stackDestroy(&hStack_operators);
}

/*Algorithm:
- if a number is encountered, put it on the stack
- if an operator is encountered, pop the top two items off the stack (or 1
  if it's for an operation requiring one operand like square root) with the 
  second one popped being the first operator used with the operator (i.e. if
  a '-' is encountered, it would pop off 7 then 4 and it would be "4 - 7" and
  not "7 - 4"*/
double evaluatePostfix(char *postfix)
{
	int i, j, len = strlen(postfix);
	double a, b;
	Status status;
	char term[20];
	STACK hStack_operators = stackInitDefault(10);

	for (i = 0, j = 0; i < len; i++, j = 0) {
		//addition/subtraction/multiplication/division
		if (postfix[i] == '+' || (postfix[i] == '-' && !isdigit(postfix[i + 1]) &&
			postfix[i + 1] != '.') || postfix[i] == '/' || postfix[i] == '*') {
			b = (double)stackGetTopItem(hStack_operators, &status);
			stackPop(hStack_operators);
			a = (double)stackGetTopItem(hStack_operators, &status);
			stackPop(hStack_operators);
			if (postfix[i] == '+')
				stackPush(hStack_operators, (Item)(a + b));
			else if (postfix[i] == '-')
				stackPush(hStack_operators, (Item)(a - b));
			else if (postfix[i] == '/')
				stackPush(hStack_operators, (Item)(a / b));
			else
				stackPush(hStack_operators, (Item)(a * b));
		}
		//square root
		else if (postfix[i] == '$') {
			a = (double)stackGetTopItem(hStack_operators, &status);
			stackPop(hStack_operators);
			if (a < 0) {
				printf("Cannot take square root of a negative\n");
				break;
			}
			stackPush(hStack_operators, (Item)sqrt(a));
		}
		/*Negative/positive, decimal starting with '.', negative decimal starting
		with '-.'*/
		else if (postfix[i] == '.' || postfix[i] == '-' || isdigit(postfix[i])) {
			j = 0;
			while (postfix[i] == '.' || postfix[i] == '-' || isdigit(postfix[i]))
				term[j++] = postfix[i++];
			i--;
			term[j] = '\0';
			sscanf(term, "%lf", &a);
			stackPush(hStack_operators, (Item)a);
		}
	}
	
	a = stackGetTopItem(hStack_operators, &status);
	stackDestroy(&hStack_operators);
	return a;
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
