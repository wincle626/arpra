/*
 * set_d_rad.c -- Set centre and radius using double-precision floats.
 *
 * Copyright 2016-2018 James Paul Turner.
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

void arpra_set_d_rad (arpra_range *z, const double centre, const double radius)
{
    arpra_mpfr temp;
    arpra_prec prec_internal;

    // Handle domain violations.
    if (isnan(centre) || isnan(radius) || (radius < 0)) {
        arpra_set_nan(z);
        return;
    }
    if (isinf(centre) || isinf(radius)) {
        arpra_set_inf(z);
        return;
    }

    // Initialise vars.
    prec_internal = arpra_get_internal_precision();
    mpfr_init2(&temp, prec_internal);
    mpfr_set_prec(&(z->centre), prec_internal);
    mpfr_set_prec(&(z->radius), prec_internal);

    // MPFI set_d
    mpfi_set_d(&(z->true_range), centre);
    mpfr_sub_d(&(z->true_range.left), &(z->true_range.left), radius, MPFR_RNDD);
    mpfr_add_d(&(z->true_range.right), &(z->true_range.right), radius, MPFR_RNDU);

    // z_0 = (x_lo + x_hi) / 2
    mpfi_mid(&(z->centre), &(z->true_range));

    // rad(z) = max{(z_0 - x_lo), (x_hi - z_0)}
    mpfr_sub(&(z->radius), &(z->centre), &(z->true_range.left), MPFR_RNDU);
    mpfr_sub(&temp, &(z->true_range.right), &(z->centre), MPFR_RNDU);
    mpfr_max(&(z->radius), &(z->radius), &temp, MPFR_RNDU);

    // Clear existing deviation terms.
    arpra_helper_clear_terms(z);

    // Store nonzero rounding error term.
    if (!mpfr_zero_p(&(z->radius))) {
        z->nTerms = 1;
        z->symbols = malloc(sizeof(arpra_uint));
        z->deviations = malloc(sizeof(arpra_mpfr));
        z->symbols[0] = arpra_helper_next_symbol();
        mpfr_init2(&(z->deviations[0]), prec_internal);
        mpfr_set(&(z->deviations[0]), &(z->radius), MPFR_RNDU);
    }

    // Check for NaN and Inf.
    arpra_helper_check_result(z);

    // Clear vars.
    mpfr_clear(&temp);
}
