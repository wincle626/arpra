/*
 * neg.c -- Negate an affine form.
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

void mpfa_neg (mpfa_ptr z, mpfa_srcptr x) {
	mpfr_t alpha, gamma, delta;
	mpfr_prec_t prec;

	prec = mpfr_get_prec(&(z->centre));
	mpfr_init2(alpha, prec);
	mpfr_set_si(alpha, -1, MPFR_RNDN);
	mpfr_init2(gamma, prec);
	mpfr_set_si(gamma, 0, MPFR_RNDN);
	mpfr_init2(delta, prec);
	mpfr_set_si(delta, 0, MPFR_RNDN);

	mpfa_affine_1(z, x, alpha, gamma, delta);

	mpfr_clear(alpha);
	mpfr_clear(gamma);
	mpfr_clear(delta);
}