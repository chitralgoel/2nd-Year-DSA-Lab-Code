#include <stdio.h>
#include <stdlib.h>
#include "term.h"

term_t *create_term(double coeff, int exp)
{
    term_t *new_term = (term_t *)malloc(sizeof(term_t));

    if (new_term == NULL)
        return NULL;

    new_term->coeff = coeff;
    new_term->exp = exp;
    new_term->next = NULL;

    return new_term;
}

void print_term(term_t *ptr_term, int is_first)
{
    double coeff;

    if (ptr_term == NULL)
        return;

    coeff = ptr_term->coeff;

    if (coeff == 0.0)
        return;

    if (!is_first) {
        if (coeff > 0.0)
            printf(" + ");
        else {
            printf(" - ");
            coeff = -coeff;
        }
    } else if (coeff < 0.0) {
        printf("-");
        coeff = -coeff;
    }

    if (ptr_term->exp == 0) {
        printf("%.2g", coeff);
    } else if (ptr_term->exp == 1) {
        if (coeff == 1.0)
            printf("x");
        else
            printf("%.2gx", coeff);
    } else {
        if (coeff == 1.0)
            printf("x^%d", ptr_term->exp);
        else
            printf("%.2gx^%d", coeff, ptr_term->exp);
    }
}

void integrate_term(term_t *ptr_term, term_t *ptr_integrated_term)
{
    if (ptr_term == NULL || ptr_integrated_term == NULL)
        return;

    if (ptr_term->exp == -1) {
        ptr_integrated_term->coeff = 0.0;
        ptr_integrated_term->exp = 0;
        ptr_integrated_term->next = NULL;
        return;
    }

    ptr_integrated_term->coeff =
        ptr_term->coeff / (double)(ptr_term->exp + 1);
    ptr_integrated_term->exp = ptr_term->exp + 1;
    ptr_integrated_term->next = NULL;
}
