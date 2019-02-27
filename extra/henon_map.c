/*
 * henon_map.c -- Test Henon map model.
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

#include <stdlib.h>
#include <stdio.h>
#include <arpra.h>

int main (int argc, char *argv[])
{
    arpra_range one, x_new, y_new;
    arpra_range a, b, x, y;
    FILE *x_out, *y_out;
    arpra_uint prec, prec_internal;
    arpra_uint n, i;

    n = 500;
    prec = 53;
    prec_internal = 256;

    arpra_set_default_precision(prec);
    arpra_set_internal_precision(prec_internal);

    // Initialise Arpra ranges
    arpra_init2(&one, 2);
    arpra_init(&x_new);
    arpra_init(&y_new);
    arpra_init(&a);
    arpra_init(&b);
    arpra_init(&x);
    arpra_init(&y);

    // Set Arpra ranges (almost chaotic)
    arpra_set_d(&one, 1.0);
    arpra_set_str(&a, "1.057", 10);
    arpra_set_str(&b, "0.3", 10);
    arpra_set_str_rad(&x, "0", "1e-5", 10);
    arpra_set_str_rad(&y, "0", "1e-5", 10);

    // Open output files
    x_out = fopen("henon_x.dat", "w");
    y_out = fopen("henon_y.dat", "w");

    // Iterate Henon map
    for (i = 0; i < n; i++) {
        if (i % 10 == 0) {
            printf("%u\n", i);
        }

        // Compute new x
        arpra_mul(&x_new, &x, &x);
        arpra_mul(&x_new, &x_new, &a);
        arpra_sub(&x_new, &one, &x_new);
        arpra_add(&x_new, &x_new, &y);

        // Compute new y
        arpra_mul(&y_new, &b, &x);

        // Update x and y
        arpra_set(&x, &x_new);
        arpra_set(&y, &y_new);

        // Write output
        mpfr_out_str(x_out, 10, 40, &(x.true_range.left), MPFR_RNDN);
        fputs(" ", x_out);
        mpfr_out_str(x_out, 10, 40, &(x.true_range.right), MPFR_RNDN);
        fputs("\n", x_out);
        mpfr_out_str(y_out, 10, 40, &(y.true_range.left), MPFR_RNDN);
        fputs(" ", y_out);
        mpfr_out_str(y_out, 10, 40, &(y.true_range.right), MPFR_RNDN);
        fputs("\n", y_out);
    }

    // Clear Arpra ranges
    arpra_clear(&one);
    arpra_clear(&x_new);
    arpra_clear(&y_new);
    arpra_clear(&a);
    arpra_clear(&b);
    arpra_clear(&x);
    arpra_clear(&y);

    // Close output files
    fclose(x_out);
    fclose(y_out);

    // Cleanup
    arpra_clear_buffers();
    mpfr_free_cache();
}