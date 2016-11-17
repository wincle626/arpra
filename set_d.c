/*
 * set_d.c
 *
 *  Created on: 21 Oct 2016
 *      Author: jt273
 */

#include "mpfa.h"
#include <malloc.h>

void mpfa_set_d (mpfa_ptr z, const double x) {
	unsigned zTerm;
	for (zTerm = 0; zTerm < z->nTerms; zTerm++) {
		mpfr_clear(&(z->deviations[zTerm]));
	}
	z->nTerms = 0;
	z->symbols = realloc(z->symbols, 0);
	z->deviations = realloc(z->deviations, 0);
	mpfr_set_d(&(z->centre), x, MPFR_RNDN);
	mpfr_set_d(&(z->radius), 0.0, MPFR_RNDU);
}
