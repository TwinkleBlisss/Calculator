#include "stack.h"
#include <stdlib.h>

#define INIT_SIZE 10
#define MULTIPLIER 2
#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY   -102

Stack* createStack() {
    Stack* out = NULL;
    out = (Stack*)malloc(sizeof(Stack));
    if (out == NULL) {
        exit(OUT_OF_MEMORY);
    }
    out->size = INIT_SIZE;
    out->data = (double*)malloc(out->size * sizeof(double));
    if (out->data == NULL) {
        free(out);
        exit(OUT_OF_MEMORY);
    }
    out->top = 0;
    return out;
}

void deleteStack(Stack** stack) {
    free((*stack)->data);
    free(*stack);
    *stack = NULL;
}

void resize(Stack* stack) {
    stack->size *= MULTIPLIER;
    stack->data = (double*)realloc(stack->data, stack->size * sizeof(double));
    if (stack->data == NULL) {
        exit(STACK_OVERFLOW);
    }
}

void push(Stack* stack, double value) {
    if (stack->top >= stack->size) {
        resize(stack);
    }
    stack->data[stack->top] = value;
    stack->top++;
}

double pop(Stack* stack) {
    // Возвращает элемент с вершины и переходит к следующему.
    if (stack->top == 0) {
        exit(STACK_UNDERFLOW);
    }
    stack->top--;
    return stack->data[stack->top];
}

double head(const Stack* stack) {
    // Возвращает элемент с вершины.
    if (stack->top <= 0) {
        exit(STACK_UNDERFLOW);
    }
    return stack->data[stack->top - 1];
}

void cut(Stack* stack) {
    // Сокращает максимальный размер массива до фактического.
    stack->size = stack->top;
    stack->data = (double*)realloc(stack->data, stack->size * sizeof(double));
}