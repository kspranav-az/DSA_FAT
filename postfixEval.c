#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 30

typedef struct Stack {
    int *arr;
    int tos;
} Stack;

Stack *createStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->tos = -1;
    stack->arr = (int *)calloc(SIZE, sizeof(int));
    return stack;
}

int isEmpty(Stack *stack) {
    return stack->tos == -1;
}

int pop(Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->arr[stack->tos--];
    } else {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
}

void push(Stack *stack, int data) {
    if (stack->tos < SIZE - 1) {
        stack->arr[++stack->tos] = data;
    } else {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
}

int evaluatePostfix(char postfix[]) {
    Stack *stack = createStack();
    int i, operand1, operand2, result;

    for (i = 0; postfix[i] != '\0'; i++) {
        char token = postfix[i];

        if (isdigit(token)) {
            push(stack, token - '0');
        } else if (token == '+' || token == '-' || token == '*' || token == '/' || token == '^') {
            operand2 = pop(stack);
            operand1 = pop(stack);

            switch (token) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                case '^':
                    result = 1;
                    for (int i = 0; i < operand2; i++) {
                        result *= operand1;
                    }
                    break;
            }

            push(stack, result);
        }
    }

    result = pop(stack);
    free(stack->arr);
    free(stack);

    return result;
}

int main() {
    char postfix[100];

    printf("Enter postfix expression: ");
    scanf("%s", postfix);

    int result = evaluatePostfix(postfix);

    printf("Result of postfix expression: %d\n", result);

    return 0;
}
