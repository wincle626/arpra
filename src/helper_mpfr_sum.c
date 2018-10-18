/*
 * helper_mpfr_sum.c -- Compute the sum of n MPFR numbers.
 *
 * Copyright 2018 James Paul Turner.
 *
 * This file is part of the Arpra library.
 *
 * The Arpra library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The Arpra library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with the Arpra library. If not, see <http://www.gnu.org/licenses/>.
 */

#include "arpra-impl.h"

int arpra_helper_mpfr_sum (arpra_mpfr *z, arpra_mpfr *x,
                           const arpra_uint n, const mpfr_rnd_t rnd)
{
    arpra_mpfr **buffer_mpfr_ptr;
    arpra_uint i;

    // Save number pointers to buffer.
    buffer_mpfr_ptr = arpra_helper_buffer_mpfr_ptr(n);
    for (i = 0; i < n; i++) {
        buffer_mpfr_ptr[i] = &(x[i]);
    }

    // Sum the numbers.
    return mpfr_sum(z, buffer_mpfr_ptr, n, rnd);
}

int arpra_helper_mpfr_sumabs (arpra_mpfr *z, arpra_mpfr *x,
                              const arpra_uint n, const mpfr_rnd_t rnd)
{
    arpra_mpfr *buffer_mpfr;
    arpra_uint i;

    // Save absolute value numbers to buffer.
    buffer_mpfr = arpra_helper_buffer_mpfr(n);
    for (i = 0; i < n; i++) {
        buffer_mpfr[i] = x[i];
        buffer_mpfr[i]._mpfr_sign = 1;
    }

    // Sum the absolute value numbers.
    return arpra_helper_mpfr_sum(z, buffer_mpfr, n, rnd);
}
