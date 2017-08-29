/*
 * mpfa2mpfi.h -- MPFA public header file for MPFI support.
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

#ifndef MPFA2MPFI_H
#define MPFA2MPFI_H

#include <mpfi.h>

#ifdef __cplusplus
extern "C" {
#endif

// Get and set MPFI intervals.
void mpfa_get_mpfi (mpfi_ptr z, mpfa_srcptr x);
void mpfa_set_mpfi (mpfa_ptr z, mpfi_srcptr x);

#ifdef __cplusplus
}
#endif

#endif // MPFA2MPFI_H
