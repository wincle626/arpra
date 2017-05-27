/*
 * init2.c -- Initialise an affine form, and set its precision.
 *
 * Copyright 2016-2017 James Paul Turner.
 *
 * This file is part of the MPFA library.
 *
 * The MPFA library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The MPFA library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with the MPFA library. If not, see <http://www.gnu.org/licenses/>.
 */

#include "mpfa.h"
#include <assert.h>

void mpfa_init2 (mpfa_ptr x, mpfr_prec_t prec) {
    x->nTerms = 0;
    mpfr_init2(&(x->centre), prec);
    mpfr_init2(&(x->radius), prec);
    mpfr_init2(&(x->u), prec);

    assert(mpfr_set_si(&(x->u), -prec, MPFR_RNDN) == 0);
    assert(mpfr_exp2(&(x->u), &(x->u), MPFR_RNDN) == 0);
}
