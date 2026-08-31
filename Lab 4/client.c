#include <stdio.h>
#include "poly.h"

int main(void)
{
    poly_t poly1, poly2, sum;
    poly_t poly, integrated_poly;
    double lower_limit, upper_limit;
    double result;

    /* Part A - Polynomial Addition */
    printf("Enter first polynomial:\n");
    poly1 = create_poly();

    printf("Enter second polynomial:\n");
    poly2 = create_poly();

    add_poly(poly1, poly2, &sum);

    printf("\nPolynomial 1: ");
    display_poly(poly1);

    printf("Polynomial 2: ");
    display_poly(poly2);

    printf("Sum         : ");
    display_poly(sum);

    destroy_poly(&poly1);
    destroy_poly(&poly2);
    destroy_poly(&sum);

    /* Part B - Definite Integration */
    printf("\nEnter the polynomial to integrate:\n");
    poly = create_poly();

    integrated_poly = integrate_poly(poly);

    if (integrated_poly == NULL && poly != NULL) {
        destroy_poly(&poly);
        return 1;
    }

    printf("Enter lower limit: ");
    if (scanf("%lf", &lower_limit) != 1) {
        fprintf(stderr, "Invalid lower limit.\n");
        destroy_poly(&poly);
        destroy_poly(&integrated_poly);
        return 1;
    }

    printf("Enter upper limit: ");
    if (scanf("%lf", &upper_limit) != 1) {
        fprintf(stderr, "Invalid upper limit.\n");
        destroy_poly(&poly);
        destroy_poly(&integrated_poly);
        return 1;
    }

    result = eval_poly(integrated_poly, upper_limit)
           - eval_poly(integrated_poly, lower_limit);

    printf("\nPolynomial           : ");
    display_poly(poly);

    printf("Integrated Polynomial: ");
    display_poly(integrated_poly);

    printf("Definite integral from %.2lf to %.2lf = %.4lf\n",
           lower_limit, upper_limit, result);

    destroy_poly(&poly);
    destroy_poly(&integrated_poly);

    return 0;
}
