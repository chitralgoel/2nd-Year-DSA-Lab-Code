#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

static int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

static int precedence(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return -1;
    }
}

static int isLeftAssociative(char c) {
    return c != '^';   /* ^ is right-associative */
}

/*
 * Returns 1 if the operator at the top of the stack must be popped
 * before pushing the incoming operator.
 */
static int shouldPop(char topOp, char currentOp) {
    if (topOp == '(')
        return 0;

    if (precedence(topOp) > precedence(currentOp))
        return 1;

    if (precedence(topOp) == precedence(currentOp) &&
        isLeftAssociative(currentOp))
        return 1;

    return 0;
}

/* Print one operand followed by exactly one space. */
static void printOperand(const char *start, size_t length, int *firstOutput) {
    if (!*firstOutput)
        putchar(' ');

    for (size_t i = 0; i < length; ++i)
        putchar(start[i]);

    *firstOutput = 0;
}

static int convert(const char *expr) {
    Stack stack;
    initStack(&stack);

    int expectingOperand = 1;
    int firstOutput = 1;
    int sawToken = 0;

    for (size_t i = 0; expr[i] != '\0'; ) {
        unsigned char ch = (unsigned char)expr[i];

        if (isspace(ch)) {
            ++i;
            continue;
        }

        sawToken = 1;

        /* Identifier: letter followed by letters/digits/underscore. */
        if (isalpha(ch)) {
            if (!expectingOperand) {
                fprintf(stderr, "Error: missing operator before identifier\n");
                return 0;
            }

            size_t start = i++;
            while (isalnum((unsigned char)expr[i]) || expr[i] == '_')
                ++i;

            printOperand(expr + start, i - start, &firstOutput);
            expectingOperand = 0;
            continue;
        }

        /* Numeric operand: supports integers and simple decimal numbers. */
        if (isdigit(ch) || (ch == '.' && isdigit((unsigned char)expr[i + 1]))) {
            if (!expectingOperand) {
                fprintf(stderr, "Error: missing operator before number\n");
                return 0;
            }

            size_t start = i;
            int dotSeen = 0;

            while (isdigit((unsigned char)expr[i]) ||
                   expr[i] == '.') {
                if (expr[i] == '.') {
                    if (dotSeen) {
                        fprintf(stderr, "Error: invalid number\n");
                        return 0;
                    }
                    dotSeen = 1;
                }
                ++i;
            }

            printOperand(expr + start, i - start, &firstOutput);
            expectingOperand = 0;
            continue;
        }

        if (ch == '(') {
            if (!expectingOperand) {
                fprintf(stderr, "Error: missing operator before '('\n");
                return 0;
            }
            push(&stack, '(');
            ++i;
            continue;
        }

        if (ch == ')') {
            if (expectingOperand) {
                fprintf(stderr, "Error: unexpected ')'\n");
                return 0;
            }

            int matched = 0;
            while (!isEmpty(&stack)) {
                char top = pop(&stack);
                if (top == '(') {
                    matched = 1;
                    break;
                }

                if (!firstOutput)
                    putchar(' ');
                putchar(top);
                firstOutput = 0;
            }

            if (!matched) {
                fprintf(stderr, "Error: unmatched ')'\n");
                return 0;
            }

            ++i;
            continue;
        }

        if (isOperator((char)ch)) {
            if (expectingOperand) {
                fprintf(stderr, "Error: operator '%c' appears where an operand is expected\n", ch);
                return 0;
            }

            while (!isEmpty(&stack) &&
                   shouldPop(peek(&stack), (char)ch)) {
                if (!firstOutput)
                    putchar(' ');
                putchar(pop(&stack));
                firstOutput = 0;
            }

            push(&stack, (char)ch);
            expectingOperand = 1;
            ++i;
            continue;
        }

        fprintf(stderr, "Error: invalid character '%c'\n", ch);
        return 0;
    }

    if (!sawToken) {
        fprintf(stderr, "Error: empty input\n");
        return 0;
    }

    if (expectingOperand) {
        fprintf(stderr, "Error: expression ends where an operand is expected\n");
        return 0;
    }

    while (!isEmpty(&stack)) {
        char op = pop(&stack);

        if (op == '(') {
            fprintf(stderr, "Error: unmatched '('\n");
            return 0;
        }

        if (!firstOutput)
            putchar(' ');
        putchar(op);
        firstOutput = 0;
    }

    putchar('\n');
    return 1;
}

int main(void) {
    char input[1000];

    printf("Enter infix expression: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: input failed\n");
        return EXIT_FAILURE;
    }

    printf("Postfix: ");
    if (!convert(input))
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
