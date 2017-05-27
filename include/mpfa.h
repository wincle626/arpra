/*
 * mpfa.h -- The MPFA library header file.
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

#ifndef MPFA_H
#define MPFA_H

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdio.h>
#include <gmp.h>
#include <mpfr.h>

typedef struct {
    __mpfr_struct centre;
    __mpfr_struct radius;
    __mpfr_struct u;
    __mpfr_struct *deviations;
    unsigned *symbols;
    unsigned nTerms;
} __mpfa_struct;

typedef __mpfa_struct mpfa_t[1];
typedef __mpfa_struct *mpfa_ptr;
typedef __gmp_const __mpfa_struct *mpfa_srcptr;

#ifdef __cplusplus
extern "C" {
#endif

// Initialise and clear
void mpfa_init (mpfa_ptr x);
void mpfa_init2 (mpfa_ptr x, mpfr_prec_t prec);
void mpfa_clear (mpfa_ptr x);

// Set affine form
void mpfa_set (mpfa_ptr z, mpfa_srcptr x);
void mpfa_set_d (mpfa_ptr z, const double centre, const double radius);
void mpfa_set_mpfr (mpfa_ptr z, mpfr_srcptr centre, mpfr_srcptr radius);
//void mpfa_set_str (mpfa_ptr z, const char *x, int base);

// Affine operations
void mpfa_affine_1 (mpfa_ptr z, mpfa_srcptr x, mpfr_srcptr alpha, mpfr_srcptr gamma, mpfr_srcptr delta);
void mpfa_affine_2 (mpfa_ptr z, mpfa_srcptr x, mpfa_srcptr y, mpfr_srcptr alpha, mpfr_srcptr beta, mpfr_srcptr gamma, mpfr_srcptr delta);
void mpfa_add (mpfa_ptr z, mpfa_srcptr x, mpfa_srcptr y);
void mpfa_sub (mpfa_ptr z, mpfa_srcptr x, mpfa_srcptr y);
void mpfa_neg (mpfa_ptr z, mpfa_srcptr x);
void mpfa_sum (mpfa_ptr z, const mpfa_ptr *x, unsigned long n);

// Non-affine operations
void mpfa_mul(mpfa_ptr z, mpfa_srcptr x, mpfa_srcptr y);
void mpfa_div (mpfa_ptr z, mpfa_srcptr x, mpfa_srcptr y);
void mpfa_sqrt (mpfa_ptr z, mpfa_srcptr x);
void mpfa_exp (mpfa_ptr z, mpfa_srcptr x);
void mpfa_inv (mpfa_ptr z, mpfa_srcptr x);

// Get and set precision
mpfr_prec_t mpfa_get_prec (mpfa_srcptr x);
mpfr_prec_t mpfa_get_default_prec ();
void mpfa_set_prec (mpfa_ptr x, mpfr_prec_t prec);
void mpfa_set_default_prec (mpfr_prec_t prec);

// Helper functions
int mpfa_term (mpfr_ptr z, mpfr_srcptr x, mpfr_srcptr y, mpfr_srcptr alpha, mpfr_srcptr beta, mpfr_srcptr gamma);
unsigned long mpfa_next_sym();

#ifdef __cplusplus
}
#endif

/*
 * If MPFA_TIGHT_MUL is defined, then the linear approximation to the quadratic term of
 * mpfa_mul (in mul.c) is defined the same as in (26) of:
 *
 * S. M. Rump and M. Kashiwagi, Implementation and improvements of affine arithmetic,
 * Nonlinear Theory an Its Applications, IEICE, vol. 6, no. 3, pp. 341-359, 2015.
 *
 * Otherwise it is trivially defined as the product of the radii of x and y:
 *
 * \sum^{n}_{i=1} x_{i} \sum^{n}_{i=1} y_{i}
 */

#define MPFA_TIGHT_MUL

#endif /* MPFA_H */
