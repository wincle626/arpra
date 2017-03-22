/*
 * set_d.c
 *
 *  Created on: 21 Oct 2016
 *      Author: jt273
 */

#include "mpfa.h"
#include <malloc.h>
#include <assert.h>

void mpfa_set_d (mpfa_ptr z, const double centre, const double radius) {
	unsigned zTerm;
	mpfr_prec_t prec;

	prec = mpfr_get_prec(&(z->centre));

	if (mpfr_set_d(&(z->centre), centre, MPFR_RNDN)) {
		assert(mpfr_set_si(&(z->radius), (-prec + mpfr_get_exp(&(z->centre))), MPFR_RNDN) == 0);
		assert(mpfr_exp2(&(z->radius), &(z->radius), MPFR_RNDN) == 0);
		mpfr_add_d(&(z->radius), &(z->radius), radius, MPFR_RNDU);
	}
	else {
		mpfr_set_d(&(z->radius), radius, MPFR_RNDU);
	}

	if (mpfr_zero_p(&(z->radius))) {
		if (z->nTerms > 0) {
			for (zTerm = 0; zTerm < z->nTerms; zTerm++) {
				mpfr_clear(&(z->deviations[zTerm]));
			}
			z->nTerms = 0;
			free(z->symbols);
			free(z->deviations);
		}
	}
	else {
		if (z->nTerms == 0) {
			z->symbols = malloc(sizeof(unsigned));
			z->deviations = malloc(sizeof(mpfa_t));
			mpfr_init2(&(z->deviations[0]), prec);
		}
		else if (z->nTerms >= 2) {
			for (zTerm = 1; zTerm < z->nTerms; zTerm++) {
				mpfr_clear(&(z->deviations[zTerm]));
			}
			z->symbols = realloc(z->symbols, sizeof(unsigned));
			z->deviations = realloc(z->deviations, sizeof(mpfa_t));
		}
		z->nTerms = 1;
		z->symbols[0] = mpfa_next_sym();
		mpfr_set_d(&(z->deviations[0]), radius, MPFR_RNDN);
	}
}
