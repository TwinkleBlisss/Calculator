#pragma once

struct Stack {
    double *data;
    int size;   // ����. ������ �������.
    int top;    // ����������� ����� ��������� � �������.
};

Stack* createStack();
void deleteStack(Stack** stack);
void resize(Stack* stack);
void push(Stack* stack, double value);
double pop(Stack* stack);
double head(const Stack* stack);
void cut(Stack* stack);