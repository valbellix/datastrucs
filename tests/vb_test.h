/*
 * @file vb_test.h
 * @author Valerio Bellizia
 *
 * This file contains useful things that can be used in UT
 */

#ifndef vb_test_h
#define vb_test_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

void vb_finfoln(FILE* f, const char* format, ...) {
	va_list args;
	va_start(args, format);
	vfprintf(f, format, args);
	fprintf(f, "\n");
	va_end(args);
}

void vb_infoln(const char* format, ...) {
	va_list args;
	va_start(args, format);
	vfprintf(stdout, format, args);
	printf("\n");
	va_end(args);
}

int _vb_check_equals_int(const char* msg, const int result, const int expected) {
	vb_infoln(msg);
	if (result != expected) {
		vb_infoln("Check failed. Arguments to compare should be equals: found [%d] != expected [%d]", result, expected);
		return 0;
	}

	return 1;
}

int _vb_check_not_equals_int(const char* msg, const int result, const int not_expected) {
	vb_infoln(msg);
	if (result == not_expected) {
		vb_infoln("Check failed. Arguments to compare should be different: found [%d] == not_expected [%d]", result, not_expected);
		return 0;
	}

	return 1;
}

#define vb_check_equals_int(MSG, RES, EXP) if (!_vb_check_equals_int(MSG, RES, EXP)) return 1
#define vb_check_not_equals_int(MSG, RES, NOEXP) if (!_vb_check_not_equals(MSG, RES, NOEXP)) return 1

#endif
