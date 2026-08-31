#ifndef TERM_H
#define TERM_H

typedef struct term {
    double coeff;
    int exp;
    struct term *next;
} term_t;

term_t *create_term(double coeff, int exp);
void print_term(term_t *ptr_term, int is_first);
void integrate_term(term_t *ptr_term, term_t *ptr_integrated_term);

#endif
