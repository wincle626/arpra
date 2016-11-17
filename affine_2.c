/*
 * affine_2.c
 *
 *  Created on: 2 Nov 2016
 *      Author: jt273
 */

#include "mpfa.h"
#include <malloc.h>

void mpfa_affine_2 (mpfa_ptr z, mpfr_srcptr alpha, mpfa_srcptr x, mpfr_srcptr beta, mpfa_srcptr y, mpfr_ptr gamma, mpfr_ptr delta) {
	unsigned xTerm, yTerm, zTerm;
	mpfa_t z_new;
	mpfr_t temp;

	mpfr_init(temp);
	z_new->nTerms = x->nTerms + y->nTerms + 1;
	z_new->symbols = malloc(z_new->nTerms * sizeof(unsigned));
	z_new->deviations = malloc(z_new->nTerms * sizeof(mpfr_t));
	mpfr_init(&(z_new->centre));
	mpfa_term_linear_2(&(z_new->centre), alpha, &(x->centre), beta, &(y->centre), gamma, delta);
	mpfr_init_set_d(&(z_new->radius), 0.0, MPFR_RNDN);

	for (xTerm = 0, yTerm = 0, zTerm = 0; ((xTerm < x->nTerms) && (yTerm < y->nTerms)); zTerm++) {
		if ((yTerm == y->nTerms) || (x->symbols[xTerm] < y->symbols[yTerm])) {
			z_new->symbols[zTerm] = x->symbols[xTerm];
			mpfr_init(&(z_new->deviations[zTerm]));
			mpfa_term_linear_1(&(z_new->deviations[zTerm]), alpha, &(x->deviations[xTerm]), NULL, delta);
			xTerm++;
		}
		else if ((xTerm == x->nTerms) || (y->symbols[yTerm] < x->symbols[xTerm])) {
			z_new->symbols[zTerm] = y->symbols[yTerm];
			mpfr_init(&(z_new->deviations[zTerm]));
			mpfa_term_linear_1(&(z_new->deviations[zTerm]), beta, &(y->deviations[yTerm]), NULL, delta);
			yTerm++;
		}
		else {
			z_new->symbols[zTerm] = x->symbols[xTerm];
			mpfr_init(&(z_new->deviations[zTerm]));
			mpfa_term_linear_2(&(z_new->deviations[zTerm]), alpha, &(x->deviations[xTerm]), beta, &(y->deviations[yTerm]), NULL, delta);
			xTerm++;
			yTerm++;
		}
		mpfr_abs(temp, &(z_new->deviations[zTerm]), MPFR_RNDN);
		mpfr_add(&(z_new->radius), &(z_new->radius), temp, MPFR_RNDU);
	}

	z_new->nTerms = zTerm + 1;
	z_new->symbols = realloc(z_new->symbols, z_new->nTerms * sizeof(unsigned));
	z_new->symbols[zTerm] = mpfa_next_sym();
	z_new->deviations = realloc(z_new->symbols, z_new->nTerms * sizeof(mpfr_t));
	mpfr_init_set(&(z_new->deviations[zTerm]), delta, MPFR_RNDU);
	mpfr_add(&(z_new->radius), &(z_new->radius), delta, MPFR_RNDU);

	mpfa_clear(z);
	*z = *z_new;
	mpfr_clear(temp);
}
