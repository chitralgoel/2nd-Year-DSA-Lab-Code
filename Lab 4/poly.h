#ifndef POLY_H
#define POLY_H

#include "term.h"

typedef term_t *poly_t;

poly_t create_poly(void);
void display_poly(poly_t poly);
void add_poly(poly_t poly1, poly_t poly2, poly_t *sum);
double eval_poly(poly_t poly, double x);
poly_t integrate_poly(poly_t poly);
void destroy_poly(poly_t *poly);

#endif
