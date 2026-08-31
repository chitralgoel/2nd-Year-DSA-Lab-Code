#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "poly.h"

static void append_term(poly_t *poly, double coeff, int exp)
{
    term_t *new_term;
    term_t *current;

    if (coeff == 0.0)
        return;

    new_term = create_term(coeff, exp);
    if (new_term == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    if (*poly == NULL) {
        *poly = new_term;
        return;
    }

    current = *poly;
    while (current->next != NULL)
        current = current->next;

    current->next = new_term;
}

poly_t create_poly(void)
{
    int n, i;
    double coeff;
    int exp;
    poly_t poly = NULL;

    printf("Number of terms: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid number of terms.\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++) {
        printf("Coefficient Exponent: ");
        if (scanf("%lf %d", &coeff, &exp) != 2) {
            fprintf(stderr, "Invalid coefficient/exponent.\n");
            destroy_poly(&poly);
            exit(EXIT_FAILURE);
        }

        if (exp == -1) {
            fprintf(stderr,
                    "Exponent -1 is not supported because its integral "
                    "is logarithmic, not a polynomial.\n");
            destroy_poly(&poly);
            exit(EXIT_FAILURE);
        }

        append_term(&poly, coeff, exp);
    }

    return poly;
}

void display_poly(poly_t poly)
{
    term_t *current = poly;
    int first = 1;

    if (poly == NULL) {
        printf("0\n");
        return;
    }

    while (current != NULL) {
        if (current->coeff != 0.0) {
            print_term(current, first);
            first = 0;
        }
        current = current->next;
    }

    if (first)
        printf("0");

    printf("\n");
}

void add_poly(poly_t poly1, poly_t poly2, poly_t *sum)
{
    term_t *p1;
    term_t *p2;

    if (sum == NULL)
        return;

    *sum = NULL;
    p1 = poly1;
    p2 = poly2;

    while (p1 != NULL && p2 != NULL) {
        if (p1->exp == p2->exp) {
            double coeff = p1->coeff + p2->coeff;
            if (coeff != 0.0)
                append_term(sum, coeff, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->exp > p2->exp) {
            append_term(sum, p1->coeff, p1->exp);
            p1 = p1->next;
        } else {
            append_term(sum, p2->coeff, p2->exp);
            p2 = p2->next;
        }
    }

    while (p1 != NULL) {
        append_term(sum, p1->coeff, p1->exp);
        p1 = p1->next;
    }

    while (p2 != NULL) {
        append_term(sum, p2->coeff, p2->exp);
        p2 = p2->next;
    }
}

double eval_poly(poly_t poly, double x)
{
    double result = 0.0;
    term_t *current = poly;

    while (current != NULL) {
        result += current->coeff * pow(x, current->exp);
        current = current->next;
    }

    return result;
}

poly_t integrate_poly(poly_t poly)
{
    term_t *current = poly;
    poly_t integrated = NULL;

    while (current != NULL) {
        term_t *integrated_term;

        if (current->exp == -1) {
            fprintf(stderr,
                    "Cannot integrate x^-1 as a polynomial term.\n");
            destroy_poly(&integrated);
            return NULL;
        }

        integrated_term = create_term(0.0, 0);
        if (integrated_term == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            destroy_poly(&integrated);
            exit(EXIT_FAILURE);
        }

        integrate_term(current, integrated_term);
        append_term(&integrated,
                    integrated_term->coeff,
                    integrated_term->exp);

        free(integrated_term);
        current = current->next;
    }

    return integrated;
}

void destroy_poly(poly_t *poly)
{
    term_t *current;
    term_t *next;

    if (poly == NULL)
        return;

    current = *poly;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *poly = NULL;
}
