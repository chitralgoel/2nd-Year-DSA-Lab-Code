#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(const Stack *s) {
    return s->top == -1;
}

int isFull(const Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack *s, char value) {
    if (isFull(s)) {
        fprintf(stderr, "Error: stack overflow\n");
        exit(EXIT_FAILURE);
    }
    s->items[++s->top] = value;
}

char pop(Stack *s) {
    if (isEmpty(s)) {
        fprintf(stderr, "Error: stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->items[s->top--];
}

char peek(const Stack *s) {
    if (isEmpty(s)) {
        fprintf(stderr, "Error: stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return s->items[s->top];
}

void clearStack(Stack *s) {
    s->top = -1;
}
