/*
 * bivariate_mpfi.c -- Test bivariate MPFA function against MPFI function.
 *
 * Copyright 2017 James Paul Turner.
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

#include "mpfa-test.h"

int test_bivariate_mpfi (
    void (*f_MPFA) (mpfa_ptr z, mpfa_srcptr x, mpfa_srcptr y),
    int  (*f_MPFI) (mpfi_ptr z, mpfi_srcptr x, mpfi_srcptr y))
{
    int fail = 0;

    // Convert arguments.
    mpfa_get_mpfi(x_I, x_A);
    mpfa_get_mpfi(y_I, y_A);
    test_log_mpfi(x_I, "x  ");
    test_log_mpfi(y_I, "y  ");

    // Compute z with MPFI.
    f_MPFI(z_I, x_I, y_I);
    test_log_mpfi(z_I, "z_I");

    // Compute z with MPFA (unshared symbols).
    f_MPFA(z_A, x_A, y_A);
    mpfa_get_mpfi(z_AI, z_A);
    test_log_mpfi(z_AI, "z_A");

    // Compute relative diameter difference.
    mpfi_diam_rel(rdiam_I, z_I);
    mpfi_diam_rel(rdiam_AI, z_AI);
    mpfr_sub(rdiam_diff, rdiam_I, rdiam_AI, MPFR_RNDN);
    test_log_mpfr(rdiam_diff, "z_D");

    // Log unshared symbol result.
    test_log_printf("Result (unshared symbol): ");
    if (mpfi_bounded_p(z_I) != mpfi_bounded_p(z_AI)) {
        test_log_printf("FAIL\n");
        fail = 1;
    }
    else if ((mpfr_cmp(&(z_I->left), &(z_AI->left)) < 0)
             || (mpfr_cmp(&(z_I->right), &(z_AI->right)) > 0)) {
        test_log_printf("FAIL\n");
        fail = 1;
    }
    else {
        test_log_printf("PASS\n");
    }

    // Compute z with MPFA (randomly shared symbols).
    test_share_rand_syms(x_A, y_A);
    f_MPFA(z_A, x_A, y_A);
    mpfa_get_mpfi(z_AI, z_A);
    test_log_mpfi(z_AI, "z_A");

    // Compute relative diameter difference.
    mpfi_diam_rel(rdiam_I, z_I);
    mpfi_diam_rel(rdiam_AI, z_AI);
    mpfr_sub(rdiam_diff, rdiam_I, rdiam_AI, MPFR_RNDN);
    test_log_mpfr(rdiam_diff, "z_D");

    // Log randomly shared symbol result.
    test_log_printf("Result (randomly shared symbol): ");
    if (mpfi_bounded_p(z_I) == mpfi_bounded_p(z_AI)) {
        test_log_printf("PASS\n");
    }
    else {
        test_log_printf("FAIL\n");
        fail = 1;
    }

    // Compute z with MPFA (all shared symbols).
    test_share_all_syms(x_A, y_A);
    f_MPFA(z_A, x_A, y_A);
    mpfa_get_mpfi(z_AI, z_A);
    test_log_mpfi(z_AI, "z_A");

    // Compute relative diameter difference.
    mpfi_diam_rel(rdiam_I, z_I);
    mpfi_diam_rel(rdiam_AI, z_AI);
    mpfr_sub(rdiam_diff, rdiam_I, rdiam_AI, MPFR_RNDN);
    test_log_mpfr(rdiam_diff, "z_D");

    // Log all shared symbol result.
    test_log_printf("Result (all shared symbol): ");
    if (mpfi_bounded_p(z_I) == mpfi_bounded_p(z_AI)) {
        test_log_printf("PASS\n");
    }
    else {
        test_log_printf("FAIL\n");
        fail = 1;
    }

    test_log_printf("\n");
    return fail;
}