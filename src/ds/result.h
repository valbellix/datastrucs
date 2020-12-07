/**
 * @file result.h
 * @author Valerio Bellizia
 *
 * This file contains a common definition of result.
 */

#ifndef result_h
#define result_h

typedef enum ds_result {
	SUCCESS,
	GENERIC_ERROR,
	ELEMENT_ALREADY_EXISTS,
	OUT_OF_BOUND
} ds_result;

#endif
