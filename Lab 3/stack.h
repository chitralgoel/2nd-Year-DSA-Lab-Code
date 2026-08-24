#ifndef STACK_H
#define STACK_H

#define MAX_SIZE 100

typedef struct {
    char items[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *s);
int isEmpty(const Stack *s);
int isFull(const Stack *s);
void push(Stack *s, char value);
char pop(Stack *s);
char peek(const Stack *s);
void clearStack(Stack *s);

#endif
