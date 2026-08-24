DATA STRUCTURES LAB — STACK SOLUTIONS

PART A: INFIX TO POSTFIX
------------------------
Folder: part_a
Files:
  stack.h
  stack.c
  infixToPostfix.c
  Makefile

Compile:
  make

Run:
  ./infixToPostfix

Windows MinGW alternative:
  gcc -std=c11 -Wall -Wextra -pedantic -O2 infixToPostfix.c stack.c -o infixToPostfix.exe

Examples:
  2+3*4                 -> 2 3 4 * +
  (1+2)*(3-4)           -> 1 2 + 3 4 - *
  3^2^4                 -> 3 2 4 ^ ^
  a+b*c                 -> a b c * +
  (a+b)^c               -> a b + c ^
  total+count1*rate2    -> total count1 rate2 * +
  value1^value2^value3  -> value1 value2 value3 ^ ^

PART B: POSTFIX EVALUATION
--------------------------
Folder: part_b
Files:
  stack.h
  stack.c
  evaluatePostfix.c
  Makefile

Compile:
  make

Run:
  ./evaluatePostfix

Windows MinGW alternative:
  gcc -std=c11 -Wall -Wextra -pedantic -O2 evaluatePostfix.c stack.c -o evaluatePostfix.exe -lm

Examples:
  2 3 4 * +     -> 14
  1 2 + 3 4 - * -> -3
  5 0 /         -> Error: division by zero
  3 2 4 ^ ^     -> 43046721
  2 3 ^ 4 *     -> 32

NOTES
-----
- Part A is the final Step 3 implementation, so it includes all earlier features.
- Part A validates parentheses, invalid characters, missing operators/operands,
  and supports right-associative ^.
- Part B uses a numeric stack of double values and implements the requested
  REPL, error handling, and ^ evaluation.
- Postfix input must be whitespace-separated as required by the Part B
  specification.
