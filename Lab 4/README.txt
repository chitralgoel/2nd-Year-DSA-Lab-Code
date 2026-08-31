POLYNOMIAL ADT LAB SUBMISSION
==============================

Files:
    term.h
    term.c
    poly.h
    poly.c
    client.c

Compile with GCC:
    gcc -Wall -Wextra -std=c11 term.c poly.c client.c -lm -o polynomial_lab

Run:
    ./polynomial_lab

Windows:
    gcc -Wall -Wextra -std=c11 term.c poly.c client.c -lm -o polynomial_lab.exe
    polynomial_lab.exe

IMPORTANT INPUT REQUIREMENT
----------------------------
The problem statement requires polynomial terms to be stored in strictly
decreasing order of exponent. Enter each polynomial in that order.

The implementation uses double coefficients because integration may produce
fractional coefficients.

Exponent -1 is rejected because the integral of c*x^-1 is c*ln|x|, which
cannot be represented by the polynomial term structure used in this lab.

The program creates independent linked lists for addition and integration,
does not modify input polynomials, and frees dynamically allocated nodes.
