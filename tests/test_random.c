/*
 * test_random.c -- Functions for random test arguments.
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
#include <stdlib.h>
#include <time.h>

static gmp_randstate_t mpfa_test_randstate;
static char mpfa_test_rand_is_init = 0;

void mpfa_test_rand_init ()
{
    unsigned long int seed;
    char *environment_seed;

    if (mpfa_test_rand_is_init) {
        fprintf(stderr, "Error: test is alreay initialised.\n");
        exit(EXIT_FAILURE);
    }

    gmp_randinit_default(mpfa_test_randstate);
    mpfa_test_rand_is_init = 1;

    environment_seed = getenv("MPFA_TEST_RAND_SEED");
    if (environment_seed != NULL) {
        seed = strtoul(environment_seed, NULL, 10);
        gmp_randseed_ui(mpfa_test_randstate, seed);
        printf("Seeding with MPFA_TEST_RAND_SEED=%lu.\n", seed);
    }
    else {
#ifdef HAVE_CLOCK_GETTIME
        // Seed with clock_gettime.
        struct timespec t;
        clock_gettime(CLOCK_REALTIME, &t);
        seed = t.tv_sec + t.tv_nsec;
#else
        // Else seed with stdlib clock.
        time(&seed);
#endif
        gmp_randseed_ui(mpfa_test_randstate, seed);
        printf("Seeding with %lu.\n", seed);
    }
}

void mpfa_test_rand_clear ()
{
    if (mpfa_test_rand_is_init) {
        gmp_randclear(mpfa_test_randstate);
        mpfa_test_rand_is_init = 0;
    }
    else {
        fprintf(stderr, "Error: test is not initialised.\n");
        exit(EXIT_FAILURE);
    }
}

mpfa_uint_t mpfa_test_rand_ui (mpfa_uint_t n_bits)
{
    return gmp_urandomb_ui(mpfa_test_randstate, n_bits);
}

void mpfa_test_rand_mpfr (mpfr_ptr z)
{
    mpfa_uint_t r;

    r = mpfa_test_rand_ui (3);

    if (r < 1) {
        // P(z == +oo) = 1/8
        mpfr_set_inf (z, +1);
        return;
    }
    else if (r < 2) {
        // P(z == -oo) = 1/8
        mpfr_set_inf (z, -1);
        return;
    }

    mpfr_urandomb (z, mpfa_test_randstate);

    if (r < 3) {
        // P(0 <= z < +1) = 1/8
        return;
    }
    else if (r < 4) {
        // P(-1 < z <= 0) = 1/8
        mpfr_neg (z, z, MPFI_RNDD);
        return;
    }

    mpfr_ui_div (z, 1, z, MPFI_RNDD);

    if (r < 6) {
        // P(+1 < z <= +oo) = 1/4
        return;
    }
    else {
        // P(-oo <= z < -1) = 1/4
        mpfr_neg (z, z, MPFI_RNDD);
        return;
    }
}