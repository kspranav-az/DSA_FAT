#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 30

typedef struct Stack {
    char *arr;
    int tos;
} Stack;

Stack *createStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->tos = -1;
    stack->arr = (char *)calloc(SIZE, sizeof(char));
    return stack;
}

char peek(Stack *stack) {
    if (stack->tos < 0) {
        return '\0';
    }
    return stack->arr[stack->tos];
}

char pop(Stack *stack) {
    if (stack->tos >= 0) {
        return stack->arr[stack->tos--];
    } else {
        return '\0';
    }
}

void push(Stack *stack, char data) {
    if (stack->tos < SIZE - 1) {
        stack->arr[++stack->tos] = data;
    } else {
        printf("Stack Overflow\n");
    }
}

int precedence(char const ch) {
    switch (ch) {
    case '^':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

int isRightAssociative(char ch) {
    return (ch == '^');
}

void infixToPostfix(char infix[], char postfix[]) {
    Stack *stack = createStack();
    int i, j;

    for (i = 0, j = 0; infix[i] != '\0'; i++) {
        char token = infix[i];

        if (isdigit(token) || isalpha(token)) {
            postfix[j++] = token;
        } else if (token == '(') {
            push(stack, token);
        } else if (token == ')') {
            while (peek(stack) != '(' && peek(stack) != '\0') {
                postfix[j++] = pop(stack);
            }
            if (peek(stack) == '(') {
                pop(stack);
            }
        } else if (token == '+' || token == '-' || token == '*' || token == '/' || token == '^') {
            while ((precedence(token) < precedence(peek(stack)) ||
                    (precedence(token) == precedence(peek(stack)) && !isRightAssociative(token))) &&
                   peek(stack) != '\0') {
                postfix[j++] = pop(stack);
            }
            push(stack, token);
        }
    }

    
    while (peek(stack) != '\0') {
        postfix[j++] = pop(stack);
    }

    postfix[j] = '\0'; 
    free(stack->arr);
    free(stack);
}

int main() {
    char infix[100], postfix[100];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
