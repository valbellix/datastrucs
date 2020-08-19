/*
 * @file common_stuff.h
 * @author Valerio Bellizia
 *
 * This file contains common definitions used while testing the library.
 */

#ifndef common_stuff_h
#define common_stuff_h

#include "vb_test.h"

#include <stdio.h>

int int_cmp(const void* e1, const void* e2) {
	const int* i1 = (int*) e1;
	const int* i2 = (int*) e2;

	if (*i1 < *i2)
		return -1;
	else if (*i1 == *i2)
		return 0;
	else
		return 1;
}

#endif

