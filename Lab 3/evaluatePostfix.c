#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

typedef enum {
    EVAL_OK,
    EVAL_EMPTY,
    EVAL_INVALID_TOKEN,
    EVAL_UNDERFLOW,
    EVAL_DIV_ZERO,
    EVAL_LEFTOVER
} EvalStatus;

static int isOperatorToken(const char *token) {
    return token[0] != '\0' &&
           token[1] == '\0' &&
           (token[0] == '+' || token[0] == '-' ||
            token[0] == '*' || token[0] == '/' ||
            token[0] == '^');
}

static EvalStatus applyOperator(Stack *stack, char op) {
    if (stack->top < 1)
        return EVAL_UNDERFLOW;

    double rightOperand = pop(stack);
    double leftOperand = pop(stack);
    double result;

    switch (op) {
        case '+':
            result = leftOperand + rightOperand;
            break;
        case '-':
            result = leftOperand - rightOperand;
            break;
        case '*':
            result = leftOperand * rightOperand;
            break;
        case '/':
            if (rightOperand == 0.0)
                return EVAL_DIV_ZERO;
            result = leftOperand / rightOperand;
            break;
        case '^':
            result = pow(leftOperand, rightOperand);
            break;
        default:
            return EVAL_INVALID_TOKEN;
    }

    push(stack, result);
    return EVAL_OK;
}

static EvalStatus evaluatePostfix(const char *input, double *result, Stack *stack) {
    char buffer[1000];
    char *token;
    int sawToken = 0;

    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    clearStack(stack);

    token = strtok(buffer, " \t\r\n");
    while (token != NULL) {
        sawToken = 1;

        if (isOperatorToken(token)) {
            EvalStatus status = applyOperator(stack, token[0]);
            if (status != EVAL_OK)
                return status;
        } else {
            char *endPtr;
            double value;

            errno = 0;
            value = strtod(token, &endPtr);

            if (token[0] == '\0' || *endPtr != '\0' ||
                errno == ERANGE) {
                return EVAL_INVALID_TOKEN;
            }

            push(stack, value);
        }

        token = strtok(NULL, " \t\r\n");
    }

    if (!sawToken)
        return EVAL_EMPTY;

    if (stack->top != 0)
        return EVAL_LEFTOVER;

    *result = pop(stack);
    return EVAL_OK;
}

static const char *errorMessage(EvalStatus status) {
    switch (status) {
        case EVAL_EMPTY:
            return "empty expression";
        case EVAL_INVALID_TOKEN:
            return "invalid token";
        case EVAL_UNDERFLOW:
            return "stack underflow";
        case EVAL_DIV_ZERO:
            return "division by zero";
        case EVAL_LEFTOVER:
            return "leftover operands (missing operator)";
        default:
            return "unknown error";
    }
}

static int isExitCommand(const char *input) {
    char word[32];

    if (sscanf(input, " %31s", word) != 1)
        return 0;

    for (size_t i = 0; word[i] != '\0'; ++i)
        word[i] = (char)tolower((unsigned char)word[i]);

    return strcmp(word, "exit") == 0 || strcmp(word, "quit") == 0;
}

int main(void) {
    char input[1000];
    Stack stack;
    double result;

    initStack(&stack);

    printf("Postfix Evaluator\n");
    printf("Enter postfix expression using space-separated tokens.\n");
    printf("Type exit or quit to terminate.\n");

    while (1) {
        printf("postfix> ");

        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        if (isExitCommand(input))
            break;

        EvalStatus status = evaluatePostfix(input, &result, &stack);

        if (status == EVAL_OK)
            printf("Result = %g\n", result);
        else
            printf("Error: %s\n", errorMessage(status));
    }

    printf("Program terminated.\n");
    return 0;
}
