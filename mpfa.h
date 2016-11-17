/*
 * mpfa.h
 *
 *  Created on: 21 Jul 2016
 *      Author: jt273
 */

#ifndef MPFA_H
#define MPFA_H

#include <gmp.h>
#include <mpfr.h>

typedef struct {
	__mpfr_struct centre;
	__mpfr_struct radius;
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
void mpfa_init_nterms (mpfa_ptr x, unsigned n);
void mpfa_clear (mpfa_ptr x);

// Set affine form
void mpfa_set (mpfa_ptr z, mpfa_srcptr x);
//void mpfa_set_si (mpfa_ptr z, const long x);
//void mpfa_set_ui (mpfa_ptr z, const long unsigned x);
void mpfa_set_d (mpfa_ptr z, const double x);
//void mpfa_set_fr (mpfa_ptr z, mpfr_srcptr x);
//void mpfa_set_str (mpfa_ptr z, const char *x, int base);

// Affine operations
void mpfa_affine_1 (mpfa_ptr z, mpfr_srcptr alpha, mpfa_srcptr x, mpfr_ptr gamma, mpfr_ptr delta);
void mpfa_affine_2 (mpfa_ptr z, mpfr_srcptr alpha, mpfa_srcptr x, mpfr_srcptr beta, mpfa_srcptr y, mpfr_ptr gamma, mpfr_ptr delta);
void mpfa_add (mpfa_ptr z, mpfa_srcptr x, mpfa_srcptr y);
void mpfa_sub (mpfa_ptr z, mpfa_srcptr x, mpfa_srcptr y);
void mpfa_neg (mpfa_ptr z, mpfa_srcptr x);

// Non-affine operations
void mpfa_mul (mpfa_ptr z, mpfa_srcptr x, mpfa_srcptr y);
void mpfa_div (mpfa_ptr z, mpfa_srcptr x, mpfa_srcptr y);

// Get and set precision
mp_prec_t mpfa_get_prec (mpfa_srcptr x);
void mpfa_set_prec (mpfa_ptr x, mp_prec_t p);

// Helper functions
unsigned long mpfa_next_sym();
void mpfa_term_linear_1 (mpfr_ptr z, mpfr_srcptr alpha, mpfr_srcptr x, mpfr_srcptr gamma, mpfr_ptr delta);
void mpfa_term_linear_2 (mpfr_ptr z, mpfr_srcptr alpha, mpfr_srcptr x, mpfr_srcptr beta, mpfr_srcptr y, mpfr_srcptr gamma, mpfr_ptr delta);

#ifdef __cplusplus
}
#endif

#endif /* MPFA_H */
