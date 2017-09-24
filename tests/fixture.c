/*
 * fixture.c -- Initialise and clear the test fixture.
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

mpfa_t x_A, y_A, z_A;
int test_fixture_ready = 0;
#ifdef WITH_MPFI
mpfi_t x_I, y_I, z_I, z_AI;
mpfr_t rdiam_I, rdiam_AI, rdiam_diff;
#endif // WITH_MPFI

void test_fixture_init (mpfa_prec_t prec, mpfa_prec_t prec_internal)
{
    // Ensure that we do not double-initialise.
    if (!test_fixture_ready) {
        test_fixture_ready = 1;

        // Set internal precision.
        mpfa_set_internal_prec(prec_internal);

        // Initialise MPFA variables.
        mpfa_init2(x_A, prec);
        mpfa_init2(y_A, prec);
        mpfa_init2(z_A, prec);

#ifdef WITH_MPFI
        // Initialise MPFI variables.
        mpfi_init2(x_I, prec);
        mpfi_init2(y_I, prec);
        mpfi_init2(z_I, prec);
        mpfi_init2(z_AI, prec);

        // Initialise relative diameter variables.
        mpfr_init2(rdiam_I, prec_internal);
        mpfr_init2(rdiam_AI, prec_internal);
        mpfr_init2(rdiam_diff, prec_internal);
#endif // WITH_MPFI
    }
    else {
        fprintf(stderr, "Error: test fixture is alreay initialised.\n");
        exit(EXIT_FAILURE);
    }
}

void test_fixture_clear ()
{
    // Ensure that we do not double-clear.
    if (test_fixture_ready) {
        test_fixture_ready = 0;

        // Clear MPFA variables.
        mpfa_clear(x_A);
        mpfa_clear(y_A);
        mpfa_clear(z_A);

#ifdef WITH_MPFI
        // Clear MPFI variables.
        mpfi_clear(x_I);
        mpfi_clear(y_I);
        mpfi_clear(z_I);
        mpfi_clear(z_AI);

        // Clear relative diameter variables.
        mpfr_clear(rdiam_I);
        mpfr_clear(rdiam_AI);
        mpfr_clear(rdiam_diff);
#endif // WITH_MPFI

        // All else.
        mpfr_free_cache();
    }
    else {
        fprintf(stderr, "Error: test fixture is not initialised.\n");
        exit(EXIT_FAILURE);
    }
}