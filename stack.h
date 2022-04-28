#pragma once

struct Stack {
    double *data;
    int size;   // Макс. размер массива.
    int top;    // Фактическое число элементов в массиве.
};

Stack* createStack();
void deleteStack(Stack** stack);
void resize(Stack* stack);
void push(Stack* stack, double value);
void pop(Stack* stack);
double head(const Stack* stack);
void cut(Stack* stack);
