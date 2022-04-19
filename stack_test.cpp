#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

int main() {
    cout << "hello world";
    int n = 3;
    Stack* s = createStack();
    double a;
    for (int i = 0; i < n; i++) {
        scanf_s("%lf", &a);
        push(s, a);
    }
    printf_s("\n%d %d\n", s->size, s->top);
    cut(s);
    printf_s("\n%d %d\n", s->size, s->top);
    for (int i = 0; i < n; i++) {
        printf_s("%lf ", head(s));
        printf_s("%lf ", pop(s));
        printf_s("\n");
    }
    
    deleteStack(&s);

    /*int* mas;
    int p;
    mas = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        mas[i] = i;
    }
    for (int i = 0; i < n; i++) {
        printf_s("%d ", mas[i]);
    }
    printf_s("\n");
    
    int n1 = 2 * n;
    mas = (int*)realloc(mas, n1 * sizeof(int));
    for (int i = n; i < n1; i++) {
        mas[i] = i;
    }
    for (int i = 0; i < n1; i++) {
        printf_s("%d ", mas[i]);
    }*/
	return 0;
}